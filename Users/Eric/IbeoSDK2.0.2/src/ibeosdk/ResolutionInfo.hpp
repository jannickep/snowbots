//======================================================================
/*! \file ResolutionInfo.hpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date Apr 26, 2012
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_RESOLUTIONINFO_HPP_SEEN
#define IBEOSDK_RESOLUTIONINFO_HPP_SEEN

//======================================================================

#include <ibeosdk/misc/WinCompatibility.hpp>

#include <ibeosdk/misc/Serializable.hpp>

//======================================================================

namespace ibeo {

//======================================================================

class ResolutionInfo : public Serializable {
public:
	ResolutionInfo();
	ResolutionInfo(const ResolutionInfo& src);
	virtual ~ResolutionInfo();

public:
	ResolutionInfo& operator= (const ResolutionInfo& src);

public:
	static std::streamsize getSerializedSize_static();

public:
	virtual std::streamsize getSerializedSize() const { return getSerializedSize_static(); }

	virtual bool deserialize(std::istream& is);
	virtual bool serialize(std::ostream& os) const;

public:
	float getResolutionStartAngle() const { return m_resolutionStartAngle; }
	float getResolution() const { return m_resolution; }

protected:
	float m_resolutionStartAngle; // TODO: define FLOAT32
	float m_resolution; // TODO: define FLOAT32
}; // ResolutionInfo

//======================================================================

} // namespace ibeo

//======================================================================

#endif // IBEOSDK_RESOLUTIONINFO_HPP_SEEN

//======================================================================

