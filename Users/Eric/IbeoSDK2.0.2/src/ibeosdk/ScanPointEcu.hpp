//======================================================================
/*! \file ScanPointEcu.hpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date Apr 26, 2012
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_SCANPOINTECU_HPP_SEEN
#define IBEOSDK_SCANPOINTECU_HPP_SEEN

//======================================================================

#include <ibeosdk/misc/WinCompatibility.hpp>

#include <ibeosdk/misc/Serializable.hpp>
#include <ibeosdk/inttypes.hpp>

//======================================================================

namespace ibeo {

//======================================================================

class ScanPointEcu : public Serializable {
public:
	//======================================================================

	enum EcuScanPointFlags {
		ESPF_Ground             = 0x0001,  ///< Invalid scan point, echo from ground
		ESPF_Dirt               = 0x0002,  ///< Invalid scan point, echo from dirt
		ESPF_Rain               = 0x0004,  ///< Invalid scan point, echo from rain drop
		// 0x0008 unused
		ESPF_ThresholdSwitching = 0x0010,  ///< Scan point was measured using the higher threshold (since FGPA version 8.0.08)
		                                   ///< Old: Scan point was measured in a shot with threshold switching (earlier FPGA versions)
		ESPF_Reflector          = 0x0020,  ///< EPW of scan point is high enough to be a reflector
		ESPF_NearRange          = 0x0040,  ///< Scan point is measured in near range. Flag is set by FPGA according threshold switching time.
		// 0x0080 unused
		ESPF_LeftCovered        = 0x0100,  ///< Left neighbour point may be covered
		ESPF_RightCovered       = 0x0200,  ///< Right neighbour point may be covered
		ESPF_Background         = 0x0400,  ///< Point has been recognized as background and should not be used in the tracking anymore
		ESPF_Marker             = 0x0800,  ///< Point is "marked" (see above)
		ESPF_Transparent        = 0x1000,  ///< There is at least one more echo behind this scan point (B or C echo)
		// 0x2000 unused
		// 0x4000 unused
		// 0x8000 unused
		ESPF_MaskInvalid            = ESPF_Ground | ESPF_Dirt | ESPF_Rain | ESPF_Background,  ///< All flags of invalid scan points
		ESPF_MaskCovered            = ESPF_LeftCovered | ESPF_RightCovered                    ///< All coverage flags
	}; // EcuScanPointFlags

public:
	ScanPointEcu();
	ScanPointEcu(const ScanPointEcu& src);
	virtual ~ScanPointEcu();

	ScanPointEcu& operator= (const ScanPointEcu& src);
public:
	static std::streamsize getSerializedSize_static();

public:
	virtual std::streamsize getSerializedSize() const { return getSerializedSize_static(); }
	virtual bool deserialize(std::istream& is);
	virtual bool serialize(std::ostream& os) const;

public:
	float getPositionX() const { return m_posX; }
	float getPositionY() const { return m_posY; }
	float getPositionZ() const { return m_posZ; }

	float getEchoPulseWidth() const { return m_epw; }

	UINT8 getDeviceId() const { return m_deviceId; }

	UINT8 getLayer() const { return m_layer; }
	UINT8 getEcho() const { return m_echo; }

	UINT32 getTimeOffset() const { return m_timeOffset; }

	UINT16 getFlags() const { return m_flags; }

protected:
	float m_posX;
	float m_posY;
	float m_posZ;
	float m_epw;
	UINT8 m_deviceId;
	UINT8 m_layer;
	UINT8 m_echo;
	UINT8 m_reserved;
	UINT32 m_timeOffset;
	UINT16 m_flags; // combination of bits from EcuScanPointFlag
	UINT16 m_segmentId;
}; // scanPointEcu

//======================================================================

} // namespace ibeo

//======================================================================

#endif // IBEOSDK_SCANPOINTECU_HPP_SEEN

//======================================================================

