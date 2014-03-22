//======================================================================
/*! \file IbeoSdkDataLoggerrDemo.cpp
 *
 * \copydoc Copyright
 * \author Jan Christian Dittmer (jcd)
 * \date Jul 21, 2012
 *
 * Demo project for data logging. This tool is connecting
 * with a LUX sensor and saves the data into an IDC file.
 * This is basically an IbeoSdkWriterDemo with more elaborated
 * disk management.
 *///-------------------------------------------------------------------

#include <ibeosdk/lux.hpp>
#include <ibeosdk/IdcFile.hpp>

#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/vfs.h>

//======================================================================

using namespace ibeo;

//======================================================================

const ibeo::Version::MajorVersion majorVersion(2);
const ibeo::Version::MinorVersion minorVersion(0);
const ibeo::Version::Revision revision(2);
const ibeo::Version::PatchLevel patchLevel(0);
const ibeo::Version::Build build(-1);
const std::string info = "Demo";

ibeo::Version appVersion(majorVersion, minorVersion, revision, patchLevel, build, info);
IbeoSDK ibeoSDK;

//======================================================================

class IdcWriter : ibeo::IdcFile,
                  public ibeo::DataStreamer,
                  public ibeo::SplitFile {
public:
	IdcWriter(const std::string filename,
	          IbeoLux* lux,
	          LogFileManager& logFileManager,
	          const off_t fileSizeLimit,
	          const double memoryConsumptionLimit);

	virtual ~IdcWriter();

private:
	IdcWriter(const IdcWriter&); // forbidden
	IdcWriter& operator=(const IdcWriter&); // forbidden

public:
	virtual bool create(const std::string& filename, const bool append = false);
	virtual void onData(const IbeoDataHeader& dh, const char* const bodyBuf);
	virtual void split(const int fileIndex);

	void checkDiskSpace(const std::string& devPath, unsigned long& diskSize, unsigned long& totalFreeBytes);
	bool isMemoryConsumed() const { return m_isMemoryConsumed; }

protected:
	std::string getFileName(const int fileIndex) const;
	void splitFileIfNeeded();

protected:
	LogFileManager& logFileManager;
	std::string filenameTemplate;
	std::string currentFileName;
	off_t currentFileSize;
	const off_t fileSizeLimit;

	const double memoryConsumptionLimit;
	bool m_isMemoryConsumed;
}; // IDCWriter

//======================================================================
//======================================================================
//======================================================================



//======================================================================
//======================================================================
//======================================================================

IdcWriter::IdcWriter(const std::string filename,
                     IbeoLux* lux,
                     LogFileManager& logFileManager,
                     const off_t fileSizeLimit,
                     const double memoryConsumptionLimit)
  : IdcFile(),
    logFileManager(logFileManager),
    filenameTemplate(filename),
    currentFileName(),
    currentFileSize(0),
    fileSizeLimit(fileSizeLimit),
    memoryConsumptionLimit(memoryConsumptionLimit)
{
	int len = filenameTemplate.length();
	if (len > 4) {
		if (filenameTemplate.substr(len-4)==".idc") {
			filenameTemplate = filenameTemplate.substr(0, len-4);
		}
	}

	const int idx = this->logFileManager.registerSplitFile(this);
	this->create(this->getFileName(idx), false);

	if (lux && this->isOpen()) {
		lux->registerStreamer(this);
	}
}

//======================================================================

IdcWriter::~IdcWriter()
{
	this->logFileManager.unregisterSplitFile(this);
}

//======================================================================

void IdcWriter::checkDiskSpace(const std::string& devPath, unsigned long& diskSize, unsigned long& totalFreeBytes)
{
	struct statfs fs;

	if( ( statfs( devPath.c_str(), &fs ) ) < 0 ) {
		printf( "Failed to stat %s: %s\n", devPath.c_str() ,strerror( errno ) );
	}
	else {
		diskSize = fs.f_blocks * fs.f_bsize;
		totalFreeBytes = fs.f_bfree * fs.f_bsize;
	}
}

//======================================================================

