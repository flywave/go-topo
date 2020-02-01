// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _TFunction_DataMapIteratorOfDataMapOfGUIDDriver_HeaderFile
#define _TFunction_DataMapIteratorOfDataMapOfGUIDDriver_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Macro.hxx>

#include <TCollection_BasicMapIterator.hxx>
#include <Handle_TFunction_Driver.hxx>
#include <Handle_TFunction_DataMapNodeOfDataMapOfGUIDDriver.hxx>
class Standard_NoSuchObject;
class Standard_GUID;
class TFunction_Driver;
class TFunction_DataMapOfGUIDDriver;
class TFunction_DataMapNodeOfDataMapOfGUIDDriver;



class TFunction_DataMapIteratorOfDataMapOfGUIDDriver  : public TCollection_BasicMapIterator
{
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT TFunction_DataMapIteratorOfDataMapOfGUIDDriver();
  
  Standard_EXPORT TFunction_DataMapIteratorOfDataMapOfGUIDDriver(const TFunction_DataMapOfGUIDDriver& aMap);
  
  Standard_EXPORT   void Initialize (const TFunction_DataMapOfGUIDDriver& aMap) ;
  
  Standard_EXPORT  const  Standard_GUID& Key()  const;
  
  Standard_EXPORT  const  Handle(TFunction_Driver)& Value()  const;




protected:





private:





};







#endif // _TFunction_DataMapIteratorOfDataMapOfGUIDDriver_HeaderFile