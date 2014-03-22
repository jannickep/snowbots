//======================================================================
/*! \file Image.cpp
 *
 * \copydoc Copyright
 * \author Jan Christian Dittmer (jcd)
 * \date Sep 29, 2013
 *///-------------------------------------------------------------------

#include <ibeosdk/datablocks/Image.hpp>
#include <ibeosdk/io.hpp>
#include <ibeosdk/Math.hpp>

//======================================================================

namespace ibeo {

//======================================================================

Image::ImageBuffer::ImageBuffer()
  : length(0),
    data(NULL)
{}

//======================================================================

Image::ImageBuffer::ImageBuffer(const UINT32 size)
  : length(size),
    data((buffer_type*)malloc(length))
{}

//======================================================================

Image::ImageBuffer::ImageBuffer(const UINT16 width,
                                const UINT16 height,
                                const UINT8 bytesPerPixel)
  : length(width*height*bytesPerPixel),
    data((buffer_type*)malloc(length))
{}

//======================================================================

Image::ImageBuffer::ImageBuffer(const Image::ImageBuffer& other)
  : length(other.length),
    data((buffer_type*)malloc(length))
{
	memcpy(this->data, other.data, this->length);
}

//======================================================================

Image::ImageBuffer& Image::ImageBuffer::operator=(const Image::ImageBuffer& other)
{
	if (this != &other) {
		this->realloc(other.length);
		memcpy(this->data, other.data, this->length);
	}
	return *this;
}

//======================================================================

Image::ImageBuffer::~ImageBuffer()
{
	if (data) free(data);
}

//======================================================================

bool Image::ImageBuffer::operator==(const ImageBuffer& rhs) const
{
	return this->length == rhs.length
			&& (memcmp(this->data, rhs.data, this->length)==0);
}

//======================================================================

void Image::ImageBuffer::realloc(const UINT32 newSize)
{
	this->length = newSize;
	if (data) {
		this->data = (buffer_type*)std::realloc(this->data, this->length);
	}
	else {
		this->data = (buffer_type*)std::malloc(this->length);
	}
}

//======================================================================

void Image::ImageBuffer::assureSize(const UINT32 neededSize)
{
	if (neededSize > this->length)
		this->realloc(neededSize);
}

//======================================================================



//======================================================================
//======================================================================
//======================================================================



//======================================================================

Image::Image()
  : DataBlock(),
    m_imageFormat(JPEG),
    m_microseconds(0),
    m_timestamp(),
    m_deviceId(0),
    m_mountingPosition(),
    m_hOpeningAngle(ibeo::NaN_double),
    m_vOpeningAngle(ibeo::NaN_double),
    m_width(640),
    m_height(480),
    m_imageSize(0),
    m_imageBuffer(m_width, m_height,3)
//    m_RGB24Buffer(m_width, m_height,3),
//    m_isCompressedCurrent(false),
//    m_isRGBCurrent(false)
{}


//======================================================================

bool Image::operator==(const Image& other) const
{
	const bool otherDataEqual =
		m_imageFormat == other.m_imageFormat
		&& m_microseconds == other.m_microseconds
		&& m_timestamp == other.m_timestamp
		&& m_deviceId == other.m_deviceId
		&& m_mountingPosition == other.m_mountingPosition
		&& m_hOpeningAngle == other.m_hOpeningAngle
		&& m_vOpeningAngle == other.m_vOpeningAngle
		&& m_width == other.m_width
		&& m_height == other.m_height;

	const bool compressedEqual =
		   m_imageSize == other.m_imageSize
		&& m_imageBuffer == other.m_imageBuffer;

	// Either both images are completely empty, or those parts
	// which are set must be identical

	return otherDataEqual && compressedEqual;
}

//======================================================================

std::streamsize Image::getSerializedSize() const
{
	return 2 + 4 + 8 + 1 + m_mountingPosition.getSerializedSize()
			+ 8 + 8 + 2 + 2 + 4 + m_imageSize;
}

//======================================================================

bool Image::serialize(std::ostream& os) const
{
	const std::istream::pos_type startPos = os.tellp();

	const UINT16 imgFmt = this->m_imageFormat;
	ibeo::writeBE(os, imgFmt);    // 2
	ibeo::writeBE(os, this->m_microseconds);   // 4
	ibeo::writeBE(os, this->m_timestamp);      // 8
	ibeo::writeBE(os, this->m_deviceId);       // 1
	this->m_mountingPosition.serialize(os);  // 6*4 = 24
	ibeo::writeBE(os, this->m_hOpeningAngle);  // 8
	ibeo::writeBE(os, this->m_vOpeningAngle);  // 8
	ibeo::writeBE(os, this->m_width);          // 2
	ibeo::writeBE(os, this->m_height);         // 2
	ibeo::writeBE(os, this->m_imageSize); // 4
	os.write(reinterpret_cast<const char*>(this->m_imageBuffer.getData()), this->m_imageSize);

	return !os.fail() && ((os.tellp() - startPos) == this->getSerializedSize());
}

//======================================================================

bool Image::deserialize(std::istream& is, const IbeoDataHeader& dh)
{
	const std::istream::pos_type startPos = is.tellg();

	UINT16 imgFmt = 0;
	ibeo::readBE(is, imgFmt);      // 2
	this->m_imageFormat = ImageFormat(imgFmt);

	ibeo::readBE(is, this->m_microseconds);     // 4
	ibeo::readBE(is, this->m_timestamp);        // 8
	ibeo::readBE(is, this->m_deviceId);         // 1
	this->m_mountingPosition.deserialize(is);   // 6*4 = 24
	ibeo::readBE(is, this->m_hOpeningAngle);    // 8
	ibeo::readBE(is, this->m_vOpeningAngle);    // 8
	ibeo::readBE(is, this->m_width);            // 2
	ibeo::readBE(is, this->m_height) ;          // 2
	ibeo::readBE(is, this->m_imageSize);        // 4

	this->m_imageBuffer.assureSize(this->m_imageSize);
	is.read(reinterpret_cast<char*>(this->m_imageBuffer.getData()), this->m_imageSize );

//	this->m_isCompressedCurrent = true;
//	this->m_isRGBCurrent = false;
//	this->m_RGB24Buffer.realloc(0);

	return !is.fail()
	       && ((is.tellg() - startPos) == this->getSerializedSize())
	       && this->getSerializedSize() == dh.getMessageSize();
}

//======================================================================

void Image::setImage(const ImageFormat imageFormat,
                     const unsigned char* const buffer,
                     const UINT32 length,
                     const UINT16 width,
                     const UINT16 height,
                     const UINT32 microseconds,
                     const ibeo::NTPTime timestamp)
{
	m_imageFormat = imageFormat;
	m_microseconds = microseconds;
	m_timestamp = timestamp;
	// deviceId, mountingPosition, h/vOpeningAngle
	m_width = width;
	m_height = height;

	m_imageSize = length;
	m_imageBuffer.assureSize(m_imageSize);

	memcpy(m_imageBuffer.getData(), buffer, length);
}

//======================================================================

bool Image::getImageBuffer(const buffer_type*& buffer, UINT32& length ) const
{
	buffer = m_imageBuffer.getData();
	length = m_imageSize;

	return true;
}

//======================================================================

bool Image::getImageBuffer(buffer_type*& buffer, UINT32& length )
{
	buffer = m_imageBuffer.getData();
	length = m_imageSize;

	return true;
}

//======================================================================

std::string Image::formatToString(const ImageFormat format)
{
	std::string name;

	// Get the key name
	switch (format) {
	case JPEG:   name = "JPEG";                    break;
	case MJPEG:  name = "MotionJPEG (MJPEG)";      break;
	case GRAY8:  name = "8-bit grayscale (GRAY8)"; break;
	case YUV420: name = "YUV 4:2:0 (YUV420)";      break;
	case YUV422: name = "YUV 4:2:2 (YUV422)";      break;
	default:     name = "Unknown " + format;       break;
	} // switch

	return name;
}

//======================================================================

} // namespace ibeo

//======================================================================
