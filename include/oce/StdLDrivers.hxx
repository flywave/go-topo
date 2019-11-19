// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _StdLDrivers_HeaderFile
#define _StdLDrivers_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Macro.hxx>

#include <Handle_Standard_Transient.hxx>
class Standard_Transient;
class Standard_GUID;
class StdLDrivers_DocumentRetrievalDriver;
class StdLDrivers_DocumentStorageDriver;



class StdLDrivers 
{
public:

  DEFINE_STANDARD_ALLOC

  
  //! Depending from the  ID, returns a list of  storage
  //! or retrieval attribute drivers. Used for plugin
  Standard_EXPORT static   Handle(Standard_Transient) Factory (const Standard_GUID& aGUID) ;




protected:





private:




friend class StdLDrivers_DocumentRetrievalDriver;
friend class StdLDrivers_DocumentStorageDriver;

};







#endif // _StdLDrivers_HeaderFile