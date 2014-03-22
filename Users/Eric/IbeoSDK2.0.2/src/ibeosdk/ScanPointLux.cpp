//======================================================================
/*! \file ScanPointLux.cpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date Apr 25, 2012
 *///-------------------------------------------------------------------

#include <ibeosdk/ScanPointLux.hpp>
#include <ibeosdk/Log.hpp>
#include <ibeosdk/io.hpp>

//======================================================================

namespace ibeo {

//======================================================================

ScanPointLux::ScanPointLux() {}

//======================================================================

ScanPointLux::ScanPointLux(const ScanPointLux& src)
  : m_layer(src.m_layer),
    m_echo(src.m_echo),
    m_flags(src.m_flags),
    m_angle(src.m_angle),
    m_distance(src.m_distance),
    m_epw(src.m_epw),
    m_reserved(src.m_reserved)
{}

//======================================================================

ScanPointLux& ScanPointLux::operator= (const ScanPointLux& src)
{
	if (&src != this) {
		m_layer = src.m_layer;
		m_echo = src.m_echo;
		m_flags = src.m_flags;
		m_angle = src.m_angle;
		m_distance = src.m_distance;
		m_epw = src.m_epw;
		m_reserved = src.m_reserved;
	}

	return *this;
}

//======================================================================

ScanPointLux::~ScanPointLux() {}

//======================================================================

// static
std::streamsize ScanPointLux::getSerializedSize_static()
{
	return 2 * sizeof(UINT8) + 3* sizeof(UINT16) + 2;
}

//======================================================================

bool ScanPointLux::deserialize(std::istream& is)
{
	const std::istream::pos_type startPos = is.tellg();

	BYTE layerAndEcho;
	ibeo::readLE(is,layerAndEcho);
	m_layer = layerAndEcho & 0xF;
	m_echo = (layerAndEcho >> 4) & 0xF;
	ibeo::readLE(is, m_flags);
	ibeo::readLE(is, m_angle);
	ibeo::readLE(is, m_distance);

	ibeo::readLE(is, m_epw);
	ibeo::readLE(is,m_reserved);

	return !is.fail() && ((is.tellg() - startPos) == this->getSerializedSize());
}

//======================================================================

bool ScanPointLux::serialize(std::ostream& os) const
{
	const std::istream::pos_type startPos = os.tellp();

	const BYTE layerAndEcho = (m_echo << 4) | (m_layer & 0xF);
	ibeo::writeLE(os, layerAndEcho);
	ibeo::writeLE(os, m_flags);
	ibeo::writeLE(os, m_angle);
	ibeo::writeLE(os, m_distance);
	ibeo::writeLE(os, m_epw);
	ibeo::writeLE(os, m_reserved);

	return !os.fail() && ((os.tellp() - startPos) == this->getSerializedSize());
}

//======================================================================

} // namespace ibeo

//======================================================================

