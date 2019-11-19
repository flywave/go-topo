// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _TDocStd_XLinkRoot_HeaderFile
#define _TDocStd_XLinkRoot_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineHandle.hxx>
#include <Handle_TDocStd_XLinkRoot.hxx>

#include <TDocStd_XLinkPtr.hxx>
#include <TDF_Attribute.hxx>
#include <Handle_TDF_Data.hxx>
#include <Handle_TDF_Attribute.hxx>
#include <Handle_TDF_RelocationTable.hxx>
#include <Standard_OStream.hxx>
class TDocStd_XLinkIterator;
class Standard_GUID;
class TDF_Data;
class TDF_Attribute;
class TDF_RelocationTable;


//! This attribute is the root of all external
//! references contained in a Data from TDF. Only one
//! instance of this class is added to the TDF_Data
//! root label. Starting from this attribute all the
//! Reference are linked together, to be found
//! easely.
class TDocStd_XLinkRoot : public TDF_Attribute
{

public:

  
  //! Returns the ID: 2a96b61d-ec8b-11d0-bee7-080009dc3333
  Standard_EXPORT static  const  Standard_GUID& GetID() ;
  
  //! Sets an empty XLinkRoot to Root or gets the
  //! existing one. Only one attribute per TDF_Data.
  Standard_EXPORT static   Handle(TDocStd_XLinkRoot) Set (const Handle(TDF_Data)& aDF) ;
  
  //! Inserts <anXLinkPtr> at the beginning of the XLink chain.
  Standard_EXPORT static   void Insert (const TDocStd_XLinkPtr& anXLinkPtr) ;
  
  //! Removes <anXLinkPtr> from the XLink chain, if it exists.
  Standard_EXPORT static   void Remove (const TDocStd_XLinkPtr& anXLinkPtr) ;
  
  //! Returns the ID of the attribute.
  Standard_EXPORT  const  Standard_GUID& ID()  const;
  
  //! Returns a null handle.
  Standard_EXPORT   Handle(TDF_Attribute) BackupCopy()  const;
  
  //! Does nothing.
  Standard_EXPORT   void Restore (const Handle(TDF_Attribute)& anAttribute) ;
  
  //! Returns a null handle.
  Standard_EXPORT   Handle(TDF_Attribute) NewEmpty()  const;
  
  //! Does nothing.
  Standard_EXPORT   void Paste (const Handle(TDF_Attribute)& intoAttribute, const Handle(TDF_RelocationTable)& aRelocationTable)  const;
  
  //! Dumps the attribute on <aStream>.
  Standard_EXPORT   Standard_OStream& Dump (Standard_OStream& anOS)  const;


friend class TDocStd_XLinkIterator;


  DEFINE_STANDARD_RTTI(TDocStd_XLinkRoot)

protected:




private: 

  
  //! Initializes fields.
  Standard_EXPORT TDocStd_XLinkRoot();
  
  //! Sets the field <myFirst> with <anXLinkPtr>.
      void First (const TDocStd_XLinkPtr& anXLinkPtr) ;
  
  //! Returns the contents of the field <myFirst>.
      TDocStd_XLinkPtr First()  const;

  TDocStd_XLinkPtr myFirst;


};


#include <TDocStd_XLinkRoot.lxx>





#endif // _TDocStd_XLinkRoot_HeaderFile