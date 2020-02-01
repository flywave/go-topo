// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _StepRepr_PropertyDefinitionRepresentation_HeaderFile
#define _StepRepr_PropertyDefinitionRepresentation_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineHandle.hxx>
#include <Handle_StepRepr_PropertyDefinitionRepresentation.hxx>

#include <StepRepr_RepresentedDefinition.hxx>
#include <Handle_StepRepr_Representation.hxx>
#include <MMgt_TShared.hxx>
class StepRepr_Representation;
class StepRepr_RepresentedDefinition;


//! Representation of STEP entity PropertyDefinitionRepresentation
class StepRepr_PropertyDefinitionRepresentation : public MMgt_TShared
{

public:

  
  //! Empty constructor
  Standard_EXPORT StepRepr_PropertyDefinitionRepresentation();
  
  //! Initialize all fields (own and inherited)
  Standard_EXPORT   void Init (const StepRepr_RepresentedDefinition& aDefinition, const Handle(StepRepr_Representation)& aUsedRepresentation) ;
  
  //! Returns field Definition
  Standard_EXPORT   StepRepr_RepresentedDefinition Definition()  const;
  
  //! Set field Definition
  Standard_EXPORT   void SetDefinition (const StepRepr_RepresentedDefinition& Definition) ;
  
  //! Returns field UsedRepresentation
  Standard_EXPORT   Handle(StepRepr_Representation) UsedRepresentation()  const;
  
  //! Set field UsedRepresentation
  Standard_EXPORT   void SetUsedRepresentation (const Handle(StepRepr_Representation)& UsedRepresentation) ;




  DEFINE_STANDARD_RTTI(StepRepr_PropertyDefinitionRepresentation)

protected:




private: 


  StepRepr_RepresentedDefinition theDefinition;
  Handle(StepRepr_Representation) theUsedRepresentation;


};







#endif // _StepRepr_PropertyDefinitionRepresentation_HeaderFile