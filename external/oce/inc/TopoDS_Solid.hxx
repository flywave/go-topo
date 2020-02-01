// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _TopoDS_Solid_HeaderFile
#define _TopoDS_Solid_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Macro.hxx>

#include <TopoDS_Shape.hxx>


//! Describes a solid shape which
//! - references an underlying solid shape with the
//! potential to be given a location and an orientation
//! - has a location for the underlying shape, giving its
//! placement in the local coordinate system
//! - has an orientation for the underlying shape, in
//! terms of its geometry (as opposed to orientation in
//! relation to other shapes).
class TopoDS_Solid  : public TopoDS_Shape
{
public:

  DEFINE_STANDARD_ALLOC

  
  //! Constructs an Undefined Solid.
    TopoDS_Solid();




protected:





private:





};


#include <TopoDS_Solid.lxx>





#endif // _TopoDS_Solid_HeaderFile