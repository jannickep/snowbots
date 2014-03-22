//======================================================================
/*! \file Point2dFloat.cpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \author Jan Christian Dittmer (jcd)
 * \date Apr 27, 2012
 * \date May 30, 2012
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_POINT2DFLOAT_HPP_SEEN
#define IBEOSDK_POINT2DFLOAT_HPP_SEEN

//======================================================================

#include <ibeosdk/misc/WinCompatibility.hpp>

#include <ibeosdk/misc/Serializable.hpp>
#include <ibeosdk/Point2d.hpp>

#include <cmath>

//======================================================================

namespace ibeo {

//======================================================================

class Point2dFloat : public Serializable {
public:
	static std::streamsize getSerializedSize_static() { return 2*sizeof(float); }
public:
	Point2dFloat();
	Point2dFloat(const float x, const float y);
	virtual ~Point2dFloat();

public:
	Point2dFloat(const Point2dFloat& src);
	Point2dFloat& operator=(const Point2dFloat& src);
	Point2dFloat& operator+=(const Point2dFloat& other);

public:
	Point2dFloat operator+(const Point2dFloat& other) const;
	Point2dFloat operator*(const float other) const;

public:
	virtual std::streamsize getSerializedSize() const { return getSerializedSize_static(); }
	virtual bool deserialize(std::istream& is);
	virtual bool serialize(std::ostream& os) const;

public:
	float getX() const { return this->m_x; }
	float getY() const { return this->m_y; }
	float& getX() { return this->m_x; }
	float& getY() { return this->m_y; }

	float dist() const { return std::sqrt(this->m_x * this->m_x + this->m_y * this->m_y); }
	float polarCoordAngle() const { return std::atan2(this->m_y, this->m_x); }

protected:
	float m_x;
	float m_y;
}; // Point2Dfloat

//======================================================================

inline Point2dFloat operator*(const float factor, const Point2d pt)
{
	return Point2dFloat(factor * pt.getX(), factor * pt.getY());
}

//======================================================================

inline Point2dFloat operator*(const Point2d pt, const float factor)
{
	return Point2dFloat(pt.getX() * factor, pt.getY() * factor);
}

//======================================================================

inline
bool operator<(const Point2dFloat& l, const Point2dFloat& r)
{
	return ((l.getX() < r.getX()) && (l.getY() < r.getY()));
}

//======================================================================

inline
bool operator<=(const Point2dFloat& l, const Point2dFloat& r)
{
	return ((l.getX() <= r.getX()) && (l.getY() <= r.getY()));
}

//======================================================================

std::ostream& operator<<(std::ostream& os, const Point2dFloat& p);

//======================================================================

} // namespace ibeo

//======================================================================

#endif // IBEOSDK_POINT2DFLOAT_HPP_SEEN
