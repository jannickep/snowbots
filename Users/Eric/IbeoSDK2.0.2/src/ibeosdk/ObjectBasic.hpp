//======================================================================
/*! \file  ObjectBasic.hpp
 *
 * \copydoc Copyright
 * \author Jan Christian Dittmer (jcd)
 * \date Sep 4, 2013
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_OBJECTBASIC_HPP_SEEN
#define IBEOSDK_OBJECTBASIC_HPP_SEEN

//======================================================================

namespace ibeo {

//======================================================================

enum ObjectClass {
	ObjectClass_Unclassified = 0,
	ObjectClass_UnknownSmall = 1,
	ObjectClass_UnknownBig = 2,
	ObjectClass_Pedestrian = 3,
	ObjectClass_Bike = 4,
	ObjectClass_Car = 5,
	ObjectClass_Truck = 6
}; // ObjectClass

//======================================================================

enum RefPointBoxLocation
{
	RPL_CenterOfGravity = 0,
	RPL_FrontLeft       = 1,
	RPL_FrontRight      = 2,
	RPL_RearRight       = 3,
	RPL_RearLeft        = 4,
	RPL_FrontCenter     = 5,
	RPL_RightCenter     = 6,
	RPL_RearCenter      = 7,
	RPL_LeftCenter      = 8,
	RPL_ObjectCenter    = 9,
	RPL_Unknown         = 0xFF
}; // RefPointBoxLocation


//======================================================================

} // namespace ibeo

//======================================================================

#endif // IBEOSDK_OBJECTBASIC_HPP_SEEN
