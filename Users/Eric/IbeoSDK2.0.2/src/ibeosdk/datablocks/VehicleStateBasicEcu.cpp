//======================================================================
/*! \file VehicleStateBasicEcu.cpp
 *
 * \copydoc Copyright
 * \author Jan Christian Dittmer (jcd)
 * \date Sep 2, 2013
 *///-------------------------------------------------------------------

#include <ibeosdk/datablocks/VehicleStateBasicEcu.hpp>
#include <ibeosdk/io.hpp>

//======================================================================

namespace ibeo {

//======================================================================

VehicleStateBasicEcu::VehicleStateBasicEcu()
  : m_microseconds(0),
    m_timestamp(0),
    m_xPos(0),
    m_yPos(0),
    m_courseAngle(.0f),
    m_longitudinalVelocity(.0f),
    m_yawRate(.0f),
    m_steeringWheelAngle(.0f),
    m_reserved0(.0f),
    m_frontWheelAngle(.0f),
    m_reserved1(0),
    m_vehicleWidth(.0f),
    m_reserved2(.0f),
    m_vehicleFrontToFrontAxle(.0f),
    m_frontAxleToRearAxle(.0f),
    m_rearAxleToVehicleRear(.0f),
    m_reserved3(.0f),
    m_stearRatioCoeff0(.0f),
    m_stearRatioCoeff1(.0f),
    m_stearRatioCoeff2(.0f),
    m_stearRatioCoeff3(.0f),
    m_reserved4(.0f)
{}

//======================================================================

VehicleStateBasicEcu::~VehicleStateBasicEcu() {}

//======================================================================

bool VehicleStateBasicEcu::deserialize(std::istream& is, const IbeoDataHeader& dh)
{
	const std::istream::pos_type startPos = is.tellg();

	lock();

	ibeo::readBE(is, m_microseconds);
	ibeo::readBE(is, m_timestamp);
	ibeo::readBE(is, m_xPos);
	ibeo::readBE(is, m_yPos);
	ibeo::readBE(is, m_courseAngle);
	ibeo::readBE(is, m_longitudinalVelocity);
	ibeo::readBE(is, m_yawRate);
	ibeo::readBE(is, m_steeringWheelAngle);
	ibeo::readBE(is, m_reserved0);
	ibeo::readBE(is, m_frontWheelAngle);
	ibeo::readBE(is, m_reserved1);
	ibeo::readBE(is, m_vehicleWidth);
	ibeo::readBE(is, m_reserved2);
	ibeo::readBE(is, m_vehicleFrontToFrontAxle);
	ibeo::readBE(is, m_frontAxleToRearAxle);
	ibeo::readBE(is, m_rearAxleToVehicleRear);
	ibeo::readBE(is, m_reserved3);
	ibeo::readBE(is, m_stearRatioCoeff0);
	ibeo::readBE(is, m_stearRatioCoeff1);
	ibeo::readBE(is, m_stearRatioCoeff2);
	ibeo::readBE(is, m_stearRatioCoeff3);
	ibeo::readBE(is, m_reserved4);

	unlock();

	return !is.fail()
	       && ((is.tellg() - startPos) == this->getSerializedSize())
	       && this->getSerializedSize() == dh.getMessageSize();}

//======================================================================

bool VehicleStateBasicEcu::serialize(std::ostream& os) const
{
	const std::istream::pos_type startPos = os.tellp();

	lock();

	ibeo::writeBE(os, m_microseconds);
	ibeo::writeBE(os, m_timestamp);
	ibeo::writeBE(os, m_xPos);
	ibeo::writeBE(os, m_yPos);
	ibeo::writeBE(os, m_courseAngle);
	ibeo::writeBE(os, m_longitudinalVelocity);
	ibeo::writeBE(os, m_yawRate);
	ibeo::writeBE(os, m_steeringWheelAngle);
	ibeo::writeBE(os, m_reserved0);
	ibeo::writeBE(os, m_frontWheelAngle);
	ibeo::writeBE(os, m_reserved1);
	ibeo::writeBE(os, m_vehicleWidth);
	ibeo::writeBE(os, m_reserved2);
	ibeo::writeBE(os, m_vehicleFrontToFrontAxle);
	ibeo::writeBE(os, m_frontAxleToRearAxle);
	ibeo::writeBE(os, m_rearAxleToVehicleRear);
	ibeo::writeBE(os, m_reserved3);
	ibeo::writeBE(os, m_stearRatioCoeff0);
	ibeo::writeBE(os, m_stearRatioCoeff1);
	ibeo::writeBE(os, m_stearRatioCoeff2);
	ibeo::writeBE(os, m_stearRatioCoeff3);
	ibeo::writeBE(os, m_reserved4);

	unlock();

	return !os.fail() && ((os.tellp() - startPos) == this->getSerializedSize());
}

//======================================================================

} // namespace ibeo

//======================================================================
