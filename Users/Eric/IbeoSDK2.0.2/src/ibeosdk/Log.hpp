//======================================================================
/*! \file Log.hpp
 *
 * \copydoc Copyright
 * \author Jan Christian Dittmer (jcd)
 * \date Jun 8, 2012
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_LOG_HPP_SEEN
#define IBEOSDK_LOG_HPP_SEEN

//======================================================================

#include <ibeosdk/misc/WinCompatibility.hpp>

#include <ibeosdk/Convert.hpp>
#include <ibeosdk/Time.hpp>

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

//======================================================================

typedef struct stat Stat;

namespace ibeo {

//======================================================================

enum LogLevel {
	LogLevel_Error,
	LogLevel_Warning,
	LogLevel_Info,
	LogLevel_InfoDetails,
	LogLevel_Debug,
	LogLevel_Debug2
}; // LogLevel

//======================================================================

LogLevel logLevelFromString(const std::string& llStr);

//======================================================================

class LogFile : public std::ofstream {
public:
	static bool setLogFileIndex(const int index);
	static bool increaseIndex() { return LogFile::setLogFileIndex(++LogFile::m_logFileIndex); }

	static std::ostream& getLogFile(bool& ok);
	static bool setLogFileBaseName(const std::string& baseFilename);
	static void setLogLevel(const LogLevel newLogLevel);
	static void setTargetFileSize(const off_t newTargetFileSize);

	static void closeLogFile();

	static bool hasFileTargetSizeBeenReached();

	static const std::string& getCurrentFilename() { return LogFile::m_currentFilename; }

public:
	//========================================

	static
	inline std::ostream& log(const std::string& intro,
	                         const char* const file,
	                         const char* const func,
	                         const int line)
	{
		m_logStream->clear();
		return (*m_logStream) << intro << " - " << file << "::" << func << "(" << line << "): ";
	}

	//========================================
	static
	std::ostream& _log(const LogLevel ll,
	                   const std::string& intro,
	                   const char* const file,
	                   const char* const func,
	                   const int line);

	//========================================

	static
	inline std::ostream& _logError(const char* const file,
	                               const char* const func,
	                               const int line)
	{ return _log(LogLevel_Error, "Error ", file, func, line); }

	static
	inline std::ostream& _logWarning(const char* const file,
	                               const char* const func,
	                               const int line)
	{ return _log(LogLevel_Warning, "Warning ", file, func, line); }

	static
	inline std::ostream& _logInfo(const char* const file,
	                               const char* const func,
	                               const int line)
	{ return _log(LogLevel_Info, "Info ", file, func, line); }

	static
	inline std::ostream& _logInfoDetails(const char* const file,
	                                     const char* const func,
	                                     const int line)
	{ return _log(LogLevel_InfoDetails, "InfoDetails ", file, func, line); }

	static
	inline std::ostream& _logDebug(const char* const file,
	                               const char* const func,
	                               const int line)
	{ return _log(LogLevel_Debug, "Debug ", file, func, line); }

	static
	inline std::ostream& _logDebug2(const char* const file,
	                               const char* const func,
	                               const int line)
	{ return _log(LogLevel_Debug2, "Debug2 ", file, func, line); }

public:
	static std::ostream* m_logStream;
	static std::string m_filenameTemplate;
	static std::string m_currentFilename;
	static int m_logFileIndex;
	static off_t m_logFileTargetSize;
	static LogLevel m_logLevel;
	static TimeConversion timeConversion;
protected:
	static Stat m_fileStat;
}; // LogFile


//======================================================================

inline std::ostream& log(const std::string& intro,
                         const char* const file,
                         const char* const func,
                         const int line)
{
	std::cerr.clear();
	return std::cerr << intro << " - " << file << "::" << func << "(" << line << "): ";
}

//======================================================================

#define logError LogFile::_logError(__FILE__, __func__, __LINE__)
#define logInfo LogFile::_logInfo(__FILE__, __func__, __LINE__)
#define logInfoDetails LogFile::_logInfoDetails(__FILE__, __func__, __LINE__)
#define logWarning LogFile::_logWarning(__FILE__, __func__, __LINE__)
#define logDebug LogFile::_logDebug(__FILE__, __func__, __LINE__)
#define logDebug2 LogFile::_logDebug2(__FILE__, __func__, __LINE__)

//======================================================================

} // namespace ibeo

//======================================================================

#include "SdkAbort.hpp"

//======================================================================

#endif // IBEOSDK_LOG_HPP_SEEN

//======================================================================
