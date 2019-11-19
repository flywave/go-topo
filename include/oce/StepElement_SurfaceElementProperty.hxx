// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _StepElement_SurfaceElementProperty_HeaderFile
#define _StepElement_SurfaceElementProperty_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineHandle.hxx>
#include <Handle_StepElement_SurfaceElementProperty.hxx>

#include <Handle_TCollection_HAsciiString.hxx>
#include <Handle_StepElement_SurfaceSectionField.hxx>
#include <MMgt_TShared.hxx>
class TCollection_HAsciiString;
class StepElement_SurfaceSectionField;


//! Representation of STEP entity SurfaceElementProperty
class StepElement_SurfaceElementProperty : public MMgt_TShared
{

public:

  
  //! Empty constructor
  Standard_EXPORT StepElement_SurfaceElementProperty();
  
  //! Initialize all fields (own and inherited)
  Standard_EXPORT   void Init (const Handle(TCollection_HAsciiString)& aPropertyId, const Handle(TCollection_HAsciiString)& aDescription, const Handle(StepElement_SurfaceSectionField)& aSection) ;
  
  //! Returns field PropertyId
  Standard_EXPORT   Handle(TCollection_HAsciiString) PropertyId()  const;
  
  //! Set field PropertyId
  Standard_EXPORT   void SetPropertyId (const Handle(TCollection_HAsciiString)& PropertyId) ;
  
  //! Returns field Description
  Standard_EXPORT   Handle(TCollection_HAsciiString) Description()  const;
  
  //! Set field Description
  Standard_EXPORT   void SetDescription (const Handle(TCollection_HAsciiString)& Description) ;
  
  //! Returns field Section
  Standard_EXPORT   Handle(StepElement_SurfaceSectionField) Section()  const;
  
  //! Set field Section
  Standard_EXPORT   void SetSection (const Handle(StepElement_SurfaceSectionField)& Section) ;




  DEFINE_STANDARD_RTTI(StepElement_SurfaceElementProperty)

protected:




private: 


  Handle(TCollection_HAsciiString) thePropertyId;
  Handle(TCollection_HAsciiString) theDescription;
  Handle(StepElement_SurfaceSectionField) theSection;


};







#endif // _StepElement_SurfaceElementProperty_HeaderFile