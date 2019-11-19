// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _XSControl_Vars_HeaderFile
#define _XSControl_Vars_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineHandle.hxx>
#include <Handle_XSControl_Vars.hxx>

#include <Handle_Dico_DictionaryOfTransient.hxx>
#include <MMgt_TShared.hxx>
#include <Standard_CString.hxx>
#include <Handle_Standard_Transient.hxx>
#include <Handle_Geom_Geometry.hxx>
#include <Handle_Geom2d_Curve.hxx>
#include <Handle_Geom_Curve.hxx>
#include <Handle_Geom_Surface.hxx>
#include <Standard_Boolean.hxx>
class Dico_DictionaryOfTransient;
class Standard_Transient;
class Geom_Geometry;
class Geom2d_Curve;
class Geom_Curve;
class Geom_Surface;
class gp_Pnt;
class gp_Pnt2d;
class TopoDS_Shape;


//! Defines a receptacle for externally defined variables, each
//! one has a name
//!
//! I.E. a WorkSession for XSTEP is generally used inside a
//! context, which brings variables, especially shapes and
//! geometries. For instance DRAW or an application engine
//!
//! This class provides a common form for this. It also provides
//! a default implementation (locally recorded variables in a
//! dictionary), but which is aimed to be redefined
class XSControl_Vars : public MMgt_TShared
{

public:

  
  Standard_EXPORT XSControl_Vars();
  
  Standard_EXPORT virtual   void Set (const Standard_CString name, const Handle(Standard_Transient)& val) ;
  
  Standard_EXPORT virtual   Handle(Standard_Transient) Get (Standard_CString& name)  const;
  
  Standard_EXPORT virtual   Handle(Geom_Geometry) GetGeom (Standard_CString& name)  const;
  
  Standard_EXPORT virtual   Handle(Geom2d_Curve) GetCurve2d (Standard_CString& name)  const;
  
  Standard_EXPORT virtual   Handle(Geom_Curve) GetCurve (Standard_CString& name)  const;
  
  Standard_EXPORT virtual   Handle(Geom_Surface) GetSurface (Standard_CString& name)  const;
  
  Standard_EXPORT virtual   void SetPoint (const Standard_CString name, const gp_Pnt& val) ;
  
  Standard_EXPORT virtual   void SetPoint2d (const Standard_CString name, const gp_Pnt2d& val) ;
  
  Standard_EXPORT virtual   Standard_Boolean GetPoint (Standard_CString& name, gp_Pnt& pnt)  const;
  
  Standard_EXPORT virtual   Standard_Boolean GetPoint2d (Standard_CString& name, gp_Pnt2d& pnt)  const;
  
  Standard_EXPORT virtual   void SetShape (const Standard_CString name, const TopoDS_Shape& val) ;
  
  Standard_EXPORT virtual   TopoDS_Shape GetShape (Standard_CString& name)  const;




  DEFINE_STANDARD_RTTI(XSControl_Vars)

protected:




private: 


  Handle(Dico_DictionaryOfTransient) thevars;


};







#endif // _XSControl_Vars_HeaderFile