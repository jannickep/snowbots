//======================================================================
/*! \file IbeoDataHeader.cpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date April 4, 2012
 *///-------------------------------------------------------------------

#include <ibeosdk/IbeoDataHeader.hpp>
#include <ibeosdk/Log.hpp>
#include <ibeosdk/io.hpp>

#include <iostream>
using namespace std;

//======================================================================

namespace ibeo {

//======================================================================

// static
const UINT32 IbeoDataHeader::magicWord = 0xAFFEC0C2;

//======================================================================

IbeoDataHeader::IbeoDataHeader()
  : m_sizeOfPrevMessage(0),
    m_sizeOfThisMessage(0),
    m_deviceId(0),
    m_dataType(DataType_Unknown),
    m_ntpTime(0)
{}

//======================================================================

IbeoDataHeader::IbeoDataHeader(const DataType dataType,
                               const UINT32 sizeOfPrevMessage,
                               const UINT32 sizeOfThisMessage,
                               const UINT8 deviceId,
                               const NTPTime ntpTime)
  : m_sizeOfPrevMessage(sizeOfPrevMessage),
    m_sizeOfThisMessage(sizeOfThisMessage),
    m_deviceId(deviceId),
    m_dataType(dataType),
    m_ntpTime(ntpTime)
{}

//======================================================================

IbeoDataHeader::~IbeoDataHeader() {}

//======================================================================

bool IbeoDataHeader::deserialize(std::istream& is)
{
	if (!IbeoDataHeader::findMagicWord(is))
		return false;

	const std::istream::pos_type startPos = is.tellg();

	ibeo::readBE(is, m_sizeOfPrevMessage);
	ibeo::readBE(is, m_sizeOfThisMessage);

	UINT8 dummy;
	ibeo::readBE(is, dummy);
	//is.ignore(); // reserved byte

	ibeo::readBE(is, m_deviceId);

	UINT16 dt;
	ibeo::readBE(is, dt);
	this->m_dataType = ibeo::DataType(dt);
//	switch (dt) {
//	case DataType_Command:
//	case DataType_Reply:
//	case DataType_Notification:
//	case DataType_LuxScan:
//	case DataType_EcuScan:
//	case DataType_LuxObjectList:
//	case DataType_EcuObjectList:
//	case DataType_LuxObjectListET:
//	case DataType_EcuObjectListET:
//	case DataType_Image:
//	case DataType_LuxVehicleStateBasic:
//	case DataType_EcuVehicleStateBasicOld:
//	case DataType_EcuVehicleStateBasic:
//		this->m_dataType = ibeo::DataType(dt);
//		break;
//	default:
//		this->m_dataType = DataType_Unknown;
//		break;
//	}

	ibeo::readBE(is, m_ntpTime); // 64 Bit NTP time stamp

	return !is.fail() && ((is.tellg() - startPos) == this->getSerializedSize()-4); // adjust because of magic word

}

//======================================================================

bool IbeoDataHeader::serialize(std::ostream& os) const
{
	const std::istream::pos_type startPos = os.tellp();

	ibeo::writeBE(os, magicWord);
	ibeo::writeBE(os, this->m_sizeOfPrevMessage);
	ibeo::writeBE(os, this->m_sizeOfThisMessage);
	const char res1 = 0;
	ibeo::writeBE(os, res1);
	ibeo::writeBE(os, this->m_deviceId);
	ibeo::writeBE(os, UINT16(this->m_dataType));
	ibeo::writeBE(os, this->m_ntpTime);

	return !os.fail() && ((os.tellp() - startPos) == this->getSerializedSize());}

//======================================================================

bool IbeoDataHeader::findMagicWord(std::istream& is)
{
	UINT32 nMagicWord = 0;
//	int nbOfSkippedBytes = -4;
	char cByte;

	// Read bytes from input stream until the next magic word is found
	while (nMagicWord != 0xAFFEC0C2) {
		// Note that the right-hand side of the &&-operator is evaluated
		// only if the left-hand side is true, i.e. is.get() will be
		// called only if the magic word is incorrect.
//		++nbOfSkippedBytes;
		is >> cByte;
		if (is.eof()) {
			return false;
		}
//		std::cerr << " 0x" << hex << int(cByte) << dec;

		// By definition, header data have network byte order (Big Endian),
		// i.e. the high byte of the magic word is received first. Therefore
		// we must shift the received byte from the LSB side into the magic
		// word m_uVersion.
		nMagicWord <<= 8;
		nMagicWord |= cByte & 0x000000FF;
	}
//	std::cerr << endl;

//logError << nbOfSkippedBytes << " Bytes skipped" << std::endl;
	return true;
}

//======================================================================

bool IbeoDataHeader::moveToMagicWord(std::istream& is)
{
	if (IbeoDataHeader::findMagicWord(is)) {
		is.putback(char(0xc2));
		is.putback(char(0xc0));
		is.putback(char(0xfe));
		is.putback(char(0xaf));
		return true;
	}
	return false;
}

//======================================================================

} // namespace ibeo

//======================================================================
