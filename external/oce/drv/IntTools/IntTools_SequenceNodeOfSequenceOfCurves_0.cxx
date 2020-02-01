// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#include <IntTools_SequenceNodeOfSequenceOfCurves.hxx>

#include <Standard_Type.hxx>

#include <IntTools_Curve.hxx>
#include <IntTools_SequenceOfCurves.hxx>

 


IMPLEMENT_STANDARD_TYPE(IntTools_SequenceNodeOfSequenceOfCurves)
IMPLEMENT_STANDARD_SUPERTYPE_ARRAY()
  STANDARD_TYPE(TCollection_SeqNode),
  STANDARD_TYPE(MMgt_TShared),
  STANDARD_TYPE(Standard_Transient),

IMPLEMENT_STANDARD_SUPERTYPE_ARRAY_END()
IMPLEMENT_STANDARD_TYPE_END(IntTools_SequenceNodeOfSequenceOfCurves)


IMPLEMENT_DOWNCAST(IntTools_SequenceNodeOfSequenceOfCurves,Standard_Transient)
IMPLEMENT_STANDARD_RTTI(IntTools_SequenceNodeOfSequenceOfCurves)


#define SeqItem IntTools_Curve
#define SeqItem_hxx <IntTools_Curve.hxx>
#define TCollection_SequenceNode IntTools_SequenceNodeOfSequenceOfCurves
#define TCollection_SequenceNode_hxx <IntTools_SequenceNodeOfSequenceOfCurves.hxx>
#define Handle_TCollection_SequenceNode Handle_IntTools_SequenceNodeOfSequenceOfCurves
#define TCollection_SequenceNode_Type_() IntTools_SequenceNodeOfSequenceOfCurves_Type_()
#define TCollection_Sequence IntTools_SequenceOfCurves
#define TCollection_Sequence_hxx <IntTools_SequenceOfCurves.hxx>
#include <TCollection_SequenceNode.gxx>
