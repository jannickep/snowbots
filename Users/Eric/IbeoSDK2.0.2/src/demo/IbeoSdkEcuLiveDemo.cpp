//======================================================================
/*! \file IbeoSdkEcuLiveDemo.cpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date Jun 1, 2012
 *
 * Demo project for connecting to an ECU and process the received
 * data blocks.
 *///-------------------------------------------------------------------

#include <ibeosdk/ecu.hpp>

#include <iostream>
#include <cstdlib>

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

void live_demo(LogFileManager& logFileManager, const std::string ip);

//======================================================================

TimeConversion tc;

//======================================================================

class AllEcuListener : public ibeo::ScanEcuListener,
                       public ibeo::ObjectListEcuListener,
                       public ibeo::ObjectListEcuEtListener,
                       public ibeo::VehicleStateBasicEcuListener,
                       public ibeo::ImageListener,
                       public ibeo::LogMessageErrorListener,
                       public ibeo::LogMessageDebugListener,
                       public ibeo::LogMessageNoteListener,
                       public ibeo::LogMessageWarningListener {
public:
	//========================================
	virtual void onData(const ScanEcu* const scan)
	{
		logInfo << "Scan received: # " << scan->getScanNumber()
			<<"  time: " << tc.toString(scan->getStartTimestamp().toPtime(), 3)
			<< std::endl;
	}

	//========================================
	virtual void onData(const ObjectListEcu* const objectList)
	{
		logInfo << "Objects received: # " << objectList->getNumberOfObjects() << std::endl;
	}

	//========================================
	virtual void onData(const ObjectListEcuEt* const objectList)
	{
		logInfo << "ET Objects received: # " << objectList->getNbOfObjects() << std::endl;
	}

	//========================================
	virtual void onData(const VehicleStateBasicEcu* const vsb)
	{
		TimeConversion tc;
		logInfo << "VSB " << tc.toString(vsb->getTimestamp().toPtime(), 3) << std::endl;
	}

	//========================================
	virtual void onData(const Image* const image)
	{
		logInfo << std::setw(5) << image->getSerializedSize() << "Bytes  " << "Image received: time: " << tc.toString(image->getTimestamp().toPtime()) << std::endl;
	}

	//========================================
	virtual void onData(const LogMessageError* const logMsg)
	{
		logInfo << std::setw(5) << logMsg->getSerializedSize() << "Bytes  "
				<< "LogMessage (Error) received: time: " << logMsg->getTraceLevel() << ": " << logMsg->getMessage() << std::endl;
	}

	//========================================
	virtual void onData(const LogMessageWarning* const logMsg)
	{
		logInfo << std::setw(5) << logMsg->getSerializedSize() << "Bytes  "
				<< "LogMessage (Warning) received: time: " << logMsg->getTraceLevel() << ": " << logMsg->getMessage() << std::endl;
	}

	//========================================
	virtual void onData(const LogMessageNote* const logMsg)
	{
		logInfo << std::setw(5) << logMsg->getSerializedSize() << "Bytes  "
				<< "LogMessage (Note) received: time: " << logMsg->getTraceLevel() << ": " << logMsg->getMessage() << std::endl;
	}

	//========================================
	virtual void onData(const LogMessageDebug* const logMsg)
	{
		logInfo << std::setw(5) << logMsg->getSerializedSize() << "Bytes  "
				<< "LogMessage (Debug) received: time: " << logMsg->getTraceLevel() << ": " << logMsg->getMessage() << std::endl;
	}
}; // AllEcuListener

//============================================================================

int main(const int argc, const char** argv)
{
	std::cerr << argv[0] << " Version " << appVersion.toString();
	std::cerr << "  using IbeoSDK " << ibeoSDK.getVersion().toString() << std::endl;

	if (argc==1) {
		std::cerr << "A sensor IP address needed as argument." << std::endl;
		exit(1);
	}

	std::string ip = argv[1];

	LogFileManager logFileManager;
	ibeo::LogFile::setTargetFileSize(10000);

	const bool hasLogFile = argc>2;

	if (hasLogFile) {
		ibeo::LogFile::setLogFileBaseName(argv[2]);
		ibeo::LogFile::setTargetFileSize(10000);
	}
	const ibeo::LogLevel ll = ibeo::logLevelFromString("Debug");
	ibeo::LogFile::setLogLevel(ll);

	logFileManager.start();

	if (hasLogFile) {
		logInfo << argv[0] << " Version " << appVersion.toString()
		        << "  using IbeoSDK " << ibeoSDK.getVersion().toString() << std::endl;
	}


	live_demo(logFileManager, ip);

	exit(0);
}

//============================================================================

void live_demo(LogFileManager& logFileManager, const std::string ip)
{
	AllEcuListener allEcuListener;
	IbeoEcu ecu(ip);
	ecu.setLogFileManager(&logFileManager);

	ecu.registerListener(dynamic_cast<ScanEcuListener*>(&allEcuListener));
	ecu.registerListener(dynamic_cast<ObjectListEcuListener*>(&allEcuListener));
	ecu.registerListener(dynamic_cast<ObjectListEcuEtListener*>(&allEcuListener));
	ecu.registerListener(dynamic_cast<VehicleStateBasicEcuListener*>(&allEcuListener));
	ecu.registerListener(dynamic_cast<ImageListener*>(&allEcuListener));
	ecu.registerListener(dynamic_cast<LogMessageErrorListener*>(&allEcuListener));
	ecu.registerListener(dynamic_cast<LogMessageDebugListener*>(&allEcuListener));
	ecu.registerListener(dynamic_cast<LogMessageNoteListener*>(&allEcuListener));
	ecu.registerListener(dynamic_cast<LogMessageWarningListener*>(&allEcuListener));

	ecu.getConnected();

	// Just to keep the program alive
	while (true) {
		if (!ecu.isConnected())
			return;
#		ifdef _WIN32
			::Sleep(1);
#		else // _WIN32
			sleep(1);
#		endif // _WIN32
	}
}

//============================================================================
