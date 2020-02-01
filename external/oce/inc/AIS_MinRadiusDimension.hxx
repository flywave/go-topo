// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _AIS_MinRadiusDimension_HeaderFile
#define _AIS_MinRadiusDimension_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineHandle.hxx>
#include <Handle_AIS_MinRadiusDimension.hxx>

#include <gp_Pnt.hxx>
#include <AIS_EllipseRadiusDimension.hxx>
#include <Standard_Real.hxx>
#include <DsgPrs_ArrowSide.hxx>
#include <PrsMgr_PresentationManager3d.hxx>
#include <Handle_Prs3d_Presentation.hxx>
#include <Standard_Integer.hxx>
#include <Handle_Prs3d_Projector.hxx>
#include <Handle_Geom_Transformation.hxx>
#include <SelectMgr_Selection.hxx>
class Standard_ConstructionError;
class TopoDS_Shape;
class TCollection_ExtendedString;
class gp_Pnt;
class Prs3d_Presentation;
class Prs3d_Projector;
class Geom_Transformation;


//! --  Ellipse  Min  radius  dimension  of  a  Shape  which
//! can  be  Edge  or  Face  (planar  or  cylindrical(surface  of
//! extrusion  or  surface  of  offset))
class AIS_MinRadiusDimension : public AIS_EllipseRadiusDimension
{

public:

  
  //! Max  Ellipse  radius dimension
  //! Shape  can  be  edge  ,  planar  face  or  cylindrical  face
  Standard_EXPORT AIS_MinRadiusDimension(const TopoDS_Shape& aShape, const Standard_Real aVal, const TCollection_ExtendedString& aText);
  
  //! Max  Ellipse  radius dimension with  position
  //! Shape  can  be  edge  ,  planar  face  or  cylindrical  face
  Standard_EXPORT AIS_MinRadiusDimension(const TopoDS_Shape& aShape, const Standard_Real aVal, const TCollection_ExtendedString& aText, const gp_Pnt& aPosition, const DsgPrs_ArrowSide aSymbolPrs, const Standard_Real anArrowSize = 0.0);
  
  //! computes the presentation according to a point of view
  //! given by <aProjector>.
  //! To be Used when the associated degenerated Presentations
  //! have been transformed by <aTrsf> which is not a Pure
  //! Translation. The HLR Prs can't be deducted automatically
  //! WARNING :<aTrsf> must be applied
  //! to the object to display before computation  !!!
  Standard_EXPORT virtual   void Compute (const Handle(Prs3d_Projector)& aProjector, const Handle(Geom_Transformation)& aTrsf, const Handle(Prs3d_Presentation)& aPresentation) ;




  DEFINE_STANDARD_RTTI(AIS_MinRadiusDimension)

protected:




private: 

  
  Standard_EXPORT virtual   void Compute (const Handle(PrsMgr_PresentationManager3d)& aPresentationManager, const Handle(Prs3d_Presentation)& aPresentation, const Standard_Integer aMode = 0) ;
  
  Standard_EXPORT   void Compute (const Handle(Prs3d_Projector)& aProjector, const Handle(Prs3d_Presentation)& aPresentation) ;
  
  Standard_EXPORT virtual   void ComputeSelection (const Handle(SelectMgr_Selection)& aSelection, const Standard_Integer aMode) ;
  
  Standard_EXPORT   void ComputeEllipse (const Handle(Prs3d_Presentation)& aPresentation) ;
  
  Standard_EXPORT   void ComputeArcOfEllipse (const Handle(Prs3d_Presentation)& aPresentation) ;

  gp_Pnt myApexP;
  gp_Pnt myApexN;
  gp_Pnt myEndOfArrow;


};







#endif // _AIS_MinRadiusDimension_HeaderFile