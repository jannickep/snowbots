//======================================================================
/*! \file LogMessageWarningListener.hpp
 *
 * \copydoc Copyright
 * \author Jan Christian Dittmer (jcd)
 * \date Sep 30, 2013
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_LOGMESSAGEWARNINGLISTENER_HPP_SEEN
#define IBEOSDK_LOGMESSAGEWARNINGLISTENER_HPP_SEEN

//======================================================================

#include <ibeosdk/listener/DataListener.hpp>
#include <ibeosdk/datablocks/LogMessageWarning.hpp>
#include <ibeosdk/datatypes.hpp>

//======================================================================

namespace ibeo {

//======================================================================

class LogMessageWarningListener : public ibeo::DataListener {
public:
	//========================================
	/*!\brief Get ibeo#DataType_LogWarning as
	 *        associated DataType.
	 * \return Always ibeo#DataType_LogWarning.
	 *///-------------------------------------
	virtual DataType getAssociatedDataType() { return DataType_LogWarning; }

	//========================================
	/*!\brief Called on receiving a new LogMessageWarning DataBlock.
	 *
	 * Method to be called by the IbeoDevice where this listener
	 * is registered when a new DataBlock of type LogMessageWarning
	 * has been received.
	 *
	 * \param[in] scan  Pointer to the scan that has
	 *                  been received.
	 *///-------------------------------------
	virtual void onData(const LogMessageWarning* const scan) = 0;
}; // LogMessageWarningListener

//======================================================================

} // namespace ibeo

//======================================================================

#endif // IBEOSDK_LOGMESSAGEWARNINGLISTENER_HPP_SEEN

//======================================================================
