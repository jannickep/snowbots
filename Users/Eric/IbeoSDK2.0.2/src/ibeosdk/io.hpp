//======================================================================
/*! \file io.hpp
 *
 * \copydoc Copyright
 * \author Jan Christian Dittmer (jcd)
 * \date Sep 4, 2013
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_IO_HPP_SEEN
#define IBEOSDK_IO_HPP_SEEN

//======================================================================

#include <ibeosdk/misc/WinCompatibility.hpp>

#include <boost/detail/endian.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_fundamental.hpp>

#include <iostream>
#include <istream>
#include <string>
#include <iomanip>

//======================================================================

namespace ibeo {

//======================================================================
/*!\brief Read a value of type \a T from stream
 *        \a is given in little endian byte order.
 *
 * \tparam T              Type of the value to be read.
 * \param[in, out] is     Stream providing the
 *                        data to be read.
 * \param[out]     value  On exit it will hold
 *                        the value that has
 *                        been read.
 *///------------------------------------------------------------------
template<typename T>
void readLE(std::istream& is, T& value)
{
#ifdef BOOST_BIG_ENDIAN
	readSwapped(is, value);
#else
	readLinear(is, value);
#endif
}



//======================================================================
/*!\brief Read a value of type \a T from stream
 *        \a is given in big endian byte order.
 *
 * \tparam T              Type of the value to be read.
 * \param[in, out] is     Stream providing the
 *                        data to be read.
 * \param[out]     value  On exit it will hold
 *                        the value that has
 *                        been read.
 *///------------------------------------------------------------------
template<typename T>
void readBE(std::istream& is, T& value)
{
#ifdef BOOST_BIG_ENDIAN
	readLinear(is, value);
#else
	readSwapped(is, value);
#endif
}



//======================================================================
/*!\brief Read a value of type \a T from stream \a is.
 *
 * \tparam T              Type of the value to be read.
 * \param[in, out] is     Stream providing the
 *                        data to be read.
 * \param[out]     value  On exit it will hold
 *                        the value that has
 *                        been read.
 * \param[in]      sourceIsBigEndian
 *                        tells whether the
 *                        stream \a is has big
 *                        endian byte order.
 *///------------------------------------------------------------------
template<typename T>
void read(std::istream& is, T& value, bool sourceIsBigEndian = false)
{
#ifdef BOOST_BIG_ENDIAN
	bool do_swap = !sourceIsBigEndian;
#else
	bool do_swap = sourceIsBigEndian;
#endif

	if (do_swap)
		readSwapped(is, value);
	else
		readLinear(is, value);
}



//======================================================================
/*!\brief Read a value of type \a T from stream \a is.
 *
 * It is assumed that the stream provides the data in the same byte order
 * as the system the code is running on. So the byte order will left
 * untouched.
 *
 * \tparam T              Type of the value to be read.
 * \param[in, out] is     Stream providing the
 *                        data to be read.
 * \param[out]     value  On exit it will hold
 *                        the value that has
 *                        been read.
 *///------------------------------------------------------------------
template<typename T>
void readLinear(std::istream& is, T& value)
{
	is.read(reinterpret_cast<char*>(&value), sizeof(value));
}



//======================================================================
#ifndef _WIN32
#  pragma GCC diagnostic ignored "-Warray-bounds"
#endif // _WIN32
//======================================================================
/*!\brief Read a value of type \a T for stream \a is and flip the byte order.
 *
 * It is assumed that the stream provides the data in different byte order
 * as the system the code is running on. So the byte order has to be swapped.
 *
 * \tparam T              Type of the value to be read.
 * \param[in, out] is     Stream providing the
 *                        data to be read.
 * \param[out]     value  On exit it will hold
 *                        the value that has
 *                        been read.
 *///------------------------------------------------------------------
