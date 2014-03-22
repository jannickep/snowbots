//======================================================================
/*! \file ObjectEcuEt.hpp
 *
 * \copydoc Copyright
 * \author Jan Christian Dittmer (jcd)
 * \date Sep 5, 2013
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_OBJECTECUET_HPP_SEEN
#define IBEOSDK_OBJECTECUET_HPP_SEEN

//======================================================================

#include <ibeosdk/misc/WinCompatibility.hpp>

#include <ibeosdk/misc/Serializable.hpp>
#include <ibeosdk/Point2dFloat.hpp>
#include <ibeosdk/Time.hpp>
#include <ibeosdk/ObjectBasic.hpp>

#include <vector>
#include <iostream>

//======================================================================

namespace ibeo {

//======================================================================

class ObjectEcuEt : public ibeo::Serializable {
public:
	ObjectEcuEt();

public:
	virtual std::streamsize getSerializedSize() const;
	virtual bool deserialize(std::istream& is);
	virtual bool serialize(std::ostream& os) const;

public: // getter
	uint16_t getObjectId() const { return m_objectId; }
	uint16_t getFlags() const { return m_flags; }
	uint32_t getObjectAge() const { return m_objectAge; }
	NTPTime getTimestamp() const { return m_timestamp; }
	uint16_t getObjectPredAge() const { return m_objectPredAge; }
	ObjectClass getClassification() const { return m_classification; }
	uint8_t getClassCertainty() const { return m_classCertainty; }
	uint32_t getClassAge() const { return m_classAge; }
	Point2dFloat getObjBoxCenter() const { return m_objBoxCenter; }
	Point2dFloat getObjBoxCenterSigma() const { return m_objBoxCenterSigma; }
	Point2dFloat getObjBoxSize() const { return m_objBoxSize; }
	float getObjCourseAngle() const { return m_objCourseAngle; }
	Point2dFloat getRelVelocity() const { return m_relVelocity; }
	Point2dFloat getRelVelocitySigma() const { return m_relVelocitySigma; }
	Point2dFloat getAbsVelocity() const { return m_absVelocity; }
	Point2dFloat getAbsVelocitySigma() const { return m_absVelocitySigma; }
	uint8_t getNbOfContourPoints() const { return m_contourPoints.size(); }
	uint8_t getIdxOfClosestPoint() const { return m_idxOfClosestPoint; }
	RefPointBoxLocation getRefPointLocation() const { return m_refPointLocation; }
	Point2dFloat getRefPointCoords() const { return m_refPointCoords; }
	Point2dFloat getRefPointCoordsSigma() const { return m_refPointCoordsSigma; }
	float getRefPointPosCorrCoeffs() const { return m_refPointPosCorrCoeffs; }
	uint16_t getObjPriority() const { return m_objPriority; }
	float getObjExtMeasurement() const { return m_objExtMeasurement; }
	const std::vector<Point2dFloat>& getContourPoints() const { return m_contourPoints; }
	std::vector<Point2dFloat>& getContourPoints() { return m_contourPoints; }

public: // setter
	void setObjectId(const uint16_t newObjectId) { m_objectId = newObjectId; }
	void setFlags(const uint16_t newFlags) { m_flags = newFlags; }
	void setObjectAge(const uint32_t newObjectAge) { m_objectAge = newObjectAge; }
	void setTimestamp(const NTPTime newTimestamp) { m_timestamp = newTimestamp; }
	void setObjectPredAge(const uint16_t newObjectPredAge) { m_objectPredAge = newObjectPredAge; }
	void setClassification(const ObjectClass newClassification) { m_classification = newClassification; }
	void setClassCertainty(const uint8_t newClassCertainty) { m_classCertainty = newClassCertainty; }
	void setClassAge(const uint32_t newClassAge) { m_classAge = newClassAge; }
	void setObjBoxCenter(const Point2dFloat newObjBoxCenter) { m_objBoxCenter = newObjBoxCenter; }
	void setObjBoxCenterSigma(const Point2dFloat newObjBoxCenterSigma) { m_objBoxCenterSigma = newObjBoxCenterSigma; }
	void setObjBoxSize(const Point2dFloat newObjBoxSize) { m_objBoxSize = newObjBoxSize; }
	void setObjCourseAngle(const float newObjCourseAngle) { m_objCourseAngle = newObjCourseAngle; }
	void setRelVelocity(const Point2dFloat newRelVelocity) { m_relVelocity = newRelVelocity; }
	void setRelVelocitySigma(const Point2dFloat newRelVelocitySigma) { m_relVelocitySigma = newRelVelocitySigma; }
	void setAbsVelocity(const Point2dFloat newAbsVelocity) { m_absVelocity = newAbsVelocity; }
	void setAbsVelocitySigma(const Point2dFloat newAbsVelocitySigma) { m_absVelocitySigma = newAbsVelocitySigma; }
	void setNbOfContourPoints(const uint8_t newNbOfContourPoints) { m_contourPoints.resize(newNbOfContourPoints); }
	void setIdxOfClosestPoint(const uint8_t newIdxOfClosestPoint) { m_idxOfClosestPoint = newIdxOfClosestPoint; }
	void setRefPointLocation(const RefPointBoxLocation newRefPointLocation) { m_refPointLocation = newRefPointLocation; }
	void setRefPointCoords(const Point2dFloat newRefPointCoords) { m_refPointCoords = newRefPointCoords; }
	void setRefPointCoordsSigma(const Point2dFloat newRefPointCoordsSigma) { m_refPointCoordsSigma = newRefPointCoordsSigma; }
	void setRefPointPosCorrCoeffs(const float newRefPointPosCorrCoeffs) { m_refPointPosCorrCoeffs = newRefPointPosCorrCoeffs; }
	void setObjPriority(const uint16_t newObjPriority) { m_objPriority = newObjPriority; }
	void setObjExtMeasurement(const float newObjExtMeasurement) { m_objExtMeasurement = newObjExtMeasurement; }

protected:
	uint16_t m_objectId;
	uint16_t m_flags;
	uint32_t m_objectAge;
	NTPTime m_timestamp;
	uint16_t m_objectPredAge;
	ObjectClass m_classification; // uint8_t
	uint8_t m_classCertainty;
	uint32_t m_classAge;
	Point2dFloat m_reserved0;
	Point2dFloat m_reserved1;
	Point2dFloat m_objBoxCenter;
	Point2dFloat m_objBoxCenterSigma;
	Point2dFloat m_objBoxSize;
	Point2dFloat m_reserved2;
	float m_objCourseAngle;
	float m_reserved3;
	Point2dFloat m_relVelocity;
	Point2dFloat m_relVelocitySigma;
	Point2dFloat m_absVelocity;
	Point2dFloat m_absVelocitySigma;

	// 18 bytes reserved/internal
	uint64_t m_reserved4;
	float m_reserved5;
	float m_reserved6;
	uint16_t m_reserved7;

	// nb of contour points  uint8_t
	uint8_t m_idxOfClosestPoint;

	RefPointBoxLocation m_refPointLocation; // uint16_t
	Point2dFloat m_refPointCoords;
	Point2dFloat m_refPointCoordsSigma;
	float m_refPointPosCorrCoeffs;
	float m_reserved8;
	float m_reserved9;
	uint16_t m_objPriority;
	float m_objExtMeasurement;
	std::vector<Point2dFloat> m_contourPoints;
}; // ObjectEcuEt

//======================================================================

}// namespace ibeo

//======================================================================

#endif // IBEOSDK_OBJECTECUET_HPP_SEEN

//======================================================================

