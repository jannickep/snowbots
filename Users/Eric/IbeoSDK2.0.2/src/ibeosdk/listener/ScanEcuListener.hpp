//======================================================================
/*! \file ScanEcuListener.hpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date May 03, 2012
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_SCANECULISTENER_HPP_SEEN
#define IBEOSDK_SCANECULISTENER_HPP_SEEN

//======================================================================

#include <ibeosdk/listener/DataListener.hpp>
#include <ibeosdk/datablocks/ScanEcu.hpp>
#include <ibeosdk/datatypes.hpp>

//======================================================================

namespace ibeo {

//======================================================================
/*!\class ScanEcuListener
 * \brief Abstract base class for all DataListener listen on ScanEcu.
 * \author Mario Brumm (mb)
 * \version 0.1
 * \date May 3, 2012
 *///-------------------------------------------------------------------
class ScanEcuListener: public ibeo::DataListener {
public:
	//========================================
	/*!\brief Get ibeo#DataType_EcuScan as
	 *        associated DataType.
	 * \return Always ibeo#DataType_EcuScan.
	 *///-------------------------------------
	virtual DataType getAssociatedDataType() { return DataType_EcuScan; }

	//========================================
	/*!\brief Called on receiving a new ScanEcu DataBlock.
	 *
	 * Method to be called by the IbeoDevice where this listener
	 * is registered when a new DataBlock of type ScanEcu
	 * has been received.
	 *
	 * \param[in] scan  Pointer to the scan that has
	 *                  been received.
	 *///-------------------------------------
	virtual void onData(const ScanEcu* const scan) = 0;
}; // ScanEcuListener

//======================================================================

} // namespace ibeo

//======================================================================

#endif // IBEOSDK_SCANECULISTENER_HPP_SEEN

//======================================================================

