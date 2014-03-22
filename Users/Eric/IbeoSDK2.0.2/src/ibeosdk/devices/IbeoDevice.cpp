//======================================================================
/*! \file IbeoDevice.cpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date Apr 24, 2012
 *///-------------------------------------------------------------------

#include <ibeosdk/devices/IbeoDevice.hpp>
#include <ibeosdk/listener/ScanLuxListener.hpp>
#include <ibeosdk/listener/ScanEcuListener.hpp>
#include <ibeosdk/listener/ObjectListLuxListener.hpp>
#include <ibeosdk/listener/ObjectListEcuListener.hpp>
#include <ibeosdk/listener/ObjectListEcuEtListener.hpp>
#include <ibeosdk/listener/VehicleStateBasicLuxListener.hpp>
#include <ibeosdk/listener/VehicleStateBasicEcuListener.hpp>
#include <ibeosdk/listener/ImageListener.hpp>
#include <ibeosdk/listener/LogMessageErrorListener.hpp>
#include <ibeosdk/listener/LogMessageWarningListener.hpp>
#include <ibeosdk/listener/LogMessageNoteListener.hpp>
#include <ibeosdk/listener/LogMessageDebugListener.hpp>
#include <ibeosdk/MsgBuffer.hpp>
#include <ibeosdk/Log.hpp>

#include <boost/array.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/asio.hpp>

#include <stdint.h>
#include <fstream>

//======================================================================

namespace ibeo {

//======================================================================

IbeoDevice::IbeoDevice(const std::string& ip, const unsigned short port)
  : m_strIP(ip),
    m_port(port),
    m_ioService(),
    m_socket(NULL),
    m_listeners(),
    m_threadState(TS_NotRunning),
    m_thread(NULL),
    m_logFileManager(NULL)
{}

//======================================================================

IbeoDevice::~IbeoDevice()
{
	if (this->m_thread) {
		{
			Lock lock(m_mutex);
			this->m_threadState = TS_Stopping;
		}
		m_recvCondition.notify_all();

		if (this->m_thread->joinable()) {
			this->m_thread->join();
			delete this->m_thread;
			this->m_thread = NULL;
		}
	}

	if (m_socket != NULL) {
		m_socket->close();
		delete m_socket;
		m_socket = NULL;
	}
}

//======================================================================

void IbeoDevice::disconnect()
{
	if (m_socket != NULL)
		m_socket->close();
}

//======================================================================

bool IbeoDevice::isConnected()
{
	if (m_socket == NULL)
		return false;

	if (!m_socket->is_open())
		return false;

	return (this->m_threadState == TS_Running);
}

//======================================================================

void IbeoDevice::getConnected()
{
	if (m_thread) return;

	Lock lock(m_mutex);
	m_thread = new boost::thread(&IbeoDevice::dataReceiveThread, this);

	while (this->m_threadState==TS_NotRunning) {
		m_recvCondition.wait(lock);
	}
}

//======================================================================

void IbeoDevice::dataReceiveThread()
{
	logInfo << "Thread running" << std::endl;

	try {
		m_socket = new boost::asio::ip::tcp::socket(m_ioService);
	}
	catch (const std::exception& e) {
		logError << "Failed to allocate socket. - "
				<< e.what() << std::endl;
		Lock lock(this->m_mutex);
		m_threadState = TS_StartFailed;
		return;
	}

	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(m_strIP), m_port);
	boost::system::error_code ec;
	m_socket->connect(ep, ec);

	if (ec) {
		logError << "Failed to connect to device (" << ep << ") " << ec.message() << std::endl;
		Lock lock(this->m_mutex);
		m_threadState = TS_StartFailed;
		m_recvCondition.notify_all();
		return;
	}

	logDebug << "Connected to device on " << ep << std::endl;

	boost::system::error_code error;
	const char* bodyBuf;
	const IbeoDataHeader* dh;
	ibeo::MsgBuffer msgBuf(this->m_socket, 65536);

	{
		Lock lock(this->m_mutex);
		m_threadState = TS_Running;
		m_recvCondition.notify_all();
	}

	try {
		while (this->m_threadState != TS_Stopping && m_socket->is_open()) {
			if (msgBuf.recvMsg(dh, bodyBuf)) {
				if (!m_streamers.empty()) {
					// Message has been completely received. So, we can notify all streamers
					notifyStreamers(*dh, bodyBuf);

				}
				if (!m_listeners.empty()) {
					// Message has been completely received. So, we can parse it and notify all clients
					boost::iostreams::stream<boost::iostreams::array_source> strm(bodyBuf, dh->getMessageSize());
					std::istream& s = (std::istream&)strm;
					notifyListeners(onData(*dh, s));
				}
			}
		}
	}
	catch (const boost::system::error_code& ec) {
		logError << " After Error is socket open?: " << this->m_socket->is_open() << " " << ec.message() << std::endl;
		m_threadState = TS_RunFailed;
	}

	if (!m_socket->is_open() && this->m_threadState != TS_Stopping) {
		Lock lock(this->m_mutex);
		m_threadState = TS_RunFailed;
	}
}

//======================================================================

