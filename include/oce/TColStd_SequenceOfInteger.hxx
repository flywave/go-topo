// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _TColStd_SequenceOfInteger_HeaderFile
#define _TColStd_SequenceOfInteger_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Macro.hxx>

#include <TCollection_BaseSequence.hxx>
#include <Standard_Integer.hxx>
#include <Handle_TColStd_SequenceNodeOfSequenceOfInteger.hxx>
class Standard_NoSuchObject;
class Standard_OutOfRange;
class TColStd_SequenceNodeOfSequenceOfInteger;



class TColStd_SequenceOfInteger  : public TCollection_BaseSequence
{
public:

  DEFINE_STANDARD_ALLOC

  
    TColStd_SequenceOfInteger();
  
  Standard_EXPORT TColStd_SequenceOfInteger(const TColStd_SequenceOfInteger& Other);
  
  Standard_EXPORT   void Clear() ;
~TColStd_SequenceOfInteger()
{
  Clear();
}
  
  Standard_EXPORT  const  TColStd_SequenceOfInteger& Assign (const TColStd_SequenceOfInteger& Other) ;
 const  TColStd_SequenceOfInteger& operator = (const TColStd_SequenceOfInteger& Other) 
{
  return Assign(Other);
}
  
  Standard_EXPORT   void Append (const Standard_Integer& T) ;
  
      void Append (TColStd_SequenceOfInteger& S) ;
  
  Standard_EXPORT   void Prepend (const Standard_Integer& T) ;
  
      void Prepend (TColStd_SequenceOfInteger& S) ;
  
      void InsertBefore (const Standard_Integer Index, const Standard_Integer& T) ;
  
      void InsertBefore (const Standard_Integer Index, TColStd_SequenceOfInteger& S) ;
  
  Standard_EXPORT   void InsertAfter (const Standard_Integer Index, const Standard_Integer& T) ;
  
      void InsertAfter (const Standard_Integer Index, TColStd_SequenceOfInteger& S) ;
  
  Standard_EXPORT  const  Standard_Integer& First()  const;
  
  Standard_EXPORT  const  Standard_Integer& Last()  const;
  
      void Split (const Standard_Integer Index, TColStd_SequenceOfInteger& Sub) ;
  
  Standard_EXPORT  const  Standard_Integer& Value (const Standard_Integer Index)  const;
 const  Standard_Integer& operator() (const Standard_Integer Index)  const
{
  return Value(Index);
}
  
  Standard_EXPORT   void SetValue (const Standard_Integer Index, const Standard_Integer& I) ;
  
  Standard_EXPORT   Standard_Integer& ChangeValue (const Standard_Integer Index) ;
  Standard_Integer& operator() (const Standard_Integer Index) 
{
  return ChangeValue(Index);
}
  
  Standard_EXPORT   void Remove (const Standard_Integer Index) ;
  
  Standard_EXPORT   void Remove (const Standard_Integer FromIndex, const Standard_Integer ToIndex) ;




protected:





private:





};

#define SeqItem Standard_Integer
#define SeqItem_hxx <Standard_Integer.hxx>
#define TCollection_SequenceNode TColStd_SequenceNodeOfSequenceOfInteger
#define TCollection_SequenceNode_hxx <TColStd_SequenceNodeOfSequenceOfInteger.hxx>
#define Handle_TCollection_SequenceNode Handle_TColStd_SequenceNodeOfSequenceOfInteger
#define TCollection_SequenceNode_Type_() TColStd_SequenceNodeOfSequenceOfInteger_Type_()
#define TCollection_Sequence TColStd_SequenceOfInteger
#define TCollection_Sequence_hxx <TColStd_SequenceOfInteger.hxx>

#include <TCollection_Sequence.lxx>

#undef SeqItem
#undef SeqItem_hxx
#undef TCollection_SequenceNode
#undef TCollection_SequenceNode_hxx
#undef Handle_TCollection_SequenceNode
#undef TCollection_SequenceNode_Type_
#undef TCollection_Sequence
#undef TCollection_Sequence_hxx




#endif // _TColStd_SequenceOfInteger_HeaderFile