bool IdcWriter::create(const std::string& filename, const bool append)
{
	char tempPath[200];
	getcwd(tempPath,200);
	std::string absPath(tempPath);
	const unsigned position = absPath.find("/",1);
	absPath = absPath.substr(0,position);
	bool result = false;

	unsigned long diskSize;
	unsigned long totalFreeBytes;
	this->checkDiskSpace(absPath, diskSize, totalFreeBytes);

	logInfo << "Main path of the executable file: " << absPath << std::endl;
	logInfo << "Disc size: " << diskSize << " Byte" << std::endl;
	logInfo << "Free size: " << totalFreeBytes << " Byte\n" << std::endl;

	const double actualMemConsumptionPercent = 100.0 - ((double)totalFreeBytes*100)/(double)diskSize;
	if (memoryConsumptionLimit < actualMemConsumptionPercent) {
		m_isMemoryConsumed = true;
		this->close();
		result = false;
	}
	else {
		m_isMemoryConsumed = false;
		result = IdcFile::create(filename, append);
	}

	logInfo << "Current memory consumption in percent: " << actualMemConsumptionPercent << "%" << std::endl;
	logInfo << "Memory consumption limit: " << memoryConsumptionLimit << std::endl;
	logInfo << "isMemoryConsumed: " << m_isMemoryConsumed << "\n" << std::endl;

	if (result) {
		logInfo << "Successfully open IDC file '" << filename << "'." << std::endl;
	}
	else {
		logError << "Failed to open IDC file '" << filename << "'." << std::endl;
	}
	return result;
}

//======================================================================

void IdcWriter::onData(const IbeoDataHeader& dh, const char* const bodyBuf)
{
	logDebug << "Received message 0x" << std::hex << dh.getDataType() << std::dec << std::endl;
	switch (dh.getDataType()) {
	case DataType_LuxScan:
		this->splitFileIfNeeded();
		break;
	default:
		break;
	}

	dh.serialize(this->m_strm);
	const uint32_t sz = dh.getMessageSize();
	this->currentFileSize += sz;
	this->write(bodyBuf, sz);
	logDebug << "Total file size: " << this->currentFileSize << std::endl;
}

//======================================================================

std::string IdcWriter::getFileName(const int fileIndex) const
{
	std::stringstream ss;
	ss << filenameTemplate;
	ss << "_" << std::setfill('0') << std::setw(4) << fileIndex;
	ss << ".idc";
	return ss.str();
}

//======================================================================

void IdcWriter::split(const int fileIndex)
{
	this->m_strm.flush();
	this->create(this->getFileName(fileIndex), false);
	currentFileSize = 0;
}

//======================================================================

void IdcWriter::splitFileIfNeeded()
{
	if (currentFileSize >= fileSizeLimit) {
		this->logFileManager.splitRequest();
	}
}

//======================================================================
//======================================================================
//======================================================================











//======================================================================
//======================================================================
//======================================================================


void idcwriter_demo(LogFileManager& logFileManager,
                    const std::string& ip,
                    const std::string& outFilename,
                    const std::string& fileSize,
                    const std::string& memoryConsumptionLimit);


//======================================================================

int main(const int argc, const char** argv)
{
	std::cerr << argv[0] << " Version " << appVersion.toString();
	std::cerr << "  using IbeoSDK " << ibeoSDK.getVersion().toString() << std::endl;

	if (argc<5) {
		std::cerr << "A sensor IP address and output filename needed as arguments." << std::endl;
		exit(1);
	}

	const std::string ip = argv[1];
	const std::string outFilename = argv[2];
	const std::string fileSize = argv[3];
	const std::string memoryConsumpionLimit = argv[4];

	LogFileManager logFileManager;
	ibeo::LogFile::setTargetFileSize(atoi(fileSize.c_str()));

	const bool hasLogFile = argc>5;

	if (hasLogFile) {
		ibeo::LogFile::setLogFileBaseName(argv[5]);
		ibeo::LogFile::setTargetFileSize(atoi(fileSize.c_str()));
	}
	const ibeo::LogLevel ll = ibeo::logLevelFromString("Debug");
	ibeo::LogFile::setLogLevel(ll);

	logFileManager.start();

	if (hasLogFile) {
		logInfo << argv[0] << " Version " << appVersion.toString()
		        << "  using IbeoSDK " << ibeoSDK.getVersion().toString() << std::endl;
	}

	idcwriter_demo(logFileManager, ip, outFilename, fileSize, memoryConsumpionLimit);

	exit(0);
}

//======================================================================

void idcwriter_demo(LogFileManager& logFileManager,
                    const std::string& ip,
                    const std::string& outFilename,
                    const std::string& fileSize,
                    const std::string& memoryConsumptionLimit)
{
	IbeoLux lux(ip);
	lux.setLogFileManager(&logFileManager);
	IdcWriter idcWriter(outFilename, &lux, logFileManager, atoi(fileSize.c_str()), strtod(memoryConsumptionLimit.c_str(),NULL));
	lux.getConnected();

	while (true) {
		if (!lux.isConnected() || idcWriter.isMemoryConsumed())
			return;
#		ifdef _WIN32
			::Sleep(1);
#		else // _WIN32
			sleep(1);
#		endif // _WIN32
	}
}

//======================================================================

