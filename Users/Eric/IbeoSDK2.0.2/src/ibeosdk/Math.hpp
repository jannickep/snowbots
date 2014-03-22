//======================================================================
/*! \file Math.hpp
 *
 * \copydoc Copyright
 * \author Jan Christian Dittmer (jcd)
 * \date Sep 29, 2013
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_MATH_HPP_SEEN
#define IBEOSDK_MATH_HPP_SEEN

//======================================================================

#include <ibeosdk/misc/WinCompatibility.hpp>

#include <limits>
#include <cmath>

//======================================================================

namespace ibeo {

//======================================================================

//========================================
/*!\brief Shortcut for the double NaN value.
 *///-------------------------------------
const double NaN_double = std::numeric_limits<double>::quiet_NaN();

//======================================================================
/*!\brief Tests whether two \c float values are nearly equal.
 * \param[in] a  First value to be compared with second value.
 * \param[in] b  Second value to be compared with first value.
 * \return \c true if the two \c float numbers are equal in
 *         terms of the machine precision, which means their
 *         difference must be less than 1E-6.
 *///-------------------------------------------------------------------
inline bool fuzzyCompare(const float a, const float b)
{
	return std::abs(a - b) < 1E-6f;
}


//======================================================================
/*!\brief Normalize the given angle.
 *
 * Normalizes an angle given in radians by adding or subtracting an integer
 * multiple of 2*pi so that the resulting angle is in the half-open interval
 * (-pi,+pi]. The current implementation takes O(1) time, i.e. the time of
 * execution has a fixed upper boundary independend from the angle.
 *
 * \param[in] angleInRad  Angle to be normalized given in rad.
 * \return The normalized angle in (-pi, +pi].
 * \TODO check whether (-pi, +pi] or [-pi, +pi) is correct.
 *///-------------------------------------------------------------------
inline float normalizeRadians (float angleInRad)
{
	if (std::abs(angleInRad) > (3.0f * M_PI)) {
		// For numerical stability we must use this sin/cos/atan2
		// implementation even though it might consume more cycles.
		// Note that radians = -pi converts to atan2(0,-1) = +pi!
		angleInRad = std::atan2 (std::sin(angleInRad), std::cos(angleInRad));
		// radians now in (-pi,+pi]
	} // if
	else {
		// fast version for "normal" out of range values
		while (angleInRad > M_PI) {
			angleInRad -= 2.0f * float(M_PI);
		} // while
		while (angleInRad <= float(-M_PI)) {
			angleInRad += 2.0f * float(M_PI);
		} // while
	} // else
	return angleInRad;
}

//======================================================================

} // namespace ibeo

//======================================================================

#endif // IBEOSDK_MATH_HPP_SEEN
