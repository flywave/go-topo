// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _BRepTools_ShapeSet_HeaderFile
#define _BRepTools_ShapeSet_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Macro.hxx>

#include <BRep_Builder.hxx>
#include <GeomTools_SurfaceSet.hxx>
#include <GeomTools_CurveSet.hxx>
#include <GeomTools_Curve2dSet.hxx>
#include <TColStd_IndexedMapOfTransient.hxx>
#include <Standard_Boolean.hxx>
#include <TopTools_ShapeSet.hxx>
#include <Standard_OStream.hxx>
#include <Standard_IStream.hxx>
#include <TopAbs_ShapeEnum.hxx>
class BRep_Builder;
class TopoDS_Shape;


//! Contains a Shape and all  its subshapes, locations
//! and geometries.
//!
//! The topology is inherited from TopTools.
class BRepTools_ShapeSet  : public TopTools_ShapeSet
{
public:

  DEFINE_STANDARD_ALLOC

  
  //! Builds an empty ShapeSet.
  //! Parameter <isWithTriangles> is added for XML Persistence
  Standard_EXPORT BRepTools_ShapeSet(const Standard_Boolean isWithTriangles = Standard_True);
  
  //! Builds an empty ShapeSet.
  //! Parameter <isWithTriangles> is added for XML Persistence
  Standard_EXPORT BRepTools_ShapeSet(const BRep_Builder& B, const Standard_Boolean isWithTriangles = Standard_True);
  
  //! Clears the content of the set.
  Standard_EXPORT virtual   void Clear() ;
  
  //! Stores the goemetry of <S>.
  Standard_EXPORT virtual   void AddGeometry (const TopoDS_Shape& S) ;
  
  //! Dumps the geometry of me on the stream <OS>.
  Standard_EXPORT virtual   void DumpGeometry (Standard_OStream& OS)  const;
  
  //! Writes the geometry of  me  on the stream <OS> in a
  //! format that can be read back by Read.
  Standard_EXPORT virtual   void WriteGeometry (Standard_OStream& OS) ;
  
  //! Reads the geometry of me from the  stream  <IS>.
  Standard_EXPORT virtual   void ReadGeometry (Standard_IStream& IS) ;
  
  //! Dumps the geometry of <S> on the stream <OS>.
  Standard_EXPORT virtual   void DumpGeometry (const TopoDS_Shape& S, Standard_OStream& OS)  const;
  
  //! Writes the geometry of <S>  on the stream <OS> in a
  //! format that can be read back by Read.
  Standard_EXPORT virtual   void WriteGeometry (const TopoDS_Shape& S, Standard_OStream& OS)  const;
  
  //! Reads the geometry of a shape of type <T> from the
  //! stream <IS> and returns it in <S>.
  Standard_EXPORT virtual   void ReadGeometry (const TopAbs_ShapeEnum T, Standard_IStream& IS, TopoDS_Shape& S) ;
  
  //! Inserts  the shape <S2> in  the  shape <S1>.  This
  //! method must be   redefined  to  use   the  correct
  //! builder.
  Standard_EXPORT virtual   void AddShapes (TopoDS_Shape& S1, const TopoDS_Shape& S2) ;
  
  Standard_EXPORT virtual   void Check (const TopAbs_ShapeEnum T, TopoDS_Shape& S) ;
  
  //! Reads the 3d polygons  of me
  //! from the  stream  <IS>.
  Standard_EXPORT   void ReadPolygon3D (Standard_IStream& IS) ;
  
  //! Writes the 3d polygons
  //! on the stream <OS> in a format that can
  //! be read back by Read.
  Standard_EXPORT   void WritePolygon3D (Standard_OStream& OS, const Standard_Boolean Compact = Standard_True)  const;
  
  //! Dumps the 3d polygons
  //! on the stream <OS>.
  Standard_EXPORT   void DumpPolygon3D (Standard_OStream& OS)  const;
  
  //! Reads the triangulation of me
  //! from the  stream  <IS>.
  Standard_EXPORT   void ReadTriangulation (Standard_IStream& IS) ;
  
  //! Writes the triangulation
  //! on the stream <OS> in a format that can
  //! be read back by Read.
  Standard_EXPORT   void WriteTriangulation (Standard_OStream& OS, const Standard_Boolean Compact = Standard_True)  const;
  
  //! Dumps the triangulation
  //! on the stream <OS>.
  Standard_EXPORT   void DumpTriangulation (Standard_OStream& OS)  const;
  
  //! Reads the polygons on triangulation of me
  //! from the  stream  <IS>.
  Standard_EXPORT   void ReadPolygonOnTriangulation (Standard_IStream& IS) ;
  
  //! Writes the polygons on triangulation
  //! on the stream <OS> in a format that can
  //! be read back by Read.
  Standard_EXPORT   void WritePolygonOnTriangulation (Standard_OStream& OS, const Standard_Boolean Compact = Standard_True)  const;
  
  //! Dumps the polygons on triangulation
  //! on the stream <OS>.
  Standard_EXPORT   void DumpPolygonOnTriangulation (Standard_OStream& OS)  const;




protected:





private:



  BRep_Builder myBuilder;
  GeomTools_SurfaceSet mySurfaces;
  GeomTools_CurveSet myCurves;
  GeomTools_Curve2dSet myCurves2d;
  TColStd_IndexedMapOfTransient myPolygons2D;
  TColStd_IndexedMapOfTransient myPolygons3D;
  TColStd_IndexedMapOfTransient myTriangulations;
  TColStd_IndexedMapOfTransient myNodes;
  Standard_Boolean myWithTriangles;


};







#endif // _BRepTools_ShapeSet_HeaderFile