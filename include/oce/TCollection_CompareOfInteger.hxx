// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _TCollection_CompareOfInteger_HeaderFile
#define _TCollection_CompareOfInteger_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineAlloc.hxx>
#include <Standard_Macro.hxx>

#include <TCollection_PrivCompareOfInteger.hxx>
#include <Standard_Boolean.hxx>
#include <Standard_Integer.hxx>



class TCollection_CompareOfInteger  : public TCollection_PrivCompareOfInteger
{
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT TCollection_CompareOfInteger();
  
  //! Returns True if <Left> is lower than <Right>.
  Standard_EXPORT virtual   Standard_Boolean IsLower (const Standard_Integer& Left, const Standard_Integer& Right)  const;
  
  //! Returns True if <Left> is greater than <Right>.
  Standard_EXPORT virtual   Standard_Boolean IsGreater (const Standard_Integer& Left, const Standard_Integer& Right)  const;




protected:





private:





};







#endif // _TCollection_CompareOfInteger_HeaderFile