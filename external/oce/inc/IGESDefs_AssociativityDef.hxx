// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _IGESDefs_AssociativityDef_HeaderFile
#define _IGESDefs_AssociativityDef_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineHandle.hxx>
#include <Handle_IGESDefs_AssociativityDef.hxx>

#include <Handle_TColStd_HArray1OfInteger.hxx>
#include <Handle_IGESBasic_HArray1OfHArray1OfInteger.hxx>
#include <IGESData_IGESEntity.hxx>
#include <Standard_Integer.hxx>
#include <Standard_Boolean.hxx>
class TColStd_HArray1OfInteger;
class IGESBasic_HArray1OfHArray1OfInteger;
class Standard_DimensionMismatch;
class Standard_OutOfRange;


//! defines IGES Associativity Definition Entity, Type <302>
//! Form <5001 - 9999> in package IGESDefs.
//! This class permits the preprocessor to define an
//! associativity schema. i.e., by using it preprocessor
//! defines the type of relationship.
class IGESDefs_AssociativityDef : public IGESData_IGESEntity
{

public:

  
  Standard_EXPORT IGESDefs_AssociativityDef();
  
  //! This method is used to set the fields of the class
  //! AssociativityDef
  //! - requirements : Back Pointers requirements
  //! - orders       : Class Orders
  //! - numItems     : Number of Items per Class
  //! - items        : Items in each class
  //! raises exception if lengths of the arrays are not the same.
  Standard_EXPORT   void Init (const Handle(TColStd_HArray1OfInteger)& requirements, const Handle(TColStd_HArray1OfInteger)& orders, const Handle(TColStd_HArray1OfInteger)& numItems, const Handle(IGESBasic_HArray1OfHArray1OfInteger)& items) ;
  
  Standard_EXPORT   void SetFormNumber (const Standard_Integer form) ;
  
  //! returns the Number of class definitions
  Standard_EXPORT   Standard_Integer NbClassDefs()  const;
  
  //! returns 1 if the theBackPointerReqs(ClassNum) = 1
  //! returns 0 if the theBackPointerReqs(ClassNum) = 2
  //! raises exception if ClassNum <= 0 or ClassNum > NbClassDefs()
  Standard_EXPORT   Standard_Boolean IsBackPointerReq (const Standard_Integer ClassNum)  const;
  
  //! returns 1 or 2
  //! raises exception if ClassNum <= 0 or ClassNum > NbClassDefs()
  Standard_EXPORT   Standard_Integer BackPointerReq (const Standard_Integer ClassNum)  const;
  
  //! returns 1 if theClassOrders(ClassNum) = 1 (ordered class)
  //! returns 0 if theClassOrders(ClassNum) = 2 (unordered class)
  //! raises exception if ClassNum <= 0 or ClassNum > NbClassDefs()
  Standard_EXPORT   Standard_Boolean IsOrdered (const Standard_Integer ClassNum)  const;
  
  //! returns 1 or 2
  //! raises exception if ClassNum <= 0 or ClassNum > NbClassDefs()
  Standard_EXPORT   Standard_Integer ClassOrder (const Standard_Integer ClassNum)  const;
  
  //! returns no. of items per class entry
  //! raises exception if ClassNum <= 0 or ClassNum > NbClassDefs()
  Standard_EXPORT   Standard_Integer NbItemsPerClass (const Standard_Integer ClassNum)  const;
  
  //! returns ItemNum'th Item of ClassNum'th Class
  //! raises exception if
  //! ClassNum <= 0 or ClassNum > NbClassDefs()
  //! ItemNum <= 0 or ItemNum > NbItemsPerClass(ClassNum)
  Standard_EXPORT   Standard_Integer Item (const Standard_Integer ClassNum, const Standard_Integer ItemNum)  const;




  DEFINE_STANDARD_RTTI(IGESDefs_AssociativityDef)

protected:




private: 


  Handle(TColStd_HArray1OfInteger) theBackPointerReqs;
  Handle(TColStd_HArray1OfInteger) theClassOrders;
  Handle(TColStd_HArray1OfInteger) theNbItemsPerClass;
  Handle(IGESBasic_HArray1OfHArray1OfInteger) theItems;


};







#endif // _IGESDefs_AssociativityDef_HeaderFile
