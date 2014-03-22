//======================================================================
/*! \file VehicleStateBasicLux.cpp
 *
 * \copydoc Copyright
 * \author Jan Christian Dittmer (jcd)
 * \date Sep 2, 2013
 *///-------------------------------------------------------------------

#include <ibeosdk/datablocks/VehicleStateBasicLux.hpp>
#include <ibeosdk/io.hpp>

//======================================================================

namespace ibeo {

//======================================================================

VehicleStateBasicLux::VehicleStateBasicLux()
  : m_timestamp(0),
    m_scanNumber(0),
    m_errorFlags(0),
    m_longitudinalVelocity(0),
    m_steeringWheeAngle(0),
    m_wheelAngle(0),
    m_reserved0(0),
    m_xPos(0),
    m_yPos(0),
    m_courseAngle(0),
    m_timeDiff(0),
    m_xDiff(0),
    m_yDiff(0),
    m_yaw(0),
    m_reserved1(0),
    m_currentYawRate(0),
    m_reserved2(0)
{}

//======================================================================

VehicleStateBasicLux::~VehicleStateBasicLux() {}

//======================================================================

bool VehicleStateBasicLux::deserialize(std::istream& is, const IbeoDataHeader& dh)
{
	const std::istream::pos_type startPos = is.tellg();

	lock();

	ibeo::readLE(is, m_timestamp);
	ibeo::readLE(is, m_scanNumber);
	ibeo::readLE(is, m_errorFlags);
	ibeo::readLE(is, m_longitudinalVelocity);
	ibeo::readLE(is, m_steeringWheeAngle);
	ibeo::readLE(is, m_wheelAngle);
	ibeo::readLE(is, m_reserved0);

	ibeo::readLE(is, m_xPos);
	ibeo::readLE(is, m_yPos);
	ibeo::readLE(is, m_courseAngle);

	ibeo::readLE(is, m_timeDiff);
	ibeo::readLE(is, m_xDiff);
	ibeo::readLE(is, m_yDiff);
	ibeo::readLE(is, m_yaw);

	ibeo::readLE(is, m_reserved1);
	ibeo::readLE(is, m_currentYawRate);
	ibeo::readLE(is, m_reserved2);

	unlock();

	return !is.fail()
	       && ((is.tellg() - startPos) == this->getSerializedSize())
	       && this->getSerializedSize() == dh.getMessageSize();}

//======================================================================

bool VehicleStateBasicLux::serialize(std::ostream& os) const
{
	const std::istream::pos_type startPos = os.tellp();

	lock();

	ibeo::writeLE(os, m_timestamp);
	ibeo::writeLE(os, m_scanNumber);
	ibeo::writeLE(os, m_errorFlags);
	ibeo::writeLE(os, m_longitudinalVelocity);
	ibeo::writeLE(os, m_steeringWheeAngle);
	ibeo::writeLE(os, m_wheelAngle);
	ibeo::writeLE(os, m_reserved0);

	ibeo::writeLE(os, m_xPos);
	ibeo::writeLE(os, m_yPos);
	ibeo::writeLE(os, m_courseAngle);

	ibeo::writeLE(os, m_timeDiff);
	ibeo::writeLE(os, m_xDiff);
	ibeo::writeLE(os, m_yDiff);
	ibeo::writeLE(os, m_yaw);

	ibeo::writeLE(os, m_reserved1);
	ibeo::writeLE(os, m_currentYawRate);
	ibeo::writeLE(os, m_reserved2);

	unlock();

	return !os.fail() && ((os.tellp() - startPos) == this->getSerializedSize());
}

//======================================================================

} // namespace ibeo

//======================================================================
