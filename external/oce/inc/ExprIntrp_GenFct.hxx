// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _ExprIntrp_GenFct_HeaderFile
#define _ExprIntrp_GenFct_HeaderFile

#include <Standard.hxx>
#include <Standard_DefineHandle.hxx>
#include <Handle_ExprIntrp_GenFct.hxx>

#include <Standard_Boolean.hxx>
#include <ExprIntrp_Generator.hxx>
class Standard_NoSuchObject;
class TCollection_AsciiString;


//! Implements an interpreter for defining functions.
//! All its functionnalities can be found in class
//! GenExp.
class ExprIntrp_GenFct : public ExprIntrp_Generator
{

public:

  
  Standard_EXPORT static   Handle(ExprIntrp_GenFct) Create() ;
  
  Standard_EXPORT   void Process (const TCollection_AsciiString& str) ;
  
  Standard_EXPORT   Standard_Boolean IsDone()  const;




  DEFINE_STANDARD_RTTI(ExprIntrp_GenFct)

protected:




private: 

  
  Standard_EXPORT ExprIntrp_GenFct();

  Standard_Boolean done;


};







#endif // _ExprIntrp_GenFct_HeaderFile