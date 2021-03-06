//======================================================================
/*! \file Box2dF.cpp
 *
 * \copydoc Copyright
 * \author Jan Christian Dittmer (jcd)
 * \date May 30, 2012
 *///-------------------------------------------------------------------

//======================================================================

#include <ibeosdk/Box2dF.hpp>

//======================================================================

namespace ibeo {

//======================================================================

Box2dF::Box2dF()
  : center(),
    size(),
    rotation(.0)
{}

//======================================================================

Box2dF::Box2dF(const Point2dFloat& center,
               const Point2dFloat& size,
               const float rotation)
  : center(center),
    size(size),
    rotation(rotation)
{}

//======================================================================

bool Box2dF::containsPoint(const Point2dFloat& point) const
{
	if (this->rotation < 1E-6f) {
		// Rotation is zero, hence we can directly check this in
		// cartesian coordinates.
		const float pointX = point.getX() - this->center.getX();
		const float pointY = point.getY() - this->center.getY();

		// compare position to half size
		return (std::abs(pointX) <=  0.5f * this->size.getX())
		       && (std::abs(pointY) <=  0.5f * this->size.getY());
	}
	else {
		// 2D coordinate transformation as proposed by Uni Ulm.

		// Move coordinate system to center of the box
		const float deltaX = point.getX() - this->center.getX();
		const float deltaY = point.getY() - this->center.getY();

		// If any of the X or Y components are outside of the
		// "manhatten" diagonal bounding box, the point cannot be
		// inside the box (and we don't even have to calculate the
		// rotated point).
		const float half_sizeX = 0.5f * this->size.getX();
		const float half_sizeY = 0.5f * this->size.getY();
		if (std::max(std::abs(deltaX), std::abs(deltaY)) > half_sizeX + half_sizeY)
			return false;

		// Rotate by -psi
		const float dCos = std::cos(this->rotation);
		const float dSin = std::sin(this->rotation);
		const float pointX =  dCos * deltaX  +  dSin * deltaY;
		const float pointY = -dSin * deltaX  +  dCos * deltaY;

		// compare position to half size
		return ((std::abs(pointX) <=  half_sizeX)
		       && (std::abs(pointY) <=  half_sizeY));
	}
}

//======================================================================

std::pair<float, float> Box2dF::getBoundingAngles() const
{
	// This function calculates a low and a high boundary angle for
	// all edges of the given (rotated) Box2D. The returned FloatPair
	// has the component "first" for the lower bounding angle, and
	// "second" for the upper bounding angle. (Note: This ordering is
	// swapped compared to the scan point ordering!)

	// Need to check whether the origin is inside the box
	if (this->containsPoint(Point2dFloat(0, 0)))
	{
		// Origin is inside. Then return the full interval.
		return std::make_pair<float, float>(float(-M_PI), float(M_PI));
	}

	// The usual case: The box does not contain the origin. Then we
	// look for the min and max angles of the edges.

	std::vector<Point2dFloat> corners = this->getCorners();
	float minangle = corners[0].polarCoordAngle();
	float maxangle = minangle;
	for (unsigned k = 1; k < 4; ++k) {
		float pointangle = corners[k].polarCoordAngle();

		if (pointangle < minangle)
			minangle = pointangle;

		if (pointangle > maxangle)
			maxangle = pointangle;
	}

	return std::pair<float, float>(minangle, maxangle);
}
//======================================================================

std::vector<Point2dFloat> Box2dF::getCorners() const
{
	// This is the delta between center and edges
	const float deltaX = this->size.getX() * 0.5f;
	const float deltaY = this->size.getY() * 0.5f;

	// The cos/sin rotation factors
	const float dCos = std::cos(this->rotation);
	const float dSin = std::sin(this->rotation);

	// The dimensions after the rotation
	const float XCos = deltaX * dCos, XSin = deltaX * dSin;
	const float YCos = deltaY * dCos, YSin = deltaY * dSin;

	// Create the resulting points
	std::vector<Point2dFloat> corners(4);
	// Rotate each edge according to the this->rotation
	corners[0] = this->center + Point2dFloat(  XCos - YSin,  XSin + YCos);
	corners[1] = this->center + Point2dFloat(  XCos + YSin,  XSin - YCos);
	corners[2] = this->center + Point2dFloat( -XCos + YSin, -XSin - YCos);
	corners[3] = this->center + Point2dFloat( -XCos - YSin, -XSin + YCos);
	return corners;
}

//======================================================================

} // namespace ibeo

//======================================================================
