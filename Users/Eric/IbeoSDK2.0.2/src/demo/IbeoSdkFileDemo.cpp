//======================================================================
/*! \file IbeoSdkFileDemo.cpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date Jun 1, 2012
 *
 * Demo project for reading IDC files and process the data blocks.
 *///-------------------------------------------------------------------

#include <ibeosdk/lux.hpp>
#include <ibeosdk/ecu.hpp>
#include <ibeosdk/IdcFile.hpp>

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
const std::string info = "IbeoSdkFileDemo";

ibeo::Version appVersion(majorVersion, minorVersion, revision, patchLevel, build, info);

IbeoSDK ibeoSDK;

//======================================================================

void file_demo(const std::string& filename);

//======================================================================

TimeConversion tc;

//======================================================================

class MyLuxScanListener : public ibeo::ScanLuxListener {
public:
	void onData(const ScanLux* const scan)
	{
		logInfo << std::setw(5) << scan->getSerializedSize() << "Bytes  "
				<< "ScanLux received: # " << scan->getScanNumber()
				<< "  ScanStart: " << tc.toString(scan->getStartTimestamp().toPtime())
				<< std::endl;
	}
}; // MyLuxScanListener

//======================================================================

class MyEcuScanListener : public ibeo::ScanEcuListener {
public:
	void onData(const ScanEcu* const scan)
	{
		logInfo << std::setw(5) << scan->getSerializedSize() << "Bytes  "
				<< "ScanEcu received: # " << scan->getScanNumber()
				<< "  #Pts: " << scan->getNumberOfScanPoints()
				<< "  ScanStart: " << tc.toString(scan->getStartTimestamp().toPtime(), 3)
				<< std::endl;
	}
}; // MyEcuScanListener

//======================================================================

class MyLuxObjectListener : public ibeo::ObjectListLuxListener {
public:
	void onData(const ObjectListLux* const objList)
	{
		logInfo << std::setw(5) << objList->getSerializedSize() << "Bytes  " << "ObjectListLux received: # " << objList->getNumberOfObjects() << std::endl;
	}
}; // MyLuxObjectListener

//======================================================================

class MyEcuObjectListener : public ibeo::ObjectListEcuListener {
public:
	void onData(const ObjectListEcu* const objList)
	{
		logInfo << std::setw(5) << objList->getSerializedSize() << "Bytes  " << "ObjectListEcu received: # " << objList->getNumberOfObjects() << std::endl;
	}
}; // MyEcuObjectListener

//======================================================================

class MyObjectListEcuEtListener : public ibeo::ObjectListEcuEtListener {
public:
	void onData(const ObjectListEcuEt* const objList)
	{
		logInfo << std::setw(5) << objList->getSerializedSize() << "Bytes  " << "ObjectListEcUEts received: # " << objList->getNbOfObjects() << std::endl;
	}
}; // MyObjectListEcuEtListener

//======================================================================

class MyImageListener : public ibeo::ImageListener {
public:
	void onData(const Image* const image)
	{
		logInfo << std::setw(5) << image->getSerializedSize() << "Bytes  " << "Image received: time: " << tc.toString(image->getTimestamp().toPtime()) << std::endl;
	}
}; // MyVehicleStateBasicLuxListener

//======================================================================

class MyVehicleStateBasicLuxListener : public ibeo::VehicleStateBasicLuxListener {
public:
	void onData(const VehicleStateBasicLux* const vsb)
	{
		logInfo << std::setw(5) << vsb->getSerializedSize() << "Bytes  " << "VSB (LUX) received: time: " << tc.toString(vsb->getTimestamp().toPtime()) << std::endl;
	}
}; // MyVehicleStateBasicLuxListener

//======================================================================

class MyVehicleStateBasicEcuListener : public ibeo::VehicleStateBasicEcuListener {
public:
	void onData(const VehicleStateBasicEcu* const vsb)
	{
		logInfo << std::setw(5) << vsb->getSerializedSize() << "Bytes  "
				<< "VSB (ECU) received: time: " << tc.toString(vsb->getTimestamp().toPtime())
				<< std::endl;
	}
}; // MyVehicleStateBasicEcuListener

//======================================================================

class MyLogMessageErrorListener : public ibeo::LogMessageErrorListener {
public:
	void onData(const LogMessageError* const logMsg)
	{
		logInfo << std::setw(5) << logMsg->getSerializedSize() << "Bytes  "
				<< "LogMessage (Error) received: time: " << logMsg->getTraceLevel() << ": " << logMsg->getMessage() << std::endl;
	}
}; // MyLogMessageErrorListener

//======================================================================

class MyLogMessageWarningListener : public ibeo::LogMessageWarningListener {
public:
	void onData(const LogMessageWarning* const logMsg)
	{
		logInfo << std::setw(5) << logMsg->getSerializedSize() << "Bytes  "
				<< "LogMessage (Warning) received: time: " << logMsg->getTraceLevel() << ": " << logMsg->getMessage() << std::endl;
	}
}; // MyLogMessageWarningListener

