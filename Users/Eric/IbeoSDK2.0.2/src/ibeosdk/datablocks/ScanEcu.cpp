//======================================================================
/*! \file ScanEcu.cpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date Apr 25, 2012
 *///-------------------------------------------------------------------

#include <ibeosdk/datablocks/ScanEcu.hpp>
#include <ibeosdk/io.hpp>

//======================================================================

namespace ibeo {

//======================================================================

ScanEcu::ScanEcu()
  : m_scanStartTime(),
    m_endTimeOffset(),
    m_flags(),
    m_scanNumber(),
    m_nbOfScanPoints(0),
    m_nbOfScannerInfos(),
    m_scannerInfos(8),
    m_scanPoints(1024)
{}

//======================================================================

ScanEcu::~ScanEcu() {}

//======================================================================

bool ScanEcu::deserialize(std::istream& is, const IbeoDataHeader& dh)
{
	const std::istream::pos_type startPos = is.tellg();

	lock();

	ibeo::readBE(is, m_scanStartTime);
	ibeo::readBE(is, m_endTimeOffset);

	ibeo::readBE(is, m_flags);
	ibeo::readBE(is, m_scanNumber);
	ibeo::readBE(is, m_nbOfScanPoints);
	ibeo::readBE(is, m_nbOfScannerInfos);

	is.ignore(3); // 3 bytes reserved

	if (m_scannerInfos.size() != m_nbOfScannerInfos)
		m_scannerInfos.resize(m_nbOfScannerInfos);

	for (int i=0; i<m_nbOfScannerInfos; i++) {
		m_scannerInfos[i].deserialize(is);
	}

	m_scanPoints.resize(m_nbOfScanPoints);

	for (int i=0; i<m_nbOfScanPoints; i++) {
		m_scanPoints[i].deserialize(is);
	}

	unlock();

	return !is.fail()
	       && ((is.tellg() - startPos) == this->getSerializedSize())
	       && this->getSerializedSize() == dh.getMessageSize();
}

//======================================================================

bool ScanEcu::serialize(std::ostream& os) const
{
	const std::istream::pos_type startPos = os.tellp();

	lock();

	ibeo::writeBE(os, m_scanStartTime);
	ibeo::writeBE(os, m_endTimeOffset);

	ibeo::writeBE(os, m_flags);
	ibeo::writeBE(os, m_scanNumber);
	ibeo::writeBE(os, m_nbOfScanPoints);
	ibeo::writeBE(os, m_nbOfScannerInfos);

	UINT8 b=0;
	os << b << b << b; // 3 bytes reserved

	for (int i=0; i<m_nbOfScannerInfos; i++) {
		m_scannerInfos[i].serialize(os);
	}

	for (int i=0; i<m_nbOfScanPoints; i++) {
		m_scanPoints[i].serialize(os);
	}

	unlock();

	return !os.fail() && ((os.tellp() - startPos) == this->getSerializedSize());
}

//======================================================================

std::streamsize ScanEcu::getSerializedSize() const
{
	return sizeof(NTPTime) + 2*sizeof(UINT32) +
			2*sizeof(UINT16) + sizeof(UINT8)
			+ 3
			+ m_nbOfScannerInfos * ScannerInfo::getSerializedSize_static()
			+ this->m_nbOfScanPoints * ScanPointEcu::getSerializedSize_static();
}

//======================================================================

} // namespace ibeo

//======================================================================
