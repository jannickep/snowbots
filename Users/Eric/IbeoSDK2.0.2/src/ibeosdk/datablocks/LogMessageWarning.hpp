//======================================================================
/*! \file LogMessageWarning.hpp
 *
 * \copydoc Copyright
 * \author Jan Christian Dittmer (jcd)
 * \date Sep 30, 2013
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_LOGMESSAGEWARNING_HPP_SEEN
#define IBEOSDK_LOGMESSAGEWARNING_HPP_SEEN

//======================================================================

#include <ibeosdk/misc/WinCompatibility.hpp>

#include <ibeosdk/datablocks/LogMessageBase.hpp>

//======================================================================

namespace ibeo {

//======================================================================

class LogMessageWarning : public LogMessageBase {
public:
	LogMessageWarning(const TraceLevel traceLevel = TL_Off, const std::string msg = std::string())
	  : LogMessageBase(traceLevel, msg)
	{}

public:
	//========================================
	/*!\brief get the DataType of this DataBlock.
	 * \return DataType of this DataBlock.
	 *///-------------------------------------
	virtual DataType getDataType() const { return DataType_LogWarning; }
}; // LogMessageWarning

//======================================================================

} // namespace ibeo

//======================================================================

#endif // IBEOSDK_LOGMESSAGEWARNING_HPP_SEEN

//======================================================================
