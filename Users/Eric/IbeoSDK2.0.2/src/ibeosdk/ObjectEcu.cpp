//======================================================================
/*! \file ObjectEcu.cpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date Apr 26, 2012
 *///-------------------------------------------------------------------

#include <ibeosdk/ObjectEcu.hpp>
#include <ibeosdk/io.hpp>

//======================================================================

namespace ibeo {

//======================================================================

ObjectEcu::ObjectEcu()
  : m_id(0),
    m_age(0),
    m_timestamp(0),
    m_hiddenStatusAge(0),
    m_class(),
    m_classCertainty(0.),
    m_classAge(0),
    m_boundingBoxCenter(),
    m_boundingBoxSize(),
    m_objectBoxCenter(),
    m_objectBoxSigma(),
    m_objectBoxSize(),
    m_yawAngle(0.),
    m_relVelocity(),
    m_relVelocitySigma(),
    m_absVelocity(),
    m_absVelocitySigma(),
    m_numContourPoints(0),
    m_indexOfClosedPoint(0),
    m_contourPoints(m_numContourPoints),
    m_orientation(0.f)
{
	m_contourPoints.reserve(16);
}

//======================================================================

ObjectEcu::ObjectEcu(const ObjectEcu& other)
  : m_id(other.m_id),
    m_age(other.m_age),
    m_timestamp(other.m_timestamp),
    m_hiddenStatusAge(other.m_hiddenStatusAge),
    m_class(other.m_class),
    m_classCertainty(other.m_classCertainty),
    m_classAge(other.m_classAge),
    m_boundingBoxCenter(other.m_boundingBoxCenter),
    m_boundingBoxSize(other.m_boundingBoxSize),
    m_objectBoxCenter(other.m_objectBoxCenter),
    m_objectBoxSigma(other.m_objectBoxSigma),
    m_objectBoxSize(other.m_objectBoxSize),
    m_yawAngle(other.m_yawAngle),
    m_relVelocity(other.m_relVelocity),
    m_relVelocitySigma(other.m_relVelocitySigma),
    m_absVelocity(other.m_absVelocity),
    m_absVelocitySigma(other.m_absVelocitySigma),
    m_numContourPoints(other.m_numContourPoints),
    m_indexOfClosedPoint(other.m_indexOfClosedPoint),
    m_contourPoints(other.m_contourPoints),
    m_orientation(other.m_orientation)
{}

//======================================================================

ObjectEcu& ObjectEcu::operator=(const ObjectEcu& other)
{
	if (&other == this)
		return *this;

	m_id = other.m_id;
	m_age = other.m_age;
	m_timestamp = other.m_timestamp;
	m_hiddenStatusAge = other.m_hiddenStatusAge;
	m_class = other.m_class;
	m_classCertainty = other.m_classCertainty;
	m_classAge = other.m_classAge;
	m_boundingBoxCenter = other.m_boundingBoxCenter;
	m_boundingBoxSize = other.m_boundingBoxSize;
	m_objectBoxCenter = other.m_objectBoxCenter;
	m_objectBoxSigma = other.m_objectBoxSigma;
	m_objectBoxSize = other.m_objectBoxSize;
	m_yawAngle = other.m_yawAngle;
	m_relVelocity = other.m_relVelocity;
	m_relVelocitySigma = other.m_relVelocitySigma;
	m_absVelocity = other.m_absVelocity;
	m_absVelocitySigma = other.m_absVelocitySigma;
	m_numContourPoints = other.m_numContourPoints;
	m_indexOfClosedPoint = other.m_indexOfClosedPoint;
	m_contourPoints = other.m_contourPoints;
	m_orientation = other.m_orientation;
	return *this;
}

//======================================================================

std::streamsize ObjectEcu::getSerializedSize() const
{
	return 132 + 8*m_numContourPoints;
}

//======================================================================

bool ObjectEcu::deserialize(std::istream& is)
{
	const std::istream::pos_type startPos = is.tellg();

	ibeo::readBE(is, m_id);
	is.ignore(2); // 2 bytes reserved
	ibeo::readBE(is, m_age);
	ibeo::readBE(is, m_timestamp);
	ibeo::readBE(is, m_hiddenStatusAge);

	UINT8 c;
	ibeo::readBE(is, c);
	switch (c) {
	case 1: m_class = ObjectClass_UnknownSmall; break;
	case 2: m_class = ObjectClass_UnknownBig; break;
	case 3: m_class = ObjectClass_Pedestrian; break;
	case 4: m_class = ObjectClass_Bike; break;
	case 5: m_class = ObjectClass_Car; break;
	case 6: m_class = ObjectClass_Truck; break;
	default: m_class = ObjectClass_Unclassified; break;
	} // switch c

	ibeo::readBE(is, m_classCertainty);
	ibeo::readBE(is, m_classAge);

	m_boundingBoxCenter.deserialize(is);
	m_boundingBoxSize.deserialize(is);

	m_objectBoxCenter.deserialize(is);
	m_objectBoxSigma.deserialize(is);
	m_objectBoxSize.deserialize(is);

	is.ignore(8); // 8 bytes reserved

	ibeo::readBE(is, m_yawAngle);

	is.ignore(4); // 4 bytes reserved

	m_relVelocity.deserialize(is);
	m_relVelocitySigma.deserialize(is);


	m_absVelocity.deserialize(is);
	m_absVelocitySigma.deserialize(is);


	is.ignore(18); // 18 byte reserved

	ibeo::readBE(is, m_numContourPoints);
	ibeo::readBE(is, m_indexOfClosedPoint);

	if (m_contourPoints.size() != m_numContourPoints)
		m_contourPoints.resize(m_numContourPoints);

	std::vector<Point2dFloat>::iterator cpIter = m_contourPoints.begin();
	for (; cpIter != m_contourPoints.end(); ++cpIter) {
		cpIter->deserialize(is);
	}

	m_orientation = atan2(m_absVelocity.getY(), m_absVelocity.getX());

	return !is.fail() && ((is.tellg() - startPos) == this->getSerializedSize());
}

//======================================================================

bool ObjectEcu::serialize(std::ostream& os) const
{
	const std::istream::pos_type startPos = os.tellp();

	const uint16_t reserved = 0;

	ibeo::writeBE(os, m_id);
	ibeo::writeBE(os, reserved);// 2 bytes reserved
	ibeo::writeBE(os, m_age);
	ibeo::writeBE(os, m_timestamp);
	ibeo::writeBE(os, m_hiddenStatusAge);

	const UINT8 c = m_class;
	ibeo::writeBE(os, c);

	ibeo::writeBE(os, m_classCertainty);
	ibeo::writeBE(os, m_classAge);

	m_boundingBoxCenter.serialize(os);
	m_boundingBoxSize.serialize(os);

	m_objectBoxCenter.serialize(os);
	m_objectBoxSigma.serialize(os);
	m_objectBoxSize.serialize(os);

	ibeo::writeBE(os, reserved);// 2 bytes reserved
	ibeo::writeBE(os, reserved);// 2 bytes reserved
	ibeo::writeBE(os, reserved);// 2 bytes reserved
	ibeo::writeBE(os, reserved);// 2 bytes reserved

	ibeo::writeBE(os, m_yawAngle);

	ibeo::writeBE(os, reserved);// 2 bytes reserved
	ibeo::writeBE(os, reserved);// 2 bytes reserved

	m_relVelocity.serialize(os);
	m_relVelocitySigma.serialize(os);


	m_absVelocity.serialize(os);
	m_absVelocitySigma.serialize(os);

	for (int i = 0; i < 9; ++i)
		ibeo::writeBE(os, reserved); // 18 bytes reserved

	ibeo::writeBE(os, m_numContourPoints);
	ibeo::writeBE(os, m_indexOfClosedPoint);


	std::vector<Point2dFloat>::const_iterator cpIter = m_contourPoints.begin();
	for (; cpIter != m_contourPoints.end(); ++cpIter) {
		cpIter->serialize(os);
	}

	return !os.fail() && ((os.tellp() - startPos) == this->getSerializedSize());
}

//======================================================================

std::ostream& operator<<(std::ostream& os, const ObjectEcu& o)
{
	os.width(3);
//	os.precision(10);
	os << o.getObjectId() << ": ";
	os << "Age: " << o.getObjectAge() << ", ";
	os << "TS: " << o.getTimestamp() << ", ";
	os << "HS: " << o.getHiddenStatusAge() << ", ";
	os << "CL: " << o.getClassification() << "  ";
	os << "CC: " << int(o.getClassificationCertainty()) << ", ";
	os << "CA: " << o.getClassificationAge() << ", ";
	os << "BBC: " << o.getBoundingBoxCenter() << ", ";
	os << "BBS: " << o.getBoundingBoxSize() << ", ";
	os << "OBC: " << o.getObjectBoxCenter() << ", ";
	os << "OBCs: " << o.getObjectBoxSigma() << ", ";
	os << "OBS: " << o.getObjectBoxSize() << ", ";
	os << "Yaw: " << o.getYawAngle() << ", ";
	os << "RV: " << o.getRelativeVelocity() << ", ";
	os << "RVs: " << o.getRelativeVelocitySigma() << ", ";
	os << "AV: " << o.getAbsoluteVelocity() << ", ";
	os << "AVs: " << o.getAbsoluteVelocitySigma() << ", ";
	os << "#CP:" << int(o.getNumberOfContourPoints()) <<  ", ";
	os << "iCP:" << int(o.getIndexOfClosestPoint()) <<  ", ";
	os << "ori:" << o.getOrientation() <<  ", ";

	return os;
}

//======================================================================

} // namespace ibeo

//======================================================================
