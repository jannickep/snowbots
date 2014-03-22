//======================================================================
/*! \file IbeoSDK.hpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date April 4, 2012
 *
 * Ibeo SDK main header file
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_IBEOSDK_HPP_SEEN
#define IBEOSDK_IBEOSDK_HPP_SEEN

//======================================================================

#include <ibeosdk/misc/WinCompatibility.hpp>

#include <ibeosdk/misc/Version.hpp>

//======================================================================

namespace ibeo {

//======================================================================

class IbeoSDK {
public:
	IbeoSDK() {}
	virtual ~IbeoSDK() {}

	static ibeo::Version getVersion()
	{
		return ibeo::Version(ibeo::Version::MajorVersion(2),
		                     ibeo::Version::MinorVersion(0),
		                     ibeo::Version::Revision(2));
	}
}; // IbeoSDK

//======================================================================

} // namespace ibeo

//======================================================================

#endif // IBEOSDK_IBEOSDK_HPP_SEEN

//======================================================================

