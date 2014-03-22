//======================================================================
/*! \file IbeoLux.hpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date Apr 24, 2012
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_IBEOLUX_HPP_SEEN
#define IBEOSDK_IBEOLUX_HPP_SEEN

//======================================================================

#include <ibeosdk/misc/WinCompatibility.hpp>

#include <ibeosdk/IbeoDataHeader.hpp>
#include <ibeosdk/devices/IbeoScanner.hpp>

//======================================================================

namespace ibeo {

//======================================================================

class ScanLux;
class ObjectListLux;
class VehicleStateBasicLux;
class LogMessageDebug;
class LogMessageError;
class LogMessageNote;
class LogMessageWarning;

//======================================================================
/*!\class IbeoLux
 * \brief Class to connect to a LUX3/LUX4 sensor.
 * \author Jan Christian Dittmer (jcd)
 * \version 0.1
 * \date Oct 1, 2013
 *
 *///-------------------------------------------------------------------
class IbeoLux : public IbeoScanner {
public:
	//========================================
	/*!\brief Create an IbeoLux (connection class).
	 *
	 * This constructor will create an IbeoLux class object
	 * which will try to connect to a LUX3/LUX4 sensor,
	 * using the given IP address and port number.
	 *
	 * \param[in] ip    IP address of the scanner
	 *                  to be connected with.
	 * \param[in] port  Port number for the connection
	 *                  with the scanner.
	 *///-------------------------------------
	IbeoLux(const std::string& ip, const unsigned short port = 12002);

	//========================================
	/*!\brief Destructor.
	 *
	 * Will disconnect before destruction.
	 *///-------------------------------------
	virtual ~IbeoLux();

protected:
	virtual const DataBlock* onData(const IbeoDataHeader& dh, std::istream& is);

protected:
	//========================================
	/*!\brief Variable to hold the deserialization
	 *        of a ScanLux.
	 *///-------------------------------------
	ScanLux* m_scan;

	//========================================
	/*!\brief Variable to hold the deserialization
	 *        of a ObjectListLux.
	 *///-------------------------------------
	ObjectListLux* m_obj;

	//========================================
	/*!\brief Variable to hold the deserialization
	 *        of a VehicleStateBasicLux.
	 *///-------------------------------------
	VehicleStateBasicLux* m_vsb;

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
}; // IbeoLux

//======================================================================

} // namespace ibeo

//======================================================================

#endif // IBEOSDK_IBEOLUX_HPP_SEEN

//======================================================================

