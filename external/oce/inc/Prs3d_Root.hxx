// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _Prs3d_Root_HeaderFile
#define _Prs3d_Root_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Macro.hxx>

#include <Handle_Graphic3d_Group.hxx>
#include <Handle_Prs3d_Presentation.hxx>
class Graphic3d_Group;
class Prs3d_Presentation;


//! A root class for the standard presentation algorithms
//! of the StdPrs package.
class Prs3d_Root 
{
public:

  DEFINE_STANDARD_ALLOC

  
  //! Returns the current group of primititves inside graphic
  //! objects in the display.
  //! A group also contains the attributes whose ranges are
  //! limited to the primitives in it.
  Standard_EXPORT static   Handle(Graphic3d_Group) CurrentGroup (const Handle(Prs3d_Presentation)& Prs3d) ;
  
  //! Returns the new group of primitives inside graphic
  //! objects in the display.
  //! A group also contains the attributes whose ranges are limited to the primitives in it.
  Standard_EXPORT static   Handle(Graphic3d_Group) NewGroup (const Handle(Prs3d_Presentation)& Prs3d) ;




protected:





private:





};







#endif // _Prs3d_Root_HeaderFile
