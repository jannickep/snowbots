//======================================================================
/*! \file IbeoEcu.hpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date Apr 24, 2012
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_IBEOECU_HPP_SEEN
#define IBEOSDK_IBEOECU_HPP_SEEN

//======================================================================

#include <ibeosdk/misc/WinCompatibility.hpp>

#include <ibeosdk/devices/IbeoDevice.hpp>

//======================================================================

namespace ibeo {

//======================================================================

class ScanEcu;
class ObjectListEcu;
class ObjectListEcuEt;
class VehicleStateBasicEcu;
class Image;
class LogMessageDebug;
class LogMessageError;
class LogMessageNote;
class LogMessageWarning;

//======================================================================

class IbeoEcu : public IbeoDevice {
public:
	//========================================
	/*!\brief Create an IbeoEcu (connection class).
	 *
	 * This constructor will create an IbeoEcu class object
	 * which will try to connect to an ECU,
	 * using the given IP address and port number.
	 *
	 * \param[in] ip    IP address of the ECU
	 *                  to be connected with.
	 * \param[in] port  Port number for the connection
	 *                  with the scanner.
	 *///-------------------------------------
	IbeoEcu(const std::string& ip, const unsigned short port = 12002);

	//========================================
	/*!\brief Destructor.
	 *
	 * Will disconnect before destruction.
	 *///-------------------------------------
	virtual ~IbeoEcu();

public:
	//========================================
	/*!\brief Establish the connection to the hardware.
	 *
	 * Reimplements IbeoDevice::getConnected. In
	 * addition it will send a setFilter command
	 * to the ECU to make all messages passes its
	 * output filter.
	 *///-------------------------------------
	virtual void getConnected();

protected:
	virtual const DataBlock* onData(const IbeoDataHeader& dh, std::istream& is);

protected:
	//========================================
	/*!\brief Variable to hold the deserialization
	 *        of a ScanEcu.
	 *///-------------------------------------
	ScanEcu* m_scan;

	//========================================
	/*!\brief Variable to hold the deserialization
	 *        of a ObjectListEcu.
	 *///-------------------------------------
	ObjectListEcu* m_obj;

	//========================================
	/*!\brief Variable to hold the deserialization
	 *        of a ObjectListEcuEt.
	 *///-------------------------------------
	ObjectListEcuEt* m_objEt;

	//========================================
	/*!\brief Variable to hold the deserialization
	 *        of a VehicleStateBasicEcu.
	 *///-------------------------------------
	VehicleStateBasicEcu* m_vsbEcu;

	//========================================
	/*!\brief Variable to hold the deserialization
	 *        of an Image
	 *///-------------------------------------
	Image* m_image;

	//========================================
	/*!\brief Variable to hold the deserialization
	 *        of a LogMessageError
	 *///-------------------------------------
	LogMessageError* m_logMsgError;

	//========================================
	/*!\brief Variable to hold the deserialization
	 *        of a LogMessageWarning
	 *///-------------------------------------
	LogMessageWarning* m_logMsgWarning;
	//========================================
	/*!\brief Variable to hold the deserialization
	 *        of a LogMessageNote
	 *///-------------------------------------
	LogMessageNote* m_logMsgNote;

	//========================================
	/*!\brief Variable to hold the deserialization
	 *        of a LogMessageDebug
	 *///-------------------------------------
	LogMessageDebug* m_logMsgDebug;
}; // ibeoEcu

//======================================================================

} // namespace ibeo

//======================================================================

#endif // IBEOSDK_IBEOECU_HPP_SEEN

//======================================================================

