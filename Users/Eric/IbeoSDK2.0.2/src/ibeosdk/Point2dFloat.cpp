//======================================================================
/*! \file Point2dFloat.cpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \author Jan Christian Dittmer (jcd)
 * \date Apr 27, 2012
 * \date May 30, 2012
 *///-------------------------------------------------------------------

#include <ibeosdk/Point2dFloat.hpp>
#include <ibeosdk/io.hpp>

//======================================================================

namespace ibeo {

//======================================================================

Point2dFloat::Point2dFloat()
  : m_x(0.0),
    m_y(0.0)
{}

//======================================================================

Point2dFloat::Point2dFloat(const float x, const float y)
  : m_x(x),
    m_y(y)
{}

//======================================================================

Point2dFloat::Point2dFloat(const Point2dFloat& other)
  : m_x(other.m_x),
    m_y(other.m_y)
{}

//======================================================================

Point2dFloat& Point2dFloat::operator= (const Point2dFloat& other)
{
	this->m_x = other.m_x;
	this->m_y = other.m_y;

	return *this;
}

//======================================================================

Point2dFloat::~Point2dFloat() {}

//======================================================================

Point2dFloat& Point2dFloat::operator+= (const Point2dFloat& other)
{
	this->m_x += other.m_x;
	this->m_y += other.m_y;
	return *this;
}

//======================================================================

Point2dFloat Point2dFloat::operator+ (const Point2dFloat& other) const
{
	return Point2dFloat(this->m_x + other.m_x,
	                    this->m_y + other.m_y);
}

Point2dFloat Point2dFloat::operator* (const float other) const
{
	return Point2dFloat(this->m_x * other,
	                    this->m_y * other);
}


//======================================================================

bool Point2dFloat::deserialize(std::istream& is)
{
	const std::istream::pos_type startPos = is.tellg();

	ibeo::readBE(is, this->m_x);
	ibeo::readBE(is, this->m_y);

	return !is.fail() && ((is.tellg() - startPos) == this->getSerializedSize());
}

//======================================================================

bool Point2dFloat::serialize(std::ostream& os) const
{
	const std::istream::pos_type startPos = os.tellp();

	ibeo::writeBE(os, this->m_x);
	ibeo::writeBE(os, this->m_y);

	return !os.fail() && ((os.tellp() - startPos) == this->getSerializedSize());
}

//======================================================================

std::ostream& operator<<(std::ostream& os, const Point2dFloat& p)
{
	os << "(" << p.getX() << ", " << p.getY() << ")";
	return os;
}

//======================================================================

} // namespace ibeo

//======================================================================
