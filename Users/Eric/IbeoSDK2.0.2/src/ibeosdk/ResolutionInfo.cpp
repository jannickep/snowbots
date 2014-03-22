//======================================================================
/*! \file ResolutionInfo.cpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date Apr 26, 2012
 *///-------------------------------------------------------------------

#include <ibeosdk/ResolutionInfo.hpp>
#include <ibeosdk/io.hpp>

//======================================================================

namespace ibeo {

//======================================================================

ResolutionInfo::ResolutionInfo()
  : m_resolutionStartAngle(0.0),
    m_resolution(0.0)
{}

//======================================================================

ResolutionInfo::ResolutionInfo(const ResolutionInfo& other)
  : m_resolutionStartAngle(other.m_resolutionStartAngle),
    m_resolution(other.m_resolution)
{}

//======================================================================

ResolutionInfo& ResolutionInfo::operator= (const ResolutionInfo& other)
{
	m_resolutionStartAngle = other.m_resolutionStartAngle;
	m_resolution = other.m_resolution;

	return *this;
}

//======================================================================

ResolutionInfo::~ResolutionInfo() {}

//======================================================================

//static
std::streamsize ResolutionInfo::getSerializedSize_static()
{
	return 2*sizeof(float);
}

//======================================================================

bool ResolutionInfo::deserialize(std::istream& is)
{
	const std::istream::pos_type startPos = is.tellg();

	ibeo::readBE(is, m_resolutionStartAngle);
	ibeo::readBE(is, m_resolution);

	return !is.fail() && ((is.tellg() - startPos) == this->getSerializedSize());
}

//======================================================================

bool ResolutionInfo::serialize(std::ostream& os) const
{
	const std::istream::pos_type startPos = os.tellp();

	ibeo::writeBE(os, m_resolutionStartAngle);
	ibeo::writeBE(os, m_resolution);

	return !os.fail() && ((os.tellp() - startPos) == this->getSerializedSize());
}

//======================================================================

} // namespace ibeo

//======================================================================
