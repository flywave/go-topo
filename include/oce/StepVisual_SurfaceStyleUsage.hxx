// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _StepVisual_SurfaceStyleUsage_HeaderFile
#define _StepVisual_SurfaceStyleUsage_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineHandle.hxx>
#include <Handle_StepVisual_SurfaceStyleUsage.hxx>

#include <StepVisual_SurfaceSide.hxx>
#include <Handle_StepVisual_SurfaceSideStyle.hxx>
#include <MMgt_TShared.hxx>
class StepVisual_SurfaceSideStyle;



class StepVisual_SurfaceStyleUsage : public MMgt_TShared
{

public:

  
  //! Returns a SurfaceStyleUsage
  Standard_EXPORT StepVisual_SurfaceStyleUsage();
  
  Standard_EXPORT virtual   void Init (const StepVisual_SurfaceSide aSide, const Handle(StepVisual_SurfaceSideStyle)& aStyle) ;
  
  Standard_EXPORT   void SetSide (const StepVisual_SurfaceSide aSide) ;
  
  Standard_EXPORT   StepVisual_SurfaceSide Side()  const;
  
  Standard_EXPORT   void SetStyle (const Handle(StepVisual_SurfaceSideStyle)& aStyle) ;
  
  Standard_EXPORT   Handle(StepVisual_SurfaceSideStyle) Style()  const;




  DEFINE_STANDARD_RTTI(StepVisual_SurfaceStyleUsage)

protected:




private: 


  StepVisual_SurfaceSide side;
  Handle(StepVisual_SurfaceSideStyle) style;


};







#endif // _StepVisual_SurfaceStyleUsage_HeaderFile