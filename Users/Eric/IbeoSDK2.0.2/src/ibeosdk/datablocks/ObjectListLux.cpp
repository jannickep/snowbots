//======================================================================
/*! \file ObjectListLux.cpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date Apr 26, 2012
 *///-------------------------------------------------------------------

#include <ibeosdk/datablocks/ObjectListLux.hpp>
#include <ibeosdk/Log.hpp>
#include <ibeosdk/io.hpp>

//======================================================================

namespace ibeo {

//======================================================================

ObjectListLux::ObjectListLux()
  : m_scanStartTimestamp(0),
    m_objects()
{
	m_objects.reserve(maxLuxObjects);
}

//======================================================================

ObjectListLux::ObjectListLux(const NTPTime scanStartTimeStamp)
  : m_scanStartTimestamp(scanStartTimeStamp),
    m_objects()
{
	m_objects.reserve(maxLuxObjects);
}

//======================================================================

ObjectListLux::~ObjectListLux() {}

//======================================================================

void ObjectListLux::addObject(const ObjectLux& newObj)
{
	this->m_objects.push_back(newObj);
}

//======================================================================

const ObjectLux* ObjectListLux::findObject(const UINT16 id) const
{
	std::vector<ObjectLux>::const_iterator oIter = this->m_objects.begin();
	for (; oIter != this->m_objects.end(); ++oIter) {
		if (oIter->getObjectId() == id) {
			return &(*oIter);
		}
	}
	return NULL;
}

//======================================================================

bool ObjectListLux::deserialize(std::istream& is, const IbeoDataHeader& dh)
{
	const std::istream::pos_type startPos = is.tellg();

	lock();

	ibeo::readLE(is, m_scanStartTimestamp);

	{
		UINT16 nbOfObjects = 0;
		ibeo::readLE(is, nbOfObjects);

		if (nbOfObjects > ObjectListLux::maxLuxObjects) {
			logWarning << "Object list with too many objects (" << nbOfObjects << ") received."
			" List will be ignored." << std::endl;
			return false;
		}
		m_objects.resize(nbOfObjects);
	}

	std::vector<ObjectLux>::iterator objIter = m_objects.begin();
	for (; objIter != m_objects.end(); ++objIter) {
		objIter->deserialize(is);
	}

	unlock();

	return !is.fail()
	       && ((is.tellg() - startPos) == this->getSerializedSize())
	       && this->getSerializedSize() == dh.getMessageSize();
}

//======================================================================

bool ObjectListLux::serialize(std::ostream& os) const
{
	const std::istream::pos_type startPos = os.tellp();

	lock();

	ibeo::writeLE(os, m_scanStartTimestamp);
	const UINT16 nbOfObjects = this->m_objects.size();
	ibeo::writeLE(os, nbOfObjects);

	std::vector<ObjectLux>::const_iterator objIter = m_objects.begin();
	for (; objIter != m_objects.end(); ++objIter) {
		objIter->serialize(os);
	}

	unlock();

	return !os.fail() && ((os.tellp() - startPos) == this->getSerializedSize());
}

//======================================================================

std::streamsize ObjectListLux::getSerializedSize() const
{
	std::streamsize sz = sizeof(UINT16) + sizeof(NTPTime);
	std::vector<ObjectLux>::const_iterator objIter = m_objects.begin();
	for (; objIter != m_objects.end(); ++objIter) {
		sz += objIter->getSerializedSize();
	}
	return sz;
}

//======================================================================

std::string getObjectIdsAsString(const ObjectListLux& objList)
{
	if (objList.getNumberOfObjects() == 0)
		return "";

	// at least 1 object is in the list
	std::stringstream ssList;

	std::vector<ObjectLux>::const_iterator dObjIter = objList.getObjects().begin();
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

