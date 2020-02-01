// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _IntPatch_SequenceOfPathPointOfTheSOnBounds_HeaderFile
#define _IntPatch_SequenceOfPathPointOfTheSOnBounds_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Macro.hxx>

#include <TCollection_BaseSequence.hxx>
#include <Handle_IntPatch_SequenceNodeOfSequenceOfPathPointOfTheSOnBounds.hxx>
#include <Standard_Integer.hxx>
class Standard_NoSuchObject;
class Standard_OutOfRange;
class IntPatch_ThePathPointOfTheSOnBounds;
class IntPatch_SequenceNodeOfSequenceOfPathPointOfTheSOnBounds;



class IntPatch_SequenceOfPathPointOfTheSOnBounds  : public TCollection_BaseSequence
{
public:

  DEFINE_STANDARD_ALLOC

  
    IntPatch_SequenceOfPathPointOfTheSOnBounds();
  
  Standard_EXPORT IntPatch_SequenceOfPathPointOfTheSOnBounds(const IntPatch_SequenceOfPathPointOfTheSOnBounds& Other);
  
  Standard_EXPORT   void Clear() ;
~IntPatch_SequenceOfPathPointOfTheSOnBounds()
{
  Clear();
}
  
  Standard_EXPORT  const  IntPatch_SequenceOfPathPointOfTheSOnBounds& Assign (const IntPatch_SequenceOfPathPointOfTheSOnBounds& Other) ;
 const  IntPatch_SequenceOfPathPointOfTheSOnBounds& operator = (const IntPatch_SequenceOfPathPointOfTheSOnBounds& Other) 
{
  return Assign(Other);
}
  
  Standard_EXPORT   void Append (const IntPatch_ThePathPointOfTheSOnBounds& T) ;
  
      void Append (IntPatch_SequenceOfPathPointOfTheSOnBounds& S) ;
  
  Standard_EXPORT   void Prepend (const IntPatch_ThePathPointOfTheSOnBounds& T) ;
  
      void Prepend (IntPatch_SequenceOfPathPointOfTheSOnBounds& S) ;
  
      void InsertBefore (const Standard_Integer Index, const IntPatch_ThePathPointOfTheSOnBounds& T) ;
  
      void InsertBefore (const Standard_Integer Index, IntPatch_SequenceOfPathPointOfTheSOnBounds& S) ;
  
  Standard_EXPORT   void InsertAfter (const Standard_Integer Index, const IntPatch_ThePathPointOfTheSOnBounds& T) ;
  
      void InsertAfter (const Standard_Integer Index, IntPatch_SequenceOfPathPointOfTheSOnBounds& S) ;
  
  Standard_EXPORT  const  IntPatch_ThePathPointOfTheSOnBounds& First()  const;
  
  Standard_EXPORT  const  IntPatch_ThePathPointOfTheSOnBounds& Last()  const;
  
      void Split (const Standard_Integer Index, IntPatch_SequenceOfPathPointOfTheSOnBounds& Sub) ;
  
  Standard_EXPORT  const  IntPatch_ThePathPointOfTheSOnBounds& Value (const Standard_Integer Index)  const;
 const  IntPatch_ThePathPointOfTheSOnBounds& operator() (const Standard_Integer Index)  const
{
  return Value(Index);
}
  
  Standard_EXPORT   void SetValue (const Standard_Integer Index, const IntPatch_ThePathPointOfTheSOnBounds& I) ;
  
  Standard_EXPORT   IntPatch_ThePathPointOfTheSOnBounds& ChangeValue (const Standard_Integer Index) ;
  IntPatch_ThePathPointOfTheSOnBounds& operator() (const Standard_Integer Index) 
{
  return ChangeValue(Index);
}
  
  Standard_EXPORT   void Remove (const Standard_Integer Index) ;
  
  Standard_EXPORT   void Remove (const Standard_Integer FromIndex, const Standard_Integer ToIndex) ;




protected:





private:





};

#define SeqItem IntPatch_ThePathPointOfTheSOnBounds
#define SeqItem_hxx <IntPatch_ThePathPointOfTheSOnBounds.hxx>
#define TCollection_SequenceNode IntPatch_SequenceNodeOfSequenceOfPathPointOfTheSOnBounds
#define TCollection_SequenceNode_hxx <IntPatch_SequenceNodeOfSequenceOfPathPointOfTheSOnBounds.hxx>
#define Handle_TCollection_SequenceNode Handle_IntPatch_SequenceNodeOfSequenceOfPathPointOfTheSOnBounds
#define TCollection_SequenceNode_Type_() IntPatch_SequenceNodeOfSequenceOfPathPointOfTheSOnBounds_Type_()
#define TCollection_Sequence IntPatch_SequenceOfPathPointOfTheSOnBounds
#define TCollection_Sequence_hxx <IntPatch_SequenceOfPathPointOfTheSOnBounds.hxx>

#include <TCollection_Sequence.lxx>

#undef SeqItem
#undef SeqItem_hxx
#undef TCollection_SequenceNode
#undef TCollection_SequenceNode_hxx
#undef Handle_TCollection_SequenceNode
#undef TCollection_SequenceNode_Type_
#undef TCollection_Sequence
#undef TCollection_Sequence_hxx




#endif // _IntPatch_SequenceOfPathPointOfTheSOnBounds_HeaderFile