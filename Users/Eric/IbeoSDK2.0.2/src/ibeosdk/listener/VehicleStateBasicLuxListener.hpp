//======================================================================
/*! \file VehicleStateBasicLuxListener.hpp
 *
 * \copydoc Copyright
 * \author Jan Christian Dittmer (jcd)
 * \date Sep 2, 2013
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_VEHICLESTATEBASICLUXLISTENER_HPP_SEEN
#define IBEOSDK_VEHICLESTATEBASICLUXLISTENER_HPP_SEEN

//======================================================================

#include <ibeosdk/listener/DataListener.hpp>
#include <ibeosdk/datablocks/VehicleStateBasicLux.hpp>
#include <ibeosdk/datatypes.hpp>

//======================================================================

namespace ibeo {

//======================================================================
/*!\class VehicleStateBasicLuxListener
 * \brief Abstract base class for all DataListener listen on VehicleStateBasicLux.
 * \author Jan Christian Dittmer (jcd)
 * \version 0.1
 * \date Sep 2, 2013
 *///-------------------------------------------------------------------
class VehicleStateBasicLuxListener : public DataListener {
public:
	//========================================
	/*!\brief Get ibeo#DataType_LuxVehicleStateBasic as
	 *        associated DataType.
	 * \return Always ibeo#DataType_LuxVehicleStateBasic.
	 *///-------------------------------------
	virtual DataType getAssociatedDataType() { return DataType_LuxVehicleStateBasic; }

	//========================================
	/*!\brief Called on receiving a new VehicleStateBasicLux DataBlock.
	 *
	 * Method to be called by the IbeoDevice where this listener
	 * is registered when a new DataBlock of type VehicleStateBasicLux
	 * has been received.
	 *
	 * \param[in] vsb  Pointer to the vehicle state that has
	 *                 been received.
	 *///-------------------------------------
	virtual void onData(const VehicleStateBasicLux* const vsb) = 0;
}; // VehicleStateBasicLuxListener

//======================================================================

}// namespace ibeo

//======================================================================

#endif // IBEOSDK_VEHICLESTATEBASICLUXLISTENER_HPP_SEEN

//======================================================================

