//======================================================================
/*! \file IbeoSdkWriterDemo.cpp
 *
 * \copydoc Copyright
 * \author Jan Christian Dittmer (jcd)
 * \date Jul 21, 2012
 *
 * Demo project connecting to an LUX and writing the received data
 * blocks to an IDC file.
 *///-------------------------------------------------------------------

#include <ibeosdk/lux.hpp>
#include <ibeosdk/IdcFile.hpp>

#include <sstream>
#include <iomanip>

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
	          const off_t fileSizeLimit);

	virtual ~IdcWriter();

private:
	IdcWriter(const IdcWriter&); // forbidden
	IdcWriter& operator=(const IdcWriter&); // forbidden

public:
	virtual bool create(const std::string& filename, const bool append = false);

	virtual void onData(const IbeoDataHeader& dh, const char* const bodyBuf);
	virtual void split(const int fileIndex);

protected:
	std::string getFileName(const int fileIndex) const;
	void splitFileIfNeeded();

protected:
	LogFileManager& logFileManager;
	std::string filenameTemplate;
	std::string currentFileName;
	off_t currentFileSize;
	const off_t fileSizeLimit;
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
                     const off_t fileSizeLimit)
  : IdcFile(),
    logFileManager(logFileManager),
    filenameTemplate(filename),
    currentFileName(),
    currentFileSize(0),
    fileSizeLimit(fileSizeLimit)
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

bool IdcWriter::create(const std::string& filename, const bool append)
{
	const bool result = IdcFile::create(filename, append);

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
                    const std::string& outFilename);


//======================================================================

int main(const int argc, const char** argv)
{
	std::cerr << argv[0] << " Version " << appVersion.toString();
	std::cerr << "  using IbeoSDK " << ibeoSDK.getVersion().toString() << std::endl;

	if (argc<3) {
		std::cerr << "A sensor IP address and output filename needed as arguments." << std::endl;
		exit(1);
	}

	const std::string ip = argv[1];
	const std::string outFilename = argv[2];

	LogFileManager logFileManager;
	ibeo::LogFile::setTargetFileSize(1000000);

	const bool hasLogFile = argc>3;

	if (hasLogFile) {
		ibeo::LogFile::setLogFileBaseName(argv[3]);
		ibeo::LogFile::setTargetFileSize(1000000);
	}
	const ibeo::LogLevel ll = ibeo::logLevelFromString("Debug");
	ibeo::LogFile::setLogLevel(ll);

	logFileManager.start();

	if (hasLogFile) {
		logInfo << argv[0] << " Version " << appVersion.toString()
		        << "  using IbeoSDK " << ibeoSDK.getVersion().toString() << std::endl;
	}

	idcwriter_demo(logFileManager, ip, outFilename);

	exit(0);
}

//======================================================================

void idcwriter_demo(LogFileManager& logFileManager,
                    const std::string& ip,
                    const std::string& outFilename)
{
	IbeoLux lux(ip);
	lux.setLogFileManager(&logFileManager);
	IdcWriter idcWriter(outFilename, &lux, logFileManager, 10000000);
	lux.getConnected();

	while (true) {
		if (!lux.isConnected())
			return;
#		ifdef _WIN32
			::Sleep(1);
#		else // _WIN32
			sleep(1);
#		endif // _WIN32
	}
}

//======================================================================

