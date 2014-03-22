//======================================================================
/*! \file LogMessageError.hpp
 *
 * \copydoc Copyright
 * \author Jan Christian Dittmer (jcd)
 * \date Sep 30, 2013
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_LOGMESSAGEERROR_HPP_SEEN
#define IBEOSDK_LOGMESSAGEERROR_HPP_SEEN

//======================================================================

#include <ibeosdk/misc/WinCompatibility.hpp>

#include <ibeosdk/datablocks/LogMessageBase.hpp>

//======================================================================

namespace ibeo {

//======================================================================

class LogMessageError : public LogMessageBase {
public:
	LogMessageError(const TraceLevel traceLevel = TL_Off, const std::string msg = std::string())
	  : LogMessageBase(traceLevel, msg)
	{}

public:
	//========================================
	/*!\brief get the DataType of this DataBlock.
	 * \return DataType of this DataBlock.
	 *///-------------------------------------
	virtual DataType getDataType() const { return DataType_LogError; }
}; // LogMessageError

//======================================================================

} // namespace ibeo

//======================================================================

#endif // IBEOSDK_LOGMESSAGEERROR_HPP_SEEN

//======================================================================
