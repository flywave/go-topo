// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _TopTools_DataMapIteratorOfDataMapOfShapeSequenceOfShape_HeaderFile
#define _TopTools_DataMapIteratorOfDataMapOfShapeSequenceOfShape_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Macro.hxx>

#include <TCollection_BasicMapIterator.hxx>
#include <Handle_TopTools_DataMapNodeOfDataMapOfShapeSequenceOfShape.hxx>
class Standard_NoSuchObject;
class TopoDS_Shape;
class TopTools_SequenceOfShape;
class TopTools_ShapeMapHasher;
class TopTools_DataMapOfShapeSequenceOfShape;
class TopTools_DataMapNodeOfDataMapOfShapeSequenceOfShape;



class TopTools_DataMapIteratorOfDataMapOfShapeSequenceOfShape  : public TCollection_BasicMapIterator
{
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT TopTools_DataMapIteratorOfDataMapOfShapeSequenceOfShape();
  
  Standard_EXPORT TopTools_DataMapIteratorOfDataMapOfShapeSequenceOfShape(const TopTools_DataMapOfShapeSequenceOfShape& aMap);
  
  Standard_EXPORT   void Initialize (const TopTools_DataMapOfShapeSequenceOfShape& aMap) ;
  
  Standard_EXPORT  const  TopoDS_Shape& Key()  const;
  
  Standard_EXPORT  const  TopTools_SequenceOfShape& Value()  const;




protected:





private:





};







#endif // _TopTools_DataMapIteratorOfDataMapOfShapeSequenceOfShape_HeaderFile