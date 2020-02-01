// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _Vrml_IndexedLineSet_HeaderFile
#define _Vrml_IndexedLineSet_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineHandle.hxx>
#include <Handle_Vrml_IndexedLineSet.hxx>

#include <Handle_TColStd_HArray1OfInteger.hxx>
#include <MMgt_TShared.hxx>
#include <Standard_OStream.hxx>
class TColStd_HArray1OfInteger;


//! defines a IndexedLineSet node of VRML specifying geometry shapes.
//! This node represents a 3D shape formed by constructing polylines from vertices
//! located at the current coordinates. IndexedLineSet uses the indices in its coordIndex
//! field to specify the polylines. An index of -1 separates one polyline from the next
//! (thus, a final -1 is optional). the current polyline has ended and the next one begins.
//! Treatment of the current material and normal binding is as follows: The PER_PART binding
//! specifies a material or normal for each segment of the line. The PER_FACE binding
//! specifies a material or normal for each polyline. PER_VERTEX specifies a material or
//! normal for each vertex. The corresponding _INDEXED bindings are the same, but use
//! the materialIndex or normalIndex indices. The DEFAULT material binding is equal
//! to OVERALL. The DEFAULT normal binding is equal to  PER_VERTEX_INDEXED;
//! if insufficient normals exist in the state, the lines will be drawn unlit. The same
//! rules for texture coordinate generation as IndexedFaceSet are used.
class Vrml_IndexedLineSet : public MMgt_TShared
{

public:

  
  Standard_EXPORT Vrml_IndexedLineSet(const Handle(TColStd_HArray1OfInteger)& aCoordIndex, const Handle(TColStd_HArray1OfInteger)& aMaterialIndex, const Handle(TColStd_HArray1OfInteger)& aNormalIndex, const Handle(TColStd_HArray1OfInteger)& aTextureCoordIndex);
  
  Standard_EXPORT Vrml_IndexedLineSet();
  
  Standard_EXPORT   void SetCoordIndex (const Handle(TColStd_HArray1OfInteger)& aCoordIndex) ;
  
  Standard_EXPORT   Handle(TColStd_HArray1OfInteger) CoordIndex()  const;
  
  Standard_EXPORT   void SetMaterialIndex (const Handle(TColStd_HArray1OfInteger)& aMaterialIndex) ;
  
  Standard_EXPORT   Handle(TColStd_HArray1OfInteger) MaterialIndex()  const;
  
  Standard_EXPORT   void SetNormalIndex (const Handle(TColStd_HArray1OfInteger)& aNormalIndex) ;
  
  Standard_EXPORT   Handle(TColStd_HArray1OfInteger) NormalIndex()  const;
  
  Standard_EXPORT   void SetTextureCoordIndex (const Handle(TColStd_HArray1OfInteger)& aTextureCoordIndex) ;
  
  Standard_EXPORT   Handle(TColStd_HArray1OfInteger) TextureCoordIndex()  const;
  
  Standard_EXPORT   Standard_OStream& Print (Standard_OStream& anOStream)  const;




  DEFINE_STANDARD_RTTI(Vrml_IndexedLineSet)

protected:




private: 


  Handle(TColStd_HArray1OfInteger) myCoordIndex;
  Handle(TColStd_HArray1OfInteger) myMaterialIndex;
  Handle(TColStd_HArray1OfInteger) myNormalIndex;
  Handle(TColStd_HArray1OfInteger) myTextureCoordIndex;


};







#endif // _Vrml_IndexedLineSet_HeaderFile