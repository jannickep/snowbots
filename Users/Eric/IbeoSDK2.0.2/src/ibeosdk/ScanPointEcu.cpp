//======================================================================
/*! \file ScanPointEcu.cpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date Apr 26, 2012
 *///-------------------------------------------------------------------

#include <ibeosdk/ScanPointEcu.hpp>
#include <ibeosdk/io.hpp>

//======================================================================

namespace ibeo {

//======================================================================

ScanPointEcu::ScanPointEcu()
  : m_posX(0.),
    m_posY(0.),
    m_posZ(0.),
    m_epw(0.),
    m_deviceId(0),
    m_layer(0),
    m_echo(0),
    m_reserved(0),
    m_timeOffset(0),
    m_flags(0),
    m_segmentId(0)
{}

//======================================================================

ScanPointEcu::ScanPointEcu(const ScanPointEcu& other)
  : m_posX(other.m_posX),
    m_posY(other.m_posY),
    m_posZ(other.m_posZ),
    m_epw(other.m_epw),
    m_deviceId(other.m_deviceId),
    m_layer(other.m_layer),
    m_echo(other.m_echo),
    m_reserved(other.m_reserved),
    m_timeOffset(other.m_timeOffset),
    m_flags(other.m_flags),
    m_segmentId(other.m_segmentId)
{}

//======================================================================

ScanPointEcu& ScanPointEcu::operator=(const ScanPointEcu& other)
{
	m_posX = other.m_posX;
	m_posY = other.m_posY;
	m_posZ = other.m_posZ;
	m_epw = other.m_epw;
	m_deviceId = other.m_deviceId;
	m_layer = other.m_layer;
	m_echo = other.m_echo;
	m_reserved = other.m_reserved;
	m_timeOffset = other.m_timeOffset;
	m_flags = other.m_flags;
	m_segmentId = other.m_segmentId;

  return *this;
}

//======================================================================

ScanPointEcu::~ScanPointEcu() {}

//======================================================================

bool ScanPointEcu::deserialize(std::istream& is)
{
	const std::istream::pos_type startPos = is.tellg();

	ibeo::readBE(is, m_posX);
	ibeo::readBE(is, m_posY);
	ibeo::readBE(is, m_posZ);

	ibeo::readBE(is, m_epw);

	ibeo::readBE(is, m_deviceId);
	ibeo::readBE(is, m_layer);
	ibeo::readBE(is, m_echo);

	ibeo::readBE(is, m_reserved);

	ibeo::readBE(is, m_timeOffset);
	ibeo::readBE(is, m_flags);
	ibeo::readBE(is, m_segmentId);

	return !is.fail() && ((is.tellg() - startPos) == this->getSerializedSize());
}

//======================================================================

//static
std::streamsize ScanPointEcu::getSerializedSize_static()
{
	return
		4*sizeof(float)
		+ 3*sizeof(UINT8) + 1
		+ sizeof(UINT32)
		+ sizeof(UINT16) + 2;
}

//======================================================================

bool ScanPointEcu::serialize(std::ostream& os) const
{
	const std::istream::pos_type startPos = os.tellp();

	ibeo::writeBE(os, m_posX);
	ibeo::writeBE(os, m_posY);
	ibeo::writeBE(os, m_posZ);

	ibeo::writeBE(os, m_epw);

	ibeo::writeBE(os, m_deviceId);
	ibeo::writeBE(os, m_layer);
	ibeo::writeBE(os, m_echo);

	ibeo::writeBE(os, m_reserved);

	ibeo::writeBE(os, m_timeOffset);
	ibeo::writeBE(os, m_flags);

	ibeo::writeBE(os, m_segmentId);

	return !os.fail() && ((os.tellp() - startPos) == this->getSerializedSize());
}

//======================================================================

} // namespace ibeo

//======================================================================

