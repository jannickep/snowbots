//======================================================================
/*! \file WinCompatibility.hpp
 *
 * \copydoc Copyright
 * \author Jan Christian Dittmer (jcd)
 * \date Oct 2, 2013
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_WINCOMPATIBILITY_HPP_SEEN
#define IBEOSDK_WINCOMPATIBILITY_HPP_SEEN

//======================================================================

#ifdef _WIN32
#	ifndef _USE_MATH_DEFINES
#		define _USE_MATH_DEFINES
#	endif // _USE_MATH_DEFINES

#	ifndef NOMINMAX
#		define NOMINMAX
#	endif // NOMINMAX

#	define __func__ __FUNCTION__
#endif // _WIN32

//======================================================================

#endif // IBEOSDK_WINCOMPATIBILITY_HPP_SEEN

//======================================================================
