// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _GeomFill_Coons_HeaderFile
#define _GeomFill_Coons_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Macro.hxx>

#include <GeomFill_Filling.hxx>
class TColgp_Array1OfPnt;
class TColStd_Array1OfReal;



class GeomFill_Coons  : public GeomFill_Filling
{
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT GeomFill_Coons();
  
  Standard_EXPORT GeomFill_Coons(const TColgp_Array1OfPnt& P1, const TColgp_Array1OfPnt& P2, const TColgp_Array1OfPnt& P3, const TColgp_Array1OfPnt& P4);
  
  Standard_EXPORT GeomFill_Coons(const TColgp_Array1OfPnt& P1, const TColgp_Array1OfPnt& P2, const TColgp_Array1OfPnt& P3, const TColgp_Array1OfPnt& P4, const TColStd_Array1OfReal& W1, const TColStd_Array1OfReal& W2, const TColStd_Array1OfReal& W3, const TColStd_Array1OfReal& W4);
  
  Standard_EXPORT   void Init (const TColgp_Array1OfPnt& P1, const TColgp_Array1OfPnt& P2, const TColgp_Array1OfPnt& P3, const TColgp_Array1OfPnt& P4) ;
  
  Standard_EXPORT   void Init (const TColgp_Array1OfPnt& P1, const TColgp_Array1OfPnt& P2, const TColgp_Array1OfPnt& P3, const TColgp_Array1OfPnt& P4, const TColStd_Array1OfReal& W1, const TColStd_Array1OfReal& W2, const TColStd_Array1OfReal& W3, const TColStd_Array1OfReal& W4) ;




protected:





private:





};







#endif // _GeomFill_Coons_HeaderFile