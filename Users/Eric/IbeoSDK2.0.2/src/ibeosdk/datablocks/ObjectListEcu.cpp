//======================================================================
/*! \file ObjectListEcu.cpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date Apr 26, 2012
 *///-------------------------------------------------------------------

#include <ibeosdk/datablocks/ObjectListEcu.hpp>
#include <ibeosdk/Log.hpp>
#include <ibeosdk/io.hpp>

//======================================================================

namespace ibeo {

//======================================================================

ObjectListEcu::ObjectListEcu()
  : m_scanStartTimestamp(),
    m_objects()
{
	m_objects.reserve(maxEcuObjects);
}

//======================================================================

std::streamsize ObjectListEcu::getSerializedSize() const
{
	std::streamsize sz = sizeof(NTPTime) + sizeof(UINT16);

	std::vector<ObjectEcu>::const_iterator objIter = m_objects.begin();
	for (; objIter != m_objects.end(); ++objIter) {
		sz += objIter->getSerializedSize();
	}
	return sz;
}

//======================================================================

bool ObjectListEcu::deserialize(std::istream& is, const IbeoDataHeader& dh)
{
	const std::istream::pos_type startPos = is.tellg();

	lock();

	ibeo::readBE(is, m_scanStartTimestamp);

	{
		UINT16 nbOfObjects;
		ibeo::readBE(is, nbOfObjects);

		if (nbOfObjects > ObjectListEcu::maxEcuObjects) {
			logWarning << "Object list with too many objects (" << nbOfObjects << ") received."
			" List will be ignored." << std::endl;
			return false;
		}

		if (m_objects.size() != nbOfObjects)
			m_objects.resize(nbOfObjects);
	}

	std::vector<ObjectEcu>::iterator objIter = m_objects.begin();
	for (; objIter != m_objects.end(); ++objIter) {
		objIter->deserialize(is);
	}

	unlock();
	return !is.fail()
	       && ((is.tellg() - startPos) == this->getSerializedSize())
	       && this->getSerializedSize() == dh.getMessageSize();
}

//======================================================================

bool ObjectListEcu::serialize(std::ostream& os) const
{
	const std::istream::pos_type startPos = os.tellp();

	lock();

	ibeo::writeBE(os, m_scanStartTimestamp);
	const UINT16 nbOfObjects = this->m_objects.size();
	ibeo::writeBE(os, nbOfObjects);

	std::vector<ObjectEcu>::const_iterator objIter = m_objects.begin();
	for (; objIter != m_objects.end(); ++objIter) {
		objIter->serialize(os);
	}

	unlock();

	return !os.fail() && ((os.tellp() - startPos) == this->getSerializedSize());
}

//======================================================================

std::string getObjectIdsAsString(const ObjectListEcu& objList)
{
	if (objList.getNumberOfObjects() == 0)
		return "";

	// at least 1 object is in the list
	std::stringstream ssList;

	std::vector<ObjectEcu>::const_iterator dObjIter = objList.getObjects().begin();
	ssList << dObjIter->getObjectId();
	++dObjIter;
	for (; dObjIter != objList.getObjects().end(); ++dObjIter) {
		ssList << ", " << dObjIter->getObjectId();
	}

	return ssList.str();
}

//======================================================================

} // namespace ibeo

//======================================================================
