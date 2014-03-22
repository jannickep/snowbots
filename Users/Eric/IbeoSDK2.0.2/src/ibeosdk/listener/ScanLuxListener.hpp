//======================================================================
/*! \file ScanLuxListener.hpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date Apr 30, 2012
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_SCANLUXLISTENER_HPP_SEEN
#define IBEOSDK_SCANLUXLISTENER_HPP_SEEN

//======================================================================

#include <ibeosdk/listener/DataListener.hpp>
#include <ibeosdk/datablocks/ScanLux.hpp>
#include <ibeosdk/datatypes.hpp>

//======================================================================

namespace ibeo {

//======================================================================
/*!\class ScanLuxListener
 * \brief Abstract base class for all DataListener listen on ScanLux.
 * \author Mario Brumm (mb)
 * \version 0.1
 * \date Apr 30, 2012
 *///-------------------------------------------------------------------
class ScanLuxListener : public DataListener {
public:
	//========================================
	/*!\brief Get ibeo#DataType_LuxScan as
	 *        associated DataType.
	 * \return Always ibeo#DataType_LuxScan.
	 *///-------------------------------------
	virtual DataType getAssociatedDataType() { return DataType_LuxScan; }

	//========================================
	/*!\brief Called on receiving a new ScanLux DataBlock.
	 *
	 * Method to be called by the IbeoDevice where this listener
	 * is registered when a new DataBlock of type ScanLux
	 * has been received.
	 *
	 * \param[in] scan  Pointer to the scan that has
	 *                  been received.
	 *///-------------------------------------
	virtual void onData(const ScanLux* const scan) = 0;
}; // ScanLuxListener

//======================================================================

} // namespace ibeo

//======================================================================

#endif // IBEOSDK_SCANLUXLISTENER_HPP_SEEN

//======================================================================

