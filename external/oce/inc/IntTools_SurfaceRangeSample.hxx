// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _IntTools_SurfaceRangeSample_HeaderFile
#define _IntTools_SurfaceRangeSample_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Macro.hxx>

#include <IntTools_CurveRangeSample.hxx>
#include <Standard_Integer.hxx>
#include <Standard_Real.hxx>
#include <Standard_Boolean.hxx>
class IntTools_CurveRangeSample;
class IntTools_Range;


//! class for range index management of surface
class IntTools_SurfaceRangeSample 
{
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT IntTools_SurfaceRangeSample();
  
  Standard_EXPORT IntTools_SurfaceRangeSample(const Standard_Integer theIndexU, const Standard_Integer theDepthU, const Standard_Integer theIndexV, const Standard_Integer theDepthV);
  
  Standard_EXPORT IntTools_SurfaceRangeSample(const IntTools_CurveRangeSample& theRangeU, const IntTools_CurveRangeSample& theRangeV);
  
  Standard_EXPORT IntTools_SurfaceRangeSample(const IntTools_SurfaceRangeSample& Other);
  
  Standard_EXPORT   IntTools_SurfaceRangeSample& Assign (const IntTools_SurfaceRangeSample& Other) ;
  IntTools_SurfaceRangeSample& operator = (const IntTools_SurfaceRangeSample& Other) 
{
  return Assign(Other);
}
  
      void SetRanges (const IntTools_CurveRangeSample& theRangeU, const IntTools_CurveRangeSample& theRangeV) ;
  
      void GetRanges (IntTools_CurveRangeSample& theRangeU, IntTools_CurveRangeSample& theRangeV)  const;
  
      void SetIndexes (const Standard_Integer theIndexU, const Standard_Integer theIndexV) ;
  
      void GetIndexes (Standard_Integer& theIndexU, Standard_Integer& theIndexV)  const;
  
      void GetDepths (Standard_Integer& theDepthU, Standard_Integer& theDepthV)  const;
  
      void SetSampleRangeU (const IntTools_CurveRangeSample& theRangeSampleU) ;
  
     const  IntTools_CurveRangeSample& GetSampleRangeU()  const;
  
      void SetSampleRangeV (const IntTools_CurveRangeSample& theRangeSampleV) ;
  
     const  IntTools_CurveRangeSample& GetSampleRangeV()  const;
  
      void SetIndexU (const Standard_Integer theIndexU) ;
  
      Standard_Integer GetIndexU()  const;
  
      void SetIndexV (const Standard_Integer theIndexV) ;
  
      Standard_Integer GetIndexV()  const;
  
      void SetDepthU (const Standard_Integer theDepthU) ;
  
      Standard_Integer GetDepthU()  const;
  
      void SetDepthV (const Standard_Integer theDepthV) ;
  
      Standard_Integer GetDepthV()  const;
  
  Standard_EXPORT   IntTools_Range GetRangeU (const Standard_Real theFirstU, const Standard_Real theLastU, const Standard_Integer theNbSampleU)  const;
  
  Standard_EXPORT   IntTools_Range GetRangeV (const Standard_Real theFirstV, const Standard_Real theLastV, const Standard_Integer theNbSampleV)  const;
  
      Standard_Boolean IsEqual (const IntTools_SurfaceRangeSample& Other)  const;
  
      Standard_Integer GetRangeIndexUDeeper (const Standard_Integer theNbSampleU)  const;
  
      Standard_Integer GetRangeIndexVDeeper (const Standard_Integer theNbSampleV)  const;




protected:





private:



  IntTools_CurveRangeSample myRangeU;
  IntTools_CurveRangeSample myRangeV;


};


#include <IntTools_SurfaceRangeSample.lxx>





#endif // _IntTools_SurfaceRangeSample_HeaderFile