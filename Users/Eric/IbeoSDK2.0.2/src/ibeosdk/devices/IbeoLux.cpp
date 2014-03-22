//======================================================================
/*! \file IbeoLux.cpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date Apr 24, 2012
 *///-------------------------------------------------------------------

#include <ibeosdk/devices/IbeoLux.hpp>

#include <ibeosdk/datablocks/ScanLux.hpp>
#include <ibeosdk/datablocks/ObjectListLux.hpp>
#include <ibeosdk/datablocks/VehicleStateBasicLux.hpp>
#include <ibeosdk/datablocks/LogMessageDebug.hpp>
#include <ibeosdk/datablocks/LogMessageError.hpp>
#include <ibeosdk/datablocks/LogMessageNote.hpp>
#include <ibeosdk/datablocks/LogMessageWarning.hpp>

//======================================================================

namespace ibeo {

//======================================================================

IbeoLux::IbeoLux(const std::string& ip, const unsigned short port)
  : IbeoScanner(ip, port),
    m_scan(new ScanLux),
    m_obj(new ObjectListLux),
    m_vsb(new VehicleStateBasicLux),
    m_logMsgError(new LogMessageError),
    m_logMsgWarning(new LogMessageWarning),
    m_logMsgNote(new LogMessageNote),
    m_logMsgDebug(new LogMessageDebug)
{}

//======================================================================

IbeoLux::~IbeoLux()
{
	delete m_logMsgDebug;
	delete m_logMsgNote;
	delete m_logMsgWarning;
	delete m_logMsgError;
	delete m_vsb;
	delete m_obj;
	delete m_scan;
}

//======================================================================

const DataBlock* IbeoLux::onData(const IbeoDataHeader& dh, std::istream& is)
{
	switch (dh.getDataType()) {
	case DataType_LuxScan:
		if (const DataBlock* db = deserialize(is, *m_scan, dh))          return db;
		break;
	case DataType_LuxObjectList:
		if (const DataBlock* db = deserialize(is, *m_obj, dh))           return db;
		break;
	case DataType_LuxVehicleStateBasic:
		if (const DataBlock* db = deserialize(is, *m_vsb, dh))           return db;
		break;
	case DataType_LogError:
		if (const DataBlock* db = deserialize(is, *m_logMsgError, dh))   return db;
		break;
	case DataType_LogWarning:
		if (const DataBlock* db = deserialize(is, *m_logMsgWarning, dh)) return db;
		break;
	case DataType_LogNote:
		if (const DataBlock* db = deserialize(is, *m_logMsgNote, dh))    return db;
		break;
	case DataType_LogDebug:
		if (const DataBlock* db = deserialize(is, *m_logMsgDebug, dh))   return db;
		break;
	default:
		logDebug << "Ignoring unknown datatype "
			<< "0x" <<  std::hex << dh.getDataType() << std::dec << std::endl;
		return NULL;
	} // switch

	logError << "Failed to deserialize datatype "
		<< "0x" << std::hex << dh.getDataType() << std::dec << std::endl;
	return NULL;
}

//======================================================================

} // namespace ibeo

//======================================================================
