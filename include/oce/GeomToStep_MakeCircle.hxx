// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _GeomToStep_MakeCircle_HeaderFile
#define _GeomToStep_MakeCircle_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Macro.hxx>

#include <Handle_StepGeom_Circle.hxx>
#include <GeomToStep_Root.hxx>
#include <Handle_Geom_Circle.hxx>
#include <Handle_Geom2d_Circle.hxx>
class StepGeom_Circle;
class StdFail_NotDone;
class gp_Circ;
class Geom_Circle;
class Geom2d_Circle;


//! This class implements the mapping between classes
//! Circle from Geom, and Circ from gp, and the class
//! Circle from StepGeom which describes a circle from
//! Prostep.
class GeomToStep_MakeCircle  : public GeomToStep_Root
{
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT GeomToStep_MakeCircle(const gp_Circ& C);
  
  Standard_EXPORT GeomToStep_MakeCircle(const Handle(Geom_Circle)& C);
  
  Standard_EXPORT GeomToStep_MakeCircle(const Handle(Geom2d_Circle)& C);
  
  Standard_EXPORT  const  Handle(StepGeom_Circle)& Value()  const;




protected:





private:



  Handle(StepGeom_Circle) theCircle;


};







#endif // _GeomToStep_MakeCircle_HeaderFile