// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _AIS_Line_HeaderFile
#define _AIS_Line_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineHandle.hxx>
#include <Handle_AIS_Line.hxx>

#include <Handle_Geom_Line.hxx>
#include <Handle_Geom_Point.hxx>
#include <Standard_Boolean.hxx>
#include <AIS_InteractiveObject.hxx>
#include <PrsMgr_PresentationManager3d.hxx>
#include <Handle_Prs3d_Presentation.hxx>
#include <Standard_Integer.hxx>
#include <Handle_Prs3d_Projector.hxx>
#include <Handle_Geom_Transformation.hxx>
#include <SelectMgr_Selection.hxx>
#include <AIS_KindOfInteractive.hxx>
#include <Quantity_NameOfColor.hxx>
#include <Standard_Real.hxx>
class Geom_Line;
class Geom_Point;
class Prs3d_Presentation;
class Prs3d_Projector;
class Geom_Transformation;
class Quantity_Color;


//! Constructs line datums to be used in construction of
//! composite shapes.
class AIS_Line : public AIS_InteractiveObject
{

public:

  
  //! Initializes the line aLine.
  Standard_EXPORT AIS_Line(const Handle(Geom_Line)& aLine);
  
  //! Initializes a starting point aStartPoint
  //! and a finishing point aEndPoint for the line.
  Standard_EXPORT AIS_Line(const Handle(Geom_Point)& aStartPoint, const Handle(Geom_Point)& aEndPoint);
  
  //! computes the presentation according to a point of view
  //! given by <aProjector>.
  //! To be Used when the associated degenerated Presentations
  //! have been transformed by <aTrsf> which is not a Pure
  //! Translation. The HLR Prs can't be deducted automatically
  //! WARNING :<aTrsf> must be applied
  //! to the object to display before computation  !!!
  Standard_EXPORT virtual   void Compute (const Handle(Prs3d_Projector)& aProjector, const Handle(Geom_Transformation)& aTrsf, const Handle(Prs3d_Presentation)& aPresentation) ;
  
  //! Returns the signature 5.
    virtual   Standard_Integer Signature()  const;
  
  //! Returns the type Datum.
    virtual   AIS_KindOfInteractive Type()  const;
  
  //! Constructs an infinite line.
     const  Handle(Geom_Line)& Line()  const;
  
  //! Returns the starting point PStart and the end point
  //! PEnd of the line set by SetPoints.
      void Points (Handle(Geom_Point)& PStart, Handle(Geom_Point)& PEnd)  const;
  
  //! instantiates an infinite line.
      void SetLine (const Handle(Geom_Line)& L) ;
  

  //! Sets the starting point P1 and ending point P2 of the
  //! infinite line to create a finite line segment.
      void SetPoints (const Handle(Geom_Point)& P1, const Handle(Geom_Point)& P2) ;
  
  //! Provides a new color setting aColor for the line in the
  //! drawing tool, or "Drawer".
  Standard_EXPORT   void SetColor (const Quantity_NameOfColor aColor) ;
  
  Standard_EXPORT   void SetColor (const Quantity_Color& aColor) ;
  
  //! Provides the new width setting aValue for the line in
  //! the drawing tool, or "Drawer".
  Standard_EXPORT   void SetWidth (const Standard_Real aValue) ;
  
  //! Removes the color setting and returns the original color.
  Standard_EXPORT   void UnsetColor() ;
  
  //! Removes the width setting and returns the original width.
  Standard_EXPORT   void UnsetWidth() ;




  DEFINE_STANDARD_RTTI(AIS_Line)

protected:




private: 

  
  Standard_EXPORT   void Compute (const Handle(PrsMgr_PresentationManager3d)& aPresentationManager, const Handle(Prs3d_Presentation)& aPresentation, const Standard_Integer aMode = 0) ;
  
  Standard_EXPORT   void Compute (const Handle(Prs3d_Projector)& aProjector, const Handle(Prs3d_Presentation)& aPresentation) ;
  
  Standard_EXPORT   void ComputeSelection (const Handle(SelectMgr_Selection)& aSelection, const Standard_Integer aMode) ;
  
  Standard_EXPORT   void ComputeInfiniteLine (const Handle(Prs3d_Presentation)& aPresentation) ;
  
  Standard_EXPORT   void ComputeSegmentLine (const Handle(Prs3d_Presentation)& aPresentation) ;
  
  Standard_EXPORT   void ComputeInfiniteLineSelection (const Handle(SelectMgr_Selection)& aSelection) ;
  
  Standard_EXPORT   void ComputeSegmentLineSelection (const Handle(SelectMgr_Selection)& aSelection) ;

  Handle(Geom_Line) myComponent;
  Handle(Geom_Point) myStartPoint;
  Handle(Geom_Point) myEndPoint;
  Standard_Boolean myLineIsSegment;


};


#include <AIS_Line.lxx>





#endif // _AIS_Line_HeaderFile