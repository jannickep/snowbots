//======================================================================
/*! \file ObjectListEcuListener.hpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date May 05, 2012
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_OBJECTLISTECULISTENER_HPP_SEEN
#define IBEOSDK_OBJECTLISTECULISTENER_HPP_SEEN

//======================================================================

#include <ibeosdk/listener/DataListener.hpp>
#include <ibeosdk/datablocks/ObjectListEcu.hpp>
#include <ibeosdk/datatypes.hpp>

//======================================================================

namespace ibeo {

//======================================================================
/*!\class ObjectListEcuListener
 * \brief Abstract base class for all DataListener listen on ObjectListEcu.
 * \author Mario Brumm (mb)
 * \version 0.1
 * \date May 3, 2012
 *///-------------------------------------------------------------------
class ObjectListEcuListener: public ibeo::DataListener {
public:
	//========================================
	/*!\brief Get ibeo#DataType_EcuObjectList as
	 *        associated DataType.
	 * \return Always ibeo#DataType_EcuObjectList.
	 *///-------------------------------------
	virtual DataType getAssociatedDataType() { return DataType_EcuObjectList; }

	//========================================
	/*!\brief Called on receiving a new ObjectListEcu DataBlock.
	 *
	 * Method to be called by the IbeoDevice where this listener
	 * is registered when a new DataBlock of type ObjectListEcu
	 * has been received.
	 *
	 * \param[in] objectList  Pointer to the object list that has
	 *                        been received.
	 *///-------------------------------------
	virtual void onData(const ObjectListEcu* const objectList) = 0;
}; // ObjectListEcuListener

//======================================================================

} // namespace ibeo

//======================================================================

#endif // IBEOSDK_OBJECTLISTECULISTENER_HPP_SEEN

//======================================================================