//======================================================================

class MyLogMessageNoteListener : public ibeo::LogMessageNoteListener {
public:
	void onData(const LogMessageNote* const logMsg)
	{
		logInfo << std::setw(5) << logMsg->getSerializedSize() << "Bytes  "
				<< "LogMessage (Note) received: time: " << logMsg->getTraceLevel() << ": " << logMsg->getMessage() << std::endl;
	}
}; // MyLogMessageNoteListener

//======================================================================

class MyLogMessageDebugListener : public ibeo::LogMessageDebugListener {
public:
	void onData(const LogMessageDebug* const logMsg)
	{
		logInfo << std::setw(5) << logMsg->getSerializedSize() << "Bytes  "
				<< "LogMessage (Debug) received: time: " << logMsg->getTraceLevel() << ": " << logMsg->getMessage() << std::endl;
	}
}; // MyLogMessageDebugListener

//============================================================================

int main(const int argc, const char** argv)
{
	std::cerr << argv[0] << " Version " << appVersion.toString();
	std::cerr << "  using IbeoSDK " << ibeoSDK.getVersion().toString() << std::endl;
	if (argc==1) {
		std::cerr << "A IDC filename is needed as argument." << std::endl;
		exit(1);
	}

	std::string filename = argv[1];

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

	file_demo(filename);

	exit(0);
}

//============================================================================

void file_demo(const std::string& filename)
{
	IdcFile file;
	file.open(filename);
	if (file.isOpen()) {

		MyLuxScanListener myLuxScanListener;
		MyLuxObjectListener myLuxObjectListener;
		MyEcuScanListener myEcuScanListener;
		MyEcuObjectListener myEcuObjectListener;
		MyVehicleStateBasicLuxListener myVehicleStateBasicLuxListener;
		MyImageListener myImageListener;
		MyObjectListEcuEtListener myObjectListEcuEtListener;
		MyVehicleStateBasicEcuListener myVehicleStateBasicEcuListener;
		MyLogMessageErrorListener myLogMessageErrorListener;
		MyLogMessageWarningListener myLogMessageWarningListener;
		MyLogMessageNoteListener myLogMessageNoteListener;
		MyLogMessageDebugListener myLogMessageDebugListener;

		const DataBlock* db = NULL;
		unsigned short nbMessages = 0; // # of messages we parsed

		while (file.isGood()) {
			db = file.getNextDataBlock();
			if (db == 0) {
				continue; // might be eof or unknown file type
			}
//			logDebug << "Data block type: 0x" << std::hex << db->getDataType() << std::dec << std::endl;
			switch (db->getDataType()) {
			case DataType_LuxScan:
//				logDebug << "LUX scan data block read" << std::endl;
				myLuxScanListener.onData(dynamic_cast<const ScanLux*>(db));
				break;
			case DataType_LuxObjectList:
//				logDebug << "LUX object data block read" << std::endl;
				myLuxObjectListener.onData(dynamic_cast<const ObjectListLux*>(db));
				break;
			case DataType_EcuScan:
//				logDebug << "ECU scan data block read" << std::endl;
				myEcuScanListener.onData(dynamic_cast<const ScanEcu*>(db));
				break;
			case DataType_EcuObjectList:
//				logDebug << "ECU object data block read" << std::endl;
				myEcuObjectListener.onData(dynamic_cast<const ObjectListEcu*>(db));
				break;
			case DataType_EcuObjectListET:
				myObjectListEcuEtListener.onData(dynamic_cast<const ObjectListEcuEt*>(db));
				break;
			case DataType_Image:
				myImageListener.onData(dynamic_cast<const Image*>(db));
				break;
			case DataType_LuxVehicleStateBasic:
//				logDebug << "LUX vehicle state basic data block read" << std::endl;
				myVehicleStateBasicLuxListener.onData(dynamic_cast<const VehicleStateBasicLux*>(db));
				break;
			case DataType_EcuVehicleStateBasic:
				myVehicleStateBasicEcuListener.onData(dynamic_cast<const VehicleStateBasicEcu*>(db));
				break;
			case DataType_LogError:
				myLogMessageErrorListener.onData(dynamic_cast<const LogMessageError*>(db));
				break;
			case DataType_LogWarning:
				myLogMessageWarningListener.onData(dynamic_cast<const LogMessageWarning*>(db));
				break;
			case DataType_LogNote:
				myLogMessageNoteListener.onData(dynamic_cast<const LogMessageNote*>(db));
				break;
			case DataType_LogDebug:
				myLogMessageDebugListener.onData(dynamic_cast<const LogMessageDebug*>(db));
				break;
			default:
				logWarning << "Unhandled message type: 0x" << std::hex << db->getDataType() << std::endl;
				break;
			}

			++nbMessages;
		}

		logDebug << "EOF reached. " << nbMessages << " known blocks found." << std::endl;

	}
	else {
		logError << "File not readable." << std::endl;
	}
}

//============================================================================
