//======================================================================
/*! \file datatypes.hpp
 *
 * \copydoc Copyright
 * \author Jan Christian Dittmer (jcd)
 * \date Sep 4, 2013
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_DATATYPES_HPP_SEEN
#define IBEOSDK_DATATYPES_HPP_SEEN

//======================================================================

#include <ibeosdk/misc/WinCompatibility.hpp>

//======================================================================

namespace ibeo {

//======================================================================
/*!\brief DataType of a DataBlock.
 *///-------------------------------------------------------------------
enum DataType {
	DataType_Unknown                 = 0x0000,
	DataType_Command                 = 0x2010,
	DataType_Reply                   = 0x2020,
	DataType_Notification            = 0x2030, //!< error and warning messages sent by ibeo LUX/Scala family sensors
	DataType_LuxScan                 = 0x2202, //!< scan data sent by ibeo LUX/Scala family sensors
	DataType_EcuScan                 = 0x2205, //!< scan data sent by ibeo ECU devices
	DataType_LuxObjectList           = 0x2221, //!< objects sent by ibeo LUX family sensors
	DataType_EcuObjectList           = 0x2225, //!< objects sent by ibeo ECU devices
	DataType_LuxObjectListET         = 0x2270, //!< send by Scala family sensors
	DataType_EcuObjectListET         = 0x2280, //!< send by ECU devices
	DataType_Image                   = 0x2403, //!< An image
	DataType_LuxVehicleStateBasic    = 0x2805, //!< send by LUX/Scala
	DataType_EcuVehicleStateBasicOld = 0x2806, //!< send by ECU
	DataType_EcuVehicleStateBasic    = 0x2807, //!< send by ECU
	DataType_IdcTrailer              = 0x6120, //!< Trailer Message in an IDC file
	DataType_LogError                = 0x6400,
	DataType_LogWarning              = 0x6410,
	DataType_LogNote                 = 0x6420,
	DataType_LogDebug                = 0x6430
}; // DataType

//======================================================================

} // namespace ibeo

//======================================================================

#endif // IBEOSDK_DATATYPES_HPP_SEEN

//======================================================================

