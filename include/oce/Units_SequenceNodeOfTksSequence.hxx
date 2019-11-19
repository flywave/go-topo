// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _Units_SequenceNodeOfTksSequence_HeaderFile
#define _Units_SequenceNodeOfTksSequence_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineHandle.hxx>
#include <Handle_Units_SequenceNodeOfTksSequence.hxx>

#include <Handle_Units_Token.hxx>
#include <TCollection_SeqNode.hxx>
#include <TCollection_SeqNodePtr.hxx>
class Units_Token;
class Units_TksSequence;



class Units_SequenceNodeOfTksSequence : public TCollection_SeqNode
{

public:

  
    Units_SequenceNodeOfTksSequence(const Handle(Units_Token)& I, const TCollection_SeqNodePtr& n, const TCollection_SeqNodePtr& p);
  
      Handle(Units_Token)& Value()  const;




  DEFINE_STANDARD_RTTI(Units_SequenceNodeOfTksSequence)

protected:




private: 


  Handle(Units_Token) myValue;


};

#define SeqItem Handle(Units_Token)
#define SeqItem_hxx <Units_Token.hxx>
#define TCollection_SequenceNode Units_SequenceNodeOfTksSequence
#define TCollection_SequenceNode_hxx <Units_SequenceNodeOfTksSequence.hxx>
#define Handle_TCollection_SequenceNode Handle_Units_SequenceNodeOfTksSequence
#define TCollection_SequenceNode_Type_() Units_SequenceNodeOfTksSequence_Type_()
#define TCollection_Sequence Units_TksSequence
#define TCollection_Sequence_hxx <Units_TksSequence.hxx>

#include <TCollection_SequenceNode.lxx>

#undef SeqItem
#undef SeqItem_hxx
#undef TCollection_SequenceNode
#undef TCollection_SequenceNode_hxx
#undef Handle_TCollection_SequenceNode
#undef TCollection_SequenceNode_Type_
#undef TCollection_Sequence
#undef TCollection_Sequence_hxx




#endif // _Units_SequenceNodeOfTksSequence_HeaderFile