// Created by: Anastasia BORISOVA
// Copyright (c) 2016 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef _AIS_AnimationObject_HeaderFile
#define _AIS_AnimationObject_HeaderFile

<<<<<<< HEAD
#include <AIS_Animation.hxx>
#include <AIS_InteractiveContext.hxx>
#include <gp_TrsfNLerp.hxx>

//! Animation defining object transformation.
class AIS_AnimationObject : public AIS_Animation
{
  DEFINE_STANDARD_RTTIEXT(AIS_AnimationObject, AIS_Animation)
=======
#include <AIS_BaseAnimationObject.hxx>
#include <gp_TrsfNLerp.hxx>

//! Animation defining object transformation.
class AIS_AnimationObject : public AIS_BaseAnimationObject
{
  DEFINE_STANDARD_RTTIEXT(AIS_AnimationObject, AIS_BaseAnimationObject)
>>>>>>> accb2f351 (u)
public:

  //! Constructor with initialization.
  //! Note that start/end transformations specify exactly local transformation of the object,
  //! not the transformation to be applied to existing local transformation.
<<<<<<< HEAD
  //! @param theAnimationName animation identifier
  //! @param theContext       interactive context where object have been displayed
  //! @param theObject        object to apply local transformation
  //! @param theTrsfStart     local transformation at the start of animation (e.g. theObject->LocalTransformation())
  //! @param theTrsfEnd       local transformation at the end   of animation
=======
  //! @param[in] theAnimationName animation identifier
  //! @param[in] theContext       interactive context where object have been displayed
  //! @param[in] theObject        object to apply local transformation
  //! @param[in] theTrsfStart     local transformation at the start of animation (e.g. theObject->LocalTransformation())
  //! @param[in] theTrsfEnd       local transformation at the end   of animation
>>>>>>> accb2f351 (u)
  Standard_EXPORT AIS_AnimationObject (const TCollection_AsciiString& theAnimationName,
                                       const Handle(AIS_InteractiveContext)& theContext,
                                       const Handle(AIS_InteractiveObject)&  theObject,
                                       const gp_Trsf& theTrsfStart,
                                       const gp_Trsf& theTrsfEnd);

protected:

  //! Update the progress.
  Standard_EXPORT virtual void update (const AIS_AnimationProgress& theProgress) Standard_OVERRIDE;

<<<<<<< HEAD
  //! Invalidate the viewer for proper update.
  Standard_EXPORT void invalidateViewer();

protected:

  Handle(AIS_InteractiveContext) myContext;   //!< context where object is displayed
  Handle(AIS_InteractiveObject)  myObject;    //!< presentation object to set location
  gp_TrsfNLerp                   myTrsfLerp;  //!< interpolation tool

};

DEFINE_STANDARD_HANDLE(AIS_AnimationObject, AIS_Animation)

=======
private:

  gp_TrsfNLerp  myTrsfLerp; //!< interpolation tool

};

>>>>>>> accb2f351 (u)
#endif // _AIS_AnimationObject_HeaderFile
