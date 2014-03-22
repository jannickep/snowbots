//======================================================================
/*! \file Command.hpp
 *
 * \copydoc Copyright
 * \author Jan Christian Dittmer (jcd)
 * \date Sep 5, 2013
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_COMMAND_HPP_SEEN
#define IBEOSDK_COMMAND_HPP_SEEN

//======================================================================

#include <ibeosdk/misc/WinCompatibility.hpp>

#include <ibeosdk/datablocks/DataBlock.hpp>
#include <ibeosdk/inttypes.hpp>
#include <ibeosdk/datatypes.hpp>

//======================================================================

namespace ibeo {

//======================================================================
/*!\class Command
 * \brief Abstract base class for all Command classes.
 * \author Jan Christian Dittmer (jcd)
 * \version 0.1
 * \date Sep 5, 2013
 *
 *///-------------------------------------------------------------------
class Command : public DataBlock {
public:
	//========================================
	/*!\brief Create a Command object.
	 * \param[in] commandId      Id of the command.
	 * \param[in] version        Version of the command.
	 * \param[in] commandLength  Length of the command [Bytes].
	 *///-------------------------------------
	Command(const uint16_t commandId,
	        const uint16_t version,
	        const uint16_t commandLength);

public:
	//========================================
	/*!\brief Get the DataType of this DataBlock.
	 * \return Always DataType#DataType_Command.
	 *///-------------------------------------
	virtual DataType getDataType() const { return DataType_Command; }

	//========================================
	/*!\brief Get the size of the serialization.
	 * \return Number of bytes used by the serialization
	 *         of this Command.
	 *///-------------------------------------
	virtual std::streamsize getSerializedSize() const { return m_commandLength; }

public:
	//========================================
	/*!\brief Get the id of this Command.
	 * \return the id of this Command.
	 *///-------------------------------------
	uint16_t getCommandId() const { return m_commandId; }

	//========================================
	/*!\brief Get the length of this Command.
	 * Get the number of bytes totally used by this command.
	 *///-------------------------------------
	uint16_t getCommandLength() const { return m_commandLength; }

	//========================================
	/*!\brief Get the version of this Command.
	 * Get the version of this command.
	 *///-------------------------------------
	uint16_t getVersion() const { return m_version; }

protected:
	//========================================
	/*!\brief The id of this Command.
	 *///-------------------------------------
	uint16_t m_commandId;

	//========================================
	/*!\brief The version of this Command.
	 *///-------------------------------------
	uint16_t m_version;

protected:
	//========================================
	/*!\brief The length of this Command.
	 *///-------------------------------------
	uint16_t m_commandLength;
}; // Command

//======================================================================
//======================================================================
//======================================================================


//======================================================================
/*!\class CommandSetFilter
 * \brief SetFilter Command to configure the ECU output filer.
 * \author Jan Christian Dittmer (jcd)
 * \version 0.1
 * \date Oct 5, 2013
 *
 *///-------------------------------------------------------------------
class CommandSetFilter : public Command {
public:
	//========================================
	/*!\brief Id of the SetFilter command.
	 *///-------------------------------------
	static const uint16_t commandId = 0x0005;
	//========================================
	/*!\brief Length of the SetFilter command.
	 *///-------------------------------------
	static const int commandLength = 8;
	//========================================
	/*!\brief Version of the SetFilter command.
	 *///-------------------------------------
	static const uint16_t version = 2;

public:
	//========================================
	/*!\brief DataType range of the output filter.
	 *
	 * Datatypes with id between \a rangeStart and
	 * \rangeEnd shall pass the output filter.
	 * \param[in] rangeStart  Lowest DataType it
	 *                        to be passed the filter.
	 * \param[in] rangeStart  Highest DataType it
	 *                        to be passed the filter.
	 *///-------------------------------------
	CommandSetFilter(const DataType rangeStart, const DataType rangeEnd);

public:
	//========================================
	/*!\brief Deserialize data from the given stream \a is into
	 *        this CommandSetFilter.
	 * \param[in, out] is  Stream that provides the serialized
	 *                     data to fill this CommandSetFilter.
	 *                     On exit the \a is get pointer will
	 *                     be behind the read data.
	 * \param[in]      dh  IbeoDataHeader that has been received
	 *                     together with the serialized data in \a is.
	 * \return Whether the operation was successful.
	 * \retval true Everything is alright, no error occured.
	 * \retval false Reading the data from the stream has failed.
	 *///-------------------------------------
	virtual bool deserialize(std::istream& is, const IbeoDataHeader& dh);

	//========================================
	/*!\brief Serialize data into the given stream \a os.
	 * \param[out] is  Stream that receive the serialized
	 *                 data from this CommandSetFilter.
	 * \return Whether the operation was successful.
	 * \retval true Everything is alright, no error occured.
	 * \retval false Writing the data into the stream has failed.
	 *///-------------------------------------
	virtual bool serialize(std::ostream& os) const;

protected:
	DataType m_rangeStart;
	DataType m_rangeEnd;
}; // CommandSetFilter



//======================================================================
//======================================================================
//======================================================================

//======================================================================
/*!\class Reply
 * \brief Abstract base class for all Reply classes.
 * \author Jan Christian Dittmer (jcd)
 * \version 0.1
 * \date Sep 5, 2013
 *
 *///-------------------------------------------------------------------
class Reply: public DataBlock {
public:
	Reply();

public:
	//========================================
	/*!\brief Get the DataType of this DataBlock.
	 * \return Always DataType#DataType_Reply.
	 *///-------------------------------------
	virtual DataType getDataType() const { return DataType_Reply; }
}; // Reply

//======================================================================

}// namespace ibeo

//======================================================================

#endif // IBEOSDK_COMMAND_HPP_SEEN

//======================================================================
