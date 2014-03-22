//======================================================================
/*! \file DataBlock.cpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date Apr 25, 2012
 *///-------------------------------------------------------------------

#include <ibeosdk/datablocks/DataBlock.hpp>

//======================================================================

namespace ibeo {

//======================================================================

DataBlock::DataBlock()
  : Concurrency(),
    m_headerDeviceId(),
    m_headerNtpTime()
{}

//======================================================================

void DataBlock::setDataHeader(const IbeoDataHeader& dh)
{
	m_headerDeviceId = dh.getDeviceId();
	m_headerNtpTime = dh.getTimestamp();
}

//======================================================================

} // namespace ibeo

//======================================================================
