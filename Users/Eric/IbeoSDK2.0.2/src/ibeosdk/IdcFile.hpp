//======================================================================
/*! \file IdcFile.hpp
 *
 * \copydoc Copyright
 * \author Mario Brumm (mb)
 * \date April 4, 2012
 *///-------------------------------------------------------------------

#ifndef IBEOSDK_IDCFILE_HPP_SEEN
#define IBEOSDK_IDCFILE_HPP_SEEN

//======================================================================

#include <ibeosdk/misc/WinCompatibility.hpp>

#include <ibeosdk/datablocks/DataBlock.hpp>
#include <ibeosdk/IbeoDataHeader.hpp>

#include <fstream>

//======================================================================

namespace ibeo {

//======================================================================

class ScanEcu;
class ObjectListEcu;
class ScanLux;
class ObjectListLux;
class ObjectListEcuEt;
class Image;
class VehicleStateBasicLux;
class VehicleStateBasicEcu;
class LogMessageError;
class LogMessageWarning;
class LogMessageNote;
class LogMessageDebug;

//======================================================================
/*!\class
 * \brief
 * \author Jan Christian Dittmer (jcd)
 * \version 0.1
 * \date Sep 4, 2013
 *
 *///-------------------------------------------------------------------
class IdcFile {
public:
	IdcFile();
	virtual ~IdcFile();

	virtual bool open(const std::string& filename);
	virtual bool isOpen();
	virtual bool isEOF();
	virtual bool isGood();
	virtual void close();

	virtual bool create(const std::string& filename, const bool append = false);
	virtual bool write(const char* const data, const unsigned short length);
	virtual const DataBlock* getNextDataBlock();
protected:
	const DataBlock* deserialize(std::istream& is,
	                             DataBlock& db,
	                             const IbeoDataHeader& dh);

protected:
	//========================================
	/*!\brief File stream for io access to the file.
	 *///-------------------------------------
	std::fstream m_strm;

	//========================================
	/*!\brief Variable to hold the deserialization
	 *        of a IbeoDataHeader.
	 *///-------------------------------------
	IbeoDataHeader m_dh;

	//========================================
	/*!\brief Variable to hold the deserialization
	 *        of a ScanLux.
	 *///-------------------------------------
	ScanLux* m_scanLux;

	//========================================
	/*!\brief Variable to hold the deserialization
	 *        of a ObjectListLux.
	 *///-------------------------------------
	ObjectListLux* m_objLux;

	//========================================
	/*!\brief Variable to hold the deserialization
	 *        of a ScanEcu.
	 *///-------------------------------------
	ScanEcu* m_scanEcu;

	//========================================
	/*!\brief Variable to hold the deserialization
	 *        of a ObjectListEcu.
	 *///-------------------------------------
	ObjectListEcu* m_objEcu;

	//========================================
	/*!\brief Variable to hold the deserialization
	 *        of a ObjectListEcuEt.
	 *///-------------------------------------
	ObjectListEcuEt* m_objEcuEt;

	//========================================
	/*!\brief Variable to hold the deserialization
	 *        of an Image
	 *///-------------------------------------
	Image* m_image;

	//========================================
	/*!\brief Variable to hold the deserialization
	 *        of a VehicleStateBasicLux.
	 *///-------------------------------------
	VehicleStateBasicLux* m_vsbLux;

	//========================================
	/*!\brief Variable to hold the deserialization
	 *        of a VehicleStateBasicEcu.
	 *///-------------------------------------
	VehicleStateBasicEcu* m_vsbEcu;

	//========================================
	/*!\brief Variable to hold the deserialization
	 *        of a LogMessageError
	 *///-------------------------------------
	LogMessageError* m_logMsgError;

	//========================================
	/*!\brief Variable to hold the deserialization
	 *        of a LogMessageWarning
	 *///-------------------------------------
	LogMessageWarning* m_logMsgWarning;
	//========================================
	/*!\brief Variable to hold the deserialization
	 *        of a LogMessageNote
	 *///-------------------------------------
	LogMessageNote* m_logMsgNote;

	//========================================
	/*!\brief Variable to hold the deserialization
	 *        of a LogMessageDebug
	 *///-------------------------------------
	LogMessageDebug* m_logMsgDebug;
}; // IdcFile

//======================================================================

} // namespace ibeo

//======================================================================

#endif // IBEOSDK_IDCFILE_HPP_SEEN
