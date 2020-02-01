// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _GC_MakeTrimmedCylinder_HeaderFile
#define _GC_MakeTrimmedCylinder_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Macro.hxx>

#include <Handle_Geom_RectangularTrimmedSurface.hxx>
#include <GC_Root.hxx>
#include <Standard_Real.hxx>
class Geom_RectangularTrimmedSurface;
class StdFail_NotDone;
class gp_Pnt;
class gp_Circ;
class gp_Ax1;
class gp_Cylinder;


//! Implements construction algorithms for a trimmed
//! cylinder limited by two planes orthogonal to its axis.
//! The result is a Geom_RectangularTrimmedSurface surface.
//! A MakeTrimmedCylinder provides a framework for:
//! -   defining the construction of the trimmed cylinder,
//! -   implementing the construction algorithm, and
//! -   consulting the results. In particular, the Value
//! function returns the constructed trimmed cylinder.
class GC_MakeTrimmedCylinder  : public GC_Root
{
public:

  DEFINE_STANDARD_ALLOC

  
  //! Make a cylindricalSurface <Cyl> from Geom
  //! Its axis is is <P1P2> and its radius is the distance
  //! between <P3> and <P1P2>.
  //! The height is the distance between P1 and P2.
  Standard_EXPORT GC_MakeTrimmedCylinder(const gp_Pnt& P1, const gp_Pnt& P2, const gp_Pnt& P3);
  
  //! Make a cylindricalSurface <Cyl> from gp by its base <Circ>.
  //! Its axis is the normal to the plane defined bi <Circ>.
  //! <Height> can be greater than zero or lower than zero.
  //! In the first case the V parametric direction of the
  //! result has the same orientation as the normal to <Circ>.
  //! In the other case it has the opposite orientation.
  Standard_EXPORT GC_MakeTrimmedCylinder(const gp_Circ& Circ, const Standard_Real Height);
  
  //! Make a cylindricalSurface <Cyl> from gp by its
  //! axis <A1> and its radius <Radius>.
  //! It returns NullObject if <Radius> is lower than zero.
  //! <Height> can be greater than zero or lower than zero.
  //! In the first case the V parametric direction of the
  //! result has the same orientation as <A1>.
  //! In the other case it has the opposite orientation.
  Standard_EXPORT GC_MakeTrimmedCylinder(const gp_Ax1& A1, const Standard_Real Radius, const Standard_Real Height);
  
  //! Make a RectangularTrimmedSurface <Cylinder> from gp by
  //! a cylinder from gp.
  //! It is trimmed by the point <P> and the heigh <Heigh>.
  //! <Height> can be greater than zero or lower than zero.
  //! in the first case the limit section is in the side of
  //! the positives V paramters of <Cyl> and in the other
  //! side if <Heigh> is lower than zero.
  Standard_EXPORT GC_MakeTrimmedCylinder(const gp_Cylinder& Cyl, const gp_Pnt& P, const Standard_Real Height);
  
  //! Make a RectangularTrimmedSurface <Cylinder> from gp by
  //! a cylinder from gp.
  //! It is trimmed by the two points <P1> and <P2>.
  //! Warning
  //! If an error occurs (that is, when IsDone returns
  //! false), the Status function returns:
  //! -   gce_NegativeRadius if Radius is less than 0.0, or
  //! -   gce_ConfusedPoints if the points P1 and P2 are coincident.
  //! -   gce_ColinearPoints if the points P1, P2 and P3 are collinear.
  Standard_EXPORT GC_MakeTrimmedCylinder(const gp_Cylinder& Cyl, const gp_Pnt& P1, const gp_Pnt& P2);
  
  //! Returns the constructed trimmed cylinder.
  //! Exceptions
  //! StdFail_NotDone if no trimmed cylinder is constructed.
  Standard_EXPORT  const  Handle(Geom_RectangularTrimmedSurface)& Value()  const;
  
  Standard_EXPORT  const  Handle(Geom_RectangularTrimmedSurface)& Operator()  const;
Standard_EXPORT operator Handle_Geom_RectangularTrimmedSurface() const;




protected:





private:



  Handle(Geom_RectangularTrimmedSurface) TheCyl;


};







#endif // _GC_MakeTrimmedCylinder_HeaderFile