// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _StepAP214_AutoDesignPersonAndOrganizationAssignment_HeaderFile
#define _StepAP214_AutoDesignPersonAndOrganizationAssignment_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineHandle.hxx>
#include <Handle_StepAP214_AutoDesignPersonAndOrganizationAssignment.hxx>

#include <Handle_StepAP214_HArray1OfAutoDesignGeneralOrgItem.hxx>
#include <StepBasic_PersonAndOrganizationAssignment.hxx>
#include <Handle_StepBasic_PersonAndOrganization.hxx>
#include <Handle_StepBasic_PersonAndOrganizationRole.hxx>
#include <Standard_Integer.hxx>
class StepAP214_HArray1OfAutoDesignGeneralOrgItem;
class StepBasic_PersonAndOrganization;
class StepBasic_PersonAndOrganizationRole;
class StepAP214_AutoDesignGeneralOrgItem;



class StepAP214_AutoDesignPersonAndOrganizationAssignment : public StepBasic_PersonAndOrganizationAssignment
{

public:

  
  //! Returns a AutoDesignPersonAndOrganizationAssignment
  Standard_EXPORT StepAP214_AutoDesignPersonAndOrganizationAssignment();
  
  Standard_EXPORT virtual   void Init (const Handle(StepBasic_PersonAndOrganization)& aAssignedPersonAndOrganization, const Handle(StepBasic_PersonAndOrganizationRole)& aRole) ;
  
  Standard_EXPORT virtual   void Init (const Handle(StepBasic_PersonAndOrganization)& aAssignedPersonAndOrganization, const Handle(StepBasic_PersonAndOrganizationRole)& aRole, const Handle(StepAP214_HArray1OfAutoDesignGeneralOrgItem)& aItems) ;
  
  Standard_EXPORT   void SetItems (const Handle(StepAP214_HArray1OfAutoDesignGeneralOrgItem)& aItems) ;
  
  Standard_EXPORT   Handle(StepAP214_HArray1OfAutoDesignGeneralOrgItem) Items()  const;
  
  Standard_EXPORT   StepAP214_AutoDesignGeneralOrgItem ItemsValue (const Standard_Integer num)  const;
  
  Standard_EXPORT   Standard_Integer NbItems()  const;




  DEFINE_STANDARD_RTTI(StepAP214_AutoDesignPersonAndOrganizationAssignment)

protected:




private: 


  Handle(StepAP214_HArray1OfAutoDesignGeneralOrgItem) items;


};







#endif // _StepAP214_AutoDesignPersonAndOrganizationAssignment_HeaderFile