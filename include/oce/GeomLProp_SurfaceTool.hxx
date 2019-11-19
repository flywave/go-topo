// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _GeomLProp_SurfaceTool_HeaderFile
#define _GeomLProp_SurfaceTool_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Macro.hxx>

#include <Handle_Geom_Surface.hxx>
#include <Standard_Real.hxx>
#include <Standard_Integer.hxx>
class Geom_Surface;
class gp_Pnt;
class gp_Vec;



class GeomLProp_SurfaceTool 
{
public:

  DEFINE_STANDARD_ALLOC

  
  //! Computes the point <P> of parameter <U> and <V> on the
  //! Surface <S>.
  Standard_EXPORT static   void Value (const Handle(Geom_Surface)& S, const Standard_Real U, const Standard_Real V, gp_Pnt& P) ;
  
  //! Computes the point <P> and first derivative <D1*> of
  //! parameter <U> and <V> on the Surface <S>.
  Standard_EXPORT static   void D1 (const Handle(Geom_Surface)& S, const Standard_Real U, const Standard_Real V, gp_Pnt& P, gp_Vec& D1U, gp_Vec& D1V) ;
  
  //! Computes the point <P>, the first derivative <D1*> and second
  //! derivative <D2*> of parameter <U> and <V> on the Surface <S>.
  Standard_EXPORT static   void D2 (const Handle(Geom_Surface)& S, const Standard_Real U, const Standard_Real V, gp_Pnt& P, gp_Vec& D1U, gp_Vec& D1V, gp_Vec& D2U, gp_Vec& D2V, gp_Vec& DUV) ;
  
  Standard_EXPORT static   gp_Vec DN (const Handle(Geom_Surface)& S, const Standard_Real U, const Standard_Real V, const Standard_Integer IU, const Standard_Integer IV) ;
  
  //! returns the order of continuity of the Surface <S>.
  //! returns 1 : first derivative only is computable
  //! returns 2 : first and second derivative only are computable.
  Standard_EXPORT static   Standard_Integer Continuity (const Handle(Geom_Surface)& S) ;
  
  //! returns the bounds of the Surface.
  Standard_EXPORT static   void Bounds (const Handle(Geom_Surface)& S, Standard_Real& U1, Standard_Real& V1, Standard_Real& U2, Standard_Real& V2) ;




protected:





private:





};







#endif // _GeomLProp_SurfaceTool_HeaderFile