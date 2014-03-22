//======================================================================
/*! \file ScannerInfo.cpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date Apr 26, 2012
 *///-------------------------------------------------------------------

#include <ibeosdk/ScannerInfo.hpp>
#include <ibeosdk/io.hpp>

//======================================================================

namespace ibeo {

//======================================================================

ScannerInfo::ScannerInfo()
  : m_deviceId(0),
    m_scannerType(ScannerType_Invalid),
    m_scanNumber(0),
    m_scannerStatus(0),
    m_startAngle(0.),
    m_endAngle(0.),
    m_scanStartTime(0),
    m_scanEndTime(0),
    m_scanStartTimeFromDevice(0),
    m_scanEndTimeFromDevice(0),
    m_scanFrequency(0.),
    m_beamTilt(0.),
    m_scanFlags(0),
    m_yawAngle(0.),
    m_pitchAngle(0.),
    m_rollAngle(0.),
    m_offsetX(0.),
    m_offsetY(0.),
    m_offsetZ(0.),
    m_ri(8)
{}

//======================================================================

ScannerInfo::ScannerInfo(const ScannerInfo& other)
  : m_deviceId(other.m_deviceId),
    m_scannerType(other.m_scannerType),
    m_scanNumber(other.m_scanNumber),
    m_scannerStatus(other.m_scannerStatus),
    m_startAngle(other.m_startAngle),
    m_endAngle(other.m_endAngle),
    m_scanStartTime(other.m_scanStartTime),
    m_scanEndTime(other.m_scanEndTime),
    m_scanStartTimeFromDevice(other.m_scanStartTimeFromDevice),
    m_scanEndTimeFromDevice(other.m_scanEndTimeFromDevice),
    m_scanFrequency(other.m_scanFrequency),
    m_beamTilt(other.m_beamTilt),
    m_scanFlags(other.m_scanFlags),
    m_yawAngle(other.m_yawAngle),
    m_pitchAngle(other.m_pitchAngle),
    m_rollAngle(other.m_rollAngle),

    m_offsetX(other.m_offsetX),
    m_offsetY(other.m_offsetY),
    m_offsetZ(other.m_offsetZ),
    m_ri(other.m_ri.size()) // only set the size here
{
	m_ri = other.m_ri;
}

//======================================================================

ScannerInfo& ScannerInfo::operator=(const ScannerInfo& other)
{
	if (this != &other) {
		m_scannerType = other.m_scannerType;
		m_scanNumber = other.m_scanNumber;

		m_scannerStatus = other.m_scannerStatus;

		m_startAngle = other.m_startAngle;
		m_endAngle = other.m_endAngle;

		m_scanStartTime = other.m_scanStartTime;
		m_scanEndTime = other.m_scanEndTime;

		m_scanStartTimeFromDevice = other.m_scanStartTimeFromDevice;
		m_scanEndTimeFromDevice = other.m_scanEndTimeFromDevice;

		m_scanFrequency = other.m_scanFrequency;
		m_beamTilt = other.m_beamTilt;
		m_scanFlags = other.m_scanFlags;

		m_yawAngle = other.m_yawAngle;
		m_pitchAngle = other.m_pitchAngle;
		m_rollAngle = other.m_rollAngle;

		m_offsetX = other.m_offsetX;
		m_offsetY = other.m_offsetY;
		m_offsetZ = other.m_offsetZ;

		m_ri = other.m_ri;
	}

	return *this;
}

//======================================================================

ScannerInfo::~ScannerInfo() {}

//======================================================================

bool ScannerInfo::deserialize(std::istream& is)
{
	const std::istream::pos_type startPos = is.tellg();

	ibeo::readBE(is, m_deviceId);

	UINT8 st;
	ibeo::readBE(is, st);
	switch(st) {
	case 3:  m_scannerType = ScannerType_AlascaXT;     break;
	case 4:  m_scannerType = ScannerType_Ecu;          break;
	case 5:  m_scannerType = ScannerType_LuxPrototype; break;
	case 6:  m_scannerType = ScannerType_Lux;          break;
	default: m_scannerType = ScannerType_Invalid;      break;
	}

	ibeo::readBE(is, m_scanNumber);

	ibeo::readBE(is, m_scannerStatus);

	ibeo::readBE(is, m_startAngle);
	ibeo::readBE(is, m_endAngle);

	ibeo::readBE(is, m_scanStartTime);
	ibeo::readBE(is, m_scanEndTime);

	ibeo::readBE(is, m_scanStartTimeFromDevice);
	ibeo::readBE(is, m_scanEndTimeFromDevice);

	ibeo::readBE(is, m_scanFrequency);
	ibeo::readBE(is, m_beamTilt);

	ibeo::readBE(is, m_scanFlags);

	ibeo::readBE(is, m_yawAngle);
	ibeo::readBE(is, m_pitchAngle);
	ibeo::readBE(is, m_rollAngle);

	ibeo::readBE(is, m_offsetX);
	ibeo::readBE(is, m_offsetY);
	ibeo::readBE(is, m_offsetZ);

	for (int i=0; i<nbOfResolutionInfo; i++) {
		m_ri[i].deserialize(is);
	}

	return !is.fail() && ((is.tellg() - startPos) == this->getSerializedSize());
}
//======================================================================

//static
std::streamsize ScannerInfo::getSerializedSize_static()
{
	return 2 * sizeof(UINT8)
		+ sizeof(UINT16)
		+ sizeof(UINT32)
		+ 2*sizeof(float)
		+ 4*sizeof(NTPTime)
		+ 2*sizeof(float)
		+ sizeof(UINT32)
		+ 6*sizeof(float)
		+ 8* ResolutionInfo::getSerializedSize_static();
}

//======================================================================

bool ScannerInfo::serialize(std::ostream& os) const
{
	const std::istream::pos_type startPos = os.tellp();

	ibeo::writeBE(os, m_deviceId);

	UINT8 st = m_scannerType;
	ibeo::writeBE(os, st);

	ibeo::writeBE(os, m_scanNumber);

	ibeo::writeBE(os, m_scannerStatus);

	ibeo::writeBE(os, m_startAngle);
	ibeo::writeBE(os, m_endAngle);

	ibeo::writeBE(os, m_scanStartTime);
	ibeo::writeBE(os, m_scanEndTime);

	ibeo::writeBE(os, m_scanStartTimeFromDevice);
	ibeo::writeBE(os, m_scanEndTimeFromDevice);

	ibeo::writeBE(os, m_scanFrequency);
	ibeo::writeBE(os, m_beamTilt);

	ibeo::writeBE(os, m_scanFlags);

	ibeo::writeBE(os, m_yawAngle);
	ibeo::writeBE(os, m_pitchAngle);
	ibeo::writeBE(os, m_rollAngle);

	ibeo::writeBE(os, m_offsetX);
	ibeo::writeBE(os, m_offsetY);
	ibeo::writeBE(os, m_offsetZ);

	for (int i=0; i<nbOfResolutionInfo; i++) {
		m_ri[i].serialize(os);
	}

	return !os.fail() && ((os.tellp() - startPos) == this->getSerializedSize());
}

//======================================================================

} // namespace ibeo

//======================================================================
