// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _TColStd_Array1OfTransient_HeaderFile
#define _TColStd_Array1OfTransient_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Macro.hxx>

#include <Standard_Integer.hxx>
#include <Standard_Address.hxx>
#include <Standard_Boolean.hxx>
#include <Handle_Standard_Transient.hxx>
class Standard_RangeError;
class Standard_DimensionMismatch;
class Standard_OutOfRange;
class Standard_OutOfMemory;
class Standard_Transient;



class TColStd_Array1OfTransient 
{
public:

  DEFINE_STANDARD_ALLOC

  
    TColStd_Array1OfTransient(const Standard_Integer Low, const Standard_Integer Up);
  
    TColStd_Array1OfTransient(const Handle(Standard_Transient)& Item, const Standard_Integer Low, const Standard_Integer Up);
  
  Standard_EXPORT   void Init (const Handle(Standard_Transient)& V) ;
  
      void Destroy() ;
~TColStd_Array1OfTransient()
{
  Destroy();
}
  
      Standard_Boolean IsAllocated()  const;
  
  Standard_EXPORT  const  TColStd_Array1OfTransient& Assign (const TColStd_Array1OfTransient& Other) ;
 const  TColStd_Array1OfTransient& operator = (const TColStd_Array1OfTransient& Other) 
{
  return Assign(Other);
}
  
      Standard_Integer Length()  const;
  
      Standard_Integer Lower()  const;
  
      Standard_Integer Upper()  const;
  
      void SetValue (const Standard_Integer Index, const Handle(Standard_Transient)& Value) ;
  
     const  Handle(Standard_Transient)& Value (const Standard_Integer Index)  const;
   const  Handle(Standard_Transient)& operator () (const Standard_Integer Index)  const
{
  return Value(Index);
}
  
      Handle(Standard_Transient)& ChangeValue (const Standard_Integer Index) ;
    Handle(Standard_Transient)& operator () (const Standard_Integer Index) 
{
  return ChangeValue(Index);
}




protected:





private:

  
  Standard_EXPORT TColStd_Array1OfTransient(const TColStd_Array1OfTransient& AnArray);


  Standard_Integer myLowerBound;
  Standard_Integer myUpperBound;
  Standard_Address myStart;
  Standard_Boolean isAllocated;


};

#define Array1Item Handle(Standard_Transient)
#define Array1Item_hxx <Standard_Transient.hxx>
#define TCollection_Array1 TColStd_Array1OfTransient
#define TCollection_Array1_hxx <TColStd_Array1OfTransient.hxx>

#include <TCollection_Array1.lxx>

#undef Array1Item
#undef Array1Item_hxx
#undef TCollection_Array1
#undef TCollection_Array1_hxx




#endif // _TColStd_Array1OfTransient_HeaderFile