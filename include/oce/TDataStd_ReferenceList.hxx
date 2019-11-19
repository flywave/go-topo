// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _TDataStd_ReferenceList_HeaderFile
#define _TDataStd_ReferenceList_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineHandle.hxx>
#include <Handle_TDataStd_ReferenceList.hxx>

#include <TDF_LabelList.hxx>
#include <TDF_Attribute.hxx>
#include <Standard_Boolean.hxx>
#include <Standard_Integer.hxx>
#include <Handle_TDF_Attribute.hxx>
#include <Handle_TDF_RelocationTable.hxx>
#include <Handle_TDF_DataSet.hxx>
#include <Standard_OStream.hxx>
class Standard_GUID;
class TDF_Label;
class TDF_LabelList;
class TDF_Attribute;
class TDF_RelocationTable;
class TDF_DataSet;


//! Contains a list of references.
class TDataStd_ReferenceList : public TDF_Attribute
{

public:

  
  //! Static methods
  //! ==============
  //! Returns the ID of the list of references (labels) attribute.
  Standard_EXPORT static  const  Standard_GUID& GetID() ;
  
  //! Finds or creates a list of reference values (labels) attribute.
  Standard_EXPORT static   Handle(TDataStd_ReferenceList) Set (const TDF_Label& label) ;
  
  Standard_EXPORT TDataStd_ReferenceList();
  
  Standard_EXPORT   Standard_Boolean IsEmpty()  const;
  
  Standard_EXPORT   Standard_Integer Extent()  const;
  
  Standard_EXPORT   void Prepend (const TDF_Label& value) ;
  
  Standard_EXPORT   void Append (const TDF_Label& value) ;
  
  //! Inserts the <value> before the first meet of <before_value>.
  Standard_EXPORT   Standard_Boolean InsertBefore (const TDF_Label& value, const TDF_Label& before_value) ;
  
  //! Inserts the <value> after the first meet of <after_value>.
  Standard_EXPORT   Standard_Boolean InsertAfter (const TDF_Label& value, const TDF_Label& after_value) ;
  
  //! Removes the first meet of the <value>.
  Standard_EXPORT   Standard_Boolean Remove (const TDF_Label& value) ;
  
  Standard_EXPORT   void Clear() ;
  
  Standard_EXPORT  const  TDF_Label& First()  const;
  
  Standard_EXPORT  const  TDF_Label& Last()  const;
  
  Standard_EXPORT  const  TDF_LabelList& List()  const;
  
  Standard_EXPORT  const  Standard_GUID& ID()  const;
  
  Standard_EXPORT   void Restore (const Handle(TDF_Attribute)& With) ;
  
  Standard_EXPORT   Handle(TDF_Attribute) NewEmpty()  const;
  
  Standard_EXPORT   void Paste (const Handle(TDF_Attribute)& Into, const Handle(TDF_RelocationTable)& RT)  const;
  
  Standard_EXPORT virtual   void References (const Handle(TDF_DataSet)& DS)  const;
  
  Standard_EXPORT virtual   Standard_OStream& Dump (Standard_OStream& anOS)  const;




  DEFINE_STANDARD_RTTI(TDataStd_ReferenceList)

protected:




private: 


  TDF_LabelList myList;


};







#endif // _TDataStd_ReferenceList_HeaderFile