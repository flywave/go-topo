// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _MDF_ASDriver_HeaderFile
#define _MDF_ASDriver_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineHandle.hxx>
#include <Handle_MDF_ASDriver.hxx>

#include <Handle_CDM_MessageDriver.hxx>
#include <MMgt_TShared.hxx>
#include <Standard_Integer.hxx>
#include <Handle_Standard_Type.hxx>
#include <Handle_PDF_Attribute.hxx>
#include <Handle_TDF_Attribute.hxx>
#include <Handle_MDF_SRelocationTable.hxx>
class CDM_MessageDriver;
class Standard_Type;
class PDF_Attribute;
class TDF_Attribute;
class MDF_SRelocationTable;
class TCollection_ExtendedString;


//! Attribute Storage Driver.
class MDF_ASDriver : public MMgt_TShared
{

public:

  
  //! Returns the version number from which the driver
  //! is available.
  Standard_EXPORT virtual   Standard_Integer VersionNumber()  const = 0;
  
  //! Returns the type of source object, inheriting from
  //! Attribute from TDF.
  Standard_EXPORT virtual   Handle(Standard_Type) SourceType()  const = 0;
  
  //! Creates a new attribute from PDF.
  Standard_EXPORT virtual   Handle(PDF_Attribute) NewEmpty()  const = 0;
  
  //! Translate the contents of <aSource> and put it
  //! into <aTarget>, using the relocation table
  //! <aRelocTable> to keep the sharings.
  Standard_EXPORT virtual   void Paste (const Handle(TDF_Attribute)& aSource, const Handle(PDF_Attribute)& aTarget, const Handle(MDF_SRelocationTable)& aRelocTable)  const = 0;
  
  //! To send message to Application (if MessageDriver defined)
  Standard_EXPORT   void WriteMessage (const TCollection_ExtendedString& theMessage)  const;




  DEFINE_STANDARD_RTTI(MDF_ASDriver)

protected:

  
  Standard_EXPORT MDF_ASDriver(const Handle(CDM_MessageDriver)& theMessageDriver);



private: 


  Handle(CDM_MessageDriver) myMessageDriver;


};







#endif // _MDF_ASDriver_HeaderFile