//======================================================================
/*! \file ImageListener.hpp
 *
 * \copydoc Copyright
 * \author Jan Christian Dittmer (jcd)
 * \date Sep 29, 2013
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_IMAGELISTENER_HPP_SEEN
#define IBEOSDK_IMAGELISTENER_HPP_SEEN

//======================================================================

#include <ibeosdk/datablocks/Image.hpp>

//======================================================================

namespace ibeo {

//======================================================================

class ImageListener : public ibeo::DataListener {
public:
	//========================================
	/*!\brief Get ibeo#DataType_Image as
	 *        associated DataType.
	 * \return Always ibeo#DataType_Image.
	 *///-------------------------------------
	virtual DataType getAssociatedDataType() { return DataType_Image; }

	//========================================
	/*!\brief Called on receiving a new Image DataBlock.
	 *
	 * Method to be called by the IbeoDevice where this listener
	 * is registered when a new DataBlock of type Image
	 * has been received.
	 *
	 * \param[in] image  Pointer to the image that has
	 *                   been received.
	 *///-------------------------------------
	virtual void onData(const Image* const image) = 0;
}; // ImageListener

//======================================================================

}// namespace ibeo

//======================================================================

#endif // IBEOSDK_IMAGELISTENER_HPP_SEEN

//======================================================================
