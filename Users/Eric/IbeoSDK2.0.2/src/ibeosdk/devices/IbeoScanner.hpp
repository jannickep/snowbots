//======================================================================
/*! \file IbeoScanner.hpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date Apr 24, 2012
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_IBEOSCANNER_HPP_SEEN
#define IBEOSDK_IBEOSCANNER_HPP_SEEN

//======================================================================

#include <ibeosdk/misc/WinCompatibility.hpp>

#include <ibeosdk/devices/IbeoDevice.hpp>

//======================================================================

namespace ibeo {

//======================================================================
/*!\class IbeoScanner
 * \brief Base class for all Ibeo scanner classes.
 * \author Jan Christian Dittmer (jcd)
 * \version 0.1
 * \date April 24, 2012
 *
 *///-------------------------------------------------------------------
class IbeoScanner : public IbeoDevice {
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
	IbeoScanner(const std::string& ip, const unsigned short port = 12002);
}; // IbeoScanner

//======================================================================

} // namespace ibeo

//======================================================================

#endif // IBEOSDK_IBEOSCANNER_HPP_SEEN

//======================================================================
