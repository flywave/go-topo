// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _MDF_TypeASDriverMap_HeaderFile
#define _MDF_TypeASDriverMap_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Macro.hxx>

#include <TCollection_BasicMap.hxx>
#include <Handle_Standard_Type.hxx>
#include <Handle_MDF_ASDriver.hxx>
#include <Handle_MDF_DataMapNodeOfTypeASDriverMap.hxx>
#include <Standard_Integer.hxx>
#include <Standard_Boolean.hxx>
#include <Standard_Address.hxx>
class Standard_DomainError;
class Standard_NoSuchObject;
class Standard_Type;
class MDF_ASDriver;
class TColStd_MapTransientHasher;
class MDF_DataMapNodeOfTypeASDriverMap;
class MDF_DataMapIteratorOfTypeASDriverMap;



class MDF_TypeASDriverMap  : public TCollection_BasicMap
{
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT MDF_TypeASDriverMap(const Standard_Integer NbBuckets = 1);
  
  Standard_EXPORT   MDF_TypeASDriverMap& Assign (const MDF_TypeASDriverMap& Other) ;
  MDF_TypeASDriverMap& operator = (const MDF_TypeASDriverMap& Other) 
{
  return Assign(Other);
}
  
  Standard_EXPORT   void ReSize (const Standard_Integer NbBuckets) ;
  
  Standard_EXPORT   void Clear() ;
~MDF_TypeASDriverMap()
{
  Clear();
}
  
  Standard_EXPORT   Standard_Boolean Bind (const Handle(Standard_Type)& K, const Handle(MDF_ASDriver)& I) ;
  
  Standard_EXPORT   Standard_Boolean IsBound (const Handle(Standard_Type)& K)  const;
  
  Standard_EXPORT   Standard_Boolean UnBind (const Handle(Standard_Type)& K) ;
  
  Standard_EXPORT  const  Handle(MDF_ASDriver)& Find (const Handle(Standard_Type)& K)  const;
 const  Handle(MDF_ASDriver)& operator() (const Handle(Standard_Type)& K)  const
{
  return Find(K);
}
  
  Standard_EXPORT   Handle(MDF_ASDriver)& ChangeFind (const Handle(Standard_Type)& K) ;
  Handle(MDF_ASDriver)& operator() (const Handle(Standard_Type)& K) 
{
  return ChangeFind(K);
}
  
  Standard_EXPORT   Standard_Address Find1 (const Handle(Standard_Type)& K)  const;
  
  Standard_EXPORT   Standard_Address ChangeFind1 (const Handle(Standard_Type)& K) ;




protected:





private:

  
  Standard_EXPORT MDF_TypeASDriverMap(const MDF_TypeASDriverMap& Other);




};







#endif // _MDF_TypeASDriverMap_HeaderFile