void IbeoDevice::setLogFileManager(LogFileManager* const logFileManager)
{
	this->m_logFileManager = logFileManager;
}

//======================================================================

void IbeoDevice::notifyStreamers(const IbeoDataHeader& dh, const char* const bodyBuf)
{
	if (bodyBuf == NULL)
		return;

	if (this->m_logFileManager) {
		this->m_logFileManager->checkSplitRequired(dh.getDataType());
	}

	std::vector<DataStreamer*>::iterator streamerIter = m_streamers.begin();
	for (; streamerIter != m_streamers.end(); ++streamerIter) {
		(*streamerIter)->onData(dh, bodyBuf);
	}
}

//======================================================================

void IbeoDevice::notifyListeners(const DataBlock* const data)
{
	if (data == NULL)
		return;

	if (this->m_logFileManager) {
		this->m_logFileManager->checkSplitRequired(data->getDataType());
	}

	for (unsigned int i=0; i<m_listeners.size(); i++) {
		if (m_listeners[i]->getAssociatedDataType() == data->getDataType()) {
			switch (data->getDataType()) {
			case DataType_LuxScan:
				{
					ScanLuxListener* const l = dynamic_cast<ScanLuxListener*>(m_listeners[i]);
					const ScanLux* const s = dynamic_cast<const ScanLux*>(data);
					l->onData(s);
				}
				break;
				//========================================
			case DataType_EcuScan:
				{
					ScanEcuListener* const l = dynamic_cast<ScanEcuListener*>(m_listeners[i]);
					const ScanEcu* const s = dynamic_cast<const ScanEcu*>(data);
					l->onData(s);
				}
				break;
				//========================================
			case DataType_LuxObjectList:
				{
					ObjectListLuxListener* const l = dynamic_cast<ObjectListLuxListener*>(m_listeners[i]);
					const ObjectListLux* const o = dynamic_cast<const ObjectListLux*>(data);
					l->onData(o);
				}
				break;
				//========================================
			case DataType_EcuObjectList:
				{
					ObjectListEcuListener* const l = dynamic_cast<ObjectListEcuListener*>(m_listeners[i]);
					const ObjectListEcu* const o = dynamic_cast<const ObjectListEcu*>(data);
					l->onData(o);
				}
				break;
				//========================================
			case DataType_EcuObjectListET:
				{
					ObjectListEcuEtListener* const l = dynamic_cast<ObjectListEcuEtListener*>(m_listeners[i]);
					const ObjectListEcuEt* const o = dynamic_cast<const ObjectListEcuEt*>(data);
					l->onData(o);
				}
				break;
			case DataType_LuxVehicleStateBasic:
				{
					VehicleStateBasicLuxListener* const l  = dynamic_cast<VehicleStateBasicLuxListener*>(m_listeners[i]);
					const VehicleStateBasicLux* const o = dynamic_cast<const VehicleStateBasicLux*>(data);
					l->onData(o);
				}
				break;
			case DataType_EcuVehicleStateBasic:
				{
					VehicleStateBasicEcuListener* const l  = dynamic_cast<VehicleStateBasicEcuListener*>(m_listeners[i]);
					const VehicleStateBasicEcu* const o = dynamic_cast<const VehicleStateBasicEcu*>(data);
					l->onData(o);
				}
				break;
			case DataType_Image:
				{
					ImageListener* const l  = dynamic_cast<ImageListener*>(m_listeners[i]);
					const Image* const o = dynamic_cast<const Image*>(data);
					l->onData(o);
				}
				break;

			case DataType_LogError:
				{
					LogMessageErrorListener* const l  = dynamic_cast<LogMessageErrorListener*>(m_listeners[i]);
					const LogMessageError* const o = dynamic_cast<const LogMessageError*>(data);
					l->onData(o);
				}
				break;
			case DataType_LogWarning:
				{
					LogMessageWarningListener* const l  = dynamic_cast<LogMessageWarningListener*>(m_listeners[i]);
					const LogMessageWarning* const o = dynamic_cast<const LogMessageWarning*>(data);
					l->onData(o);
				}
				break;
			case DataType_LogNote:
				{
					LogMessageNoteListener* const l  = dynamic_cast<LogMessageNoteListener*>(m_listeners[i]);
					const LogMessageNote* const o = dynamic_cast<const LogMessageNote*>(data);
					l->onData(o);
				}
				break;
			case DataType_LogDebug:
				{
					LogMessageDebugListener* const l  = dynamic_cast<LogMessageDebugListener*>(m_listeners[i]);
					const LogMessageDebug* const o = dynamic_cast<const LogMessageDebug*>(data);
					l->onData(o);
				}
				break;
			default:
				logDebug << "unknown data received" << std::endl;
				break;
			}// switch
		}
	}
}

//======================================================================

void IbeoDevice::registerListener(DataListener* const listener)
{
	m_listeners.push_back(listener);
}

//======================================================================

void IbeoDevice::registerStreamer(DataStreamer* const streamer)
{
	this->m_streamers.push_back(streamer);
}

//======================================================================

const DataBlock* IbeoDevice::deserialize(std::istream& is,
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

} // namespace ibeo

//======================================================================
