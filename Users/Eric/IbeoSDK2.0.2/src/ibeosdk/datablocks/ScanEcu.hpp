//======================================================================
/*! \file ScanEcu.hpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date Apr 25, 2012
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_SCANECU_HPP_SEEN
#define IBEOSDK_SCANECU_HPP_SEEN

//======================================================================

#include <ibeosdk/misc/WinCompatibility.hpp>

#include <ibeosdk/datablocks/DataBlock.hpp>
#include <ibeosdk/IbeoDataHeader.hpp>
#include <ibeosdk/ScannerInfo.hpp>
#include <ibeosdk/ScanPointEcu.hpp>

#include <vector>

//======================================================================

namespace ibeo {

//======================================================================

class ScanEcu : public DataBlock {
public:
	ScanEcu();
	virtual ~ScanEcu();

public:
	virtual DataType getDataType() const { return DataType_EcuScan; }
	virtual bool deserialize(std::istream& is, const IbeoDataHeader& dh);
	virtual bool serialize(std::ostream& os) const;
	std::streamsize getSerializedSize() const;

public:
	NTPTime getStartTimestamp() const { return m_scanStartTime; }
	UINT32 getEndTimeOffset() const { return m_endTimeOffset; }
	UINT32 getFlags() const { return m_flags; }
	UINT16 getScanNumber() const { return m_scanNumber; }
	UINT8 getNumberOfScannerInfos() const { return m_nbOfScannerInfos; }
	const std::vector<ScannerInfo>& getScannerInfos() const { return m_scannerInfos; }
	std::vector<ScannerInfo>& getScannerInfos() { return m_scannerInfos; }

	UINT16 getNumberOfScanPoints() const { return m_nbOfScanPoints; }
	const std::vector<ScanPointEcu>& getScanPoints() const { return m_scanPoints; }
	std::vector<ScanPointEcu>& getScanPoints() { return m_scanPoints; }

public:
	void getStartTimestamp(const NTPTime newScanStartTime) { m_scanStartTime = newScanStartTime; }
	void getEndTimeOffset(const UINT32 newEndTimeOffset) { m_endTimeOffset = newEndTimeOffset; }
	void getFlags(const UINT32 newFlags) { m_flags = newFlags; }
	void getScanNumber(const UINT16 newScanNumber) { m_scanNumber = newScanNumber; }

protected:
	NTPTime m_scanStartTime;
	UINT32 m_endTimeOffset;
	UINT32 m_flags;
	UINT16 m_scanNumber;
	UINT16 m_nbOfScanPoints;
	UINT8 m_nbOfScannerInfos;
	// 3 bytes reserved
	std::vector<ScannerInfo> m_scannerInfos;
	std::vector<ScanPointEcu> m_scanPoints;
}; // ScanEcu

//======================================================================

} // namespace ibeo

//======================================================================

#endif // IBEOSDK_SCANECU_HPP_SEEN

//======================================================================

