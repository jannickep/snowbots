//======================================================================
/*! \file ObjectListEcuET.cpp
 *
 * \copydoc Copyright
 * \author Jan Christian Dittmer (jcd)
 * \date Sep 5, 2013
 *///-------------------------------------------------------------------

#include <ibeosdk/datablocks/ObjectListEcuEt.hpp>
#include <ibeosdk/io.hpp>

//======================================================================

namespace ibeo {

//======================================================================

ObjectListEcuEt::ObjectListEcuEt()
  : m_scanMidTimestamp(),
    m_objects()
{}

//======================================================================

std::streamsize ObjectListEcuEt::getSerializedSize() const
{
	std::streamsize sz = sizeof(NTPTime) + sizeof(uint16_t);

	std::vector<ObjectEcuEt>::const_iterator objIter = m_objects.begin();
	for (; objIter != m_objects.end(); ++objIter) {
		sz += objIter->getSerializedSize();
	}

	return sz;
}

//======================================================================

bool ObjectListEcuEt::deserialize(std::istream& is, const IbeoDataHeader& dh)
{
	const std::istream::pos_type startPos = is.tellg();

	readBE(is, m_scanMidTimestamp);
	uint16_t nbOfObjects = 0;
	readBE(is, nbOfObjects);
	m_objects.resize(nbOfObjects);

	std::vector<ObjectEcuEt>::iterator objIter = m_objects.begin();
	for (; objIter != m_objects.end(); ++objIter) {
		objIter->deserialize(is);
	}

	return !is.fail()
	       && ((is.tellg() - startPos) == this->getSerializedSize())
	       && this->getSerializedSize() == dh.getMessageSize();
}

//======================================================================

bool ObjectListEcuEt::serialize(std::ostream& os) const
{
	const std::istream::pos_type startPos = os.tellp();

	writeBE(os, m_scanMidTimestamp);
	writeBE(os, uint16_t(m_objects.size()));

	std::vector<ObjectEcuEt>::const_iterator objIter = m_objects.begin();
	for (; objIter != m_objects.end(); ++objIter) {
		objIter->serialize(os);
	}

	return !os.fail() && ((os.tellp() - startPos) == this->getSerializedSize());
}

//======================================================================

} // namespace ibeo

//======================================================================
