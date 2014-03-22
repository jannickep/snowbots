//======================================================================
/*! \file IbeoSdkEcuLiveDemo.cpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date Jun 1, 2012
 *
 * Demo project for connecting to an LUX and process the received
 * data blocks.
 *///-------------------------------------------------------------------

#include <ibeosdk/lux.hpp>

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

void live_demo(LogFileManager& logFileManager, std::string ip);

//======================================================================

TimeConversion tc;

//======================================================================

class AllLuxListener : public ibeo::ScanLuxListener,
                       public ibeo::ObjectListLuxListener,
                       public ibeo::VehicleStateBasicLuxListener,
                       public ibeo::LogMessageErrorListener,
                       public ibeo::LogMessageDebugListener,
                       public ibeo::LogMessageNoteListener,
                       public ibeo::LogMessageWarningListener {
public:
	//========================================
	void onData(const ScanLux* const scan)
	{
		logInfo << "Scan received: # " << scan->getScanNumber()
			<<"  time: " << tc.toString(scan->getStartTimestamp().toPtime(), 3)
			<< std::endl;
	}

	//========================================
	void onData(const ObjectListLux* const pObj)
	{
		logInfo << "Objects received: # " << pObj->getNumberOfObjects() << std::endl;
	}

	//========================================
	void onData(const VehicleStateBasicLux* const vsb)
	{
		TimeConversion tc;
		logInfo << "VSB for Scan #: " << vsb->getScanNumber() << "  "
				<< tc.toString(vsb->getTimestamp().toPtime()) << std::endl;
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
}; // AllLuxListener


//============================================================================
//============================================================================
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

void live_demo(LogFileManager& logFileManager, std::string ip)
{
	AllLuxListener allLuxListener;

	const size_t portPos = ip.find(':');
	uint16_t port = 12002;
	if (portPos != std::string::npos) {
		std::string portStr = ip.substr(portPos+1);
		std::stringstream ss;
		ss.str(portStr);
		ss >> port;
		ip = ip.substr(0, portPos);
	}

	IbeoLux lux(ip, port);
	lux.setLogFileManager(&logFileManager);

	lux.registerListener(dynamic_cast<ScanLuxListener*>(&allLuxListener));
	lux.registerListener(dynamic_cast<ObjectListLuxListener*>(&allLuxListener));
	lux.registerListener(dynamic_cast<VehicleStateBasicLuxListener*>(&allLuxListener));
	lux.registerListener(dynamic_cast<LogMessageErrorListener*>(&allLuxListener));
	lux.registerListener(dynamic_cast<LogMessageDebugListener*>(&allLuxListener));
	lux.registerListener(dynamic_cast<LogMessageNoteListener*>(&allLuxListener));
	lux.registerListener(dynamic_cast<LogMessageWarningListener*>(&allLuxListener));

	lux.getConnected();

	// Just to keep the program alive
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

//============================================================================
