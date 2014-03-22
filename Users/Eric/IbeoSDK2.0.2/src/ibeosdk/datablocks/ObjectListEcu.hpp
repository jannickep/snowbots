//======================================================================
/*! \file ObjectListEcu.hpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date Apr 26, 2012
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_OBJECTLISTECU_HPP_SEEN
#define IBEOSDK_OBJECTLISTECU_HPP_SEEN

//======================================================================

#include <ibeosdk/misc/WinCompatibility.hpp>

#include <ibeosdk/datablocks/DataBlock.hpp>
#include <ibeosdk/ObjectEcu.hpp>
#include <ibeosdk/Time.hpp>
#include <ibeosdk/datatypes.hpp>

#include <vector>

//======================================================================

namespace ibeo {

//======================================================================

class ObjectListEcu : public DataBlock {
public:
	ObjectListEcu();

public:
	virtual std::streamsize getSerializedSize() const;
	virtual DataType getDataType() const { return DataType_EcuObjectList; }
	virtual bool deserialize(std::istream& is, const IbeoDataHeader& dh);
	virtual bool serialize(std::ostream& os) const;

public:
	NTPTime getScanStartTimestamp() const { return m_scanStartTimestamp; }
	UINT16 getNumberOfObjects() const { return m_objects.size(); }
	const std::vector<ObjectEcu>& getObjects() const { return m_objects; }
	std::vector<ObjectEcu>& getObjects() { return m_objects; }

public:
	void setScanStartTimestamp(const NTPTime newScanStartTimeStamp) { m_scanStartTimestamp = newScanStartTimeStamp; }

protected:
	// TODO: Check this figure
	static const UINT16 maxEcuObjects = 50;

protected:
	NTPTime m_scanStartTimestamp;
	std::vector<ObjectEcu> m_objects;
}; // ObjectListEcu

//======================================================================

std::string getObjectIdsAsString(const ObjectListEcu& objList);

//======================================================================

} // namespace ibeo

//======================================================================

#endif // IBEOSDK_OBJECTLISTECU_HPP_SEEN

//======================================================================

