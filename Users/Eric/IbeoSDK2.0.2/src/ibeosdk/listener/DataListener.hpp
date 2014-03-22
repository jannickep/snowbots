//======================================================================
/*! \file DataListener.hpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date Apr 30, 2012
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_DATALISTENER_HPP_SEEN
#define IBEOSDK_DATALISTENER_HPP_SEEN

//======================================================================

#include <ibeosdk/datatypes.hpp>

//======================================================================

namespace ibeo {

//======================================================================
/*!\class DataListener
 * \brief Abstract base class for all listener.
 * \author Mario Brumm (mb)
 * \version 0.1
 * \date Apr 39, 2012
 *
 * A DataListener can be registered to an IbeoDevice to receive
 * all DataBlock of the associated DataType received by that
 * device.
 *
 * Derived classes will have to implement an onData method for the
 * associated DataType. This onData method will be called in the
 * context of the receive thread of that device.
 *
 * The data received by the onData method will be deserialized.
 *
 * In case one is not interested in the contents of that DataBlock
 * it may be better to implement a DataStreamer.
 *
 * \sa DataStreamer
 *///-------------------------------------------------------------------
class DataListener {
public:
	//========================================
	/*!\brief Destrutor does nothing special.
	 *///-------------------------------------
	virtual ~DataListener() {}

public:
	//========================================
	/*!\brief Get the DataType for which this
	 *        listener is listening.
	 * \return The DataType the listener is
	 *         listening for.
	 *///-------------------------------------
	virtual DataType getAssociatedDataType() = 0;
}; // DataListener

//======================================================================

} // namespace ibeo

//======================================================================

#endif // IBEOSDK_DATALISTENER_HPP_SEEN

//======================================================================

