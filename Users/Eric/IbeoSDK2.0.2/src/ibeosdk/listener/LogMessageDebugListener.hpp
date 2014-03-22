//======================================================================
/*! \file LogMessageDebugListener.hpp
 *
 * \copydoc Copyright
 * \author Jan Christian Dittmer (jcd)
 * \date Sep 30, 2013
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_LOGMESSAGEDEBUGLISTENER_HPP_SEEN
#define IBEOSDK_LOGMESSAGEDEBUGLISTENER_HPP_SEEN

//======================================================================

#include <ibeosdk/listener/DataListener.hpp>
#include <ibeosdk/datablocks/LogMessageDebug.hpp>
#include <ibeosdk/datatypes.hpp>

//======================================================================

namespace ibeo {

//======================================================================

class LogMessageDebugListener : public ibeo::DataListener {
public:
	//========================================
	/*!\brief Get ibeo#DataType_LogDebug as
	 *        associated DataType.
	 * \return Always ibeo#DataType_LogDebug.
	 *///-------------------------------------
	virtual DataType getAssociatedDataType() { return DataType_LogDebug; }

	//========================================
	/*!\brief Called on receiving a new LogMessageDebug DataBlock.
	 *
	 * Method to be called by the IbeoDevice where this listener
	 * is registered when a new DataBlock of type LogMessageDebug
	 * has been received.
	 *
	 * \param[in] scan  Pointer to the scan that has
	 *                  been received.
	 *///-------------------------------------
	virtual void onData(const LogMessageDebug* const scan) = 0;
}; // LogMessageDebugListener

//======================================================================

} // namespace ibeo

//======================================================================

#endif // IBEOSDK_LOGMESSAGEERRORLISTENER_HPP_SEEN

//======================================================================
