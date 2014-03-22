//======================================================================
/*! \file Point2d.hpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date Apr 26, 2012
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_POINT2D_HPP_SEEN
#define IBEOSDK_POINT2D_HPP_SEEN

//======================================================================

#include <ibeosdk/misc/WinCompatibility.hpp>

#include <ibeosdk/misc/Serializable.hpp>
#include <ibeosdk/inttypes.hpp>

//======================================================================

namespace ibeo {

//======================================================================

class Point2d : public Serializable {
public:
	Point2d();
	Point2d(const INT16 posX, const INT16 posY);
	Point2d(const Point2d& src);
	virtual ~Point2d();

public:
	Point2d& operator= (const Point2d& src);

public:
	static std::streamsize getSerializedSize_static() { return 2 * sizeof(INT16); }

public:
	virtual std::streamsize getSerializedSize() const { return getSerializedSize_static(); }
	virtual bool deserialize(std::istream& is);
	virtual bool serialize(std::ostream& os) const;

public:
	INT16 getX() const { return m_posX; }
	INT16 getY() const { return m_posY; }

public:
	void setX(const INT16 posX) { m_posX = posX; }
	void setY(const INT16 posY) { m_posY = posY; }

protected:
	INT16 m_posX;
	INT16 m_posY;
}; // Point2D

//======================================================================

std::ostream& operator<<(std::ostream& os, const Point2d& tObj);

//======================================================================

} // namespace ibeo

//======================================================================

#endif // IBEOSDK_POINT2D_HPP_SEEN

//======================================================================

