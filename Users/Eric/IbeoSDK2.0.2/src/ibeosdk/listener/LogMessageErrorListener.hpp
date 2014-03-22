//======================================================================
/*! \file LogMessageErrorListener.hpp
 *
 * \copydoc Copyright
 * \author Jan Christian Dittmer (jcd)
 * \date Sep 30, 2013
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_LOGMESSAGEERRORLISTENER_HPP_SEEN
#define IBEOSDK_LOGMESSAGEERRORLISTENER_HPP_SEEN

//======================================================================

#include <ibeosdk/listener/DataListener.hpp>
#include <ibeosdk/datablocks/LogMessageError.hpp>
#include <ibeosdk/datatypes.hpp>

//======================================================================

namespace ibeo {

//======================================================================

class LogMessageErrorListener : public ibeo::DataListener {
public:
	//========================================
	/*!\brief Get ibeo#DataType_LogError as
	 *        associated DataType.
	 * \return Always ibeo#DataType_LogError.
	 *///-------------------------------------
	virtual DataType getAssociatedDataType() { return DataType_LogError; }

	//========================================
	/*!\brief Called on receiving a new LogMessageError DataBlock.
	 *
	 * Method to be called by the IbeoDevice where this listener
	 * is registered when a new DataBlock of type LogMessageError
	 * has been received.
	 *
	 * \param[in] scan  Pointer to the scan that has
	 *                  been received.
	 *///-------------------------------------
	virtual void onData(const LogMessageError* const scan) = 0;
}; // LogMessageErrorListener

//======================================================================

} // namespace ibeo

//======================================================================

#endif // IBEOSDK_LOGMESSAGEERRORLISTENER_HPP_SEEN

//======================================================================
