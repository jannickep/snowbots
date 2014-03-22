//======================================================================
/*! \file LogMessageBase.cpp
 *
 * \copydoc Copyright
 * \author Jan Christian Dittmer (jcd)
 * \date Sep 30, 2013
 *///-------------------------------------------------------------------

#include <ibeosdk/datablocks/LogMessageBase.hpp>
#include <ibeosdk/io.hpp>

//======================================================================

namespace ibeo {

//======================================================================

LogMessageBase::LogMessageBase(const TraceLevel traceLevel, const std::string msg)
  : m_traceLevel(traceLevel), m_message(msg)
{}

//======================================================================

bool LogMessageBase::deserialize(std::istream& is, const IbeoDataHeader& dh)
{
	const std::istream::pos_type startPos = is.tellg();

	uint8_t tl;
	ibeo::readBE(is, tl);
	m_traceLevel = TraceLevel(tl);


	if (dh.getMessageSize()==1) {
		m_message.clear();
		if ((is.tellg() - startPos) != this->getSerializedSize())
			return false;
	}
	else {
		std::vector<char> buf(dh.getMessageSize()-1);
		is.read(buf.data(), dh.getMessageSize()-1);

		if ((is.tellg() - startPos) != dh.getMessageSize())
			return false;

		while (!buf.empty() && (buf.back() == std::string::value_type(0) || buf.back() == std::string::value_type('\n'))) {
			buf.pop_back();
		}
		m_message = toASCII(buf);
	}

	return !is.fail();
//	return !is.fail() && ((is.tellg() - startPos) == this->getSerializedSize());
}

//======================================================================

bool LogMessageBase::serialize(std::ostream& os) const
{
	const std::istream::pos_type startPos = os.tellp();

	const uint8_t tl = uint8_t(m_traceLevel);
	ibeo::writeBE(os, tl);
	os.write(m_message.c_str(), m_message.size());

	return !os.fail() && ((os.tellp() - startPos) == this->getSerializedSize());
}

//======================================================================

}// namespace ibeo

//======================================================================
