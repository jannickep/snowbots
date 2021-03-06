//======================================================================
/*! \file LogFileManager.cpp
 *
 * \copydoc Copyright
 * \author Jan Christian Dittmer (jcd)
 * \date Jan 24, 2013
 *///-------------------------------------------------------------------

#include <ibeosdk/LogFileManager.hpp>

#include <iostream>
using namespace std;

//======================================================================

namespace ibeo {

//======================================================================

LogFileManager::LogFileManager()
  : m_splitRequested(false)
{}

//======================================================================

LogFileManager::~LogFileManager()
{
	LogFile::closeLogFile();
}

//======================================================================

bool LogFileManager::start()
{
	bool isOpen;
	std::ostream* logStream = &ibeo::LogFile::getLogFile(isOpen);
	if(isOpen && !logStream->fail() && !logStream->bad()) {
		ibeo::LogFile::m_logStream = logStream;
		std::cerr << "Successfully opened log file '" << ibeo::LogFile::m_currentFilename << "'" << std::endl;
	}
	else {
		std::cerr << "Failed to open log file '" << ibeo::LogFile::m_currentFilename << "' - using std::cerr" << std::endl;
		abort();
	}
	return true;
}

//======================================================================

void LogFileManager::checkSplitRequired(const DataType dt)
{
	if (dt != DataType_LuxScan && dt != DataType_EcuScan)
		return;

	bool doSplit = false;

	if (this->m_splitRequested) {
		logInfo << "Split of log file has been requested" << endl;
		doSplit = true;
	}
	else if (LogFile::hasFileTargetSizeBeenReached()) {
		std::cerr << "Logfile '" << LogFile::m_currentFilename
					<< "' reached size limit, starting a new one." << endl;
		doSplit = true;
	}

	if (doSplit) {
		LogFile::increaseIndex();

		for (unsigned int i = 0; i < m_splitFiles.size(); ++i) {
			m_splitFiles[i]->split(LogFile::m_logFileIndex);
		}

		this->m_splitRequested = false;
	} // doSplit
}

//======================================================================

void LogFileManager::splitRequest()
{
	this->m_splitRequested = true;
}

//======================================================================

int LogFileManager::registerSplitFile(SplitFile* splitFile)
{
	for (unsigned int i = 0; i < m_splitFiles.size(); ++i) {
		if (m_splitFiles.at(i) == splitFile)
			return -1;
	}
	this->m_splitFiles.push_back(splitFile);
	return LogFile::m_logFileIndex;
}

//======================================================================

bool LogFileManager::unregisterSplitFile(SplitFile* splitFile)
{
	std::vector<SplitFile*>::iterator sfIter = this->m_splitFiles.begin();
	for (; sfIter != this->m_splitFiles.end(); ++sfIter) {
		if (*sfIter == splitFile) {
			this->m_splitFiles.erase(sfIter);
			return true;
		}
	}
	return false;
}


//======================================================================

} // namespace ibeo

//======================================================================
