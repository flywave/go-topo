// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _IGESSelect_UpdateLastChange_HeaderFile
#define _IGESSelect_UpdateLastChange_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineHandle.hxx>
#include <Handle_IGESSelect_UpdateLastChange.hxx>

#include <IGESSelect_ModelModifier.hxx>
#include <Handle_IGESData_IGESModel.hxx>
class IFSelect_ContextModif;
class IGESData_IGESModel;
class Interface_CopyTool;
class TCollection_AsciiString;


//! Allows to Change the Last Change Date indication in the Header
//! (Global Section) of IGES File. It is taken from the operating
//! system (time of application of the Modifier).
//! The Selection of the Modifier is not used : it simply acts as
//! a criterium to select IGES Files to touch up.
//! Remark : IGES Models noted as version before IGES 5.1 are in
//! addition changed to 5.1
class IGESSelect_UpdateLastChange : public IGESSelect_ModelModifier
{

public:

  
  //! Creates an UpdateLastChange, which uses the system Date
  Standard_EXPORT IGESSelect_UpdateLastChange();
  
  //! Specific action : only <target> is used : the system Date
  //! is set to Global Section Item n0 25. Also sets IGES Version
  //! (Item n0 23) to IGES5 if it was older.
  Standard_EXPORT   void Performing (IFSelect_ContextModif& ctx, const Handle(IGESData_IGESModel)& target, Interface_CopyTool& TC)  const;
  
  //! Returns a text which is
  //! "Update IGES Header Last Change Date"
  Standard_EXPORT   TCollection_AsciiString Label()  const;




  DEFINE_STANDARD_RTTI(IGESSelect_UpdateLastChange)

protected:




private: 




};







#endif // _IGESSelect_UpdateLastChange_HeaderFile