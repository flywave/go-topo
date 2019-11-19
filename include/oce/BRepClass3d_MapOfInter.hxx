// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _BRepClass3d_MapOfInter_HeaderFile
#define _BRepClass3d_MapOfInter_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Macro.hxx>

#include <TCollection_BasicMap.hxx>
#include <Standard_Address.hxx>
#include <Handle_BRepClass3d_DataMapNodeOfMapOfInter.hxx>
#include <Standard_Integer.hxx>
#include <Standard_Boolean.hxx>
class Standard_DomainError;
class Standard_NoSuchObject;
class TopoDS_Shape;
class TopTools_ShapeMapHasher;
class BRepClass3d_DataMapNodeOfMapOfInter;
class BRepClass3d_DataMapIteratorOfMapOfInter;



class BRepClass3d_MapOfInter  : public TCollection_BasicMap
{
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT BRepClass3d_MapOfInter(const Standard_Integer NbBuckets = 1);
  
  Standard_EXPORT   BRepClass3d_MapOfInter& Assign (const BRepClass3d_MapOfInter& Other) ;
  BRepClass3d_MapOfInter& operator = (const BRepClass3d_MapOfInter& Other) 
{
  return Assign(Other);
}
  
  Standard_EXPORT   void ReSize (const Standard_Integer NbBuckets) ;
  
  Standard_EXPORT   void Clear() ;
~BRepClass3d_MapOfInter()
{
  Clear();
}
  
  Standard_EXPORT   Standard_Boolean Bind (const TopoDS_Shape& K, const Standard_Address& I) ;
  
  Standard_EXPORT   Standard_Boolean IsBound (const TopoDS_Shape& K)  const;
  
  Standard_EXPORT   Standard_Boolean UnBind (const TopoDS_Shape& K) ;
  
  Standard_EXPORT  const  Standard_Address& Find (const TopoDS_Shape& K)  const;
 const  Standard_Address& operator() (const TopoDS_Shape& K)  const
{
  return Find(K);
}
  
  Standard_EXPORT   Standard_Address& ChangeFind (const TopoDS_Shape& K) ;
  Standard_Address& operator() (const TopoDS_Shape& K) 
{
  return ChangeFind(K);
}
  
  Standard_EXPORT   Standard_Address Find1 (const TopoDS_Shape& K)  const;
  
  Standard_EXPORT   Standard_Address ChangeFind1 (const TopoDS_Shape& K) ;




protected:





private:

  
  Standard_EXPORT BRepClass3d_MapOfInter(const BRepClass3d_MapOfInter& Other);




};







#endif // _BRepClass3d_MapOfInter_HeaderFile