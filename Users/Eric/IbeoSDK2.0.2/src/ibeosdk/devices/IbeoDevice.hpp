//======================================================================
/*! \file IbeoDevice.hpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date Apr 24, 2012
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_IBEODEVICE_HPP_SEEN
#define IBEOSDK_IBEODEVICE_HPP_SEEN

//======================================================================

#include <ibeosdk/misc/WinCompatibility.hpp>

#include <ibeosdk/IbeoDataHeader.hpp>
#include <ibeosdk/datablocks/DataBlock.hpp>
#include <ibeosdk/listener/DataListener.hpp>
#include <ibeosdk/LogFileManager.hpp>
#include <ibeosdk/listener/DataStreamer.hpp>

#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/asio.hpp>
#include <boost/iostreams/stream.hpp>

#include <iostream>
#include <vector>

//======================================================================

namespace ibeo {

//======================================================================
/*!\class IbeoDevice
 * \brief Base class for all Ibeo devices connected via TCP/IP.
 * \author Mario Brumm (mb)
 * \version 0.1
 * \date Apr 24, 2012
 *
 *///-------------------------------------------------------------------
class IbeoDevice {
protected:
	enum ThreadState {
		TS_NotRunning,
		TS_Running,
		TS_Stopping,
		TS_StartFailed,
		TS_RunFailed
	}; // ThreadState

	typedef boost::mutex::scoped_lock Lock;
	typedef boost::mutex Mutex;
	typedef boost::condition Condition;

protected:
	//========================================
	/*!\brief Create an IbeoScanner.
	 *
	 * The constructor will be called by derived
	 * scanner classes also.
	 *
	 * \param[in] ip    IP address of the scanner
	 *                  to be connected with.
	 * \param[in] port  Port number for the connection
	 *                  with the scanner.
	 *///-------------------------------------
	IbeoDevice(const std::string& ip, const unsigned short port = 12002);

public:
	//========================================
	/*!\brief Destrutor of the IbeoDevice class.
	 *
	 * Stopping the receiving thread and
	 * disconnecting the hardware device.
	 *///-------------------------------------
	virtual ~IbeoDevice();

private:
	IbeoDevice(const IbeoDevice&); // forbidden
	IbeoDevice& operator=(const IbeoDevice&); // forbidden

public:
	//========================================
	/*!\brief Establish the connection to the
	 *        hardware.
	 *
	 * Starting the receiving thread.
	 *///-------------------------------------
	virtual void getConnected();

	//========================================
	/*!\brief Disconnect the TCP/IP connection
	 *        to the hardware device.
	 *///-------------------------------------
	virtual void disconnect();

	//========================================
	/*!\brief Checks whether the TCP/IP connection
	 *        to the hardware device is there and
	 *        the receiving thread is still running.
	 * \return \c true if messages from the hardware
	 *         can still be received. \c false otherwise.
	 *///-------------------------------------
	virtual bool isConnected();

	//========================================
	/*!\brief Register a DataListener to this device.
	 *
	 * Each time a message has been received by the
	 * this object, the registered listener will be
	 * call which are listening to the received message
	 * type (DataType).
	 * \param[in] listener  Listener to be registered.
	 * \note There is (currently) no way to unregister a
	 *       listener, so a registered DataListener must
	 *       not be destroyed before this IbeoDevice
	 *       has been destroyed.
	 *///-------------------------------------
	virtual void registerListener(DataListener* const listener);

	//========================================
	/*!\brief Register a DataStreamer to this device.
	 *
	 * Each time a message has been received by the
	 * this object, the registered streamer will be
	 * call which are listening to the received message
	 * type (DataType).
	 * \param[in] streamer  Streamer to be registered.
	 * \note There is (currently) no way to unregister a
	 *       streamer, so a registered DataStreamer must
	 *       not be destroyed before this IbeoDevice
	 *       has been destroyed.
	 *///-------------------------------------
	virtual void registerStreamer(DataStreamer* const streamer);

	//========================================
	/*!\brief Main function of the receive thread.
	 *///-------------------------------------
	virtual void dataReceiveThread();

public:
	//========================================
	/*!\brief Set the LogFileManager.
	 *
	 * \param[in] logFileManager  LogFileManager which is
	 *                            handle the splitting of
	 *                            output files and log files.
	 *///-------------------------------------
	void setLogFileManager(LogFileManager* const logFileManager);

protected:
	virtual const DataBlock* onData(const IbeoDataHeader& dh, std::istream& is) = 0;
	virtual void notifyListeners(const DataBlock* const data);
	virtual void notifyStreamers(const IbeoDataHeader& dh, const char* const bodyBuf);

	virtual const DataBlock* deserialize(std::istream& is,
	                                     DataBlock& db,
	                                     const IbeoDataHeader& dh);

protected:
	Mutex m_mutex;
	Condition m_recvCondition;

	std::string m_strIP;
	unsigned short m_port;
	boost::asio::io_service m_ioService;
	boost::asio::ip::tcp::socket* m_socket;
	std::vector<DataListener*> m_listeners;
	std::vector<DataStreamer*> m_streamers;
	ThreadState m_threadState;
	boost::thread* m_thread;
	LogFileManager* m_logFileManager;
}; // ibeoDevice

//======================================================================

} // namespace ibeo

//======================================================================

#endif // IBEOSDK_IBEODEVICE_HPP_SEEN

//======================================================================

