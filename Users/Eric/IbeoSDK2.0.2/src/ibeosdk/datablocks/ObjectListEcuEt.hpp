//======================================================================
/*! \file ObjectListEcuET.cpp
 *
 * \copydoc Copyright
 * \author Jan Christian Dittmer (jcd)
 * \date Sep 5, 2013
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_OBJECTLISTECUET_HPP_SEEN
#define IBEOSDK_OBJECTLISTECUET_HPP_SEEN

//======================================================================

#include <ibeosdk/misc/WinCompatibility.hpp>

#include <ibeosdk/ObjectEcuEt.hpp>
#include <ibeosdk/datablocks/DataBlock.hpp>
#include <ibeosdk/Time.hpp>
#include <ibeosdk/datatypes.hpp>

#include <vector>

//======================================================================

namespace ibeo {

//======================================================================

class ObjectListEcuEt : public ibeo::DataBlock {
public:
	ObjectListEcuEt();

public:
	virtual std::streamsize getSerializedSize() const;
	virtual DataType getDataType() const { return DataType_EcuObjectListET; }
	virtual bool deserialize(std::istream& is, const IbeoDataHeader& dh);
	virtual bool serialize(std::ostream& os) const;

public:
	NTPTime getScanMidTimestamp() const { return m_scanMidTimestamp; }
	int getNbOfObjects() const { return m_objects.size(); }
	const std::vector<ObjectEcuEt> getObjects() const { return m_objects; }
	std::vector<ObjectEcuEt> getObjects() { return m_objects; }

protected:
	NTPTime m_scanMidTimestamp;
	// number of objects uint16_t
	std::vector<ObjectEcuEt> m_objects;
}; // ObjectListEcuET

//======================================================================

}// namespace ibeo

//======================================================================

#endif // IBEOSDK_OBJECTLISTECUET_HPP_SEEN

//======================================================================
