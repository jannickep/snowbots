//======================================================================
/*! \file IdcFile.cpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date April 4, 2012
 *///-------------------------------------------------------------------

#include <ibeosdk/IdcFile.hpp>
#include <ibeosdk/Log.hpp>

#include <ibeosdk/datablocks/ScanEcu.hpp>
#include <ibeosdk/datablocks/ObjectListEcu.hpp>
#include <ibeosdk/datablocks/ScanLux.hpp>
#include <ibeosdk/datablocks/ObjectListLux.hpp>
#include <ibeosdk/datablocks/ObjectListEcuEt.hpp>
#include <ibeosdk/datablocks/Image.hpp>
#include <ibeosdk/datablocks/VehicleStateBasicLux.hpp>
#include <ibeosdk/datablocks/VehicleStateBasicEcu.hpp>
#include <ibeosdk/datablocks/LogMessageError.hpp>
#include <ibeosdk/datablocks/LogMessageWarning.hpp>
#include <ibeosdk/datablocks/LogMessageNote.hpp>
#include <ibeosdk/datablocks/LogMessageDebug.hpp>

#include <iostream>

//======================================================================

using namespace std;

//======================================================================

namespace ibeo {

//======================================================================

IdcFile::IdcFile()
  : m_strm(),
    m_dh(),
    m_scanLux(new ScanLux),
    m_objLux(new ObjectListLux),
    m_scanEcu(new ScanEcu),
    m_objEcu(new ObjectListEcu),
    m_objEcuEt(new ObjectListEcuEt),
    m_image(new Image),
    m_vsbLux(new VehicleStateBasicLux),
    m_vsbEcu(new VehicleStateBasicEcu),
    m_logMsgError(new LogMessageError),
    m_logMsgWarning(new LogMessageWarning),
    m_logMsgNote(new LogMessageNote),
    m_logMsgDebug(new LogMessageDebug)
{}

//======================================================================

IdcFile::~IdcFile()
{
	this->close();

	delete m_logMsgDebug;
	delete m_logMsgNote;
	delete m_logMsgWarning;
	delete m_logMsgError;
	delete m_vsbEcu;
	delete m_vsbLux;
	delete m_image;
	delete m_objEcuEt;
	delete m_objEcu;
	delete m_scanEcu;
	delete m_objLux;
	delete m_scanLux;
}

//======================================================================
/**
 * Opens the given file
 */
bool IdcFile::open(const std::string& filename)
{
	this->close();
	m_strm.open(filename.c_str(), std::fstream::in | std::fstream::binary);
	return this->isOpen();
}

//======================================================================

bool IdcFile::create(const std::string& filename, const bool append)
{
	this->close();

	if (append)
		this->m_strm.open(filename.c_str(), std::fstream::out | std::fstream::binary | std::fstream::app);
	else
		this->m_strm.open(filename.c_str(), std::fstream::out | std::fstream::binary);

	return this->isOpen();
}

//======================================================================

bool IdcFile::write(const char* const data, const unsigned short length)
{
	if (!this->isOpen())
		return false;
	this->m_strm.write(data, length);

	return true;
}

//======================================================================

bool IdcFile::isOpen() { return this-> m_strm.is_open(); }

//======================================================================

bool IdcFile::isEOF() { return this->m_strm.eof(); }

//======================================================================

void IdcFile::close() { if (this->isOpen()) this->m_strm.close(); }

//======================================================================

bool IdcFile::isGood() { return this->m_strm.good(); }

//======================================================================

const DataBlock* IdcFile::deserialize(std::istream& is,
                                      DataBlock& db,
                                      const IbeoDataHeader& dh)
{
	db.setDataHeader(dh);
	if (db.deserialize(is, dh)) {
		return &db;
	}
	logError << "Failed to deserialization data type 0x"
		<< std::hex << dh.getDataType() << std::dec
		<< std::endl;
	return NULL;

}

//======================================================================

const DataBlock* IdcFile::getNextDataBlock()
{
	if (!isOpen())
		return NULL;

	if (!this->m_dh.deserialize(this->m_strm))
		return NULL;

	switch (m_dh.getDataType()) {
//	case DataType_Notification:
//		break;
	case DataType_LuxScan:
		if (const DataBlock* db = deserialize(m_strm, *m_scanLux, m_dh))      return db;
		break;
	case DataType_EcuScan:
		if (const DataBlock* db = deserialize(m_strm, *m_scanEcu, m_dh))      return db;
		break;
	case DataType_LuxObjectList:
		if (const DataBlock* db = deserialize(m_strm, *m_objLux, m_dh))       return db;
		break;
	case DataType_EcuObjectList:
		if (const DataBlock* db = deserialize(m_strm, *m_objEcu, m_dh))       return db;
		break;
//	case DataType_LuxObjectListET:
//		break;
	case DataType_EcuObjectListET:
		if (const DataBlock* db = deserialize(m_strm, *m_objEcuEt, m_dh))     return db;
		break;
	case DataType_Image:
		if (const DataBlock* db = deserialize(m_strm, *m_image, m_dh))        return db;
		break;
	case DataType_LuxVehicleStateBasic:
		if (const DataBlock* db = deserialize(m_strm, *m_vsbLux, m_dh))       return db;
		break;
//	case DataType_EcuVehicleStateBasicOld:
//		break;
	case DataType_EcuVehicleStateBasic:
		if (const DataBlock* db = deserialize(m_strm, *m_vsbEcu, m_dh))        return db;
		break;
	case DataType_LogError:
		if (const DataBlock* db = deserialize(m_strm, *m_logMsgError, m_dh))   return db;
		break;
	case DataType_LogWarning:
		if (const DataBlock* db = deserialize(m_strm, *m_logMsgWarning, m_dh)) return db;
		break;
	case DataType_LogNote:
		if (const DataBlock* db = deserialize(m_strm, *m_logMsgNote, m_dh))    return db;
		break;
	case DataType_LogDebug:
		if (const DataBlock* db = deserialize(m_strm, *m_logMsgDebug, m_dh))   return db;
		break;
	default:
		logDebug2 << "Ignoring unknown datatype "
			<< "0x" <<  std::hex << m_dh.getDataType() << std::dec << std::endl;
		m_strm.ignore(m_dh.getMessageSize());
		return NULL;
	}

	logInfo << "Failed to deserialize datatype "
		<< "0x" << std::hex << m_dh.getDataType() << std::dec << std::endl;
	return NULL;
}

//======================================================================

} // namespace ibeo

//======================================================================
