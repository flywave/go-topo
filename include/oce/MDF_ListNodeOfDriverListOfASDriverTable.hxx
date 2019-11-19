// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _MDF_ListNodeOfDriverListOfASDriverTable_HeaderFile
#define _MDF_ListNodeOfDriverListOfASDriverTable_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineHandle.hxx>
#include <Handle_MDF_ListNodeOfDriverListOfASDriverTable.hxx>

#include <Handle_MDF_ASDriver.hxx>
#include <TCollection_MapNode.hxx>
#include <TCollection_MapNodePtr.hxx>
class MDF_ASDriver;
class MDF_DriverListOfASDriverTable;
class MDF_ListIteratorOfDriverListOfASDriverTable;



class MDF_ListNodeOfDriverListOfASDriverTable : public TCollection_MapNode
{

public:

  
    MDF_ListNodeOfDriverListOfASDriverTable(const Handle(MDF_ASDriver)& I, const TCollection_MapNodePtr& n);
  
      Handle(MDF_ASDriver)& Value()  const;




  DEFINE_STANDARD_RTTI(MDF_ListNodeOfDriverListOfASDriverTable)

protected:




private: 


  Handle(MDF_ASDriver) myValue;


};

#define Item Handle(MDF_ASDriver)
#define Item_hxx <MDF_ASDriver.hxx>
#define TCollection_ListNode MDF_ListNodeOfDriverListOfASDriverTable
#define TCollection_ListNode_hxx <MDF_ListNodeOfDriverListOfASDriverTable.hxx>
#define TCollection_ListIterator MDF_ListIteratorOfDriverListOfASDriverTable
#define TCollection_ListIterator_hxx <MDF_ListIteratorOfDriverListOfASDriverTable.hxx>
#define Handle_TCollection_ListNode Handle_MDF_ListNodeOfDriverListOfASDriverTable
#define TCollection_ListNode_Type_() MDF_ListNodeOfDriverListOfASDriverTable_Type_()
#define TCollection_List MDF_DriverListOfASDriverTable
#define TCollection_List_hxx <MDF_DriverListOfASDriverTable.hxx>

#include <TCollection_ListNode.lxx>

#undef Item
#undef Item_hxx
#undef TCollection_ListNode
#undef TCollection_ListNode_hxx
#undef TCollection_ListIterator
#undef TCollection_ListIterator_hxx
#undef Handle_TCollection_ListNode
#undef TCollection_ListNode_Type_
#undef TCollection_List
#undef TCollection_List_hxx




#endif // _MDF_ListNodeOfDriverListOfASDriverTable_HeaderFile