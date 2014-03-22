//======================================================================
/*! \file ObjectListLux.hpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date Apr 26, 2012
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_OBJECTLISTLUX_HPP_SEEN
#define IBEOSDK_OBJECTLISTLUX_HPP_SEEN

//======================================================================

#include <ibeosdk/misc/WinCompatibility.hpp>

#include <ibeosdk/datablocks/DataBlock.hpp>
#include <ibeosdk/ObjectLux.hpp>
#include <ibeosdk/Time.hpp>
#include <ibeosdk/datatypes.hpp>

#include <vector>

//======================================================================

namespace ibeo {

//======================================================================

class ObjectListLux : public DataBlock {
public:
	ObjectListLux();
	ObjectListLux(const NTPTime scanStartTimeStamp);
	virtual ~ObjectListLux();


public:
	virtual std::streamsize getSerializedSize() const;
	virtual DataType getDataType() const { return DataType_LuxObjectList; }
	virtual bool deserialize(std::istream& is, const IbeoDataHeader& dh);
	virtual bool serialize(std::ostream& os) const;

public:
	UINT16 getNumberOfObjects() const { return m_objects.size(); }
	const std::vector<ObjectLux>& getObjects() const { return m_objects; }
	std::vector<ObjectLux>& getObjects() { return m_objects; }
	NTPTime getScanStartTimestamp() const { return m_scanStartTimestamp; }

	void addObject(const ObjectLux&);
	const ObjectLux* findObject(const UINT16 id) const;

public:
	void setScanStartTimeStamp(const NTPTime newScanStartTimeStamp) { m_scanStartTimestamp = newScanStartTimeStamp; }

protected:
	static const UINT16 maxLuxObjects = 63;

protected:
	NTPTime m_scanStartTimestamp;
	std::vector<ObjectLux> m_objects;
}; // ObjectListLux

//======================================================================

std::string getObjectIdsAsString(const ObjectListLux& objList);

//======================================================================

} // namespace ibeo

//======================================================================

#endif // IBEOSDK_OBJECTLISTLUX_HPP_SEEN

//======================================================================

