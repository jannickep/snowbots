//======================================================================
/*! \file Command.cpp
 *
 * \copydoc Copyright
 * \author Jan Christian Dittmer (jcd)
 * \date Sep 5, 2013
 *///-------------------------------------------------------------------

#include <ibeosdk/datablocks/Command.hpp>
#include <ibeosdk/io.hpp>

//======================================================================

namespace ibeo {

//======================================================================

Command::Command(const uint16_t commandId,
                 const uint16_t version,
                 const uint16_t commandLength)
  : m_commandId(commandId),
    m_version(version),
    m_commandLength(commandLength)
{}

//======================================================================

CommandSetFilter::CommandSetFilter(const DataType rangeStart,
                                   const DataType rangeEnd)
  : Command(commandId, version, commandLength),
    m_rangeStart(rangeStart),
    m_rangeEnd(rangeEnd)
{}

//======================================================================

bool CommandSetFilter::deserialize(std::istream& is, const IbeoDataHeader& dh)
{
	const std::istream::pos_type startPos = is.tellg();

	readBE(is, m_commandId);
	readBE(is, m_version);
	uint16_t rdBuf;
	readBE(is, rdBuf); m_rangeStart = DataType(rdBuf);
	readBE(is, rdBuf); m_rangeEnd = DataType(rdBuf);

	return !is.fail()
	       && ((is.tellg() - startPos) == this->getSerializedSize())
	       && this->getSerializedSize() == dh.getMessageSize();
}

//======================================================================

bool CommandSetFilter::serialize(std::ostream& os) const
{
	const std::istream::pos_type startPos = os.tellp();

	writeBE(os, m_commandId);
	writeBE(os, m_version);
	writeBE(os, uint16_t(m_rangeStart));
	writeBE(os, uint16_t(m_rangeEnd));

	return !os.fail() && ((os.tellp() - startPos) == this->getSerializedSize());
}

//======================================================================

} // namespace ibeo

//======================================================================

