//======================================================================
/*! \file LogMessageNoteListener.hpp
 *
 * \copydoc Copyright
 * \author Jan Christian Dittmer (jcd)
 * \date Sep 30, 2013
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_LOGMESSAGENOTELISTENER_HPP_SEEN
#define IBEOSDK_LOGMESSAGENOTELISTENER_HPP_SEEN

//======================================================================

#include <ibeosdk/listener/DataListener.hpp>
#include <ibeosdk/datablocks/LogMessageNote.hpp>
#include <ibeosdk/datatypes.hpp>

//======================================================================

namespace ibeo {

//======================================================================

class LogMessageNoteListener : public ibeo::DataListener {
public:
	//========================================
	/*!\brief Get ibeo#DataType_LogNote as
	 *        associated DataType.
	 * \return Always ibeo#DataType_LogNote.
	 *///-------------------------------------
	virtual DataType getAssociatedDataType() { return DataType_LogNote; }

	//========================================
	/*!\brief Called on receiving a new LogMessageNote DataBlock.
	 *
	 * Method to be called by the IbeoDevice where this listener
	 * is registered when a new DataBlock of type LogMessageNote
	 * has been received.
	 *
	 * \param[in] scan  Pointer to the scan that has
	 *                  been received.
	 *///-------------------------------------
	virtual void onData(const LogMessageNote* const scan) = 0;
}; // LogMessageNoteListener

//======================================================================

} // namespace ibeo

//======================================================================

#endif // IBEOSDK_LOGMESSAGENOTELISTENER_HPP_SEEN

//======================================================================
