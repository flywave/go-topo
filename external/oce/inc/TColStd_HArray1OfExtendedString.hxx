// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _TColStd_HArray1OfExtendedString_HeaderFile
#define _TColStd_HArray1OfExtendedString_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineHandle.hxx>
#include <Handle_TColStd_HArray1OfExtendedString.hxx>

#include <TColStd_Array1OfExtendedString.hxx>
#include <MMgt_TShared.hxx>
#include <Standard_Integer.hxx>
class Standard_RangeError;
class Standard_DimensionMismatch;
class Standard_OutOfRange;
class Standard_OutOfMemory;
class TCollection_ExtendedString;
class TColStd_Array1OfExtendedString;



class TColStd_HArray1OfExtendedString : public MMgt_TShared
{

public:

  
    TColStd_HArray1OfExtendedString(const Standard_Integer Low, const Standard_Integer Up);
  
    TColStd_HArray1OfExtendedString(const Standard_Integer Low, const Standard_Integer Up, const TCollection_ExtendedString& V);
  
      void Init (const TCollection_ExtendedString& V) ;
  
      Standard_Integer Length()  const;
  
      Standard_Integer Lower()  const;
  
      Standard_Integer Upper()  const;
  
      void SetValue (const Standard_Integer Index, const TCollection_ExtendedString& Value) ;
  
     const  TCollection_ExtendedString& Value (const Standard_Integer Index)  const;
  
      TCollection_ExtendedString& ChangeValue (const Standard_Integer Index) ;
  
     const  TColStd_Array1OfExtendedString& Array1()  const;
  
      TColStd_Array1OfExtendedString& ChangeArray1() ;




  DEFINE_STANDARD_RTTI(TColStd_HArray1OfExtendedString)

protected:




private: 


  TColStd_Array1OfExtendedString myArray;


};

#define ItemHArray1 TCollection_ExtendedString
#define ItemHArray1_hxx <TCollection_ExtendedString.hxx>
#define TheArray1 TColStd_Array1OfExtendedString
#define TheArray1_hxx <TColStd_Array1OfExtendedString.hxx>
#define TCollection_HArray1 TColStd_HArray1OfExtendedString
#define TCollection_HArray1_hxx <TColStd_HArray1OfExtendedString.hxx>
#define Handle_TCollection_HArray1 Handle_TColStd_HArray1OfExtendedString
#define TCollection_HArray1_Type_() TColStd_HArray1OfExtendedString_Type_()

#include <TCollection_HArray1.lxx>

#undef ItemHArray1
#undef ItemHArray1_hxx
#undef TheArray1
#undef TheArray1_hxx
#undef TCollection_HArray1
#undef TCollection_HArray1_hxx
#undef Handle_TCollection_HArray1
#undef TCollection_HArray1_Type_




#endif // _TColStd_HArray1OfExtendedString_HeaderFile