template<typename T>
void readSwapped(std::istream& is, T& value)
{
	const std::streamsize maxSize = sizeof(value);
	unsigned short n = maxSize;
	char* data = reinterpret_cast<char *>(&value);
	char swapBuffer[maxSize];
	is.read(swapBuffer, n);

	char* swap = swapBuffer + n - 1;
	while (n--)
		*data++ = *swap--;
}
//======================================================================
#ifndef _WIN32
#  pragma GCC diagnostic warning "-Warray-bounds"
#endif // _WIN32
//======================================================================




//======================================================================
//======================================================================
//======================================================================





//======================================================================
/*!\brief Write a value of type \a T into stream
 *        \a os given in little endian byte order.
 *
 * \tparam T              Type of the value to be written.
 * \param[in, out] os     Stream that will receive the
 *                        data to be written.
 * \param[in]      value  The value to be written.
 *///------------------------------------------------------------------
template<typename T>
void writeLE(std::ostream& os, const T& value)
{
#ifdef BOOST_BIG_ENDIAN
	writeSwapped(os, value);
#else
	writeLinear(os, value);
#endif
}



//======================================================================
/*!\brief Write a value of type \a T into stream
 *        \a os given in big endian byte order.
 *
 * \tparam T              Type of the value to be written.
 * \param[in, out] os     Stream that will receive the
 *                        data to be written.
 * \param[in]      value  The value to be written.
 *///------------------------------------------------------------------
template<typename T>
void writeBE(std::ostream& os, const T& value)
{
#ifdef BOOST_BIG_ENDIAN
	writeLinear(os, value);
#else
	writeSwapped(os, value);
#endif
}



//======================================================================
/*!\brief Write a value of type \a T into stream \a os.
 *
 * \tparam T              Type of the value to be read.
 * \param[in, out] os     Stream the data will be written to.
 * \param[in]      value  The data to be written.
 * \param[in]      destIsBigEndian
 *                        tells whether the stream \a os shall have big
 *                        endian byte order.
 *///------------------------------------------------------------------
template<typename T>
void write(std::ostream& os, const T& value, bool destIsBigEndian = false)
{
#ifdef BOOST_BIG_ENDIAN
	bool do_swap = !destIsBigEndian;
#else
	bool do_swap = destIsBigEndian;
#endif

	if (do_swap)
		writeSwapped(os, value);
	else
		writeLinear(os, value);
}



//======================================================================
/*!\brief Write a value of type \a T into stream \a os.
 *
 * It is assumed that the stream receiving the data in the same byte order
 * as the system the code is running on. So the byte order will left
 * untouched.
 *
 * \tparam T  Type of the value to be written.
 * \param[in, out] os     Stream receiving the data been written.
 * \param[in]      value  The value to be written.
 *///------------------------------------------------------------------
template<typename T>
void writeLinear(std::ostream& os, const T& value)
{
	os.write(reinterpret_cast<const char* const>(&value), sizeof(value));
}



//======================================================================
/*!\brief Write a value of type \a T into stream \a os.
 *
 * It is assumed that the stream receiving the data in different byte order
 * as the system the code is running on. So the byte order  has to be swapped.
 *
 * \tparam T              Type of the value to be written.
 * \param[in, out] os     Stream receiving the data been written.
 * \param[in]      value  The value to be written.
 *///------------------------------------------------------------------
template<typename T>
void writeSwapped(std::ostream& os, const T& value)
{
	const std::streamsize typeSize = sizeof(value);
	const short n = typeSize;
	const unsigned char* data = reinterpret_cast<const unsigned char*>(&value) + n-1;

	unsigned char swapBuffer[typeSize];
	unsigned char* swap = swapBuffer;

	while (swap < swapBuffer+n)
		*swap++ = *data--;


	os.write(reinterpret_cast<const char*>(swapBuffer), typeSize);
}

//======================================================================

} // namespace ibeo

//======================================================================

#endif // IBEOSDK_IO_HPP_SEEN

//======================================================================

