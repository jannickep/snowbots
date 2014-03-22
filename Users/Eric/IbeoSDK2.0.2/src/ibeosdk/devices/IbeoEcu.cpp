//======================================================================
/*! \file IbeoEcu.cpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date Apr 24, 2012
 *///-------------------------------------------------------------------

#include <ibeosdk/devices/IbeoEcu.hpp>
#include <ibeosdk/datablocks/Command.hpp>
#include <ibeosdk/datablocks/ScanEcu.hpp>
#include <ibeosdk/datablocks/ObjectListEcu.hpp>
#include <ibeosdk/datablocks/ObjectListEcuEt.hpp>
#include <ibeosdk/datablocks/Image.hpp>
#include <ibeosdk/datablocks/VehicleStateBasicEcu.hpp>
#include <ibeosdk/datablocks/LogMessageDebug.hpp>
#include <ibeosdk/datablocks/LogMessageError.hpp>
#include <ibeosdk/datablocks/LogMessageNote.hpp>
#include <ibeosdk/datablocks/LogMessageWarning.hpp>

#include <boost/array.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/asio.hpp>
#include <boost/scoped_ptr.hpp>

//======================================================================

namespace ibeo {

//======================================================================

IbeoEcu::IbeoEcu(const std::string& ip, const unsigned short port)
  : IbeoDevice(ip, port),
    m_scan(new ScanEcu),
    m_obj(new ObjectListEcu),
    m_objEt(new ObjectListEcuEt),
    m_vsbEcu(new VehicleStateBasicEcu),
    m_image(new Image),
    m_logMsgError(new LogMessageError),
    m_logMsgWarning(new LogMessageWarning),
    m_logMsgNote(new LogMessageNote),
    m_logMsgDebug(new LogMessageDebug)
{}

//======================================================================

IbeoEcu::~IbeoEcu()
{
	delete m_logMsgDebug;
	delete m_logMsgNote;
	delete m_logMsgWarning;
	delete m_logMsgError;
	delete m_image;
	delete m_vsbEcu;
	delete m_objEt;
	delete m_obj;
	delete m_scan;
}

//======================================================================

void IbeoEcu::getConnected()
{
	IbeoDevice::getConnected();

	// clear data type filter

	CommandSetFilter setFilterCmd(DataType_Unknown, DataType(0xffff));
	const unsigned long int cmdLength = setFilterCmd.getCommandLength();
	const int bufSize = cmdLength + IbeoDataHeader::getHeaderSize();
	boost::scoped_ptr<char> sendBuf(new char[bufSize]);
	boost::iostreams::stream<boost::iostreams::array> strm(sendBuf.get(), bufSize);
	std::ostream& s = (std::ostream&)strm;
	IbeoDataHeader dh(setFilterCmd.getDataType(), 0, cmdLength, 1, NTPTime());
	dh.serialize(s);
	setFilterCmd.serialize(s);

	if (isConnected()) {
		m_socket->send(boost::asio::buffer(sendBuf.get(), bufSize));
	}
}

//======================================================================

const DataBlock* IbeoEcu::onData(const IbeoDataHeader& dh, std::istream& is) {

	switch (dh.getDataType()) {
	case DataType_EcuScan:
		if (const DataBlock* db = deserialize(is, *m_scan, dh))          return db;
		break;
	case DataType_EcuObjectList:
		if (const DataBlock* db = deserialize(is, *m_obj, dh))           return db;
		break;
	case DataType_EcuObjectListET:
		if (const DataBlock* db = deserialize(is, *m_objEt, dh))         return db;
		break;
	case DataType_Image:
		if (const DataBlock* db = deserialize(is, *m_image, dh))         return db;
		break;
	case DataType_EcuVehicleStateBasic:
		if (const DataBlock* db = deserialize(is, *m_vsbEcu, dh))        return db;
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
			<< "0x" << std::hex << dh.getDataType() << std::dec << std::endl;
		return NULL;
	}

	logError << "Failed to deserialize datatype "
		<< "0x" << std::hex << dh.getDataType() << std::dec << std::endl;

	return NULL;
}

//======================================================================

} // namespace ibeo

//======================================================================
