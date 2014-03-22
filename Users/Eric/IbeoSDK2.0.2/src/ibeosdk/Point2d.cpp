//======================================================================
/*! \file Point2d.cpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date Apr 26, 2012
 *///-------------------------------------------------------------------

#include <ibeosdk/Point2d.hpp>
#include <ibeosdk/io.hpp>

#include <iostream>

//======================================================================

namespace ibeo {

//======================================================================

Point2d::Point2d()
  : m_posX(0), m_posY(0)
{}

//======================================================================

Point2d::Point2d(const INT16 posX, const INT16 posY)
  : m_posX(posX), m_posY(posY)
{}

//======================================================================

Point2d::Point2d(const Point2d& other)
  : m_posX(other.m_posX), m_posY(other.m_posY)
{}

//======================================================================

Point2d::~Point2d() {}

//======================================================================

Point2d& Point2d::operator= (const Point2d& src)
{
	m_posX = src.m_posX;
	m_posY = src.m_posY;

	return *this;
}

//======================================================================

bool Point2d::deserialize(std::istream& is)
{
	const std::istream::pos_type startPos = is.tellg();

	ibeo::readLE(is, m_posX);
	ibeo::readLE(is, m_posY);

	return !is.fail() && ((is.tellg() - startPos) == this->getSerializedSize());
}

//======================================================================

bool Point2d::serialize(std::ostream& os) const
{
	const std::istream::pos_type startPos = os.tellp();

	ibeo::writeLE(os, m_posX);
	ibeo::writeLE(os, m_posY);

	return !os.fail() && ((os.tellp() - startPos) == this->getSerializedSize());
}

//======================================================================

std::ostream& operator<<(std::ostream& os, const Point2d& pt)
{
	os << "(" << pt.getX() << ", " << pt.getY() << ")";
	return os;
}

//======================================================================

} // namespace ibeo

//======================================================================
