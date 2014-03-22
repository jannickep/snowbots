//======================================================================
/*! \file ScanLux.cpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date Apr 25, 2012
 *///-------------------------------------------------------------------

#include <ibeosdk/datablocks/ScanLux.hpp>
#include <ibeosdk/Log.hpp>
#include <ibeosdk/io.hpp>

//======================================================================

namespace ibeo {

//======================================================================

ScanLux::ScanLux()
  : m_scanNumber(0),
    m_scannerStatus(0),
    m_syncPhaseOffset(0),
    m_startNTP(0),
    m_endNTP(0),
    m_angleTicksPerRotation(0),
    m_startAngle(0),
    m_endAngle(0),

    m_mountingPosYawAngle(0),
    m_mountingPosPitchAngle(0),
    m_mountingPosRollAngle(0),
    m_mountingPosX(0),
    m_mountingPosY(0),
    m_mountingPosZ(0),
    m_flags(0),

    m_points()
{}


//======================================================================

ScanLux::~ScanLux() {}

//======================================================================
/**
 * Decoding scan data transmitted by ibeo LUX laserscanner family (data type 0x2202)
 *
 * @param is
 * @param source_is_big_endian
 * @return
 */
bool ScanLux::deserialize(std::istream& is, const IbeoDataHeader& dh)
{
	const std::istream::pos_type startPos = is.tellg();

	// Note: This data type is encoded by using Little Endian

	lock();
	m_points.clear();

	ibeo::readLE(is, m_scanNumber);
	ibeo::readLE(is, m_scannerStatus);
	ibeo::readLE(is, m_syncPhaseOffset);
	ibeo::readLE(is, m_startNTP);
	ibeo::readLE(is, m_endNTP);
	if (!this->timeCheck())
		return false;

	ibeo::readLE(is, m_angleTicksPerRotation);
	if (!nbOfAngleTicksPerRotationCheck())
		return false;

	ibeo::readLE(is, m_startAngle);
	ibeo::readLE(is, m_endAngle);
	if (!angleCheck())
		return false;

	{ // read the number of the scan points
		// and resize the point vector.
		UINT16 nbScanPts=0;
		ibeo::readLE(is, nbScanPts);
		// adjust the list size
		if (!nbOfPtsCheck(nbScanPts))
			return false;

		m_points.resize(nbScanPts);
	}

	ibeo::readLE(is, m_mountingPosYawAngle);
	ibeo::readLE(is, m_mountingPosPitchAngle);
	ibeo::readLE(is, m_mountingPosRollAngle);
	ibeo::readLE(is, m_mountingPosX);
	ibeo::readLE(is, m_mountingPosY);
	ibeo::readLE(is, m_mountingPosZ);
	ibeo::readLE(is, m_flags);

	std::vector<ScanPointLux>::iterator ptIter = m_points.begin();
	for (; ptIter != m_points.end();++ptIter) {
		ptIter->deserialize(is);
	}

	unlock();

	return !is.fail()
	       && ((is.tellg() - startPos) == this->getSerializedSize())
	       && this->getSerializedSize() == dh.getMessageSize();
}

//======================================================================

std::streamsize ScanLux::getSerializedSize() const
{
	return 3*sizeof(UINT16) + 2*sizeof(NTPTime) +
			2*sizeof(UINT16)+2*sizeof(INT16) +
			m_points.size() * ScanPointLux::getSerializedSize_static() +
			6*sizeof(UINT16) +
			sizeof(UINT16);
}

//======================================================================

bool ScanLux::serialize(std::ostream& os) const
{
	const std::istream::pos_type startPos = os.tellp();

	ibeo::writeLE(os, m_scanNumber);
	ibeo::writeLE(os, m_scannerStatus);
	ibeo::writeLE(os, m_syncPhaseOffset);
	ibeo::writeLE(os, m_startNTP);
	ibeo::writeLE(os, m_endNTP);
	ibeo::writeLE(os, m_angleTicksPerRotation);
	ibeo::writeLE(os, m_startAngle);
	ibeo::writeLE(os, m_endAngle);
	const UINT16 nbScanPts = m_points.size();
	ibeo::writeLE(os, nbScanPts);
	ibeo::writeLE(os, m_mountingPosYawAngle);
	ibeo::writeLE(os, m_mountingPosPitchAngle);
	ibeo::writeLE(os, m_mountingPosRollAngle);
	ibeo::writeLE(os, m_mountingPosX);
	ibeo::writeLE(os, m_mountingPosY);
	ibeo::writeLE(os, m_mountingPosZ);
	ibeo::writeLE(os, m_flags);

	for (int i=0; i < nbScanPts; ++i) {
		m_points[i].serialize(os);
	}

	return !os.fail() && ((os.tellp() - startPos) == this->getSerializedSize());
}

//======================================================================


bool ScanLux::timeCheck() const
{
	if (m_startNTP >= m_endNTP ) {
		logError << "Read scan #" << this->m_scanNumber
		    << ": Scan end time must be larger than scan start time."
		    << "  - discarding scan."
		    << std::endl;
		return false;
	}
	return true;
}

//======================================================================

bool ScanLux::nbOfAngleTicksPerRotationCheck() const
{
	if (m_angleTicksPerRotation != nbOfAngleTicksPerRotation) {
		logError << "Read scan #" << this->m_scanNumber
		    << ": number of angle ticks per rotation are " << this->m_angleTicksPerRotation
		    << " expected: " << nbOfAngleTicksPerRotation
		    << "  - discarding scan."
		    << std::endl;
		return false;
	}
	return true;
}

//======================================================================

bool ScanLux::angleCheck() const
{
	if (m_startAngle < angleRangeMin) {
		logError << "Read scan #" << this->m_scanNumber << ": "
		    << "Start angle " << m_startAngle << " smaller than min " << angleRangeMin
		    << " ticks"
		    << std::endl;
		return false;
	}
	if (m_startAngle > angleRangeMax) {
		logError << "Read scan #" << this->m_scanNumber << ": "
		    << "Start angle " << m_startAngle << " larger than max " << angleRangeMax
		    << " ticks"
		    << std::endl;
		return false;
	}
	if (m_endAngle < angleRangeMin) {
		logError << "Read scan #" << this->m_scanNumber << ": "
		    << "Start angle " << m_endAngle << " smaller than min " << angleRangeMin
		    << " ticks"
		    << std::endl;
		return false;
	}
	if (m_endAngle > angleRangeMax) {
		logError << "Read scan #" << this->m_scanNumber << ": "
		    << "Start angle " << m_endAngle << " larger than max " << angleRangeMax
		    << " ticks"
		    << std::endl;
		return false;
	}

	if (m_startAngle<=m_endAngle) {
		logError << "Read scan #" << this->m_scanNumber << ": "
		    << "Start angle (" << m_startAngle << " ticks) is smaller than "
		    << " end angle (" << m_endAngle << " ticks)"
		    << std::endl;
		return false;
	}
	return true;

}

//======================================================================

bool ScanLux::nbOfPtsCheck(const UINT16 nbScanPts) const
{
	if (nbScanPts > maxNbOfScanPts) {
		logError << "Read scan #" << this->m_scanNumber
		    << ": number of scan points " << nbScanPts
		    << " maximal expected is " << maxNbOfScanPts
		    << "  - discarding scan."
		    << std::endl;
		return false;
	}
	return true;
}

//======================================================================

} // namespace ibeo

//======================================================================

