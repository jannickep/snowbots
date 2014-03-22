//======================================================================
/*! \file inttypes.hpp
 *
 * \copydoc Copyright
 * \author Jan Christian Dittmer (jcd)
 * \date Sep 4, 2013
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_INTTYPES_HPP_SEEN
#define IBEOSDK_INTTYPES_HPP_SEEN

//======================================================================

#include <ibeosdk/misc/WinCompatibility.hpp>

#include <boost/cstdint.hpp>

//======================================================================

namespace ibeo {

//======================================================================

typedef boost:: uint8_t          BYTE;      ///<  8 bit wide unsigned integer
typedef boost:: int8_t           INT8;      ///<  8 bit wide   signed integer
typedef boost:: uint8_t          UINT8;     ///<  8 bit wide unsigned integer
typedef boost:: int16_t          INT16;     ///< 16 bit wide   signed integer
typedef boost::uint16_t         UINT16;     ///< 16 bit wide unsigned integer
#ifndef _BASETSD_H_     // avoid naming conflict with Windows <basetsd.h>
typedef boost:: int32_t          INT32;     ///< 32 bit wide   signed integer
typedef boost::uint32_t         UINT32;     ///< 32 bit wide unsigned integer
typedef boost:: int64_t          INT64;     ///< 64 bit wide   signed integer
typedef boost::uint64_t         UINT64;     ///< 64 bit wide unsigned integer
#endif

//======================================================================

} // namespace ibeo

//======================================================================

#endif // IBEOSDK_INTTYPES_HPP_SEEN

//======================================================================
