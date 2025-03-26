// Created on: 2000-08-15
// Created by: Andrey BETENEV
// Copyright (c) 2000-2014 OPEN CASCADE SAS
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

// CURRENT LIMITATIONS: 
// when val props and names assigned to instance of 
// component in assembly, it is in fact supposed that only one CDSR corresponds
// to such shape. This can be wrong and should be handled more carefully
// (analysis of SDRs which the CDSR links should be done)
// Names and validation props are supported for top-level shapes only

#include <STEPCAFControl_Writer.hxx>

#include <BRep_Builder.hxx>
#include <GeomToStep_MakeAxis2Placement3d.hxx>
#include <GeomToStep_MakeCartesianPoint.hxx>
#include <HeaderSection_FileSchema.hxx>
#include <Interface_EntityIterator.hxx>
#include <Interface_Static.hxx>
<<<<<<< HEAD
#include <Message_Messenger.hxx>
=======
#include <Message.hxx>
>>>>>>> accb2f351 (u)
#include <Message_ProgressScope.hxx>
#include <MoniTool_DataMapIteratorOfDataMapOfShapeTransient.hxx>
#include <OSD_Path.hxx>
#include <StepAP214_Protocol.hxx>
#include <StepAP242_DraughtingModelItemAssociation.hxx>
#include <StepAP242_GeometricItemSpecificUsage.hxx>
#include <StepBasic_ConversionBasedUnitAndLengthUnit.hxx>
#include <StepBasic_ConversionBasedUnitAndPlaneAngleUnit.hxx>
#include <StepBasic_DerivedUnit.hxx>
#include <StepBasic_DerivedUnitElement.hxx>
#include <StepBasic_HArray1OfDerivedUnitElement.hxx>
#include <StepBasic_MeasureValueMember.hxx>
#include <StepBasic_Product.hxx>
#include <StepBasic_ProductDefinition.hxx>
#include <StepBasic_ProductDefinitionFormation.hxx>
#include <StepBasic_SiUnitAndLengthUnit.hxx>
#include <StepBasic_SiUnitAndMassUnit.hxx>
#include <StepBasic_SiUnitAndPlaneAngleUnit.hxx>
#include <STEPCAFControl_ActorWrite.hxx>
#include <STEPCAFControl_Controller.hxx>
#include <STEPCAFControl_ExternFile.hxx>
#include <STEPConstruct.hxx>
#include <STEPConstruct_ExternRefs.hxx>
#include <STEPCAFControl_GDTProperty.hxx>
#include <STEPConstruct_Styles.hxx>
#include <STEPConstruct_ValidationProps.hxx>
#include <STEPControl_StepModelType.hxx>
#include <StepData_Logical.hxx>
#include <StepData_StepModel.hxx>
#include <StepDimTol_AngularityTolerance.hxx>
#include <StepDimTol_CircularRunoutTolerance.hxx>
#include <StepDimTol_CoaxialityTolerance.hxx>
#include <StepDimTol_ConcentricityTolerance.hxx>
#include <StepDimTol_Datum.hxx>
#include <StepDimTol_DatumFeature.hxx>
#include <StepDimTol_DatumReference.hxx>
#include <StepDimTol_DatumSystem.hxx>
#include <StepDimTol_DatumSystemOrReference.hxx>
#include <StepDimTol_GeometricToleranceType.hxx>
#include <StepDimTol_GeometricToleranceWithDatumReference.hxx>
#include <StepDimTol_GeometricToleranceWithModifiers.hxx>
#include <StepDimTol_GeoTolAndGeoTolWthDatRef.hxx>
#include <StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMaxTol.hxx>
#include <StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMod.hxx>
#include <StepDimTol_GeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol.hxx>
#include <StepDimTol_GeoTolAndGeoTolWthMaxTol.hxx>
#include <StepDimTol_GeoTolAndGeoTolWthMod.hxx>
#include <StepDimTol_HArray1OfDatumReference.hxx>
#include <StepDimTol_HArray1OfDatumReferenceElement.hxx>
#include <StepDimTol_HArray1OfDatumReferenceModifier.hxx>
#include <StepDimTol_HArray1OfDatumSystemOrReference.hxx>
#include <StepDimTol_ModifiedGeometricTolerance.hxx>
#include <StepDimTol_ParallelismTolerance.hxx>
#include <StepDimTol_PerpendicularityTolerance.hxx>
#include <StepDimTol_PlacedDatumTargetFeature.hxx>
#include <StepDimTol_RunoutZoneDefinition.hxx>
#include <StepDimTol_RunoutZoneOrientation.hxx>
#include <StepDimTol_SymmetryTolerance.hxx>
#include <StepDimTol_ToleranceZone.hxx>
#include <StepDimTol_ToleranceZoneForm.hxx>
#include <StepDimTol_TotalRunoutTolerance.hxx>
#include <StepGeom_Axis2Placement3d.hxx>
#include <StepGeom_CartesianPoint.hxx>
#include <StepGeom_Direction.hxx>
#include <StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext.hxx>
#include <StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx.hxx>
#include <StepGeom_Plane.hxx>
#include <StepRepr_CompGroupShAspAndCompShAspAndDatumFeatAndShAsp.hxx>
#include <StepRepr_CompositeShapeAspect.hxx>
#include <StepRepr_ConstructiveGeometryRepresentation.hxx>
#include <StepRepr_ConstructiveGeometryRepresentationRelationship.hxx>
#include <StepRepr_DerivedShapeAspect.hxx>
#include <StepRepr_DescriptiveRepresentationItem.hxx>
#include <StepRepr_FeatureForDatumTargetRelationship.hxx>
#include <StepRepr_HArray1OfRepresentationItem.hxx>
#include <StepRepr_MeasureRepresentationItem.hxx>
#include <StepRepr_NextAssemblyUsageOccurrence.hxx>
#include <StepRepr_ProductDefinitionShape.hxx>
#include <StepRepr_PropertyDefinition.hxx>
#include <StepRepr_Representation.hxx>
#include <StepRepr_RepresentationItem.hxx>
#include <StepRepr_ReprItemAndLengthMeasureWithUnit.hxx>
#include <StepRepr_ReprItemAndLengthMeasureWithUnitAndQRI.hxx>
#include <StepRepr_ReprItemAndPlaneAngleMeasureWithUnit.hxx>
#include <StepRepr_ReprItemAndPlaneAngleMeasureWithUnitAndQRI.hxx>
#include <StepRepr_ShapeAspect.hxx>
#include <StepRepr_ShapeAspectDerivingRelationship.hxx>
#include <StepRepr_ShapeAspectRelationship.hxx>
#include <StepRepr_SpecifiedHigherUsageOccurrence.hxx>
#include <StepRepr_ValueRange.hxx>
#include <StepShape_AdvancedFace.hxx>
#include <StepShape_AngularLocation.hxx>
#include <StepShape_AngularSize.hxx>
#include <StepShape_ConnectedFaceSet.hxx>
#include <StepShape_ContextDependentShapeRepresentation.hxx>
#include <StepShape_DimensionalCharacteristicRepresentation.hxx>
#include <StepShape_DimensionalLocation.hxx>
#include <StepShape_DimensionalLocationWithPath.hxx>
#include <StepShape_DimensionalSize.hxx>
#include <StepShape_DimensionalSizeWithPath.hxx>
#include <StepShape_EdgeCurve.hxx>
#include <StepShape_EdgeLoop.hxx>
#include <StepShape_FaceBound.hxx>
#include <StepShape_LimitsAndFits.hxx>
#include <StepShape_OrientedEdge.hxx>
#include <StepShape_PlusMinusTolerance.hxx>
#include <StepShape_QualifiedRepresentationItem.hxx>
#include <StepShape_ShapeDefinitionRepresentation.hxx>
#include <StepShape_ShapeDimensionRepresentation.hxx>
#include <StepShape_ShapeRepresentation.hxx>
#include <StepShape_ShapeRepresentationWithParameters.hxx>
#include <StepShape_ToleranceValue.hxx>
#include <StepShape_TypeQualifier.hxx>
#include <StepShape_ValueFormatTypeQualifier.hxx>
#include <StepVisual_AnnotationPlane.hxx>
#include <StepVisual_CurveStyle.hxx>
#include <StepVisual_DraughtingCallout.hxx>
#include <StepVisual_DraughtingModel.hxx>
#include <StepVisual_HArray1OfPresentationStyleAssignment.hxx>
#include <StepVisual_HArray1OfPresentationStyleSelect.hxx>
#include <StepVisual_Invisibility.hxx>
#include <StepVisual_InvisibleItem.hxx>
#include <StepVisual_MechanicalDesignGeometricPresentationRepresentation.hxx>
#include <StepVisual_NullStyleMember.hxx>
#include <StepVisual_PointStyle.hxx>
#include <StepVisual_PresentationLayerAssignment.hxx>
#include <StepVisual_PresentationRepresentation.hxx>
#include <StepVisual_PresentationStyleAssignment.hxx>
#include <StepVisual_PresentationStyleByContext.hxx>
#include <StepVisual_StyledItem.hxx>
#include <StepVisual_SurfaceStyleUsage.hxx>
#include <StepVisual_TessellatedAnnotationOccurrence.hxx>
#include <StepVisual_TessellatedGeometricSet.hxx>
#include <TCollection_AsciiString.hxx>
#include <TCollection_HAsciiString.hxx>
#include <TColStd_HArray1OfReal.hxx>
#include <TColStd_MapOfAsciiString.hxx>
#include <TColStd_MapOfTransient.hxx>
#include <TDataStd_Name.hxx>
#include <TDataStd_TreeNode.hxx>
#include <TDataStd_UAttribute.hxx>
#include <TDF_ChildIterator.hxx>
#include <TDF_Label.hxx>
#include <TDF_LabelSequence.hxx>
#include <TDocStd_Document.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_Iterator.hxx>
#include <TopoDS_Shape.hxx>
#include <TopTools_MapOfShape.hxx>
#include <Transfer_Binder.hxx>
#include <Transfer_FinderProcess.hxx>
#include <Transfer_TransientListBinder.hxx>
#include <TransferBRep.hxx>
#include <TransferBRep_ShapeMapper.hxx>
#include <XCAFDimTolObjects_DatumObject.hxx>
#include <XCAFDimTolObjects_DimensionFormVariance.hxx>
#include <XCAFDimTolObjects_DimensionGrade.hxx>
#include <XCAFDimTolObjects_DimensionObject.hxx>
#include <XCAFDimTolObjects_DimensionModif.hxx>
#include <XCAFDimTolObjects_DimensionModifiersSequence.hxx>
#include <XCAFDimTolObjects_DimensionQualifier.hxx>
#include <XCAFDimTolObjects_GeomToleranceObject.hxx>
#include <XCAFDoc.hxx>
#include <XCAFDoc_Area.hxx>
#include <XCAFDoc_Centroid.hxx>
#include <XCAFDoc_ColorTool.hxx>
#include <XCAFDoc_Datum.hxx>
#include <XCAFDoc_Dimension.hxx>
#include <XCAFDoc_DimTol.hxx>
#include <XCAFDoc_DimTolTool.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_GeomTolerance.hxx>
#include <XCAFDoc_GraphNode.hxx>
#include <XCAFDoc_LengthUnit.hxx>
#include <XCAFDoc_LayerTool.hxx>
#include <XCAFDoc_MaterialTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFDoc_Volume.hxx>
#include <XCAFDoc_VisMaterialTool.hxx>
#include <XCAFPrs_IndexedDataMapOfShapeStyle.hxx>
#include <XCAFPrs_Style.hxx>
#include <XSAlgo.hxx>
#include <XSAlgo_AlgoContainer.hxx>
#include <XSControl_TransferWriter.hxx>
#include <XSControl_WorkSession.hxx>
#include <UnitsMethods.hxx>

<<<<<<< HEAD
// added by skl 15.01.2004 for D&GT writing
//#include <StepRepr_CompoundItemDefinition.hxx>
//#include <StepRepr_CompoundItemDefinitionMember.hxx>
// added by skl 12.02.2004 for writing materials
=======
>>>>>>> accb2f351 (u)
//=======================================================================
//function : GetLabelName
//purpose  : auxiliary function: take name of label and append it to str
//=======================================================================
<<<<<<< HEAD
static Standard_Boolean GetLabelName (const TDF_Label &L, Handle(TCollection_HAsciiString) &str)
{
  Handle(TDataStd_Name) N;
  if ( ! L.FindAttribute ( TDataStd_Name::GetID(), N ) ) return Standard_False;
  TCollection_ExtendedString name = N->Get();
  if ( name.Length() <=0 ) return Standard_False;

  // set name, removing spaces around it
  TCollection_AsciiString buf(name);
  buf.LeftAdjust();
  buf.RightAdjust();
  str->AssignCat ( buf.ToCString() );
  return Standard_True;
}


=======
static Standard_Boolean GetLabelName(const TDF_Label& theL,
                                     Handle(TCollection_HAsciiString)& theStr)
{
  Handle(TDataStd_Name) anAttrName;
  if (!theL.FindAttribute(TDataStd_Name::GetID(), anAttrName))
  {
    return Standard_False;
  }
  TCollection_ExtendedString aName = anAttrName->Get();
  if (aName.IsEmpty())
    return Standard_False;

  // set name, removing spaces around it
  TCollection_AsciiString aBuffer(aName);
  aBuffer.LeftAdjust();
  aBuffer.RightAdjust();
  theStr->AssignCat(aBuffer.ToCString());
  return Standard_True;
}

>>>>>>> accb2f351 (u)
//=======================================================================
//function : STEPCAFControl_Writer
//purpose  :
//=======================================================================
<<<<<<< HEAD

STEPCAFControl_Writer::STEPCAFControl_Writer () :
       myColorMode( Standard_True ),
       myNameMode ( Standard_True ),
       myLayerMode( Standard_True ),
       myPropsMode( Standard_True ),
       mySHUOMode ( Standard_True ),
       myGDTMode  ( Standard_True ),
       myMatMode  ( Standard_True )
{
  STEPCAFControl_Controller::Init();
  Handle(XSControl_WorkSession) WS = new XSControl_WorkSession;
  Init ( WS );
}


//=======================================================================
//function : STEPCAFControl_Writer
//purpose  :
//=======================================================================

STEPCAFControl_Writer::STEPCAFControl_Writer (const Handle(XSControl_WorkSession)& WS,
                                              const Standard_Boolean scratch) :
=======
STEPCAFControl_Writer::STEPCAFControl_Writer() :
>>>>>>> accb2f351 (u)
  myColorMode(Standard_True),
  myNameMode(Standard_True),
  myLayerMode(Standard_True),
  myPropsMode(Standard_True),
  mySHUOMode(Standard_True),
  myGDTMode(Standard_True),
  myMatMode(Standard_True)
{
  STEPCAFControl_Controller::Init();
<<<<<<< HEAD
  Init ( WS, scratch );
}

=======
  Handle(XSControl_WorkSession) aWS = new XSControl_WorkSession;
  Init(aWS);
}

//=======================================================================
//function : STEPCAFControl_Writer
//purpose  :
//=======================================================================
STEPCAFControl_Writer::STEPCAFControl_Writer(const Handle(XSControl_WorkSession)& theWS,
                                             const Standard_Boolean theScratch) :
  myColorMode(Standard_True),
  myNameMode(Standard_True),
  myLayerMode(Standard_True),
  myPropsMode(Standard_True),
  mySHUOMode(Standard_True),
  myGDTMode(Standard_True),
  myMatMode(Standard_True)
{
  STEPCAFControl_Controller::Init();
  Init(theWS, theScratch);
}
>>>>>>> accb2f351 (u)

//=======================================================================
//function : Init
//purpose  :
//=======================================================================
<<<<<<< HEAD

void STEPCAFControl_Writer::Init (const Handle(XSControl_WorkSession)& WS,
				  const Standard_Boolean scratch)
{
  WS->SelectNorm ( "STEP" );
  myWriter.SetWS (WS,scratch);
  myFiles.Clear();
  myLabEF.Clear();
  myLabels.Clear();
=======
void STEPCAFControl_Writer::Init(const Handle(XSControl_WorkSession)& theWS,
                                 const Standard_Boolean theScratch)
{
  theWS->SelectNorm("STEP");
  myWriter.SetWS(theWS, theScratch);
  myFiles.Clear();
  myLabEF.Clear();
  myLabels.Clear();
  myPureRefLabels.Clear();
  myRootLabels.Clear();
>>>>>>> accb2f351 (u)
  myGDTPresentationDM = new StepVisual_DraughtingModel();
  myGDTPrsCurveStyle = new StepVisual_HArray1OfPresentationStyleAssignment(1, 1);
}

<<<<<<< HEAD

=======
>>>>>>> accb2f351 (u)
//=======================================================================
//function : Write
//purpose  :
//=======================================================================
<<<<<<< HEAD
IFSelect_ReturnStatus STEPCAFControl_Writer::Write (const Standard_CString theFileName)
{
  IFSelect_ReturnStatus aStatus = myWriter.Write (theFileName);
=======
IFSelect_ReturnStatus STEPCAFControl_Writer::Write(const Standard_CString theFileName)
{
  IFSelect_ReturnStatus aStatus = myWriter.Write(theFileName);
>>>>>>> accb2f351 (u)
  if (aStatus != IFSelect_RetDone)
  {
    return aStatus;
  }

  // get directory name of the main file
  TCollection_AsciiString aDirPath;
  {
<<<<<<< HEAD
    OSD_Path aMainFile (theFileName);
    aMainFile.SetName ("");
    aMainFile.SetExtension ("");
    aMainFile.SystemName (aDirPath);
  }

  for (NCollection_DataMap<TCollection_AsciiString, Handle(STEPCAFControl_ExternFile)>::Iterator anExtFileIter (myFiles);
       anExtFileIter.More(); anExtFileIter.Next())
  {
    Handle(STEPCAFControl_ExternFile) anExtFile = anExtFileIter.Value();
=======
    OSD_Path aMainFile(theFileName);
    aMainFile.SetName("");
    aMainFile.SetExtension("");
    aMainFile.SystemName(aDirPath);
  }

  for (NCollection_DataMap<TCollection_AsciiString, Handle(STEPCAFControl_ExternFile)>::Iterator anExtFileIter(myFiles);
       anExtFileIter.More(); anExtFileIter.Next())
  {
    const Handle(STEPCAFControl_ExternFile)& anExtFile = anExtFileIter.Value();
>>>>>>> accb2f351 (u)
    if (anExtFile->GetWriteStatus() != IFSelect_RetVoid)
    {
      continue;
    }

    // construct extern file name
<<<<<<< HEAD
    TCollection_AsciiString aFileName = OSD_Path::AbsolutePath (aDirPath, anExtFile->GetName()->String());
=======
    TCollection_AsciiString aFileName = OSD_Path::AbsolutePath(aDirPath, anExtFile->GetName()->String());
>>>>>>> accb2f351 (u)
    if (aFileName.Length() <= 0)
    {
      aFileName = anExtFile->GetName()->String();
    }
<<<<<<< HEAD
#ifdef OCCT_DEBUG
    std::cout << "Writing external file: " << aFileName << std::endl;
#endif
    
    const IFSelect_ReturnStatus anExtStatus = anExtFile->GetWS()->SendAll (aFileName.ToCString());
    anExtFile->SetWriteStatus (anExtStatus);
=======
    Message::SendTrace() << "Writing external file: " << aFileName << "\n";

    const IFSelect_ReturnStatus anExtStatus = anExtFile->GetWS()->SendAll(aFileName.ToCString());
    anExtFile->SetWriteStatus(anExtStatus);
>>>>>>> accb2f351 (u)
    if (anExtStatus != IFSelect_RetDone)
    {
      aStatus = anExtStatus;
    }
  }

  return aStatus;
}

//=======================================================================
//function : prepareUnit
//purpose  :
//=======================================================================
void STEPCAFControl_Writer::prepareUnit(const TDF_Label& theLabel,
                                        const Handle(StepData_StepModel)& theModel)
{
  Handle(XCAFDoc_LengthUnit) aLengthAttr;
  if (!theLabel.IsNull() &&
<<<<<<< HEAD
    theLabel.Root().FindAttribute(XCAFDoc_LengthUnit::GetID(), aLengthAttr))
=======
      theLabel.Root().FindAttribute(XCAFDoc_LengthUnit::GetID(), aLengthAttr))
>>>>>>> accb2f351 (u)
  {
    theModel->SetLocalLengthUnit(aLengthAttr->GetUnitValue() * 1000); // convert to mm
  }
  else
  {
    XSAlgo::AlgoContainer()->PrepareForTransfer(); // update unit info
    theModel->SetLocalLengthUnit(UnitsMethods::GetCasCadeLengthUnit());
  }
}

//=======================================================================
//function : WriteStream
//purpose  :
//=======================================================================
<<<<<<< HEAD
IFSelect_ReturnStatus STEPCAFControl_Writer::WriteStream (std::ostream& theStream)
=======
IFSelect_ReturnStatus STEPCAFControl_Writer::WriteStream(std::ostream& theStream)
>>>>>>> accb2f351 (u)
{
  if (!myFiles.IsEmpty())
  {
    // writing external files is unsupported via stream interface
    return IFSelect_RetError;
  }

<<<<<<< HEAD
  return myWriter.WriteStream (theStream);
=======
  return myWriter.WriteStream(theStream);
>>>>>>> accb2f351 (u)
}

//=======================================================================
//function : Transfer
//purpose  :
//=======================================================================
<<<<<<< HEAD

Standard_Boolean STEPCAFControl_Writer::Transfer(const Handle(TDocStd_Document) &doc,
                                                 const STEPControl_StepModelType mode,
                                                 const Standard_CString multi,
                                                 const Message_ProgressRange& theProgress)
{
  Handle(XCAFDoc_ShapeTool) STool = XCAFDoc_DocumentTool::ShapeTool( doc->Main() );
  if ( STool.IsNull() ) return Standard_False;

  TDF_LabelSequence labels;
  STool->GetFreeShapes ( labels );
  return Transfer(myWriter, labels, mode, multi, Standard_False, theProgress);
}


//=======================================================================
//function : Transfer
//purpose  :
//=======================================================================

Standard_Boolean STEPCAFControl_Writer::Transfer(const TDF_Label& L,
                                                 const STEPControl_StepModelType mode,
                                                 const Standard_CString multi,
                                                 const Message_ProgressRange& theProgress)
{
  TDF_LabelSequence labels;
  labels.Append ( L );
  return Transfer(myWriter, labels, mode, multi, Standard_False, theProgress);
}

//=======================================================================
//function : Transfer
//purpose  :
//=======================================================================

Standard_Boolean STEPCAFControl_Writer::Transfer(const TDF_LabelSequence& labels,
                                                 const STEPControl_StepModelType mode,
                                                 const Standard_CString multi,
                                                 const Message_ProgressRange& theProgress)
{
  return Transfer(myWriter, labels, mode, multi, Standard_False, theProgress);
}

//=======================================================================
//function : Perform
//purpose  :
//=======================================================================

Standard_Boolean STEPCAFControl_Writer::Perform (const Handle(TDocStd_Document) &doc,
                                                 const Standard_CString filename,
                                                 const Message_ProgressRange& theProgress)
{
  if (!Transfer(doc, STEPControl_AsIs, 0L, theProgress)) return Standard_False;
  return Write ( filename ) == IFSelect_RetDone;
}


//=======================================================================
//function : Perform
//purpose  :
//=======================================================================

Standard_Boolean STEPCAFControl_Writer::Perform (const Handle(TDocStd_Document) &doc,
                                                 const TCollection_AsciiString &filename,
                                                 const Message_ProgressRange& theProgress)
{
  if ( ! Transfer ( doc, STEPControl_AsIs, 0L, theProgress ) ) return Standard_False;
  return Write ( filename.ToCString() ) == IFSelect_RetDone;
}


//=======================================================================
//function : ExternFiles
//purpose  :
//=======================================================================

const NCollection_DataMap<TCollection_AsciiString, Handle(STEPCAFControl_ExternFile)>& STEPCAFControl_Writer::ExternFiles () const
{
  return myFiles;
}


//=======================================================================
//function : ExternFile
//purpose  :
//=======================================================================

Standard_Boolean STEPCAFControl_Writer::ExternFile (const TDF_Label &L,
						    Handle(STEPCAFControl_ExternFile) &ef) const
{
  ef.Nullify();
  if ( ! myLabEF.IsBound ( L ) ) return Standard_False;
  ef = myLabEF.Find ( L );
  return Standard_True;
}


//=======================================================================
//function : ExternFile
//purpose  :
//=======================================================================

Standard_Boolean STEPCAFControl_Writer::ExternFile (const Standard_CString name,
						    Handle(STEPCAFControl_ExternFile) &ef) const
{
  ef.Nullify();
  if ( ! myFiles.IsEmpty() || ! myFiles.IsBound ( name ) )
    return Standard_False;
  ef = myFiles.Find( name );
  return Standard_True;
}


//=======================================================================
//function : Writer
//purpose  :
//=======================================================================

STEPControl_Writer &STEPCAFControl_Writer::ChangeWriter ()
{
  return myWriter;
}


//=======================================================================
//function : Writer
//purpose  :
//=======================================================================

const STEPControl_Writer &STEPCAFControl_Writer::Writer () const
{
  return myWriter;
}


=======
Standard_Boolean STEPCAFControl_Writer::Transfer(const Handle(TDocStd_Document)& theDoc,
                                                 const STEPControl_StepModelType theMode,
                                                 const Standard_CString theMulti,
                                                 const Message_ProgressRange& theProgress)
{
  Handle(XCAFDoc_ShapeTool) aShTool = XCAFDoc_DocumentTool::ShapeTool(theDoc->Main());
  if (aShTool.IsNull())
    return Standard_False;

  myRootLabels.Clear();
  myRootLabels.Add(theDoc->Main().Root());
  TDF_LabelSequence aLabels;
  aShTool->GetFreeShapes(aLabels);
  return transfer(myWriter, aLabels, theMode, theMulti, Standard_False, theProgress);
}

>>>>>>> accb2f351 (u)
//=======================================================================
//function : Transfer
//purpose  :
//=======================================================================
<<<<<<< HEAD

Standard_Boolean STEPCAFControl_Writer::Transfer (STEPControl_Writer &writer,
                                                  const TDF_LabelSequence &labels,
                                                  const STEPControl_StepModelType mode,
                                                  const Standard_CString multi,
                                                  const Standard_Boolean isExternFile,
                                                  const Message_ProgressRange& theProgress)
{
  if ( labels.Length() <=0 ) return Standard_False;

  Handle(STEPCAFControl_ActorWrite) Actor =
    Handle(STEPCAFControl_ActorWrite)::DownCast ( writer.WS()->NormAdaptor()->ActorWrite() );

  const Handle(StepData_StepModel) aModel = Handle(StepData_StepModel)::DownCast(writer.WS()->Model());
  prepareUnit(labels.First(), aModel); // set local length unit to the model
  // translate free top-level shapes of the DECAF document
  Standard_Integer ap = Interface_Static::IVal ("write.step.schema");
  TDF_LabelSequence sublabels;
  Message_ProgressScope aPS(theProgress, "Labels", labels.Length());
  for ( Standard_Integer i=1; i <= labels.Length() && aPS.More(); i++)
  {
    Message_ProgressRange aRange = aPS.Next();
    TDF_Label L = labels.Value(i);
    if ( myLabels.IsBound ( L ) ) continue; // already processed

    TopoDS_Shape shape = XCAFDoc_ShapeTool::GetShape ( L );
    if ( shape.IsNull() ) continue;

    // write shape either as a whole, or as multifile (with extern refs)
    if ( ! multi  ) {
      Actor->SetStdMode ( Standard_False );

      TDF_LabelSequence comp;
=======
Standard_Boolean STEPCAFControl_Writer::Transfer(const TDF_Label& theLabel,
                                                 const STEPControl_StepModelType theMode,
                                                 const Standard_CString theIsMulti,
                                                 const Message_ProgressRange& theProgress)
{
  if (theLabel.IsNull())
  {
    return Standard_False;
  }
  TDF_LabelSequence aLabels;
  aLabels.Append(theLabel);
  myRootLabels.Clear();
  myRootLabels.Add(theLabel.Root());
  return transfer(myWriter, aLabels, theMode, theIsMulti, Standard_False, theProgress);
}

//=======================================================================
//function : Transfer
//purpose  :
//=======================================================================
Standard_Boolean STEPCAFControl_Writer::Transfer(const TDF_LabelSequence& theLabels,
                                                 const STEPControl_StepModelType theMode,
                                                 const Standard_CString theIsMulti,
                                                 const Message_ProgressRange& theProgress)
{
  myRootLabels.Clear();
  for (TDF_LabelSequence::Iterator aLabelIter(theLabels);
       aLabelIter.More(); aLabelIter.Next())
  {
    const TDF_Label& aLabel = aLabelIter.Value();
    if (!aLabel.IsNull())
    {
      myRootLabels.Add(aLabel.Root());
    }
  }
  return transfer(myWriter, theLabels, theMode, theIsMulti, Standard_False, theProgress);
}

//=======================================================================
//function : Perform
//purpose  :
//=======================================================================
Standard_Boolean STEPCAFControl_Writer::Perform(const Handle(TDocStd_Document)& theDoc,
                                                const Standard_CString theFileName,
                                                const Message_ProgressRange& theProgress)
{
  if (!Transfer(theDoc, STEPControl_AsIs, 0L, theProgress))
    return Standard_False;
  return Write(theFileName) == IFSelect_RetDone;
}

//=======================================================================
//function : Perform
//purpose  :
//=======================================================================
Standard_Boolean STEPCAFControl_Writer::Perform(const Handle(TDocStd_Document)& theDoc,
                                                const TCollection_AsciiString& theFileName,
                                                const Message_ProgressRange& theProgress)
{
  if (!Transfer(theDoc, STEPControl_AsIs, 0L, theProgress))
    return Standard_False;
  return Write(theFileName.ToCString()) == IFSelect_RetDone;
}

//=======================================================================
//function : ExternFile
//purpose  :
//=======================================================================
Standard_Boolean STEPCAFControl_Writer::ExternFile(const TDF_Label& theLabel,
                                                   Handle(STEPCAFControl_ExternFile)& theExtFile) const
{
  theExtFile.Nullify();
  if (!myLabEF.IsBound(theLabel))
    return Standard_False;
  theExtFile = myLabEF.Find(theLabel);
  return Standard_True;
}

//=======================================================================
//function : ExternFile
//purpose  :
//=======================================================================
Standard_Boolean STEPCAFControl_Writer::ExternFile(const Standard_CString theName,
                                                   Handle(STEPCAFControl_ExternFile)& theExtFile) const
{
  theExtFile.Nullify();
  if (!myFiles.IsEmpty() || !myFiles.IsBound(theName))
    return Standard_False;
  theExtFile = myFiles.Find(theName);
  return Standard_True;
}

//=======================================================================
//function : Transfer
//purpose  :
//=======================================================================
Standard_Boolean STEPCAFControl_Writer::transfer(STEPControl_Writer& theWriter,
                                                 const TDF_LabelSequence& theLabels,
                                                 const STEPControl_StepModelType theMode,
                                                 const Standard_CString theIsMulti,
                                                 const Standard_Boolean theIsExternFile,
                                                 const Message_ProgressRange& theProgress)
{
  if (theLabels.IsEmpty())
    return Standard_False;

  Handle(STEPCAFControl_ActorWrite) anActor =
    Handle(STEPCAFControl_ActorWrite)::DownCast(theWriter.WS()->NormAdaptor()->ActorWrite());

  const Handle(StepData_StepModel) aModel = Handle(StepData_StepModel)::DownCast(theWriter.WS()->Model());
  prepareUnit(theLabels.First(), aModel); // set local length unit to the model
  // translate free top-level shapes of the DECAF document
  const Standard_Integer aStepSchema = Interface_Static::IVal("write.step.schema");
  TDF_LabelSequence aSubLabels;
  Message_ProgressScope aPS(theProgress, "Labels", theLabels.Length());
  // Iterate on requested shapes
  for (TDF_LabelSequence::Iterator aLabelIter(theLabels);
       aLabelIter.More() && aPS.More(); aLabelIter.Next())
  {
    Message_ProgressRange aRange = aPS.Next();
    TDF_Label aCurL = aLabelIter.Value();
    if (myLabels.IsBound(aCurL))
      continue; // already processed

    TopoDS_Shape aCurShape = XCAFDoc_ShapeTool::GetShape(aCurL);
    if (aCurShape.IsNull())
      continue;
    TopoDS_Shape aShapeForBind = aCurShape;
    // write shape either as a whole, or as multifile (with extern refs)
    if (!theIsMulti)
    {
      anActor->SetStdMode(Standard_False);

      TDF_LabelSequence aCompLabels;
>>>>>>> accb2f351 (u)

      //For case when only part of assembly structure should be written in the document
      //if specified label is component of the assembly then
      //in order to save location of this component in the high-level assembly
      //and save name of high-level assembly it is necessary to represent structure of high-level assembly
      //as assembly with one component specified by current label.
      //For that compound containing only specified component is binded to the label of the high-level assembly.
      //The such way full structure of high-level assembly was replaced on the assembly containing one component.
      //For case when free shape reference is (located root) also create an auxiliary assembly.
<<<<<<< HEAD
      if ( XCAFDoc_ShapeTool::IsReference ( L ) )
=======
      if (XCAFDoc_ShapeTool::IsReference(aCurL))
>>>>>>> accb2f351 (u)
      {
        TopoDS_Compound aComp;
        BRep_Builder aB;
        aB.MakeCompound(aComp);
<<<<<<< HEAD
        aB.Add(aComp, shape);
        shape = aComp; 
        comp.Append(L);
        TDF_Label ref;
        if ( XCAFDoc_ShapeTool::GetReferredShape ( L, ref ) )
        {
          if(XCAFDoc_ShapeTool::IsAssembly ( ref))
            XCAFDoc_ShapeTool::GetComponents ( ref, comp, Standard_True );
        }
        if ( !XCAFDoc_ShapeTool::IsFree ( L ) )
          L = L.Father();
=======
        aB.Add(aComp, aCurShape);
        aCurShape = aComp;
        myPureRefLabels.Bind(aCurL, aComp);
        aCompLabels.Append(aCurL);
        TDF_Label aRefL;
        if (XCAFDoc_ShapeTool::GetReferredShape(aCurL, aRefL))
        {
          if (XCAFDoc_ShapeTool::IsAssembly(aRefL))
            XCAFDoc_ShapeTool::GetComponents(aRefL, aCompLabels, Standard_True);
        }
        if (!XCAFDoc_ShapeTool::IsFree(aCurL))
          aCurL = aCurL.Father();
>>>>>>> accb2f351 (u)
      }
      else
      {
        // fill sequence of (sub) shapes for which attributes should be written
        // and set actor to handle assemblies in a proper way
<<<<<<< HEAD
        if(XCAFDoc_ShapeTool::IsAssembly ( L ))
          XCAFDoc_ShapeTool::GetComponents ( L, comp, Standard_True );
      }
      
      for ( Standard_Integer k=1; k <= comp.Length(); k++ ) {
        TDF_Label ref;
        if ( ! XCAFDoc_ShapeTool::GetReferredShape ( comp(k), ref ) ) continue;
        if ( ! myLabels.IsBound ( ref ) ) {
          TopoDS_Shape refS = XCAFDoc_ShapeTool::GetShape ( ref );
          myLabels.Bind ( ref, refS );
          sublabels.Append ( ref );
          if ( XCAFDoc_ShapeTool::IsAssembly ( ref ) )
            Actor->RegisterAssembly ( refS );
        }
      }
      myLabels.Bind ( L, shape );
      sublabels.Append ( L );

      if ( XCAFDoc_ShapeTool::IsAssembly ( L ) || XCAFDoc_ShapeTool::IsReference ( L ) )
        Actor->RegisterAssembly ( shape );

      writer.Transfer(shape, mode, Standard_False, aRange);
      Actor->SetStdMode ( Standard_True ); // restore default behaviour
    }
    else {
      // translate final solids
      Message_ProgressScope aPS1 (aRange, NULL, 2);
      TopoDS_Shape Sass = TransferExternFiles(L, mode, sublabels, multi, aPS1.Next());
      if (aPS1.UserBreak())
        return Standard_False;

      // translate main assembly structure
/*
      if ( ap == 3 ) { // if AP203, switch to AP214
	Interface_Static::SetCVal ("write.step.schema", "AP214DIS");
	Handle(StepData_StepModel) model = 
	  Handle(StepData_StepModel)::DownCast ( writer.WS()->Model() );
	if ( model->HasHeaderEntity(STANDARD_TYPE(HeaderSection_FileSchema)) ) {
	  Handle(HeaderSection_FileSchema) fs = 
	    Handle(HeaderSection_FileSchema)::DownCast ( model->HeaderEntity(STANDARD_TYPE(HeaderSection_FileSchema)) );
	  Handle(TCollection_HAsciiString) str = fs->SchemaIdentifiersValue ( 1 );
	  Handle(TCollection_HAsciiString) ap214 = new TCollection_HAsciiString ( "AUTOMOTIVE_DESIGN" );
	  if ( str->Search ( ap214 ) <0 ) {
	    str->Clear();
	    str->AssignCat ( ap214 );
	  }
	}
      }
*/      
      Standard_Integer assemblymode = Interface_Static::IVal ("write.step.assembly");
      Interface_Static::SetCVal ("write.step.assembly", "On");
      writer.Transfer ( Sass, STEPControl_AsIs, Standard_True, aPS1.Next());
      Interface_Static::SetIVal ("write.step.assembly", assemblymode);
      Interface_Static::SetIVal ("write.step.schema", ap);
=======
        if (XCAFDoc_ShapeTool::IsAssembly(aCurL))
          XCAFDoc_ShapeTool::GetComponents(aCurL, aCompLabels, Standard_True);
      }

      for (TDF_LabelSequence::Iterator aCompIter(aCompLabels); aCompIter.More(); aCompIter.Next())
      {
        const TDF_Label aCurSubShL = aCompIter.Value();
        if (myLabels.IsBound(aCurSubShL))
        {
          continue;
        }
        const TopoDS_Shape aCurSh = XCAFDoc_ShapeTool::GetShape(aCurSubShL);
        if (aCurSh.IsNull())
        {
          continue;
        }
        myLabels.Bind(aCurSubShL, aCurSh);
        aSubLabels.Append(aCurSubShL);
        TDF_Label aRefL;
        if (!XCAFDoc_ShapeTool::GetReferredShape(aCurSubShL, aRefL))
        {
          continue;
        }
        if (!myLabels.IsBound(aRefL))
        {
          TopoDS_Shape aRefSh = XCAFDoc_ShapeTool::GetShape(aRefL);
          myLabels.Bind(aRefL, aRefSh);
          aSubLabels.Append(aRefL);
          if (XCAFDoc_ShapeTool::IsAssembly(aRefL))
          {
            anActor->RegisterAssembly(aRefSh);
          }
        }
      }
      myLabels.Bind(aCurL, aShapeForBind);
      aSubLabels.Append(aCurL);

      if (XCAFDoc_ShapeTool::IsAssembly(aCurL) || XCAFDoc_ShapeTool::IsReference(aCurL))
        anActor->RegisterAssembly(aCurShape);

      theWriter.Transfer(aCurShape, theMode, Standard_False, aRange);
      anActor->SetStdMode(Standard_True); // restore default behaviour
    }
    else
    {
      // translate final solids
      Message_ProgressScope aPS1(aRange, NULL, 2);
      TopoDS_Shape aSass = transferExternFiles(aCurL, theMode, aSubLabels, theIsMulti, aPS1.Next());
      if (aPS1.UserBreak())
        return Standard_False;

      Standard_Integer assemblymode = Interface_Static::IVal("write.step.assembly");
      Interface_Static::SetCVal("write.step.assembly", "On");
      theWriter.Transfer(aSass, STEPControl_AsIs, Standard_True, aPS1.Next());
      Interface_Static::SetIVal("write.step.assembly", assemblymode);
>>>>>>> accb2f351 (u)
    }
  }
  if (aPS.UserBreak())
    return Standard_False;

<<<<<<< HEAD
  writer.WS()->ComputeGraph(Standard_True );// added by skl 03.11.2003 since we use
                                            // writer.Transfer() without compute graph

  // write names
  if ( GetNameMode() )
    WriteNames ( writer.WS(), sublabels );

  if ( !multi ) {
    // write colors
    if ( GetColorMode() )
      WriteColors ( writer.WS(), sublabels );
    
    // write layers
    if ( GetLayerMode() )
      WriteLayers ( writer.WS(), sublabels );

    // write SHUO entities
    if ( GetSHUOMode() && !isExternFile ) 
      // do not store SHUO for extern reference for the moment
      WriteSHUOs (  writer.WS(), sublabels );
    
    // write G&DTs
    if(GetDimTolMode()) {
      if (ap == 5) {
        WriteDGTsAP242(writer.WS(), sublabels);
      }
      else {
        WriteDGTs(writer.WS(), sublabels);
=======
  theWriter.WS()->ComputeGraph(Standard_True); // Setting to clear and regenerate graph

  // write names
  if (GetNameMode())
    writeNames(theWriter.WS(), aSubLabels);

  if (!theIsMulti)
  {
    // write colors
    if (GetColorMode())
      writeColors(theWriter.WS(), aSubLabels);

    // write layers
    if (GetLayerMode())
      writeLayers(theWriter.WS(), aSubLabels);

    // write SHUO entities
    if (GetSHUOMode() && !theIsExternFile)
      // do not store SHUO for extern reference for the moment
      writeSHUOs(theWriter.WS(), aSubLabels);

    // write G&DTs
    if (GetDimTolMode())
    {
      if (aStepSchema == 5)
      {
        writeDGTsAP242(theWriter.WS(), aSubLabels);
      }
      else
      {
        writeDGTs(theWriter.WS(), aSubLabels);
>>>>>>> accb2f351 (u)
      }
    }

    // write Materials
<<<<<<< HEAD
    if(GetMaterialMode())
      WriteMaterials(writer.WS(),sublabels);

    // register all MDGPRs in model
    MoniTool_DataMapIteratorOfDataMapOfShapeTransient anItr(myMapCompMDGPR);
    for (; anItr.More(); anItr.Next())
      aModel->AddWithRefs( anItr.Value() );
  }
  
  if ( multi ) { // external refs
    WriteExternRefs ( writer.WS(), sublabels );
  }

  // write validation props
//  if ( multi && ap ==3 ) {
//      Interface_Static::SetCVal ("write.step.schema", "AP214DIS");
//  }
  if ( GetPropsMode() ) 
    WriteValProps ( writer.WS(), sublabels, multi );

  Interface_Static::SetIVal ("write.step.schema", ap);

  // refresh graph
  writer.WS()->ComputeGraph ( Standard_True );

  /* ================================
    *  Write names for the sub-shapes
    * ================================ */

  if (Interface_Static::IVal("write.stepcaf.subshapes.name") != 0)
  {
    const Handle(XSControl_TransferWriter) &TW = this->ChangeWriter().WS()->TransferWriter();
    const Handle(Transfer_FinderProcess) &FP = TW->FinderProcess();

    for ( int i = 1; i <= sublabels.Length(); i++ )
    {
      TDF_Label L = sublabels.Value(i);

      for ( TDF_ChildIterator it(L, Standard_True); it.More(); it.Next() )
      {
        TDF_Label SubL = it.Value();

        // Access name recorded in OCAF TDataStd_Name attribute
        Handle(TCollection_HAsciiString) hSubName = new TCollection_HAsciiString;
        if ( !GetLabelName(SubL, hSubName) )
          continue;

        // Access topological data
        TopoDS_Shape SubS = XCAFDoc_ShapeTool::GetShape(SubL);
        if ( SubS.IsNull() )
          continue;

        // Access the correspondent STEP Representation Item
        Handle(StepRepr_RepresentationItem) RI;
        Handle(TransferBRep_ShapeMapper) aShMapper = TransferBRep::ShapeMapper(FP, SubS);
        if ( !FP->FindTypedTransient(aShMapper, STANDARD_TYPE(StepRepr_RepresentationItem), RI) )
          continue;

        // Record the name
        RI->SetName(hSubName);
=======
    if (GetMaterialMode())
      writeMaterials(theWriter.WS(), aSubLabels);

    // register all MDGPRs in model
    for (MoniTool_DataMapIteratorOfDataMapOfShapeTransient anItr(myMapCompMDGPR);
         anItr.More(); anItr.Next())
    {
      aModel->AddWithRefs(anItr.Value());
    }
  }

  if (theIsMulti)
  { // external refs
    writeExternRefs(theWriter.WS(), aSubLabels);
  }

  // write validation props
  if (GetPropsMode())
    writeValProps(theWriter.WS(), aSubLabels, theIsMulti);

  // refresh graph
  theWriter.WS()->ComputeGraph(Standard_True);

  // Write names for the sub-shapes
  if (Interface_Static::IVal("write.stepcaf.subshapes.name") != 0)
  {
    const Handle(XSControl_TransferWriter)& TW = this->ChangeWriter().WS()->TransferWriter();
    const Handle(Transfer_FinderProcess)& aFP = TW->FinderProcess();

    // Iterate on requested sub shapes
    for (TDF_LabelSequence::Iterator aLabelIter(aSubLabels);
         aLabelIter.More(); aLabelIter.Next())
    {
      const TDF_Label& aCurL = aLabelIter.Value();

      for (TDF_ChildIterator aChildIter(aCurL, Standard_True); aChildIter.More(); aChildIter.Next())
      {
        const TDF_Label& aSubL = aChildIter.Value();

        // Access name recorded in OCAF TDataStd_Name attribute
        Handle(TCollection_HAsciiString) aHSubName = new TCollection_HAsciiString;
        if (!GetLabelName(aSubL, aHSubName))
          continue;

        // Access topological data
        TopoDS_Shape aSubS = XCAFDoc_ShapeTool::GetShape(aSubL);
        if (aSubS.IsNull())
          continue;

        // Access the correspondent STEP Representation Item
        Handle(StepRepr_RepresentationItem) aRI;
        Handle(TransferBRep_ShapeMapper) aShMapper = TransferBRep::ShapeMapper(aFP, aSubS);
        if (!aFP->FindTypedTransient(aShMapper, STANDARD_TYPE(StepRepr_RepresentationItem), aRI))
          continue;

        // Record the name
        aRI->SetName(aHSubName);
>>>>>>> accb2f351 (u)
      }
    }
  }

  return Standard_True;
}

<<<<<<< HEAD

//=======================================================================
//function : TransferExternFiles
//purpose  :
//=======================================================================

TopoDS_Shape STEPCAFControl_Writer::TransferExternFiles (const TDF_Label &L,
                                                         const STEPControl_StepModelType mode,
                                                         TDF_LabelSequence &labels,
                                                         const Standard_CString prefix,
                                                         const Message_ProgressRange& theProgress)
{
  // if label already translated, just return the shape
  if ( myLabels.IsBound ( L ) ) {
    return myLabels.Find ( L );
  }

  TopoDS_Compound C;
  BRep_Builder B;
  B.MakeCompound ( C );
  //labels.Append ( L ); 
  // if not assembly, write to separate file
  if ( ! XCAFDoc_ShapeTool::IsAssembly ( L ) && !XCAFDoc_ShapeTool::IsComponent ( L )) {
    labels.Append ( L );
    // prepare for transfer
    Handle(XSControl_WorkSession) newWS = new XSControl_WorkSession;
    newWS->SelectNorm ( "STEP" );
    STEPControl_Writer sw ( newWS, Standard_True );
    TDF_LabelSequence Lseq;
    Lseq.Append ( L );

    // construct the name for extern file
    Handle(TCollection_HAsciiString) basename = new TCollection_HAsciiString;
    if ( prefix && prefix[0] ) basename->AssignCat ( prefix );
    GetLabelName ( L, basename );
    Handle(TCollection_HAsciiString) name = new TCollection_HAsciiString ( basename );
    name->AssignCat ( ".stp" );
    if ( myFiles.IsBound( name->ToCString() ) ) { // avoid confusions
      for ( Standard_Integer k=1; k < 32000; k++ ) {
        name = new TCollection_HAsciiString ( basename );
        name->AssignCat ( "_" );
        name->AssignCat ( TCollection_AsciiString ( k ).ToCString() );
        name->AssignCat ( ".stp" );
        if ( ! myFiles.IsBound ( name->ToCString() ) ) break;
=======
//=======================================================================
//function : transferExternFiles
//purpose  :
//=======================================================================
TopoDS_Shape STEPCAFControl_Writer::transferExternFiles(const TDF_Label& theLabel,
                                                        const STEPControl_StepModelType theMode,
                                                        TDF_LabelSequence& theLabels,
                                                        const Standard_CString thePrefix,
                                                        const Message_ProgressRange& theProgress)
{
  // if label already translated, just return the shape
  if (myLabels.IsBound(theLabel))
  {
    return myLabels.Find(theLabel);
  }

  TopoDS_Compound aComp;
  BRep_Builder aBuilder;
  aBuilder.MakeCompound(aComp);
  // if not assembly, write to separate file
  if (!XCAFDoc_ShapeTool::IsAssembly(theLabel) && !XCAFDoc_ShapeTool::IsComponent(theLabel))
  {
    theLabels.Append(theLabel);
    // prepare for transfer
    Handle(XSControl_WorkSession) aNewWS = new XSControl_WorkSession;
    aNewWS->SelectNorm("STEP");
    STEPControl_Writer aStepWriter(aNewWS, Standard_True);
    TDF_LabelSequence aLabelSeq;
    aLabelSeq.Append(theLabel);

    // construct the name for extern file
    Handle(TCollection_HAsciiString) aBaseName = new TCollection_HAsciiString;
    if (thePrefix && thePrefix[0]) aBaseName->AssignCat(thePrefix);
    GetLabelName(theLabel, aBaseName);
    Handle(TCollection_HAsciiString) aNewName = new TCollection_HAsciiString(aBaseName);
    aNewName->AssignCat(".stp");
    if (myFiles.IsBound(aNewName->ToCString()))
    { // avoid confusions
      for (Standard_Integer k = 1; k < 32000; k++)
      {
        aNewName = new TCollection_HAsciiString(aBaseName);
        aNewName->AssignCat("_");
        aNewName->AssignCat(TCollection_AsciiString(k).ToCString());
        aNewName->AssignCat(".stp");
        if (!myFiles.IsBound(aNewName->ToCString())) break;
>>>>>>> accb2f351 (u)
      }
    }

    // translate and record extern file
<<<<<<< HEAD
    Handle(STEPCAFControl_ExternFile) EF = new STEPCAFControl_ExternFile;
    EF->SetWS ( newWS );
    EF->SetName ( name );
    EF->SetLabel ( L );
    Standard_Integer assemblymode = Interface_Static::IVal ("write.step.assembly");
    Interface_Static::SetCVal ("write.step.assembly", "Off");
    const Standard_CString multi = 0;
    EF->SetTransferStatus ( Transfer ( sw, Lseq, mode, multi, Standard_True, theProgress) );
    Interface_Static::SetIVal ("write.step.assembly", assemblymode);
    myLabEF.Bind ( L, EF );
    myFiles.Bind ( name->ToCString(), EF );

    // return empty compound as replacement for the shape
    myLabels.Bind ( L, C );
    return C;
  }
  TDF_LabelSequence comp;
  TDF_Label aCurL = L;
  //if specified shape is component then high-level assembly is considered
  //to get valid structure with location
  if ( XCAFDoc_ShapeTool::IsComponent ( L ) )
  {
    comp.Append(L);
    aCurL = L.Father();
  }
  // else iterate on components add create structure of empty compounds
  // representing the assembly
  else if (XCAFDoc_ShapeTool::IsAssembly ( L ))
    XCAFDoc_ShapeTool::GetComponents ( L, comp, Standard_False );

  labels.Append ( aCurL );
  Message_ProgressScope aPS(theProgress, NULL, comp.Length());
  for ( Standard_Integer k=1; k <= comp.Length() && aPS.More(); k++ ) {
    TDF_Label lab = comp(k);
    TDF_Label ref;
    if ( ! XCAFDoc_ShapeTool::GetReferredShape ( lab, ref ) ) continue;
    TopoDS_Shape Scomp = TransferExternFiles(ref, mode, labels, prefix, aPS.Next());
    Scomp.Location ( XCAFDoc_ShapeTool::GetLocation ( lab ) );
    B.Add ( C, Scomp );
  }
  myLabels.Bind ( aCurL, C );
  return C;
}


//=======================================================================
//function : WriteExternRefs
//purpose  :
//=======================================================================

Standard_Boolean STEPCAFControl_Writer::WriteExternRefs (const Handle(XSControl_WorkSession) &WS,
							 const TDF_LabelSequence &labels) const
{
  if ( labels.Length() <=0 ) return Standard_False;

  const Handle(XSControl_TransferWriter) &TW = WS->TransferWriter();
  const Handle(Transfer_FinderProcess) &FP = TW->FinderProcess();
  STEPConstruct_ExternRefs EFTool ( WS );
  Standard_Integer schema = Interface_Static::IVal("write.step.schema");
  for ( Standard_Integer k=1; k <= labels.Length(); k++ ) {
    TDF_Label lab = labels(k);
    if ( XCAFDoc_ShapeTool::IsAssembly ( lab ) ) continue; // skip assemblies

    // get extern file
    Handle(STEPCAFControl_ExternFile) EF;
    if ( ! ExternFile ( lab, EF ) ) continue; // should never be

    // find SDR
    if ( ! myLabels.IsBound ( lab ) ) continue; // not recorded as translated, skip
    TopoDS_Shape S = myLabels.Find ( lab );

    Handle(StepShape_ShapeDefinitionRepresentation) SDR;
    Handle(TransferBRep_ShapeMapper) mapper = TransferBRep::ShapeMapper ( FP, S );
    if ( ! FP->FindTypedTransient ( mapper, STANDARD_TYPE(StepShape_ShapeDefinitionRepresentation), SDR ) ) {
#ifdef OCCT_DEBUG
      std::cout << "Warning: Cannot find SDR for " << S.TShape()->DynamicType()->Name() << std::endl;
#endif
=======
    Handle(STEPCAFControl_ExternFile) anExtFile = new STEPCAFControl_ExternFile;
    anExtFile->SetWS(aNewWS);
    anExtFile->SetName(aNewName);
    anExtFile->SetLabel(theLabel);
    Standard_Integer anAssemblymode = Interface_Static::IVal("write.step.assembly");
    Interface_Static::SetCVal("write.step.assembly", "Off");
    const Standard_CString anIsMulti = 0;
    anExtFile->SetTransferStatus(transfer(aStepWriter, aLabelSeq, theMode, anIsMulti, Standard_True, theProgress));
    Interface_Static::SetIVal("write.step.assembly", anAssemblymode);
    myLabEF.Bind(theLabel, anExtFile);
    myFiles.Bind(aNewName->ToCString(), anExtFile);

    // return empty compound as replacement for the shape
    myLabels.Bind(theLabel, aComp);
    return aComp;
  }
  TDF_LabelSequence aCompLabels;
  TDF_Label aLabel = theLabel;
  //if specified shape is component then high-level assembly is considered
  //to get valid structure with location
  if (XCAFDoc_ShapeTool::IsComponent(theLabel))
  {
    aCompLabels.Append(theLabel);
    aLabel = theLabel.Father();
  }
  // else iterate on components add create structure of empty compounds
  // representing the assembly
  else if (XCAFDoc_ShapeTool::IsAssembly(theLabel))
    XCAFDoc_ShapeTool::GetComponents(theLabel, aCompLabels, Standard_False);

  theLabels.Append(aLabel);
  Message_ProgressScope aPS(theProgress, NULL, aCompLabels.Length());
  // Iterate on requested shapes
  for (TDF_LabelSequence::Iterator aLabelIter(aCompLabels);
       aLabelIter.More() && aPS.More(); aLabelIter.Next())
  {
    const TDF_Label& aCurL = aLabelIter.Value();
    TDF_Label aRefL;
    if (!XCAFDoc_ShapeTool::GetReferredShape(aCurL, aRefL))
      continue;
    TopoDS_Shape aShComp = transferExternFiles(aRefL, theMode, theLabels, thePrefix, aPS.Next());
    aShComp.Location(XCAFDoc_ShapeTool::GetLocation(aCurL));
    aBuilder.Add(aComp, aShComp);
  }
  myLabels.Bind(aLabel, aComp);
  return aComp;
}

//=======================================================================
//function : writeExternRefs
//purpose  :
//=======================================================================
Standard_Boolean STEPCAFControl_Writer::writeExternRefs(const Handle(XSControl_WorkSession)& theWS,
                                                        const TDF_LabelSequence& theLabels) const
{
  if (theLabels.IsEmpty())
    return Standard_False;

  const Handle(XSControl_TransferWriter)& aTW = theWS->TransferWriter();
  const Handle(Transfer_FinderProcess)& aFP = aTW->FinderProcess();
  STEPConstruct_ExternRefs anEFTool(theWS);
  Standard_Integer aStepSchema = Interface_Static::IVal("write.step.schema");
  // Iterate on requested shapes
  for (TDF_LabelSequence::Iterator aLabelIter(theLabels);
       aLabelIter.More(); aLabelIter.Next())
  {
    const TDF_Label& aLab = aLabelIter.Value();
    if (XCAFDoc_ShapeTool::IsAssembly(aLab)) continue; // skip assemblies

    // get extern file
    Handle(STEPCAFControl_ExternFile) anExtFile;
    if (!ExternFile(aLab, anExtFile))
      continue; // should never be

    // find SDR
    if (!myLabels.IsBound(aLab))
      continue; // not recorded as translated, skip
    TopoDS_Shape aShape = myLabels.Find(aLab);

    Handle(StepShape_ShapeDefinitionRepresentation) aSDR;
    Handle(TransferBRep_ShapeMapper) mapper = TransferBRep::ShapeMapper(aFP, aShape);
    if (!aFP->FindTypedTransient(mapper, STANDARD_TYPE(StepShape_ShapeDefinitionRepresentation), aSDR))
    {
      Message::SendTrace() << "Warning: Cannot find SDR for " << aShape.TShape()->DynamicType()->Name() << "\n";
>>>>>>> accb2f351 (u)
      continue;
    }

    // add extern ref
<<<<<<< HEAD
    const char* format = (schema == 3 ? "STEP AP203" : "STEP AP214");
    // try to get PD from SDR
    StepRepr_RepresentedDefinition RD = SDR->Definition();
    Handle(StepRepr_PropertyDefinition) aPropDef = RD.PropertyDefinition();
    if (aPropDef.IsNull()) {
#ifdef OCCT_DEBUG
      std::cout << "Warning: STEPCAFControl_Writer::WriteExternRefs StepRepr_PropertyDefinition is null for " << S.TShape()->DynamicType()->Name() << std::endl;
#endif
      continue;
    }
    StepRepr_CharacterizedDefinition CharDef = aPropDef->Definition();
    Handle(StepBasic_ProductDefinition) PD = CharDef.ProductDefinition();
    if (PD.IsNull()) {
#ifdef OCCT_DEBUG
      std::cout << "Warning: STEPCAFControl_Writer::WriteExternRefs StepBasic_ProductDefinition is null for " << S.TShape()->DynamicType()->Name() << std::endl;
#endif
      continue;
    }
    EFTool.AddExternRef ( EF->GetName()->ToCString(), PD, format );
  }
  EFTool.WriteExternRefs(schema);
  return Standard_True;
}


=======
    const char* aStepFormat = (aStepSchema == 3 ? "STEP AP203" : "STEP AP214");
    // try to get PD from SDR
    StepRepr_RepresentedDefinition aRD = aSDR->Definition();
    Handle(StepRepr_PropertyDefinition) aPropDef = aRD.PropertyDefinition();
    if (aPropDef.IsNull())
    {
      Message::SendTrace() << "Warning: STEPCAFControl_Writer::writeExternRefs StepRepr_PropertyDefinition is null for " << aShape.TShape()->DynamicType()->Name() << "\n";
      continue;
    }
    StepRepr_CharacterizedDefinition aCharDef = aPropDef->Definition();
    Handle(StepBasic_ProductDefinition) aPD = aCharDef.ProductDefinition();
    if (aPD.IsNull())
    {
      Message::SendTrace() << "Warning: STEPCAFControl_Writer::writeExternRefs StepBasic_ProductDefinition is null for " << aShape.TShape()->DynamicType()->Name() << "\n";
      continue;
    }
    anEFTool.AddExternRef(anExtFile->GetName()->ToCString(), aPD, aStepFormat);
  }
  anEFTool.WriteExternRefs(aStepSchema);
  return Standard_True;
}

>>>>>>> accb2f351 (u)
//=======================================================================
//function : FindEntities
//purpose  : auxiliary
//=======================================================================
<<<<<<< HEAD
static Standard_Integer FindEntities (const Handle(Transfer_FinderProcess) &FP,
				      const TopoDS_Shape &S,
				      TopLoc_Location &L,
				      TColStd_SequenceOfTransient &seqRI)
{
  Handle(StepRepr_RepresentationItem) item = STEPConstruct::FindEntity ( FP, S, L );

  if ( ! item.IsNull() ) {
    seqRI.Append ( item );
    return 1;
  }
      
  // may be S was splited during shape processing
  Handle(TransferBRep_ShapeMapper) mapper = TransferBRep::ShapeMapper ( FP, S );
  Handle(Transfer_Binder) bnd = FP->Find ( mapper );
  if ( bnd.IsNull() ) return 0;
  
  Handle(Transfer_TransientListBinder) TransientListBinder =
    //Handle(Transfer_TransientListBinder)::DownCast( bnd->Next(Standard_True) );
    Handle(Transfer_TransientListBinder)::DownCast( bnd );
  Standard_Integer nres=0;
  if ( TransientListBinder.IsNull() && S.ShapeType() == TopAbs_COMPOUND) 
  {
    for ( TopoDS_Iterator it(S); it.More(); it.Next() ) {
      Handle(StepRepr_RepresentationItem) aLocalItem = STEPConstruct::FindEntity ( FP, it.Value(), L );
      if (aLocalItem.IsNull() ) continue;
      nres++;
      seqRI.Append (aLocalItem);
    }
  }
  else if(!TransientListBinder.IsNull())
  {

    const Standard_Integer nb = TransientListBinder->NbTransients();
    for (Standard_Integer i=1; i<=nb; i++) {
      Handle(Standard_Transient) t = TransientListBinder->Transient(i);
      item = Handle(StepRepr_RepresentationItem)::DownCast(t);
      if ( item.IsNull() ) continue;
      nres++;
      seqRI.Append ( item );
    }
  }
/*  works but is obsolete: another approach
  if (i<=nb) {
    TopoDS_Shape comp = TransferBRep::ShapeResult(bnd);
    if ( ! comp.IsNull() && comp.ShapeType() < S.ShapeType() ) {
      for ( TopoDS_Iterator it(comp); it.More(); it.Next() ) {
        MakeSTEPStyles(Styles, it.Value(), settings, STEPstyle, 
		       Map, ( hasOwn ? &style : 0 ) );
      }
    }
  }
*/
  return nres;
}


=======
static Standard_Integer FindEntities(const Handle(Transfer_FinderProcess)& theFP,
                                     const TopoDS_Shape& theShape,
                                     TopLoc_Location& theLocation,
                                     TColStd_SequenceOfTransient& theSeqRI)
{
  Handle(StepRepr_RepresentationItem) anItem = STEPConstruct::FindEntity(theFP, theShape, theLocation);

  if (!anItem.IsNull())
  {
    theSeqRI.Append(anItem);
    return 1;
  }

  // may be S was splited during shape processing
  Handle(TransferBRep_ShapeMapper) aMapper = TransferBRep::ShapeMapper(theFP, theShape);
  Handle(Transfer_Binder) aBinder = theFP->Find(aMapper);
  if (aBinder.IsNull())
    return 0;

  Handle(Transfer_TransientListBinder) aTransientListBinder =
    //Handle(Transfer_TransientListBinder)::DownCast( bnd->Next(Standard_True) );
    Handle(Transfer_TransientListBinder)::DownCast(aBinder);
  Standard_Integer aResCount = 0;
  if (aTransientListBinder.IsNull() && theShape.ShapeType() == TopAbs_COMPOUND)
  {
    for (TopoDS_Iterator anIter(theShape); anIter.More(); anIter.Next())
    {
      Handle(StepRepr_RepresentationItem) aLocalItem =
        STEPConstruct::FindEntity(theFP, anIter.Value(), theLocation);
      if (aLocalItem.IsNull())
        continue;
      aResCount++;
      theSeqRI.Append(aLocalItem);
    }
  }
  else if (!aTransientListBinder.IsNull())
  {
    const Standard_Integer aNbTransient = aTransientListBinder->NbTransients();
    for (Standard_Integer anInd = 1; anInd <= aNbTransient; anInd++)
    {
      Handle(Standard_Transient) anEntity = aTransientListBinder->Transient(anInd);
      anItem = Handle(StepRepr_RepresentationItem)::DownCast(anEntity);
      if (anItem.IsNull())
        continue;
      aResCount++;
      theSeqRI.Append(anItem);
    }
  }
  return aResCount;
}

>>>>>>> accb2f351 (u)
//=======================================================================
//function : getStyledItem
//purpose  : auxiliary
//=======================================================================
<<<<<<< HEAD
static Standard_Boolean getStyledItem(const TopoDS_Shape& S,
                                      const Handle(XCAFDoc_ShapeTool)& STool,
                                      const STEPConstruct_Styles &Styles, 
                                      Handle(StepVisual_StyledItem) &resSelItem,
                                      const MoniTool_DataMapOfShapeTransient& myMapCompMDGPR)
{
  TDF_Label aTopShL = STool->FindShape(S, Standard_False);
  TopoDS_Shape aTopLevSh = STool->GetShape( aTopShL );
  Standard_Boolean found = Standard_False;
  if ( !aTopLevSh.IsNull() &&  myMapCompMDGPR.IsBound( aTopLevSh ) ) {
    Handle(StepVisual_PresentationRepresentation) aMDGPR = 
      Handle(StepVisual_PresentationRepresentation)::DownCast( myMapCompMDGPR.Find( aTopLevSh ) );
    Handle(StepRepr_HArray1OfRepresentationItem) anSelItmHArr = aMDGPR->Items();
    // search for PSA of Monifold solid
    if ( !anSelItmHArr.IsNull() )
    {
      TColStd_SequenceOfTransient aNewseqRI;
      Standard_Boolean isFilled = Standard_False;
      for (Standard_Integer si = 1; si <= anSelItmHArr->Length() && !found; si++) {
        Handle(StepVisual_StyledItem) aSelItm =
          Handle(StepVisual_StyledItem)::DownCast(anSelItmHArr->Value(si));

        if ( aSelItm.IsNull() ) 
          continue;

        // check that it is a stiled item for monifold solid brep
        if (!isFilled)
        {
          TopLoc_Location Loc;
          FindEntities(Styles.FinderProcess(), aTopLevSh, Loc, aNewseqRI);
          isFilled = Standard_True;
        }
        if ( aNewseqRI.Length() > 0 )
        {
          
          const Handle(StepRepr_RepresentationItem)& anItem = aSelItm->Item();
          Standard_Boolean isSameMonSolBR = Standard_False;
          for (Standard_Integer mi = 1; mi <= aNewseqRI.Length(); mi++) {
            if ( !anItem.IsNull() && anItem == aNewseqRI.Value( mi ) ) {
              isSameMonSolBR = Standard_True;
              break;
            }
          }
          if (!isSameMonSolBR)
            continue;
        }
        
        
        for (Standard_Integer jsi = 1; jsi <= aSelItm->NbStyles() && !found; jsi++) {
          const Handle(StepVisual_PresentationStyleAssignment)& aFatherPSA = aSelItm->StylesValue(jsi);
          // check for PSA for top-level (not Presentation style by context for NAUO)
          if (aFatherPSA.IsNull() || aFatherPSA->IsKind(STANDARD_TYPE(StepVisual_PresentationStyleByContext)))
            continue;
          resSelItem = aSelItm;
          found = Standard_True;
        }
      }
    }
  }
  return found;
}


=======
static Standard_Boolean getStyledItem(const TopoDS_Shape& theShape,
                                      const Handle(XCAFDoc_ShapeTool)& theShapeTool,
                                      const STEPConstruct_Styles& theStyles,
                                      Handle(StepVisual_StyledItem)& theResSelItem,
                                      const MoniTool_DataMapOfShapeTransient& theMapCompMDGPR)
{
  const TDF_Label aTopShL = theShapeTool->FindShape(theShape, Standard_False);
  TopoDS_Shape aTopLevSh = theShapeTool->GetShape(aTopShL);
  Standard_Boolean anIsFound = Standard_False;
  if (aTopLevSh.IsNull() || !theMapCompMDGPR.IsBound(aTopLevSh))
  {
    return Standard_False;
  }
  Handle(StepVisual_PresentationRepresentation) aMDGPR =
    Handle(StepVisual_PresentationRepresentation)::DownCast(theMapCompMDGPR.Find(aTopLevSh));
  Handle(StepRepr_HArray1OfRepresentationItem) anSelItmHArr = aMDGPR->Items();
  if (anSelItmHArr.IsNull())
  {
    return Standard_False;
  }
  // Search for PSA of Manifold solid
  TColStd_SequenceOfTransient aNewSeqRI;
  Standard_Boolean isFilled = Standard_False;
  for (StepRepr_HArray1OfRepresentationItem::Iterator anIter(anSelItmHArr->Array1());
       anIter.More() && !anIsFound; anIter.Next())
  {
    const Handle(StepVisual_StyledItem)& aSelItm =
      Handle(StepVisual_StyledItem)::DownCast(anIter.Value());

    if (aSelItm.IsNull())
    {
      continue;
    }
    // Check that it is a styled item for manifold solid brep
    if (!isFilled)
    {
      TopLoc_Location aLoc;
      FindEntities(theStyles.FinderProcess(), aTopLevSh, aLoc, aNewSeqRI);
      isFilled = Standard_True;
    }
    if (!aNewSeqRI.IsEmpty())
    {
      const Handle(StepRepr_RepresentationItem)& anItem = aSelItm->Item();
      Standard_Boolean isSameMonSolBR = Standard_False;
      for (TColStd_SequenceOfTransient::Iterator aIterRI(aNewSeqRI);
           aIterRI.More(); aIterRI.Next())
      {
        if (!anItem.IsNull() && anItem == aIterRI.Value())
        {
          isSameMonSolBR = Standard_True;
          break;
        }
      }
      if (!isSameMonSolBR)
        continue;
    }
    for (StepVisual_HArray1OfPresentationStyleAssignment::Iterator aStyleIter(aSelItm->Styles()->Array1());
         aStyleIter.More() && !anIsFound; aStyleIter.Next())
    {
      const Handle(StepVisual_PresentationStyleAssignment)& aFatherPSA = aStyleIter.Value();
      // check for PSA for top-level (not Presentation style by context for NAUO)
      if (aFatherPSA.IsNull() || aFatherPSA->IsKind(STANDARD_TYPE(StepVisual_PresentationStyleByContext)))
        continue;
      theResSelItem = aSelItm;
      anIsFound = Standard_True;
    }
  }
  return anIsFound;
}

>>>>>>> accb2f351 (u)
//=======================================================================
//function : setDefaultInstanceColor
//purpose  : auxiliary
//=======================================================================
<<<<<<< HEAD
static Standard_Boolean setDefaultInstanceColor (const Handle(StepVisual_StyledItem) &aSelItm,
                                                 Handle(StepVisual_PresentationStyleAssignment)& PSA)
{
   Standard_Boolean found = Standard_False;
  for (Standard_Integer jsi = 1; jsi <= aSelItm->NbStyles() && !found; jsi++) {
    Handle(StepVisual_PresentationStyleAssignment) aFatherPSA = aSelItm->StylesValue(jsi);
  // check for PSA for top-level (not Presentation style by context for NAUO)
  if (aFatherPSA.IsNull() || aFatherPSA->IsKind(STANDARD_TYPE(StepVisual_PresentationStyleByContext))) 
    return Standard_False;
          
  // get style select from father PSA
  if (aFatherPSA->NbStyles() > 0) {
    Handle(StepVisual_HArray1OfPresentationStyleSelect) aFatherStyles =
      new StepVisual_HArray1OfPresentationStyleSelect(1, aFatherPSA->NbStyles());
    for (Standard_Integer k = 1; k <= aFatherPSA->NbStyles(); k++) {
      StepVisual_PresentationStyleSelect PSS;
      StepVisual_PresentationStyleSelect olDPSS = aFatherPSA->StylesValue(k);
      if (!olDPSS.PointStyle().IsNull())
        PSS.SetValue (olDPSS.PointStyle());
      else if (!olDPSS.CurveStyle().IsNull())
        PSS.SetValue (olDPSS.CurveStyle());
      else if (!olDPSS.SurfaceStyleUsage().IsNull())
        PSS.SetValue (olDPSS.SurfaceStyleUsage());
      else {
        found = Standard_False;
        break;
      }
      //aFatherStyles->SetValue( k, PSS );
      aFatherStyles->SetValue( k, olDPSS );
      found = Standard_True;
    }
            // init PSA of NAUO
    if (found) {
      PSA->Init( aFatherStyles );
    }
  }
    
  }
  return found;
}

=======
static Standard_Boolean setDefaultInstanceColor(const Handle(StepVisual_StyledItem)& theStyleItem,
                                                Handle(StepVisual_PresentationStyleAssignment)& thePSA)
{
  Standard_Boolean anIsFound = Standard_False;
  for (StepVisual_HArray1OfPresentationStyleAssignment::Iterator aStyleIter(theStyleItem->Styles()->Array1());
       aStyleIter.More() && !anIsFound; aStyleIter.Next())
  {
    const Handle(StepVisual_PresentationStyleAssignment)& aFatherPSA = aStyleIter.Value();
    // check for PSA for top-level (not Presentation style by context for NAUO)
    if (aFatherPSA.IsNull() || aFatherPSA->IsKind(STANDARD_TYPE(StepVisual_PresentationStyleByContext)))
      return Standard_False;

    // get style select from father PSA
    if (aFatherPSA->NbStyles() > 0)
    {
      Handle(StepVisual_HArray1OfPresentationStyleSelect) aFatherStyles =
        new StepVisual_HArray1OfPresentationStyleSelect(1, aFatherPSA->NbStyles());
      Standard_Integer aSettingInd = 1;
      for (StepVisual_HArray1OfPresentationStyleSelect::Iterator aFatherStyleIter(aFatherPSA->Styles()->Array1());
           aFatherStyleIter.More(); aFatherStyleIter.Next())
      {
        StepVisual_PresentationStyleSelect aPSS;
        const StepVisual_PresentationStyleSelect& anOlDPSS = aFatherStyleIter.Value();
        if (!anOlDPSS.PointStyle().IsNull())
          aPSS.SetValue(anOlDPSS.PointStyle());
        else if (!anOlDPSS.CurveStyle().IsNull())
          aPSS.SetValue(anOlDPSS.CurveStyle());
        else if (!anOlDPSS.SurfaceStyleUsage().IsNull())
          aPSS.SetValue(anOlDPSS.SurfaceStyleUsage());
        else
        {
          anIsFound = Standard_False;
          break;
        }
        aFatherStyles->SetValue(aSettingInd++, anOlDPSS);
        anIsFound = Standard_True;
      }
      // init PSA of NAUO
      if (anIsFound)
      {
        thePSA->Init(aFatherStyles);
      }
    }
  }
  return anIsFound;
}
>>>>>>> accb2f351 (u)

//=======================================================================
//function : MakeSTEPStyles
//purpose  : auxiliary
//=======================================================================
<<<<<<< HEAD
static void MakeSTEPStyles (STEPConstruct_Styles &Styles,
			    const TopoDS_Shape &S,
			    const XCAFPrs_IndexedDataMapOfShapeStyle &settings,
			    Handle(StepVisual_StyledItem) &override,
			    TopTools_MapOfShape &Map,
                            const MoniTool_DataMapOfShapeTransient& myMapCompMDGPR,
                            STEPConstruct_DataMapOfAsciiStringTransient &DPDCs,
                            STEPConstruct_DataMapOfPointTransient &ColRGBs,
                            const Handle(XCAFDoc_ColorTool)& CTool,
			    const XCAFPrs_Style *inherit = 0,
                            const Standard_Boolean isComponent = Standard_False)
{
  // skip already processed shapes
  if ( ! Map.Add ( S ) ) return;

  // check if shape has its own style (r inherits from ancestor)
  XCAFPrs_Style style;
  if ( inherit ) style = *inherit;
  if ( settings.Contains(S) ) {
    XCAFPrs_Style own = settings.FindFromKey(S);
    if ( !own.IsVisible() ) style.SetVisibility ( Standard_False );
    if ( own.IsSetColorCurv() ) style.SetColorCurv ( own.GetColorCurv() );
    if ( own.IsSetColorSurf() ) style.SetColorSurf ( own.GetColorSurfRGBA() );
  }

  // translate colors to STEP
  Handle(StepVisual_Colour) surfColor, curvColor;
  Standard_Real RenderTransp = 0.0;
  if ( style.IsSetColorSurf() ) {
    Quantity_ColorRGBA sCol = style.GetColorSurfRGBA();
    RenderTransp = 1.0 - sCol.Alpha();
    surfColor = Styles.EncodeColor(sCol.GetRGB(),DPDCs,ColRGBs);
  }
  if ( style.IsSetColorCurv() )
    curvColor = Styles.EncodeColor(style.GetColorCurv(),DPDCs,ColRGBs);
  
  Standard_Boolean hasOwn = ( ! surfColor.IsNull() || 
                              ! curvColor.IsNull() ||
                              ! style.IsVisible() );

  // find target item and assign style to it
  Handle(StepVisual_StyledItem) STEPstyle = override;
  if ( hasOwn ) {
    if ( S.ShapeType() != TopAbs_COMPOUND || isComponent ) { // skip compounds, let subshapes inherit its colors
      TopLoc_Location L;
      TColStd_SequenceOfTransient seqRI;
      Standard_Integer nb = FindEntities ( Styles.FinderProcess(), S, L, seqRI );
#ifdef OCCT_DEBUG
      if ( nb <=0 ) std::cout << "Warning: Cannot find RI for " << S.TShape()->DynamicType()->Name() << std::endl;
#endif
      //Get overridden style gka 10.06.03
      if ( isComponent && nb) 
        getStyledItem(S, CTool->ShapeTool(), Styles, override,myMapCompMDGPR);
       
           
      for ( Standard_Integer i=1; i <= nb; i++ ) {
        Handle(StepRepr_RepresentationItem) item = 
          Handle(StepRepr_RepresentationItem)::DownCast(seqRI(i));
        Handle(StepVisual_PresentationStyleAssignment) PSA;
        if ( style.IsVisible() || !surfColor.IsNull() || !curvColor.IsNull() ) {
          PSA = Styles.MakeColorPSA ( item, surfColor, curvColor, surfColor, RenderTransp, isComponent );
        }
        else {
          // default white color
          surfColor = Styles.EncodeColor(Quantity_Color(Quantity_NOC_WHITE),DPDCs,ColRGBs);
          PSA = Styles.MakeColorPSA ( item, surfColor, curvColor, surfColor, 0.0, isComponent );
          if ( isComponent ) 
            setDefaultInstanceColor( override, PSA);
          
        } // end of component case
        
        STEPstyle = Styles.AddStyle ( item, PSA, override );
        hasOwn = Standard_False;
=======
static void MakeSTEPStyles(STEPConstruct_Styles& theStyles,
                           const TopoDS_Shape& theShape,
                           const XCAFPrs_IndexedDataMapOfShapeStyle& theSettings,
                           Handle(StepVisual_StyledItem)& theOverride,
                           TopTools_MapOfShape& theMap,
                           const MoniTool_DataMapOfShapeTransient& theMapCompMDGPR,
                           STEPConstruct_DataMapOfAsciiStringTransient& theDPDCs,
                           STEPConstruct_DataMapOfPointTransient& theColRGBs,
                           const Handle(XCAFDoc_ShapeTool)& theShTool,
                           const XCAFPrs_Style* theInherit = 0,
                           const Standard_Boolean theIsComponent = Standard_False)
{
  // skip already processed shapes
  if (!theMap.Add(theShape))
    return;

  // check if shape has its own style (r inherits from ancestor)
  XCAFPrs_Style aStyle;
  if (theInherit) aStyle = *theInherit;
  if (theSettings.Contains(theShape))
  {
    const XCAFPrs_Style& anOwnStyle = theSettings.FindFromKey(theShape);
    if (!anOwnStyle.IsVisible())
      aStyle.SetVisibility(Standard_False);
    if (anOwnStyle.IsSetColorCurv())
      aStyle.SetColorCurv(anOwnStyle.GetColorCurv());
    if (anOwnStyle.IsSetColorSurf())
      aStyle.SetColorSurf(anOwnStyle.GetColorSurfRGBA());
  }

  // translate colors to STEP
  Handle(StepVisual_Colour) aSurfColor, aCurvColor;
  Standard_Real aRenderTransp = 0.0;
  if (aStyle.IsSetColorSurf())
  {
    Quantity_ColorRGBA aSurfCol = aStyle.GetColorSurfRGBA();
    aRenderTransp = 1.0 - aSurfCol.Alpha();
    aSurfColor = theStyles.EncodeColor(aSurfCol.GetRGB(), theDPDCs, theColRGBs);
  }
  if (aStyle.IsSetColorCurv())
    aCurvColor = theStyles.EncodeColor(aStyle.GetColorCurv(), theDPDCs, theColRGBs);

  Standard_Boolean aHasOwn = (!aSurfColor.IsNull() ||
                              !aCurvColor.IsNull() ||
                              !aStyle.IsVisible());

  // find target item and assign style to it
  Handle(StepVisual_StyledItem) aSTEPstyle = theOverride;
  if (aHasOwn)
  {
    if (theShape.ShapeType() != TopAbs_COMPOUND || theIsComponent)
    { // skip compounds, let subshapes inherit its colors
      TopLoc_Location aLocation;
      TColStd_SequenceOfTransient aSeqRI;
      Standard_Integer aNbEntities = FindEntities(theStyles.FinderProcess(), theShape, aLocation, aSeqRI);
      if (aNbEntities <= 0)
        Message::SendTrace() << "Warning: Cannot find RI for " << theShape.TShape()->DynamicType()->Name() << "\n";
      //Get overridden style gka 10.06.03
      if (theIsComponent && aNbEntities > 0)
        getStyledItem(theShape, theShTool, theStyles, theOverride, theMapCompMDGPR);

      for (TColStd_SequenceOfTransient::Iterator anEntIter(aSeqRI);
           anEntIter.More(); anEntIter.Next())
      {
        const Handle(StepRepr_RepresentationItem)& anItem =
          Handle(StepRepr_RepresentationItem)::DownCast(anEntIter.Value());
        Handle(StepVisual_PresentationStyleAssignment) aPSA;
        if (aStyle.IsVisible() || !aSurfColor.IsNull() || !aCurvColor.IsNull())
        {
          aPSA = theStyles.MakeColorPSA(anItem, aSurfColor, aCurvColor, aSurfColor, aRenderTransp, theIsComponent);
        }
        else
        {
          // default white color
          aSurfColor = theStyles.EncodeColor(Quantity_Color(Quantity_NOC_WHITE), theDPDCs, theColRGBs);
          aPSA = theStyles.MakeColorPSA(anItem, aSurfColor, aCurvColor, aSurfColor, 0.0, theIsComponent);
          if (theIsComponent)
            setDefaultInstanceColor(theOverride, aPSA);

        } // end of component case

        aSTEPstyle = theStyles.AddStyle(anItem, aPSA, theOverride);
        aHasOwn = Standard_False;
>>>>>>> accb2f351 (u)
      }
    }
  }

  // iterate on subshapes (except vertices :)
<<<<<<< HEAD
  if ( S.ShapeType() == TopAbs_EDGE ) return;
  if ( !isComponent ) // PTV 10.02.2003
    for ( TopoDS_Iterator it(S); it.More(); it.Next() ) {
      MakeSTEPStyles ( Styles, it.Value(), settings, STEPstyle,
                      Map, myMapCompMDGPR, DPDCs, ColRGBs, CTool,
                      ( hasOwn ? &style : 0 ) );
    }
}

/*
static Standard_Boolean getFatherColor (const TDF_Label& L,
                                        const Handle(XCAFDoc_ColorTool)& CTool,
                                        XCAFPrs_Style& style)
{
  Standard_Boolean done = Standard_False;
  TopoDS_Shape aSh = CTool->ShapeTool()->GetShape( L );
  TDF_Label aFL = CTool->ShapeTool()->FindShape( aSh );
  if (aFL.IsNull() || aFL == L)
    return done;
  Quantity_Color C;
  if ( CTool->GetColor ( aFL, XCAFDoc_ColorGen, C ) ) {
    style.SetColorCurv ( C );
    style.SetColorSurf ( C );
    done = Standard_True;
  }
  if ( CTool->GetColor ( aFL, XCAFDoc_ColorSurf, C ) ) {
    style.SetColorSurf ( C );
    done = Standard_True;
  }
  if ( CTool->GetColor ( aFL, XCAFDoc_ColorCurv, C ) ) {
    style.SetColorCurv ( C );
    done = Standard_True;
  }
  
  return done;
}
*/


//=======================================================================
//function : WriteColors
//purpose  : 
//=======================================================================

Standard_Boolean STEPCAFControl_Writer::WriteColors (const Handle(XSControl_WorkSession) &WS,
						     const TDF_LabelSequence &labels)
{
  if ( labels.Length() <=0 ) return Standard_False;

  // Iterate on shapes in the document
  Handle(XCAFDoc_ColorTool) CTool = XCAFDoc_DocumentTool::ColorTool( labels(1) );
  Handle(XCAFDoc_VisMaterialTool) aMatTool = XCAFDoc_DocumentTool::VisMaterialTool( labels(1) );
  if ( CTool.IsNull() ) return Standard_False;

  STEPConstruct_Styles Styles ( WS );
  STEPConstruct_DataMapOfAsciiStringTransient DPDCs;
  STEPConstruct_DataMapOfPointTransient ColRGBs;
  for ( Standard_Integer i=1; i <= labels.Length(); i++ ) {
    TDF_Label L = labels.Value(i);

    Handle(XCAFDoc_ShapeTool) aSTool = XCAFDoc_DocumentTool::ShapeTool( labels(1) );
    // Skip assemblies: colors assigned to assemblies and their instances
    // are not supported (it is not clear how to encode that in STEP)
    if ( XCAFDoc_ShapeTool::IsAssembly ( L ) ) {
#ifdef OCCT_DEBUG
      std::cout << "Warning: Cannot write color  for Assembly" << std::endl;
      std::cout << "Info: Check for colors assigned to components in assembly" << std::endl;
#endif
      // PTV 22.01.2003 Write color for instances.
      TDF_LabelSequence compLabels;
      if ( aSTool.IsNull() )
        continue;
      if (!aSTool->GetComponents(L, compLabels))
        continue;
      WriteColors(WS, compLabels);
=======
  if (theShape.ShapeType() == TopAbs_EDGE)
    return;
  if (theIsComponent)
  {
    return;
  }
  for (TopoDS_Iterator anIter(theShape); anIter.More(); anIter.Next())
  {
    MakeSTEPStyles(theStyles, anIter.Value(), theSettings, aSTEPstyle,
                   theMap, theMapCompMDGPR, theDPDCs, theColRGBs, theShTool,
                   (aHasOwn ? &aStyle : 0));
  }
}

//=======================================================================
//function : writeColors
//purpose  :
//=======================================================================
Standard_Boolean STEPCAFControl_Writer::writeColors(const Handle(XSControl_WorkSession)& theWS,
                                                    const TDF_LabelSequence& theLabels)
{
  if (theLabels.IsEmpty())
    return Standard_False;

  STEPConstruct_Styles Styles(theWS);
  STEPConstruct_DataMapOfAsciiStringTransient DPDCs;
  STEPConstruct_DataMapOfPointTransient ColRGBs;
  // Iterate on requested shapes
  for (TDF_LabelSequence::Iterator aLabelIter(theLabels);
       aLabelIter.More(); aLabelIter.Next())
  {
    const TDF_Label aLabel = aLabelIter.Value();
    // Iterate on shapes in the document
    Handle(XCAFDoc_ShapeTool) aSTool = XCAFDoc_DocumentTool::ShapeTool(aLabel);
    // Skip assemblies: colors assigned to assemblies and their instances
    // are not supported (it is not clear how to encode that in STEP)
    if (XCAFDoc_ShapeTool::IsAssembly(aLabel))
    {
      Message::SendTrace() << "Warning: Cannot write color  for Assembly" << "\n";
      Message::SendTrace() << "Info: Check for colors assigned to components in assembly" << "\n";
      // PTV 22.01.2003 Write color for instances.
      TDF_LabelSequence compLabels;
      if (!aSTool->GetComponents(aLabel, compLabels))
        continue;
      writeColors(theWS, compLabels);
>>>>>>> accb2f351 (u)
      continue;
    }
    Styles.ClearStyles();

    // get a target shape and try to find corresponding context
    // (all the colors set under that label will be put into that context)
<<<<<<< HEAD
    TopoDS_Shape S;
    if ( ! XCAFDoc_ShapeTool::GetShape ( L, S ) ) continue;
    Standard_Boolean isComponent = aSTool->IsComponent( L );
    TopoDS_Shape aTopSh = S;
    Handle(StepRepr_RepresentationContext) Context = Styles.FindContext ( S );
    if ( isComponent ) {
      TDF_Label aTopShL = aSTool->FindShape(S, Standard_False);
      if (aTopShL.IsNull())
        continue;
      aTopSh = aSTool->GetShape( aTopShL );
      Context = Styles.FindContext ( aTopSh );
    }
    if ( Context.IsNull() )
        continue;
    
    // collect settings set on that label
    XCAFPrs_IndexedDataMapOfShapeStyle settings;
    TDF_LabelSequence seq;
    seq.Append ( L );
    XCAFDoc_ShapeTool::GetSubShapes ( L, seq );
    Standard_Boolean isVisible = Standard_True;
    for ( Standard_Integer j = 1; j <= seq.Length(); j++ ) {
      TDF_Label lab = seq.Value(j);
      XCAFPrs_Style style;
      Quantity_ColorRGBA C;
      if ( lab == L ) {
        // check for invisible status of object on label
        if ( !CTool->IsVisible( lab ) ) {
          isVisible = Standard_False;
          style.SetVisibility( Standard_False );
        }
      }
      if ( CTool->GetColor ( lab, XCAFDoc_ColorGen, C ) ) {
        style.SetColorCurv ( C.GetRGB() );
        style.SetColorSurf ( C );
      }
      if ( CTool->GetColor ( lab, XCAFDoc_ColorSurf, C ) )
        style.SetColorSurf ( C );
      if ( CTool->GetColor ( lab, XCAFDoc_ColorCurv, C ) )
        style.SetColorCurv ( C.GetRGB() );
      if (!style.IsSetColorSurf())
      {
        Handle(XCAFDoc_VisMaterial) aVisMat = aMatTool->GetShapeMaterial (lab);
        if (!aVisMat.IsNull()
         && !aVisMat->IsEmpty())
        {
          // only color can be stored in STEP
          style.SetColorSurf (aVisMat->BaseColor());
        }
      }
      
      // commented, cause we are need to take reference from 
//       if ( isComponent && lab == L && !isVisible)
//         if ( !style.IsSetColorSurf() && !style.IsSetColorCurv() ) {
//           getFatherColor ( L, CTool, style);
//         }
      if ( ! style.IsSetColorCurv() && ! style.IsSetColorSurf() && isVisible ) continue;

      TopoDS_Shape sub = XCAFDoc_ShapeTool::GetShape ( lab );
      XCAFPrs_Style* aMapStyle = settings.ChangeSeek (sub);
      if (aMapStyle == NULL)
        settings.Add ( sub, style );
      else
        *aMapStyle = style;
    }
    
    if ( settings.Extent() <=0 ) continue;

    // iterate on subshapes and create STEP styles
    Handle(StepVisual_StyledItem) override;
    TopTools_MapOfShape Map;
    
    MakeSTEPStyles(Styles,S,settings,override,Map,myMapCompMDGPR,DPDCs,ColRGBs,CTool,0,isComponent);
    
    // create MDGPR and record it in model
    Handle(StepVisual_MechanicalDesignGeometricPresentationRepresentation) aMDGPR;

    if (!isComponent) {
      if ( myMapCompMDGPR.IsBound( aTopSh )) {
#ifdef OCCT_DEBUG
        std::cerr << "Error: Current Top-Level shape have MDGPR already " << std::endl;
#endif
      }
      Styles.CreateMDGPR ( Context, aMDGPR );
      if (!aMDGPR.IsNull())
        myMapCompMDGPR.Bind( aTopSh, aMDGPR );
    }
    else {
      // create SDR and add to model.
      const Handle(XSControl_TransferWriter) &TW = WS->TransferWriter();
      const Handle(Transfer_FinderProcess) &FP = TW->FinderProcess();
      Handle(TransferBRep_ShapeMapper) mapper = TransferBRep::ShapeMapper ( FP, S );
      Handle(StepShape_ContextDependentShapeRepresentation) CDSR;
      if ( FP->FindTypedTransient(mapper, 
                                  STANDARD_TYPE(StepShape_ContextDependentShapeRepresentation),
                                  CDSR) ) {
        // create SDR for NAUO
        Handle(StepRepr_ProductDefinitionShape) nullPDS; // important to be NULL
        Styles.CreateNAUOSRD( Context, CDSR, nullPDS );
        
        // search for MDGPR of the component top-level shape
        if ( myMapCompMDGPR.IsBound( aTopSh )) {
          aMDGPR = Handle(StepVisual_MechanicalDesignGeometricPresentationRepresentation)::DownCast( myMapCompMDGPR.Find( aTopSh ) );
        } else {
          aMDGPR = new StepVisual_MechanicalDesignGeometricPresentationRepresentation;
          Handle(TCollection_HAsciiString) ReprName = new TCollection_HAsciiString ( "" );
          aMDGPR->SetName( ReprName );
          aMDGPR->SetContextOfItems( Context );
          myMapCompMDGPR.Bind ( aTopSh, aMDGPR );
        }
        Handle(StepRepr_HArray1OfRepresentationItem) oldItems = aMDGPR->Items();
        Standard_Integer oldLengthlen = 0;
        if (!oldItems.IsNull())
          oldLengthlen = oldItems->Length();
        const Standard_Integer nbIt = oldLengthlen + Styles.NbStyles();
        if(!nbIt)
          continue;
        Handle(StepRepr_HArray1OfRepresentationItem) newItems =
          new StepRepr_HArray1OfRepresentationItem(1, nbIt);
        Standard_Integer si;
        Standard_Integer el = 1;
        for ( si=1; si <= oldLengthlen; si++ )
          newItems->SetValue( el++, oldItems->Value( si ) );
        for ( si=1; si <= Styles.NbStyles(); si++ ) {
          newItems->SetValue( el++, Styles.Style(si));
        }
       
        if (newItems->Length() > 0)
          aMDGPR->SetItems( newItems );
      } //end of work with CDSR
    }
    if ( !isVisible ) {
    // create invisibility item and refer for styledItem
      Handle(StepVisual_Invisibility) Invsblt = new StepVisual_Invisibility();
      Handle(StepVisual_HArray1OfInvisibleItem) HInvsblItm = 
        new StepVisual_HArray1OfInvisibleItem (1,Styles.NbStyles());
      // put all style item into the harray
      for ( Standard_Integer si=1; si <= Styles.NbStyles(); si++ ) {
        Handle(StepRepr_RepresentationItem) styledItm = Styles.Style(si);
        StepVisual_InvisibleItem anInvItem;
        anInvItem.SetValue( styledItm );
        HInvsblItm->SetValue( si, anInvItem );
      }
      // set the invisibility of items
      Invsblt->Init( HInvsblItm );
      WS->Model()->AddWithRefs( Invsblt );
    }
  }

  return Standard_True;
}


//=======================================================================
//function : WriteNames
//purpose  :
//=======================================================================

Standard_Boolean STEPCAFControl_Writer::WriteNames (const Handle(XSControl_WorkSession) &WS,
						    const TDF_LabelSequence &labels) const
{
  if ( labels.Length() <=0 ) return Standard_False;

  // get working data
  const Handle(XSControl_TransferWriter) &TW = WS->TransferWriter();
  const Handle(Transfer_FinderProcess) &FP = TW->FinderProcess();

  // Iterate on requested shapes
  for ( Standard_Integer i=1; i <= labels.Length(); i++ ) {
    TDF_Label L = labels.Value(i);

    // get name
    Handle(TCollection_HAsciiString) hName = new TCollection_HAsciiString;
    if (GetLabelName (L, hName))
    {
      // find target STEP entity for the current shape
      if ( ! myLabels.IsBound ( L ) ) continue; // not recorded as translated, skip
      TopoDS_Shape S = myLabels.Find ( L );

      Handle(StepShape_ShapeDefinitionRepresentation) SDR;
      Handle(TransferBRep_ShapeMapper) mapper = TransferBRep::ShapeMapper ( FP, S );
      if ( ! FP->FindTypedTransient ( mapper, STANDARD_TYPE(StepShape_ShapeDefinitionRepresentation), SDR ) ) {
#ifdef OCCT_DEBUG
        std::cout << "Warning: Cannot find SDR for " << S.TShape()->DynamicType()->Name() << std::endl;
#endif
        continue;
      }

      // set the name to the PRODUCT
      Handle(StepRepr_PropertyDefinition) PropD = SDR->Definition().PropertyDefinition();
      if ( PropD.IsNull() ) continue;
      Handle(StepBasic_ProductDefinition) PD = PropD->Definition().ProductDefinition();
      if ( PD.IsNull() ) continue;
      Handle(StepBasic_Product) Prod = PD->Formation()->OfProduct();

      Prod->SetId ( hName );
      Prod->SetName ( hName );
    }

    // write names for components of assemblies
    if ( XCAFDoc_ShapeTool::IsAssembly ( L ) ) {
      TDF_LabelSequence seq;
      XCAFDoc_ShapeTool::GetComponents ( L, seq );
      for (Standard_Integer k=1; k <= seq.Length(); k++) {
	TDF_Label lab = seq(k);

	// get shape with correct location
	TDF_Label Lref;
	if ( ! XCAFDoc_ShapeTool::GetReferredShape ( lab, Lref ) || 
	     ! myLabels.IsBound ( Lref ) ) continue;
        TopoDS_Shape S = myLabels.Find ( Lref );
	S.Move ( XCAFDoc_ShapeTool::GetLocation ( lab ) );
	
	hName = new TCollection_HAsciiString;
	if ( ! GetLabelName (lab, hName) ) continue;
	
	// find the target CDSR corresponding to a shape
        Handle(TransferBRep_ShapeMapper) mapper = TransferBRep::ShapeMapper ( FP, S );
	Handle(Transfer_Binder) binder = FP->Find ( mapper );
	Handle(StepShape_ContextDependentShapeRepresentation) CDSR;
	if ( ! FP->FindTypedTransient (mapper,STANDARD_TYPE(StepShape_ContextDependentShapeRepresentation), CDSR) ) 
	  continue;
	Handle(StepRepr_ProductDefinitionShape) PDS = CDSR->RepresentedProductRelation();
	Handle(StepBasic_ProductDefinitionRelationship) NAUO = PDS->Definition().ProductDefinitionRelationship();
	if ( ! NAUO.IsNull() ) NAUO->SetName ( hName );
      }
    }
  }

  return Standard_True;
}


=======
    TopoDS_Shape aShape;
    if (!XCAFDoc_ShapeTool::GetShape(aLabel, aShape))
      continue;
    Standard_Boolean anIsComponent = aSTool->IsComponent(aLabel) || myPureRefLabels.IsBound(aLabel);
    TopoDS_Shape aTopSh = aShape;
    Handle(StepRepr_RepresentationContext) aContext = Styles.FindContext(aShape);
    if (anIsComponent)
    {
      TDF_Label aTopShL = aSTool->FindShape(aShape, Standard_False);
      if (aTopShL.IsNull())
        continue;
      aTopSh = aSTool->GetShape(aTopShL);
      aContext = Styles.FindContext(aTopSh);
    }
    if (aContext.IsNull())
      continue;

    // collect settings set on that label
    XCAFPrs_IndexedDataMapOfShapeStyle aSettings;
    TDF_LabelSequence aSeq;
    aSeq.Append(aLabel);
    XCAFDoc_ShapeTool::GetSubShapes(aLabel, aSeq);
    Standard_Boolean anIsVisible = Standard_True;
    for (TDF_LabelSequence::Iterator aSeqIter(aSeq);
         aSeqIter.More(); aSeqIter.Next())
    {
      const TDF_Label& aSeqValue = aSeqIter.Value();
      XCAFPrs_Style aStyle;
      Quantity_ColorRGBA aColor;
      if (aSeqValue == aLabel)
      {
        // check for invisible status of object on label
        if (!XCAFDoc_ColorTool::IsVisible(aSeqValue))
        {
          anIsVisible = Standard_False;
          aStyle.SetVisibility(Standard_False);
        }
      }
      if (XCAFDoc_ColorTool::GetColor(aSeqValue, XCAFDoc_ColorGen, aColor))
      {
        aStyle.SetColorCurv(aColor.GetRGB());
        aStyle.SetColorSurf(aColor);
      }
      if (XCAFDoc_ColorTool::GetColor(aSeqValue, XCAFDoc_ColorSurf, aColor))
        aStyle.SetColorSurf(aColor);
      if (XCAFDoc_ColorTool::GetColor(aSeqValue, XCAFDoc_ColorCurv, aColor))
        aStyle.SetColorCurv(aColor.GetRGB());
      if (!aStyle.IsSetColorSurf())
      {
        Handle(XCAFDoc_VisMaterial) aVisMat = XCAFDoc_VisMaterialTool::GetShapeMaterial(aSeqValue);
        if (!aVisMat.IsNull() && !aVisMat->IsEmpty())
        {
          // only color can be stored in STEP
          aStyle.SetColorSurf(aVisMat->BaseColor());
        }
      }
      if (!aStyle.IsSetColorCurv() && !aStyle.IsSetColorSurf() && anIsVisible) continue;

      TopoDS_Shape aSub = XCAFDoc_ShapeTool::GetShape(aSeqValue);
      XCAFPrs_Style* aMapStyle = aSettings.ChangeSeek(aSub);
      if (aMapStyle == NULL)
        aSettings.Add(aSub, aStyle);
      else
        *aMapStyle = aStyle;
    }

    if (aSettings.Extent() <= 0)
      continue;

    // iterate on subshapes and create STEP styles
    Handle(StepVisual_StyledItem) anOverride;
    TopTools_MapOfShape aMap;

    MakeSTEPStyles(Styles, aShape, aSettings, anOverride,
                   aMap, myMapCompMDGPR, DPDCs, ColRGBs, aSTool, 0, anIsComponent);

    // create MDGPR and record it in model
    Handle(StepVisual_MechanicalDesignGeometricPresentationRepresentation) aMDGPR;

    if (!anIsComponent)
    {
      if (myMapCompMDGPR.IsBound(aTopSh))
      {
        Message::SendTrace() << "Error: Current Top-Level shape have MDGPR already " << "\n";
      }
      Styles.CreateMDGPR(aContext, aMDGPR);
      if (!aMDGPR.IsNull())
        myMapCompMDGPR.Bind(aTopSh, aMDGPR);
    }
    else
    {
      // create SDR and add to model.
      const Handle(XSControl_TransferWriter)& aTW = theWS->TransferWriter();
      const Handle(Transfer_FinderProcess)& aFP = aTW->FinderProcess();
      Handle(TransferBRep_ShapeMapper) aMapper = TransferBRep::ShapeMapper(aFP, aShape);
      Handle(StepShape_ContextDependentShapeRepresentation) aCDSR;
      if (aFP->FindTypedTransient(aMapper,
          STANDARD_TYPE(StepShape_ContextDependentShapeRepresentation),
          aCDSR))
      {
        // create SDR for NAUO
        Handle(StepRepr_ProductDefinitionShape) aNullPDS; // important to be NULL
        Styles.CreateNAUOSRD(aContext, aCDSR, aNullPDS);

        // search for MDGPR of the component top-level shape
        if (myMapCompMDGPR.IsBound(aTopSh))
        {
          aMDGPR = Handle(StepVisual_MechanicalDesignGeometricPresentationRepresentation)::DownCast(myMapCompMDGPR.Find(aTopSh));
        }
        else
        {
          aMDGPR = new StepVisual_MechanicalDesignGeometricPresentationRepresentation;
          Handle(TCollection_HAsciiString) aReprName = new TCollection_HAsciiString("");
          aMDGPR->SetName(aReprName);
          aMDGPR->SetContextOfItems(aContext);
          myMapCompMDGPR.Bind(aTopSh, aMDGPR);
        }
        Handle(StepRepr_HArray1OfRepresentationItem) anOldItems = aMDGPR->Items();
        Standard_Integer oldLengthlen = 0;
        if (!anOldItems.IsNull())
          oldLengthlen = anOldItems->Length();
        const Standard_Integer aNbIt = oldLengthlen + Styles.NbStyles();
        if (!aNbIt)
          continue;
        Handle(StepRepr_HArray1OfRepresentationItem) aNewItems =
          new StepRepr_HArray1OfRepresentationItem(1, aNbIt);
        Standard_Integer anElemInd = 1;
        for (Standard_Integer aStyleInd = 1; aStyleInd <= oldLengthlen; aStyleInd++)
        {
          aNewItems->SetValue(anElemInd++, anOldItems->Value(aStyleInd));
        }
        for (Standard_Integer aStyleInd = 1; aStyleInd <= Styles.NbStyles(); aStyleInd++)
        {
          aNewItems->SetValue(anElemInd++, Styles.Style(aStyleInd));
        }

        if (aNewItems->Length() > 0)
          aMDGPR->SetItems(aNewItems);
      } //end of work with CDSR
    }
    if (!anIsVisible)
    {
      // create invisibility item and refer for styledItem
      Handle(StepVisual_Invisibility) anInvisibility = new StepVisual_Invisibility();
      Handle(StepVisual_HArray1OfInvisibleItem) anInvisibilitySeq =
        new StepVisual_HArray1OfInvisibleItem(1, Styles.NbStyles());
      // put all style item into the harray
      for (Standard_Integer aStyleInd = 1; aStyleInd <= Styles.NbStyles(); aStyleInd++)
      {
        Handle(StepRepr_RepresentationItem) aStyledItm = Styles.Style(aStyleInd);
        StepVisual_InvisibleItem anInvItem;
        anInvItem.SetValue(aStyledItm);
        anInvisibilitySeq->SetValue(aStyleInd, anInvItem);
      }
      // set the invisibility of items
      anInvisibility->Init(anInvisibilitySeq);
      theWS->Model()->AddWithRefs(anInvisibility);
    }
  }
  return Standard_True;
}

//=======================================================================
//function : writeNames
//purpose  :
//=======================================================================
Standard_Boolean STEPCAFControl_Writer::writeNames(const Handle(XSControl_WorkSession)& theWS,
                                                   const TDF_LabelSequence& theLabels) const
{
  if (theLabels.IsEmpty())
    return Standard_False;

  // get working data
  const Handle(XSControl_TransferWriter)& aTW = theWS->TransferWriter();
  const Handle(Transfer_FinderProcess)& aFP = aTW->FinderProcess();

  // Iterate on requested shapes
  for (TDF_LabelSequence::Iterator aLabelIter(theLabels);
       aLabelIter.More(); aLabelIter.Next())
  {
    const TDF_Label& aLabel = aLabelIter.Value();
    // find target STEP entity for the current shape
    if (!myLabels.IsBound(aLabel))
      continue; // not recorded as translated, skip
    // get name
    Handle(TCollection_HAsciiString) aHName = new TCollection_HAsciiString;
    if (!GetLabelName(aLabel, aHName))
    {
      continue;
    }
    const TopoDS_Shape& aShape = myLabels.Find(aLabel);
    Handle(StepShape_ShapeDefinitionRepresentation) aSDR;
    Handle(StepShape_ContextDependentShapeRepresentation) aCDSR;
    Standard_Boolean isComponent = XCAFDoc_ShapeTool::IsComponent(aLabel) || myPureRefLabels.IsBound(aLabel);
    Handle(TransferBRep_ShapeMapper) aMapper = TransferBRep::ShapeMapper(aFP, aShape);
    if (isComponent && aFP->FindTypedTransient(aMapper, STANDARD_TYPE(StepShape_ContextDependentShapeRepresentation), aCDSR))
    {
      Handle(StepRepr_ProductDefinitionShape) aPDS = aCDSR->RepresentedProductRelation();
      Handle(StepBasic_ProductDefinitionRelationship) aNAUO = aPDS->Definition().ProductDefinitionRelationship();
      if (!aNAUO.IsNull())
        aNAUO->SetName(aHName);
      TopoDS_Shape anInternalAssembly;
      if (myPureRefLabels.Find(aLabel, anInternalAssembly))
      {
        Handle(TransferBRep_ShapeMapper) aMapperOfInternalShape = TransferBRep::ShapeMapper(aFP, anInternalAssembly);
        aFP->FindTypedTransient(aMapperOfInternalShape, STANDARD_TYPE(StepShape_ShapeDefinitionRepresentation), aSDR);
      }
    }
    if (!aSDR.IsNull() ||
        (aCDSR.IsNull() && aFP->FindTypedTransient(aMapper, STANDARD_TYPE(StepShape_ShapeDefinitionRepresentation), aSDR)))
    {
      // set the name to the PRODUCT
      Handle(StepRepr_PropertyDefinition) aPropD = aSDR->Definition().PropertyDefinition();
      if (aPropD.IsNull())
        continue;
      Handle(StepBasic_ProductDefinition) aPD = aPropD->Definition().ProductDefinition();
      if (aPD.IsNull())
        continue;
      Handle(StepBasic_Product) aProd = aPD->Formation()->OfProduct();

      aProd->SetId(aHName);
      aProd->SetName(aHName);
    }
    else
    {
      Message::SendTrace() << "Warning: Cannot find RI for " << aShape.TShape()->DynamicType()->Name() << "\n";
      continue;
    }
  }
  return Standard_True;
}

>>>>>>> accb2f351 (u)
//=======================================================================
//function : WritePropsForLabel
//purpose  :
//=======================================================================
<<<<<<< HEAD
static Standard_Boolean WritePropsForLabel(const Handle(XSControl_WorkSession) &WS,
                                           const Handle(XCAFDoc_ShapeTool) &aSTool,
                                           const STEPCAFControl_DataMapOfLabelShape &myLabels,
                                           const TDF_Label &L,
                                           const Standard_CString multi)
{
  if(L.IsNull()) return Standard_False;

  STEPConstruct_ValidationProps Props ( WS );

  TopoDS_Shape S = aSTool->GetShape(L);
  if(S.IsNull()) return Standard_False;

  if ( ! multi || XCAFDoc_ShapeTool::IsAssembly ( L ) ) {
    // write area
    Handle(XCAFDoc_Area) A;
    L.FindAttribute ( XCAFDoc_Area::GetID(), A );
    if ( ! A.IsNull() ) {
      Props.AddArea ( S, A->Get() );
    }
    // write volume
    Handle(XCAFDoc_Volume) V;
    L.FindAttribute ( XCAFDoc_Volume::GetID(), V );
    if ( ! V.IsNull() ) {
      Props.AddVolume ( S, V->Get() );
    }
  }
  // write centroid
  Handle(XCAFDoc_Centroid) C;
  L.FindAttribute ( XCAFDoc_Centroid::GetID(), C );
  if ( ! C.IsNull() ) {
    Props.AddCentroid ( S, C->Get() );
  }

  if( XCAFDoc_ShapeTool::IsCompound(L) || XCAFDoc_ShapeTool::IsAssembly(L) ) {
    if(L.HasChild()) {
      for(Standard_Integer ich=1; ich<=L.NbChildren(); ich++) {
        WritePropsForLabel(WS,aSTool,myLabels,L.FindChild(ich),multi);
=======
static Standard_Boolean WritePropsForLabel(const Handle(XSControl_WorkSession)& theWS,
                                           const STEPCAFControl_DataMapOfLabelShape& theLabels,
                                           const TDF_Label& theLabel,
                                           const Standard_CString theIsMulti)
{
  if (theLabel.IsNull())
    return Standard_False;

  STEPConstruct_ValidationProps aProps(theWS);

  TopoDS_Shape aShape = XCAFDoc_ShapeTool::GetShape(theLabel);
  if (aShape.IsNull())
    return Standard_False;

  if (!theIsMulti || XCAFDoc_ShapeTool::IsAssembly(theLabel))
  {
    // write area
    Handle(XCAFDoc_Area) anArea;
    theLabel.FindAttribute(XCAFDoc_Area::GetID(), anArea);
    if (!anArea.IsNull())
    {
      aProps.AddArea(aShape, anArea->Get());
    }
    // write volume
    Handle(XCAFDoc_Volume) aVolume;
    theLabel.FindAttribute(XCAFDoc_Volume::GetID(), aVolume);
    if (!aVolume.IsNull())
    {
      aProps.AddVolume(aShape, aVolume->Get());
    }
  }
  // write centroid
  Handle(XCAFDoc_Centroid) aCentroid;
  theLabel.FindAttribute(XCAFDoc_Centroid::GetID(), aCentroid);
  if (!aCentroid.IsNull())
  {
    aProps.AddCentroid(aShape, aCentroid->Get());
  }

  if (XCAFDoc_ShapeTool::IsCompound(theLabel) || XCAFDoc_ShapeTool::IsAssembly(theLabel))
  {
    if (theLabel.HasChild())
    {
      for (Standard_Integer aChildInd = 1; aChildInd <= theLabel.NbChildren(); aChildInd++)
      {
        WritePropsForLabel(theWS, theLabels, theLabel.FindChild(aChildInd), theIsMulti);
>>>>>>> accb2f351 (u)
      }
    }
  }

  return Standard_True;
}

<<<<<<< HEAD

//=======================================================================
//function : WriteValProps
//purpose  :
//=======================================================================

Standard_Boolean STEPCAFControl_Writer::WriteValProps (const Handle(XSControl_WorkSession) &WS,
						       const TDF_LabelSequence &labels,
						       const Standard_CString multi) const
{
  if ( labels.Length() <=0 ) return Standard_False;

  // get working data
//  STEPConstruct_ValidationProps Props ( WS );
  Handle(XCAFDoc_ShapeTool) aSTool = XCAFDoc_DocumentTool::ShapeTool( labels(1) );

  // Iterate on requested shapes
  for ( Standard_Integer i=1; i <= labels.Length(); i++ ) {
    TDF_Label L = labels.Value(i);

    WritePropsForLabel(WS,aSTool,myLabels,L,multi);
/*    
    // find target STEP entity for the current shape
    if ( ! myLabels.IsBound ( L ) ) continue; // not recorded as translated, skip
    TopoDS_Shape S = myLabels.Find ( L );

    // write area and volume (except for components in multifile mode)
    if ( ! multi || XCAFDoc_ShapeTool::IsAssembly ( L ) ) {
      Handle(XCAFDoc_Area) A;
      L.FindAttribute ( XCAFDoc_Area::GetID(), A );
      if ( ! A.IsNull() ) Props.AddArea ( S, A->Get() );

      Handle(XCAFDoc_Volume) V;
      L.FindAttribute ( XCAFDoc_Volume::GetID(), V );
      if ( ! V.IsNull() ) Props.AddVolume ( S, V->Get() );
    }

    // write centroid
    Handle(XCAFDoc_Centroid) C;
    L.FindAttribute ( XCAFDoc_Centroid::GetID(), C );
    if ( ! C.IsNull() ) Props.AddCentroid ( S, C->Get() );

    // write centroid for components of assemblies
    if ( XCAFDoc_ShapeTool::IsAssembly ( L ) ) {
      TDF_LabelSequence seq;
      XCAFDoc_ShapeTool::GetComponents ( L, seq );
      for (Standard_Integer k=1; k <= seq.Length(); k++) {
	TDF_Label lab = seq(k);

	// get shape with correct location
	TDF_Label Lref;
	if ( ! XCAFDoc_ShapeTool::GetReferredShape ( lab, Lref ) || 
	     ! myLabels.IsBound ( Lref ) ) continue;
	TopLoc_Location Loc = XCAFDoc_ShapeTool::GetLocation ( lab );
	S = myLabels.Find ( Lref );
	S.Move ( Loc );
		
	C.Nullify();
	lab.FindAttribute ( XCAFDoc_Centroid::GetID(), C );
	// if centroid is not assigned to an instance, 
	// use (shifted) centroid of original shape
	gp_Pnt center;
	if ( C.IsNull() ) {
	  Lref.FindAttribute ( XCAFDoc_Centroid::GetID(), C );
	  if ( C.IsNull() ) continue;
	  center = C->Get().Transformed ( Loc.Transformation() );
	}
	else center = C->Get();

	Props.AddCentroid ( S, center, Standard_True );
      }
    }
*/
=======
//=======================================================================
//function : writeValProps
//purpose  :
//=======================================================================
Standard_Boolean STEPCAFControl_Writer::writeValProps(const Handle(XSControl_WorkSession)& theWS,
                                                      const TDF_LabelSequence& theLabels,
                                                      const Standard_CString theIsMulti) const
{
  if (theLabels.IsEmpty())
    return Standard_False;

  // Iterate on requested shapes
  for (TDF_LabelSequence::Iterator aLabelIter(theLabels);
       aLabelIter.More(); aLabelIter.Next())
  {
    const TDF_Label& aLabel = aLabelIter.Value();

    WritePropsForLabel(theWS, myLabels, aLabel, theIsMulti);
>>>>>>> accb2f351 (u)
  }

  return Standard_True;
}

<<<<<<< HEAD

//=======================================================================
//function : WriteLayers
//purpose  : 
//=======================================================================

Standard_Boolean STEPCAFControl_Writer::WriteLayers (const Handle(XSControl_WorkSession) &WS,
						     const TDF_LabelSequence  &labels ) const
{
  
  if ( labels.Length() <=0 ) return Standard_False;

  // get working data
  const Handle(Interface_InterfaceModel) &Model = WS->Model();
  const Handle(XSControl_TransferWriter) &TW = WS->TransferWriter();
  const Handle(Transfer_FinderProcess) &FP = TW->FinderProcess();
  Handle(XCAFDoc_LayerTool) LTool = XCAFDoc_DocumentTool::LayerTool( labels(1) );
  if (LTool.IsNull() ) return Standard_False;

  TDF_LabelSequence LayerLS;
  LTool->GetLayerLabels(LayerLS);
  if ( LayerLS.Length() <=0 ) return Standard_False;

  // Iterate on requested layers and for each layer take set of shapes.
  for ( Standard_Integer i=1; i <= LayerLS.Length(); i++ ) {
    TDF_Label L = LayerLS.Value(i);
    
    // get labels of shapes in that layer
    TDF_LabelSequence ShapeLs;
    LTool->GetShapesOfLayer(L, ShapeLs);
    if ( ShapeLs.Length() <=0 ) continue;
    
    // name of layer: if not set, is considered as being empty
    Handle(TCollection_HAsciiString) hName = new TCollection_HAsciiString;
    GetLabelName ( L, hName );

    // Find target STEP entity for each shape and add to StepVisual_PresentationLayerAssignment items.
    TColStd_SequenceOfTransient seqRI;
    for ( Standard_Integer j=1; j <= ShapeLs.Length(); j++) {
      TDF_Label shLabel = ShapeLs.Value(j);
      if ( shLabel.IsNull() ) continue;
      
      // there is no way to assign layer to instance in STEP
      if ( XCAFDoc_ShapeTool::IsAssembly ( shLabel ) ||
           XCAFDoc_ShapeTool::IsReference ( shLabel ) )
        continue;
      
      // check that the shape is one of (uub)labels written during current transfer
      Standard_Integer k = 1;
      for ( ; k <= labels.Length(); k++ )
	if ( shLabel.IsDescendant ( labels(k) ) ) break;
      if ( k > labels.Length() ) continue;

      // get target STEP entity
      TopoDS_Shape oneShape = XCAFDoc_ShapeTool::GetShape(shLabel);
      
      TopLoc_Location Loc;
      Standard_Integer nb = 
	FindEntities ( FP, oneShape, Loc, seqRI );
      if ( nb <=0 ) 
	FP->Messenger()->SendInfo() << "Warning: Cannot find RI for " << oneShape.TShape()->DynamicType()->Name() << std::endl;
    }
    if ( seqRI.Length() <= 0 ) continue;

    // analyze visibility
    Handle(StepVisual_PresentationLayerAssignment) StepLayerAs = new StepVisual_PresentationLayerAssignment;
    Handle(TCollection_HAsciiString) descr;
    Handle(TDataStd_UAttribute) aUAttr;
    Standard_Boolean isLinv = Standard_False;
    if (L.FindAttribute(XCAFDoc::InvisibleGUID(), aUAttr)) {
      descr = new TCollection_HAsciiString ("invisible");
#ifdef OCCT_DEBUG
      std::cout << "\tLayer \"" << hName->String().ToCString() << "\" is invisible"<<std::endl;
#endif
      isLinv = Standard_True;
    }
    else descr = new TCollection_HAsciiString ("visible");
    
    // create layer entity
    Handle(StepVisual_HArray1OfLayeredItem) HArrayOfLItem = 
      new StepVisual_HArray1OfLayeredItem ( 1, seqRI.Length() );
    for (Standard_Integer i1 = 1; i1<=seqRI.Length(); i1++) {
      StepVisual_LayeredItem LI;
      LI.SetValue ( seqRI.Value(i1) );
      HArrayOfLItem->SetValue( i1, LI );
    }
    StepLayerAs->Init(hName, descr, HArrayOfLItem);
    Model->AddWithRefs( StepLayerAs );
    // PTV 23.01.2003 add the invisibility AFTER adding layer into the model.
    // add the invisibility for the layer
    if (isLinv) {
      // Invisibility Item for containing invisible layers.
      Handle(StepVisual_HArray1OfInvisibleItem) HInvsblItm = new StepVisual_HArray1OfInvisibleItem (1,1);
      StepVisual_InvisibleItem InvIt;
      InvIt.SetValue( StepLayerAs );
      HInvsblItm->SetValue( 1, InvIt);
      
      Handle(StepVisual_Invisibility) Invsblt = new StepVisual_Invisibility();
      Invsblt->Init( HInvsblItm );
      Model->AddWithRefs( Invsblt );
=======
//=======================================================================
//function : writeLayers
//purpose  :
//=======================================================================
Standard_Boolean STEPCAFControl_Writer::writeLayers(const Handle(XSControl_WorkSession)& theWS,
                                                    const TDF_LabelSequence& theLabels) const
{

  if (theLabels.IsEmpty())
    return Standard_False;

  // get working data
  const Handle(Interface_InterfaceModel)& aModel = theWS->Model();
  const Handle(XSControl_TransferWriter)& aTW = theWS->TransferWriter();
  const Handle(Transfer_FinderProcess)& aFP = aTW->FinderProcess();
  TDF_LabelSequence aGlobalLayerLS;
  // Iterate on requested shapes collect Tools
  for (TDF_LabelMap::Iterator aLabelIter(myRootLabels);
       aLabelIter.More(); aLabelIter.Next())
  {
    const TDF_Label& aLabel = aLabelIter.Value();
    Handle(XCAFDoc_LayerTool) aLTool = XCAFDoc_DocumentTool::LayerTool(aLabel);
    TDF_LabelSequence aLayerLS;
    aLTool->GetLayerLabels(aLayerLS);
    aGlobalLayerLS.Append(aLayerLS);
  }
  for (TDF_LabelSequence::Iterator aLayerIter(aGlobalLayerLS);
       aLayerIter.More(); aLayerIter.Next())
  {
    const TDF_Label& aLayerL = aLayerIter.Value();
    // get labels of shapes in that layer
    TDF_LabelSequence aShapeLabels;
    XCAFDoc_LayerTool::GetShapesOfLayer(aLayerL, aShapeLabels);
    if (aShapeLabels.IsEmpty())
      continue;

    // name of layer: if not set, is considered as being empty
    Handle(TCollection_HAsciiString) aHName = new TCollection_HAsciiString;
    GetLabelName(aLayerL, aHName);

    // Find target STEP entity for each shape and add to StepVisual_PresentationLayerAssignment items.
    TColStd_SequenceOfTransient aSeqRI;
    for (TDF_LabelSequence::Iterator aShapeIter(aShapeLabels);
         aShapeIter.More(); aShapeIter.Next())
    {
      const TDF_Label& aShLabel = aShapeIter.Value();
      if (aShLabel.IsNull())
        continue;

      // there is no way to assign layer to instance in STEP
      if (XCAFDoc_ShapeTool::IsAssembly(aShLabel) ||
          XCAFDoc_ShapeTool::IsReference(aShLabel))
      {
        continue;
      }
      // check that the shape is one of (uub)labels written during current transfer
      Standard_Boolean anIsWritten = Standard_False;
      for (TDF_LabelSequence::Iterator aLabelIter(theLabels);
           aLabelIter.More(); aLabelIter.Next())
      {
        if (aShLabel.IsDescendant(aLabelIter.Value()))
        {
          anIsWritten = Standard_True;
          break;
        }
      }
      if (!anIsWritten)
      {
        continue;
      }

      // get target STEP entity
      TopoDS_Shape anOneShape = XCAFDoc_ShapeTool::GetShape(aShLabel);

      TopLoc_Location aLoc;
      Standard_Integer aNb = FindEntities(aFP, anOneShape, aLoc, aSeqRI);
      if (aNb <= 0)
      {
        Message::SendTrace() << "Warning: Cannot find RI for " << anOneShape.TShape()->DynamicType()->Name() << "\n";
      }
    }
    if (aSeqRI.IsEmpty())
      continue;

    // analyze visibility
    Handle(StepVisual_PresentationLayerAssignment) aStepLayerAs = new StepVisual_PresentationLayerAssignment;
    Handle(TCollection_HAsciiString) aDescr;
    Handle(TDataStd_UAttribute) aUAttr;
    Standard_Boolean isLinv = Standard_False;
    if (aLayerL.FindAttribute(XCAFDoc::InvisibleGUID(), aUAttr))
    {
      aDescr = new TCollection_HAsciiString("invisible");
      Message::SendTrace() << "\tLayer \"" << aHName->String().ToCString() << "\" is invisible" << "\n";
      isLinv = Standard_True;
    }
    else
    {
      aDescr = new TCollection_HAsciiString("visible");
    }

    // create layer entity
    Standard_Integer anSetStyleInd = 1;
    Handle(StepVisual_HArray1OfLayeredItem) aHArrayOfLItem =
      new StepVisual_HArray1OfLayeredItem(1, aSeqRI.Length());
    for (TColStd_SequenceOfTransient::Iterator aRIIter(aSeqRI);
         aRIIter.More(); aRIIter.Next())
    {
      StepVisual_LayeredItem aLI;
      aLI.SetValue(aRIIter.Value());
      aHArrayOfLItem->SetValue(anSetStyleInd++, aLI);
    }
    aStepLayerAs->Init(aHName, aDescr, aHArrayOfLItem);
    aModel->AddWithRefs(aStepLayerAs);
    // PTV 23.01.2003 add the invisibility AFTER adding layer into the model.
    // add the invisibility for the layer
    if (isLinv)
    {
      // Invisibility Item for containing invisible layers.
      Handle(StepVisual_HArray1OfInvisibleItem) aHInvsblItm = new StepVisual_HArray1OfInvisibleItem(1, 1);
      StepVisual_InvisibleItem aInvIt;
      aInvIt.SetValue(aStepLayerAs);
      aHInvsblItm->SetValue(1, aInvIt);

      Handle(StepVisual_Invisibility) aInvsblt = new StepVisual_Invisibility();
      aInvsblt->Init(aHInvsblItm);
      aModel->AddWithRefs(aInvsblt);
>>>>>>> accb2f351 (u)
    }
  }
  return Standard_True;
}

<<<<<<< HEAD

=======
>>>>>>> accb2f351 (u)
//=======================================================================
//function : getSHUOstyle
//purpose  : auxiliary
//=======================================================================
<<<<<<< HEAD
static Standard_Boolean getSHUOstyle(const TDF_Label& aSHUOlab,
                                     const Handle(XCAFDoc_ColorTool)& CTool,
                                     const Handle(XCAFDoc_VisMaterialTool)& theMatTool,
                                     XCAFPrs_Style& SHUOstyle)
{
  Quantity_Color C;
  if (!CTool->IsVisible( aSHUOlab ) )
    SHUOstyle.SetVisibility(Standard_False);
  else {
    if ( CTool->GetColor ( aSHUOlab, XCAFDoc_ColorGen, C ) ) {
      SHUOstyle.SetColorCurv ( C );
      SHUOstyle.SetColorSurf ( C );
    }
    if ( CTool->GetColor ( aSHUOlab, XCAFDoc_ColorSurf, C ) )
      SHUOstyle.SetColorSurf ( C );
    if ( CTool->GetColor ( aSHUOlab, XCAFDoc_ColorCurv, C ) )
      SHUOstyle.SetColorCurv ( C );
    if (!SHUOstyle.IsSetColorSurf())
    {
      Handle(XCAFDoc_VisMaterial) aVisMat = theMatTool->GetShapeMaterial (aSHUOlab);
      if (!aVisMat.IsNull()
       && !aVisMat->IsEmpty())
      {
        // only color can be stored in STEP
        SHUOstyle.SetColorSurf (aVisMat->BaseColor());
      }
    }
  }
  if ( !SHUOstyle.IsSetColorCurv() && 
      !SHUOstyle.IsSetColorSurf() &&
      SHUOstyle.IsVisible() )
    return Standard_False;
  return Standard_True;
}


=======
static Standard_Boolean getSHUOstyle(const TDF_Label& theSHUOlab,
                                     XCAFPrs_Style& theSHUOstyle)
{
  Quantity_Color aColor;
  if (!XCAFDoc_ColorTool::IsVisible(theSHUOlab))
  {
    theSHUOstyle.SetVisibility(Standard_False);
  }
  else
  {
    if (XCAFDoc_ColorTool::GetColor(theSHUOlab, XCAFDoc_ColorGen, aColor))
    {
      theSHUOstyle.SetColorCurv(aColor);
      theSHUOstyle.SetColorSurf(aColor);
    }
    if (XCAFDoc_ColorTool::GetColor(theSHUOlab, XCAFDoc_ColorSurf, aColor))
      theSHUOstyle.SetColorSurf(aColor);
    if (XCAFDoc_ColorTool::GetColor(theSHUOlab, XCAFDoc_ColorCurv, aColor))
      theSHUOstyle.SetColorCurv(aColor);
    if (!theSHUOstyle.IsSetColorSurf())
    {
      Handle(XCAFDoc_VisMaterial) aVisMat = XCAFDoc_VisMaterialTool::GetShapeMaterial(theSHUOlab);
      if (!aVisMat.IsNull()
          && !aVisMat->IsEmpty())
      {
        // only color can be stored in STEP
        theSHUOstyle.SetColorSurf(aVisMat->BaseColor());
      }
    }
  }
  if (!theSHUOstyle.IsSetColorCurv() &&
      !theSHUOstyle.IsSetColorSurf() &&
      theSHUOstyle.IsVisible())
  {
    return Standard_False;
  }
  return Standard_True;
}

>>>>>>> accb2f351 (u)
//=======================================================================
//function : getProDefinitionOfNAUO
//purpose  : auxiliary
//=======================================================================
<<<<<<< HEAD
static Standard_Boolean getProDefinitionOfNAUO(const Handle(XSControl_WorkSession)& WS,
                                               const TopoDS_Shape& theShape,
                                               Handle(StepBasic_ProductDefinition)& PD,
                                               Handle(StepRepr_NextAssemblyUsageOccurrence)& NAUO,
                                               Standard_Boolean IsRelating)
{
  if ( theShape.IsNull() )
    return Standard_False;
  // get CDSR
  const Handle(XSControl_TransferWriter) &TW = WS->TransferWriter();
  const Handle(Transfer_FinderProcess) &FP = TW->FinderProcess();
  Handle(StepShape_ContextDependentShapeRepresentation) CDSR;
  Handle(TransferBRep_ShapeMapper) mapper = TransferBRep::ShapeMapper ( FP, theShape );
  if (!FP->FindTypedTransient(mapper, 
                              STANDARD_TYPE(StepShape_ContextDependentShapeRepresentation),
                              CDSR))
    return Standard_False;
  // get PDS of NAUO
  Handle(StepRepr_ProductDefinitionShape) PDS = CDSR->RepresentedProductRelation();
  if (PDS.IsNull())
    return Standard_False;
  // get the NAUO entity
  Interface_Graph aGraph = WS->HGraph()->Graph();
  Interface_EntityIterator subs = aGraph.Shareds(PDS);
  for ( subs.Start(); subs.More(); subs.Next() ) {
    if (!subs.Value()->IsKind(STANDARD_TYPE(StepRepr_NextAssemblyUsageOccurrence)))
      continue;
    NAUO = Handle(StepRepr_NextAssemblyUsageOccurrence)::DownCast(subs.Value());
    break;
  }
  if ( NAUO.IsNull() )
    return Standard_False;
  // get Relatinf or Related product definition
  if ( !IsRelating )
    PD = NAUO->RelatedProductDefinition();
  else
    PD = NAUO->RelatingProductDefinition();
  if ( PD.IsNull() )
=======
static Standard_Boolean getProDefinitionOfNAUO(const Handle(XSControl_WorkSession)& theWS,
                                               const TopoDS_Shape& theShape,
                                               Handle(StepBasic_ProductDefinition)& thePD,
                                               Handle(StepRepr_NextAssemblyUsageOccurrence)& theNAUO,
                                               Standard_Boolean theIsRelating)
{
  if (theShape.IsNull())
    return Standard_False;
  // get CDSR
  const Handle(XSControl_TransferWriter)& aTW = theWS->TransferWriter();
  const Handle(Transfer_FinderProcess)& aFP = aTW->FinderProcess();
  Handle(StepShape_ContextDependentShapeRepresentation) aCDSR;
  Handle(TransferBRep_ShapeMapper) aMapper = TransferBRep::ShapeMapper(aFP, theShape);
  if (!aFP->FindTypedTransient(aMapper,
      STANDARD_TYPE(StepShape_ContextDependentShapeRepresentation),
      aCDSR))
  {
    return Standard_False;
  }
  // get PDS of NAUO
  Handle(StepRepr_ProductDefinitionShape) aPDS = aCDSR->RepresentedProductRelation();
  if (aPDS.IsNull())
    return Standard_False;
  // get the NAUO entity
  Interface_Graph aGraph = theWS->HGraph()->Graph();
  for (Interface_EntityIterator aShareds = aGraph.Shareds(aPDS); aShareds.More(); aShareds.Next())
  {
    theNAUO = Handle(StepRepr_NextAssemblyUsageOccurrence)::DownCast(aShareds.Value());
    if (!theNAUO.IsNull())
    {
      break;
    }
  }
  if (theNAUO.IsNull())
    return Standard_False;
  // get Relatinf or Related product definition
  if (!theIsRelating)
    thePD = theNAUO->RelatedProductDefinition();
  else
    thePD = theNAUO->RelatingProductDefinition();
  if (thePD.IsNull())
>>>>>>> accb2f351 (u)
    return Standard_False;
  return Standard_True;
}

<<<<<<< HEAD

=======
>>>>>>> accb2f351 (u)
//=======================================================================
//function : writeSHUO
//purpose  : auxiliary
//=======================================================================
<<<<<<< HEAD
static Standard_Boolean writeSHUO (const Handle(XCAFDoc_GraphNode)& theSHUO,
                                   const Handle(XCAFDoc_ShapeTool)& theSTool,
                                   const Handle(XSControl_WorkSession)& WS,
                                   Handle(StepRepr_SpecifiedHigherUsageOccurrence)& theTopSHUO,
                                   TopoDS_Shape& NAUOShape,
                                   Handle(StepBasic_ProductDefinition)& theRelatingPD,
                                   Standard_Boolean& isDeepest)
{
  // set the ProductDefinitionRelationship descriptin information as empty strings.
  Handle(TCollection_HAsciiString) EmptyString = new TCollection_HAsciiString("");
  
  TDF_LabelSequence aNextUsageLabs;
  theSTool->GetSHUONextUsage( theSHUO->Label(), aNextUsageLabs );
  Handle(XCAFDoc_GraphNode) NuSHUO;
  if ( theTopSHUO.IsNull() ) {
    // the top SHUO
    if (aNextUsageLabs.Length() < 1)
      return Standard_False;
    theSTool->GetSHUO( aNextUsageLabs.Value(1), NuSHUO );
    if (NuSHUO.IsNull())
      return Standard_False;
    // get relating product definition
    TopoDS_Shape aTopCompShape = theSTool->GetShape( theSHUO->Label().Father() ); 
    Handle(StepRepr_NextAssemblyUsageOccurrence) UUNAUO;
    if (!getProDefinitionOfNAUO( WS, aTopCompShape,
                                 theRelatingPD, UUNAUO, Standard_True ))
      return Standard_False;
    // get related product definition
    TopoDS_Shape aNUShape = theSTool->GetShape( NuSHUO->Label().Father() );
    Handle(StepBasic_ProductDefinition) aRelatedPD;
    Handle(StepRepr_NextAssemblyUsageOccurrence) NUNAUO;
    if (!getProDefinitionOfNAUO( WS, aNUShape,
                                 aRelatedPD, NUNAUO, Standard_False ))
      return Standard_False;
    
    theTopSHUO = new StepRepr_SpecifiedHigherUsageOccurrence;
    // create deepest shuo EmptyString
    theTopSHUO->Init(/*id*/EmptyString, /*name*/EmptyString,
                     /*no description*/Standard_False,/*description*/EmptyString,
                     theRelatingPD, aRelatedPD,
                     /*no ACURefDesignator*/Standard_False,/*ACURefDesignator*/EmptyString,
                     /*upper_usage*/UUNAUO, /*next_usage*/NUNAUO);
    // write the other SHUO.
    if(!writeSHUO( NuSHUO, theSTool, WS, theTopSHUO, NAUOShape, theRelatingPD, isDeepest )) {
      theTopSHUO.Nullify();
      return Standard_False;
    }
    
    return Standard_True;
  }
//   Handle(XCAFDoc_GraphNode) NuSHUO;
  if ( aNextUsageLabs.Length() > 0) {
    // store SHUO recursive
#ifdef OCCT_DEBUG
    if ( aNextUsageLabs.Length() > 1 )
      std::cout << "Warning: store only one next_usage of current SHUO"  << std::endl;
#endif    
    theSTool->GetSHUO( aNextUsageLabs.Value(1), NuSHUO );
    Handle(StepRepr_SpecifiedHigherUsageOccurrence) aNUEntSHUO =
      new StepRepr_SpecifiedHigherUsageOccurrence;
    if (!writeSHUO( NuSHUO, theSTool, WS, aNUEntSHUO, NAUOShape, theRelatingPD, isDeepest ))
      return Standard_False;
    
    // store the deepest SHUO to the dociment
    TopoDS_Shape aNUSh, aUUSh;
    aNUSh = theSTool->GetShape( NuSHUO->Label().Father() );
    aUUSh = theSTool->GetShape( theSHUO->Label().Father() );
=======
static Standard_Boolean writeSHUO(const Handle(XCAFDoc_GraphNode)& theSHUO,
                                  const Handle(XSControl_WorkSession)& theWS,
                                  Handle(StepRepr_SpecifiedHigherUsageOccurrence)& theTopSHUO,
                                  TopoDS_Shape& theNAUOShape,
                                  Handle(StepBasic_ProductDefinition)& theRelatingPD,
                                  Standard_Boolean& theIsDeepest)
{
  // set the ProductDefinitionRelationship descriptin information as empty strings.
  Handle(TCollection_HAsciiString) anEmptyString = new TCollection_HAsciiString("");

  TDF_LabelSequence aNextUsageLabs;
  XCAFDoc_ShapeTool::GetSHUONextUsage(theSHUO->Label(), aNextUsageLabs);
  Handle(XCAFDoc_GraphNode) aNuSHUO;
  if (theTopSHUO.IsNull())
  {
    // the top SHUO
    if (aNextUsageLabs.Length() < 1)
      return Standard_False;
    XCAFDoc_ShapeTool::GetSHUO(aNextUsageLabs.Value(1), aNuSHUO);
    if (aNuSHUO.IsNull())
      return Standard_False;
    // get relating product definition
    TopoDS_Shape aTopCompShape = XCAFDoc_ShapeTool::GetShape(theSHUO->Label().Father());
    Handle(StepRepr_NextAssemblyUsageOccurrence) aRelatingNAUO;
    if (!getProDefinitionOfNAUO(theWS, aTopCompShape,
        theRelatingPD, aRelatingNAUO, Standard_True))
    {
      return Standard_False;
    }
    // get related product definition
    TopoDS_Shape aNUShape = XCAFDoc_ShapeTool::GetShape(aNuSHUO->Label().Father());
    Handle(StepBasic_ProductDefinition) aRelatedPD;
    Handle(StepRepr_NextAssemblyUsageOccurrence) aRelatedNAUO;
    if (!getProDefinitionOfNAUO(theWS, aNUShape,
        aRelatedPD, aRelatedNAUO, Standard_False))
    {
      return Standard_False;
    }

    theTopSHUO = new StepRepr_SpecifiedHigherUsageOccurrence;
    // create deepest shuo EmptyString
    theTopSHUO->Init(/*id*/anEmptyString, /*name*/anEmptyString,
                     /*no description*/Standard_False,/*description*/anEmptyString,
                     theRelatingPD, aRelatedPD,
                     /*no ACURefDesignator*/Standard_False,/*ACURefDesignator*/anEmptyString,
                     /*upper_usage*/aRelatingNAUO, /*next_usage*/aRelatedNAUO);
    // write the other SHUO.
    if (!writeSHUO(aNuSHUO, theWS, theTopSHUO, theNAUOShape, theRelatingPD, theIsDeepest))
    {
      theTopSHUO.Nullify();
      return Standard_False;
    }

    return Standard_True;
  }
  //   Handle(XCAFDoc_GraphNode) NuSHUO;
  if (aNextUsageLabs.Length() > 0)
  {
    // store SHUO recursive
    if (aNextUsageLabs.Length() > 1)
      Message::SendTrace() << "Warning: store only one next_usage of current SHUO" << "\n";
    XCAFDoc_ShapeTool::GetSHUO(aNextUsageLabs.Value(1), aNuSHUO);
    Handle(StepRepr_SpecifiedHigherUsageOccurrence) aNUEntSHUO =
      new StepRepr_SpecifiedHigherUsageOccurrence;
    if (!writeSHUO(aNuSHUO, theWS, aNUEntSHUO, theNAUOShape, theRelatingPD, theIsDeepest))
      return Standard_False;

    // store the deepest SHUO to the dociment
    TopoDS_Shape aNUSh, aUUSh;
    aNUSh = XCAFDoc_ShapeTool::GetShape(aNuSHUO->Label().Father());
    aUUSh = XCAFDoc_ShapeTool::GetShape(theSHUO->Label().Father());
>>>>>>> accb2f351 (u)
    // get relating PD with upper_usage and related PD with next_usage
    Handle(StepBasic_ProductDefinition) nullPD;// no need to use,case have shared <theRelatingPD>
    Handle(StepBasic_ProductDefinition) aRelatedPD;
    Handle(StepRepr_NextAssemblyUsageOccurrence) UUNAUO, NUNAUO;
<<<<<<< HEAD
    if (!getProDefinitionOfNAUO( WS, aUUSh, nullPD, UUNAUO, Standard_True ) ||
        !getProDefinitionOfNAUO( WS, aNUSh, aRelatedPD, NUNAUO, Standard_False )) {
#ifdef OCCT_DEBUG
      std::cout << "Warning: cannot get related or relating PD" << std::endl;
#endif
      return Standard_False;
    }
    aNUEntSHUO->Init(/*id*/EmptyString, /*name*/EmptyString,
                     /*no description*/Standard_False,/*description*/EmptyString,
                     theRelatingPD, aRelatedPD,
                     /*no ACURefDesignator*/Standard_False,/*ACURefDesignator*/EmptyString,
                     /*upper_usage*/theTopSHUO, /*next_usage*/NUNAUO);
    if ( isDeepest ) {
      isDeepest = Standard_False;
    }
    WS->Model()->AddWithRefs ( aNUEntSHUO );
    return Standard_True;
  } // end of recurse storing
    
  // get shape 
  TDF_Label aShapeL = theSHUO->Label().Father();
  NAUOShape = theSTool->GetShape( aShapeL );
  // return to the deepest level from SHUO shape level
  // it is because SHUO is attribute on deep level and shape level.
  isDeepest = Standard_True;
  return Standard_True;
}


=======
    if (!getProDefinitionOfNAUO(theWS, aUUSh, nullPD, UUNAUO, Standard_True) ||
        !getProDefinitionOfNAUO(theWS, aNUSh, aRelatedPD, NUNAUO, Standard_False))
    {
      Message::SendTrace() << "Warning: cannot get related or relating PD" << "\n";
      return Standard_False;
    }
    aNUEntSHUO->Init(/*id*/anEmptyString, /*name*/anEmptyString,
                     /*no description*/Standard_False,/*description*/anEmptyString,
                     theRelatingPD, aRelatedPD,
                     /*no ACURefDesignator*/Standard_False,/*ACURefDesignator*/anEmptyString,
                     /*upper_usage*/theTopSHUO, /*next_usage*/NUNAUO);
    if (theIsDeepest)
    {
      theIsDeepest = Standard_False;
    }
    theWS->Model()->AddWithRefs(aNUEntSHUO);
    return Standard_True;
  } // end of recurse storing

  // get shape
  TDF_Label aShapeL = theSHUO->Label().Father();
  theNAUOShape = XCAFDoc_ShapeTool::GetShape(aShapeL);
  // return to the deepest level from SHUO shape level
  // it is because SHUO is attribute on deep level and shape level.
  theIsDeepest = Standard_True;
  return Standard_True;
}

>>>>>>> accb2f351 (u)
//=======================================================================
//function : createSHUOStyledItem
//purpose  : auxiliary
//=======================================================================
<<<<<<< HEAD
static Standard_Boolean createSHUOStyledItem (const XCAFPrs_Style& style,
                                              const Handle(StepRepr_ProductDefinitionShape)& PDS,
                                              const Handle(XSControl_WorkSession) &WS,
                                              const TopoDS_Shape& Sh,
                                              const Handle(XCAFDoc_ShapeTool)& STool,
                                              MoniTool_DataMapOfShapeTransient& myMapCompMDGPR)
{
  // create styled item for the indicated SHUO and store to the model
  STEPConstruct_Styles Styles( WS );
  // translate colors to STEP
  Handle(StepVisual_Colour) surfColor, curvColor;
  Standard_Real RenderTransp = 0.0;
  if ( style.IsSetColorSurf() ) {
    Quantity_ColorRGBA sCol = style.GetColorSurfRGBA();
    RenderTransp = 1.0 - sCol.Alpha();
    surfColor = Styles.EncodeColor ( sCol.GetRGB() );
  }
  if ( style.IsSetColorCurv() )
    curvColor = Styles.EncodeColor ( style.GetColorCurv() );
  Standard_Boolean isComponent = Standard_True;// cause need to get PSBC
  Handle(StepRepr_RepresentationItem) item;
  // set default color for invisible SHUO.
  Standard_Boolean isSetDefaultColor = Standard_False;
  if (surfColor.IsNull() && curvColor.IsNull() && !style.IsVisible() ) {
    surfColor = Styles.EncodeColor ( Quantity_Color(Quantity_NOC_WHITE) );
    isSetDefaultColor = Standard_True;
  }
  Handle(StepVisual_PresentationStyleAssignment) PSA =
    Styles.MakeColorPSA ( item, surfColor, curvColor, surfColor, RenderTransp, isComponent );
  Handle(StepVisual_StyledItem) override; //null styled item
  
  // find the repr item of the shape
  const Handle(XSControl_TransferWriter) &TW = WS->TransferWriter();
  const Handle(Transfer_FinderProcess) &FP = TW->FinderProcess();
  Handle(TransferBRep_ShapeMapper) mapper = TransferBRep::ShapeMapper ( FP, Sh );
  Handle(StepShape_ContextDependentShapeRepresentation) CDSR;
  FP->FindTypedTransient(mapper, 
                         STANDARD_TYPE(StepShape_ContextDependentShapeRepresentation),
                         CDSR);
  if ( CDSR.IsNull() )
    return Standard_False;
  // find context
  Handle(StepRepr_RepresentationContext) Context = Styles.FindContext( Sh );
  TopoDS_Shape aTopSh = Sh;
  if (Context.IsNull()) {
    TDF_Label aTopShL = STool->FindShape(Sh, Standard_False);
    if (aTopShL.IsNull())
      return Standard_False;
    aTopSh = STool->GetShape( aTopShL );
    Context = Styles.FindContext ( aTopSh );
  }
  if (Context.IsNull())
    return Standard_False;
  // get representation item of the shape
  TopLoc_Location L;
  TColStd_SequenceOfTransient seqRI;
  FindEntities ( FP, Sh, L, seqRI );
#ifdef OCCT_DEBUG
  if ( seqRI.Length() <=0 ) 
    std::cout << "Warning: Cannot find RI for " << Sh.TShape()->DynamicType()->Name() << std::endl;
#endif
  item = Handle(StepRepr_RepresentationItem)::DownCast(seqRI(1));
  //get overridden styled item
  getStyledItem(Sh,STool, Styles, override,myMapCompMDGPR);
  
  // get STEP STYLED ITEM
  Handle(StepVisual_StyledItem) STEPstyle = Styles.AddStyle ( item, PSA, override );
  // create SR, SDR and all necessary references between them and ST, PDS, PSBC, GRC
  Styles.CreateNAUOSRD( Context, CDSR, PDS );
  
  // add step styled item of SHUO to the model
  // do it by additing styled item to the MDGPR
  if ( !aTopSh.IsNull() &&  !myMapCompMDGPR.IsBound( aTopSh ) ) {
    // create MDGPR and record it in model
#ifdef OCCT_DEBUG
    std::cout << "Warning: " << __FILE__ << ": Create new MDGPR for SHUO instance"  << std::endl;
#endif
    Handle(StepVisual_MechanicalDesignGeometricPresentationRepresentation) aMDGPR;
    Styles.CreateMDGPR ( Context, aMDGPR );
    if (!aMDGPR.IsNull())
      myMapCompMDGPR.Bind( aTopSh, aMDGPR );
  }
  else if ( !aTopSh.IsNull() &&  myMapCompMDGPR.IsBound( aTopSh ) ) {
    // get MDGPR of the top-level shape
    Handle(StepVisual_PresentationRepresentation) aMDGPR = 
      Handle(StepVisual_PresentationRepresentation)::DownCast( myMapCompMDGPR.Find( aTopSh ) );
    // get old styled items to not lose it
    Handle(StepRepr_HArray1OfRepresentationItem) oldItems = aMDGPR->Items();
    Standard_Integer oldLengthlen = 0;
    if (!oldItems.IsNull())
      oldLengthlen = oldItems->Length();
    // create new array of styled items by an olds and new one
    Handle(StepRepr_HArray1OfRepresentationItem) newItems =
      new StepRepr_HArray1OfRepresentationItem(1, oldLengthlen + 1);
    Standard_Integer si;
    Standard_Integer el = 1;
    for ( si=1; si <= oldLengthlen; si++ )
      newItems->SetValue( el++, oldItems->Value( si ) );
    newItems->SetValue (el++, STEPstyle);
    // init MDGPR be new array of styled items
    if (newItems->Length() > 0)
      aMDGPR->SetItems( newItems );
  }
  else {
    WS->Model()->AddWithRefs ( STEPstyle ); // add as root to the model, but it is not good
#ifdef OCCT_DEBUG
    std::cout << "Warning: " << __FILE__ << ": adds styled item of SHUO as root, cause cannot find MDGPR" << std::endl;
#endif
  }
  // create invisibility item for the styled item
  if ( !style.IsVisible() ) {
    if (isSetDefaultColor) {
      // try to set default color from top-level shape
      
      setDefaultInstanceColor(override, PSA);
    }
    // create invisibility item and refer for styledItem
    Handle(StepVisual_Invisibility) Invsblt = new StepVisual_Invisibility();
    Handle(StepVisual_HArray1OfInvisibleItem) HInvsblItm = 
      new StepVisual_HArray1OfInvisibleItem (1,1);
    // put all style item into the harray
    StepVisual_InvisibleItem anInvItem;
    anInvItem.SetValue( STEPstyle );
    HInvsblItm->SetValue( 1, anInvItem );
    Invsblt->Init( HInvsblItm );
    WS->Model()->AddWithRefs( Invsblt );
  }
  
  return Standard_True;
}


//=======================================================================
//function : WriteSHUOs
//purpose  : 
//=======================================================================

Standard_Boolean STEPCAFControl_Writer::WriteSHUOs (const Handle(XSControl_WorkSession) &WS,
                                                    const TDF_LabelSequence  &labels )
{
  if ( labels.Length() <=0 ) return Standard_False;

  // get working data
  Handle(XCAFDoc_ColorTool) CTool = XCAFDoc_DocumentTool::ColorTool( labels(1) );
  Handle(XCAFDoc_VisMaterialTool) aMatTool = XCAFDoc_DocumentTool::VisMaterialTool( labels(1) );
  if (CTool.IsNull() )
    return Standard_False;
  // map of transferred SHUO
  TColStd_MapOfTransient aMapOfMainSHUO;
  // Iterate on requested shapes
  for ( Standard_Integer i=1; i <= labels.Length(); i++ ) {
    TDF_Label L = labels.Value(i);
    if ( ! myLabels.IsBound ( L ) ) continue; // not recorded as translated, skip
    if ( XCAFDoc_ShapeTool::IsAssembly ( L ) ) {
      TDF_LabelSequence seq;
      XCAFDoc_ShapeTool::GetComponents ( L, seq );
      // iterates on components of assembly
      for (Standard_Integer k=1; k <= seq.Length(); k++) {
	TDF_Label lab = seq(k);
        TDF_AttributeSequence anAttrSeq;
        CTool->ShapeTool()->GetAllComponentSHUO( lab, anAttrSeq );
        // work with SHUO
        for (Standard_Integer j = 1; j <= anAttrSeq.Length(); j++) {
          Handle(XCAFDoc_GraphNode) aSHUO = 
            Handle(XCAFDoc_GraphNode)::DownCast(anAttrSeq.Value( j ));
          // take label of SHUO
          TDF_Label aSHUOlab = aSHUO->Label();
          TDF_LabelSequence aUpLabels;
          // check is it SHUO of upper_usage
          CTool->ShapeTool()->GetSHUOUpperUsage( aSHUOlab, aUpLabels );
          if ( aUpLabels.Length() > 0 )
            continue; // transfer only main SHUO
          if ( aMapOfMainSHUO.Contains( aSHUO ) )
            continue; // do not try to transfer SHUO twice
          aMapOfMainSHUO.Add( aSHUO );
          // check if it is styled SHUO
          XCAFPrs_Style SHUOstyle;
          if ( !getSHUOstyle ( aSHUOlab, CTool, aMatTool, SHUOstyle ) ) {
#ifdef OCCT_DEBUG
            std::cout << "Warning: " << __FILE__ << ": do not store SHUO without any style to the STEP model" << std::endl;
#endif
            continue;
          }
          // write SHUO to the model amd then add structure type.
          TopoDS_Shape NAUOShape; // shape of the deepest NAUO in the SHUO structure
          Standard_Boolean isDeepest = Standard_False;
          Handle(StepRepr_SpecifiedHigherUsageOccurrence) anEntOfSHUO;
          Handle(StepBasic_ProductDefinition) aRelatingPD;
          // create the top SHUO and all other.
          writeSHUO( aSHUO, CTool->ShapeTool(), WS, anEntOfSHUO, NAUOShape, aRelatingPD, isDeepest );
          if ( anEntOfSHUO.IsNull() || NAUOShape.IsNull() ) {
#ifdef OCCT_DEBUG
            std::cout << "Warning: " << __FILE__ << ": Cannot store SHUO" << std::endl;
#endif
            continue;
          }
          // create new Product Definition Shape for TOP SHUO
#ifdef OCCT_DEBUG
            std::cout << "Info: " << __FILE__ << ": Create NEW PDS for current SHUO " << std::endl;
#endif
          Handle(StepRepr_ProductDefinitionShape) PDS = new StepRepr_ProductDefinitionShape;
          Handle(TCollection_HAsciiString) aPDSname = new TCollection_HAsciiString("SHUO");
          Handle(TCollection_HAsciiString) descrStr = new TCollection_HAsciiString("");
          StepRepr_CharacterizedDefinition aCharDef;
          aCharDef.SetValue( anEntOfSHUO );
          PDS->Init( aPDSname, Standard_False, descrStr, aCharDef );
          
          // create styled item for SHUO and add to the model
          createSHUOStyledItem ( SHUOstyle, PDS, WS, NAUOShape, CTool->ShapeTool(), myMapCompMDGPR );
          
        } // end work with SHUO
      } // end of an assembly components
    } // end of IsAssembly case
    // nothing to do if it is not assembly
    continue;
=======
static Standard_Boolean createSHUOStyledItem(const XCAFPrs_Style& theStyle,
                                             const Handle(StepRepr_ProductDefinitionShape)& thePDS,
                                             const Handle(XSControl_WorkSession)& theWS,
                                             const TopoDS_Shape& theShape,
                                             const Handle(XCAFDoc_ShapeTool)& theSTool,
                                             MoniTool_DataMapOfShapeTransient& theMapCompMDGPR)
{
  // create styled item for the indicated SHUO and store to the model
  STEPConstruct_Styles aStyles(theWS);
  // translate colors to STEP
  Handle(StepVisual_Colour) aSurfColor, aCurvColor;
  Standard_Real aRenderTransp = 0.0;
  if (theStyle.IsSetColorSurf())
  {
    Quantity_ColorRGBA aSurfCol = theStyle.GetColorSurfRGBA();
    aRenderTransp = 1.0 - aSurfCol.Alpha();
    aSurfColor = aStyles.EncodeColor(aSurfCol.GetRGB());
  }
  if (theStyle.IsSetColorCurv())
    aCurvColor = aStyles.EncodeColor(theStyle.GetColorCurv());
  Standard_Boolean isComponent = Standard_True;// cause need to get PSBC
  Handle(StepRepr_RepresentationItem) anItem;
  // set default color for invisible SHUO.
  Standard_Boolean isSetDefaultColor = Standard_False;
  if (aSurfColor.IsNull() && aCurvColor.IsNull() && !theStyle.IsVisible())
  {
    aSurfColor = aStyles.EncodeColor(Quantity_Color(Quantity_NOC_WHITE));
    isSetDefaultColor = Standard_True;
  }
  Handle(StepVisual_PresentationStyleAssignment) aPSA =
    aStyles.MakeColorPSA(anItem, aSurfColor, aCurvColor, aSurfColor, aRenderTransp, isComponent);
  Handle(StepVisual_StyledItem) anOverride; //null styled item

  // find the repr item of the shape
  const Handle(XSControl_TransferWriter)& aTW = theWS->TransferWriter();
  const Handle(Transfer_FinderProcess)& aFP = aTW->FinderProcess();
  Handle(TransferBRep_ShapeMapper) aMapper = TransferBRep::ShapeMapper(aFP, theShape);
  Handle(StepShape_ContextDependentShapeRepresentation) aCDSR;
  aFP->FindTypedTransient(aMapper,
                          STANDARD_TYPE(StepShape_ContextDependentShapeRepresentation),
                          aCDSR);
  if (aCDSR.IsNull())
    return Standard_False;
  // find context
  Handle(StepRepr_RepresentationContext) aContext = aStyles.FindContext(theShape);
  TopoDS_Shape aTopSh = theShape;
  if (aContext.IsNull())
  {
    TDF_Label aTopShL = theSTool->FindShape(theShape, Standard_False);
    if (aTopShL.IsNull())
      return Standard_False;
    aTopSh = XCAFDoc_ShapeTool::GetShape(aTopShL);
    aContext = aStyles.FindContext(aTopSh);
  }
  if (aContext.IsNull())
    return Standard_False;
  // get representation item of the shape
  TopLoc_Location aLocation;
  TColStd_SequenceOfTransient aSeqRI;
  FindEntities(aFP, theShape, aLocation, aSeqRI);
  if (aSeqRI.Length() <= 0)
    Message::SendTrace() << "Warning: Cannot find RI for " << theShape.TShape()->DynamicType()->Name() << "\n";
  anItem = Handle(StepRepr_RepresentationItem)::DownCast(aSeqRI(1));
  //get overridden styled item
  getStyledItem(theShape, theSTool, aStyles, anOverride, theMapCompMDGPR);

  // get STEP STYLED ITEM
  Handle(StepVisual_StyledItem) aSTEPstyle = aStyles.AddStyle(anItem, aPSA, anOverride);
  // create SR, SDR and all necessary references between them and ST, PDS, PSBC, GRC
  aStyles.CreateNAUOSRD(aContext, aCDSR, thePDS);

  // add step styled item of SHUO to the model
  // do it by additing styled item to the MDGPR
  if (!aTopSh.IsNull() && !theMapCompMDGPR.IsBound(aTopSh))
  {
    // create MDGPR and record it in model
    Message::SendTrace() << "Warning: " << __FILE__ << ": Create new MDGPR for SHUO instance" << "\n";
    Handle(StepVisual_MechanicalDesignGeometricPresentationRepresentation) aMDGPR;
    aStyles.CreateMDGPR(aContext, aMDGPR);
    if (!aMDGPR.IsNull())
      theMapCompMDGPR.Bind(aTopSh, aMDGPR);
  }
  else if (!aTopSh.IsNull() && theMapCompMDGPR.IsBound(aTopSh))
  {
    // get MDGPR of the top-level shape
    Handle(StepVisual_PresentationRepresentation) aMDGPR =
      Handle(StepVisual_PresentationRepresentation)::DownCast(theMapCompMDGPR.Find(aTopSh));
    // get old styled items to not lose it
    Handle(StepRepr_HArray1OfRepresentationItem) anOldItems = aMDGPR->Items();
    Standard_Integer anOldLengthlen = 0;
    if (!anOldItems.IsNull())
      anOldLengthlen = anOldItems->Length();
    // create new array of styled items by an olds and new one
    Handle(StepRepr_HArray1OfRepresentationItem) aNewItems =
      new StepRepr_HArray1OfRepresentationItem(1, anOldLengthlen + 1);
    Standard_Integer aSetStyleInd = 1;
    for (StepRepr_HArray1OfRepresentationItem::Iterator aStyleIter(anOldItems->Array1());
         aStyleIter.More(); aStyleIter.Next())
    {
      aNewItems->SetValue(aSetStyleInd++, aStyleIter.Value());
    }
    aNewItems->SetValue(aSetStyleInd++, aSTEPstyle);
    // init MDGPR be new array of styled items
    if (aNewItems->Length() > 0)
      aMDGPR->SetItems(aNewItems);
  }
  else
  {
    theWS->Model()->AddWithRefs(aSTEPstyle); // add as root to the model, but it is not good
    Message::SendTrace() << "Warning: " << __FILE__ << ": adds styled item of SHUO as root, cause cannot find MDGPR" << "\n";
  }
  // create invisibility item for the styled item
  if (!theStyle.IsVisible())
  {
    if (isSetDefaultColor)
    {
      // try to set default color from top-level shape

      setDefaultInstanceColor(anOverride, aPSA);
    }
    // create invisibility item and refer for styledItem
    Handle(StepVisual_Invisibility) aInvsblt = new StepVisual_Invisibility();
    Handle(StepVisual_HArray1OfInvisibleItem) aHInvsblItm =
      new StepVisual_HArray1OfInvisibleItem(1, 1);
    // put all style item into the harray
    StepVisual_InvisibleItem anInvItem;
    anInvItem.SetValue(aSTEPstyle);
    aHInvsblItm->SetValue(1, anInvItem);
    aInvsblt->Init(aHInvsblItm);
    theWS->Model()->AddWithRefs(aInvsblt);
  }

  return Standard_True;
}

//=======================================================================
//function : writeSHUOs
//purpose  :
//=======================================================================
Standard_Boolean STEPCAFControl_Writer::writeSHUOs(const Handle(XSControl_WorkSession)& theWS,
                                                   const TDF_LabelSequence& theLabels)
{
  if (theLabels.IsEmpty())
    return Standard_False;

  // map of transferred SHUO
  TColStd_MapOfTransient aMapOfMainSHUO;
  // Iterate on requested shapes
  for (TDF_LabelSequence::Iterator aLabelIter(theLabels);
       aLabelIter.More(); aLabelIter.Next())
  {
    const TDF_Label& aLabel = aLabelIter.Value();
    if (!myLabels.IsBound(aLabel))
      continue; // not recorded as translated, skip
    if (!XCAFDoc_ShapeTool::IsAssembly(aLabel))
    {
      continue;
    }
    TDF_LabelSequence aLabelSeq;
    XCAFDoc_ShapeTool::GetComponents(aLabel, aLabelSeq);
    // iterates on components of assembly
    for (TDF_LabelSequence::Iterator aCompIter(aLabelSeq);
         aCompIter.More(); aCompIter.Next())
    {
      const TDF_Label& aCompL = aCompIter.Value();
      TDF_AttributeSequence anAttrSeq;
      XCAFDoc_ShapeTool::GetAllComponentSHUO(aCompL, anAttrSeq);
      // work with SHUO
      for (TDF_AttributeSequence::Iterator anAttrIter(anAttrSeq);
           anAttrIter.More(); anAttrIter.Next())
      {
        Handle(XCAFDoc_GraphNode) aSHUO =
          Handle(XCAFDoc_GraphNode)::DownCast(anAttrIter.Value());
        // take label of SHUO
        TDF_Label aSHUOlab = aSHUO->Label();
        TDF_LabelSequence aUpLabels;
        // check is it SHUO of upper_usage
        XCAFDoc_ShapeTool::GetSHUOUpperUsage(aSHUOlab, aUpLabels);
        if (aUpLabels.Length() > 0)
          continue; // transfer only main SHUO
        if (aMapOfMainSHUO.Contains(aSHUO))
          continue; // do not try to transfer SHUO twice
        aMapOfMainSHUO.Add(aSHUO);
        // check if it is styled SHUO
        XCAFPrs_Style aSHUOstyle;
        if (!getSHUOstyle(aSHUOlab, aSHUOstyle))
        {
          Message::SendTrace() << "Warning: " << __FILE__ << ": do not store SHUO without any style to the STEP model" << "\n";
          continue;
        }
        // write SHUO to the model amd then add structure type.
        TopoDS_Shape aNAUOShape; // shape of the deepest NAUO in the SHUO structure
        Standard_Boolean isDeepest = Standard_False;
        Handle(StepRepr_SpecifiedHigherUsageOccurrence) anEntOfSHUO;
        Handle(StepBasic_ProductDefinition) aRelatingPD;
        // create the top SHUO and all other.
        writeSHUO(aSHUO, theWS, anEntOfSHUO, aNAUOShape, aRelatingPD, isDeepest);
        if (anEntOfSHUO.IsNull() || aNAUOShape.IsNull())
        {
          Message::SendTrace() << "Warning: " << __FILE__ << ": Cannot store SHUO" << "\n";
          continue;
        }
        // create new Product Definition Shape for TOP SHUO
        Message::SendTrace() << "Info: " << __FILE__ << ": Create NEW PDS for current SHUO " << "\n";
        Handle(StepRepr_ProductDefinitionShape) aPDS = new StepRepr_ProductDefinitionShape;
        Handle(TCollection_HAsciiString) aPDSname = new TCollection_HAsciiString("SHUO");
        Handle(TCollection_HAsciiString) aDescrStr = new TCollection_HAsciiString("");
        StepRepr_CharacterizedDefinition aCharDef;
        aCharDef.SetValue(anEntOfSHUO);
        aPDS->Init(aPDSname, Standard_False, aDescrStr, aCharDef);

        // create styled item for SHUO and add to the model
        createSHUOStyledItem(aSHUOstyle, aPDS, theWS, aNAUOShape, XCAFDoc_DocumentTool::ShapeTool(aLabel), myMapCompMDGPR);

      } // end work with SHUO
    } // end of an assembly components
>>>>>>> accb2f351 (u)
  } // end of iterates on indicated labels
  return Standard_True;
}

<<<<<<< HEAD

=======
>>>>>>> accb2f351 (u)
//=======================================================================
//function : FindPDSforDGT
//purpose  : auxiliary: find PDS for AdvancedFace or EdgeCurve for creation
//                     needed ShapeAspect in D&GT structure
//=======================================================================
<<<<<<< HEAD
static Standard_Boolean FindPDSforDGT(const Interface_Graph &aGraph,
                                      const Handle(Standard_Transient) &ent,
                                      Handle(StepRepr_ProductDefinitionShape) &PDS,
                                      Handle(StepRepr_RepresentationContext) &RC,
                                      Handle(StepShape_AdvancedFace) &AF,
                                      Handle(StepShape_EdgeCurve) &EC)
{
  if (ent.IsNull())
    return Standard_False;
  if( !ent->IsKind(STANDARD_TYPE(StepShape_EdgeCurve)) && 
      !ent->IsKind(STANDARD_TYPE(StepShape_AdvancedFace)) ) 
    return Standard_False;

  AF = Handle(StepShape_AdvancedFace)::DownCast(ent);
  if( AF.IsNull() ) {
    EC = Handle(StepShape_EdgeCurve)::DownCast(ent);
    Interface_EntityIterator subs = aGraph.Sharings(EC);
    for(subs.Start(); subs.More() && AF.IsNull(); subs.Next()) {
      Handle(StepShape_OrientedEdge) OE = Handle(StepShape_OrientedEdge)::DownCast(subs.Value());
      if(OE.IsNull()) continue;
      Interface_EntityIterator subs1 = aGraph.Sharings(OE);
      for(subs1.Start(); subs1.More() && AF.IsNull(); subs1.Next()) {
        Handle(StepShape_EdgeLoop) EL = Handle(StepShape_EdgeLoop)::DownCast(subs1.Value());
        if(EL.IsNull()) continue;
        Interface_EntityIterator subs2 = aGraph.Sharings(EL);
        for(subs2.Start(); subs2.More() && AF.IsNull(); subs2.Next()) {
          Handle(StepShape_FaceBound) FB = Handle(StepShape_FaceBound)::DownCast(subs2.Value());
          if(FB.IsNull()) continue;
          Interface_EntityIterator subs3 = aGraph.Sharings(FB);
          for(subs3.Start(); subs3.More() && AF.IsNull(); subs3.Next()) {
            AF = Handle(StepShape_AdvancedFace)::DownCast(subs3.Value());
=======
static Standard_Boolean FindPDSforDGT(const Interface_Graph& theGraph,
                                      const Handle(Standard_Transient)& theEnt,
                                      Handle(StepRepr_ProductDefinitionShape)& thePDS,
                                      Handle(StepRepr_RepresentationContext)& theRC,
                                      Handle(StepShape_AdvancedFace)& theAF,
                                      Handle(StepShape_EdgeCurve)& theEC)
{
  if (theEnt.IsNull())
    return Standard_False;
  if (!theEnt->IsKind(STANDARD_TYPE(StepShape_EdgeCurve)) &&
      !theEnt->IsKind(STANDARD_TYPE(StepShape_AdvancedFace)))
  {
    return Standard_False;
  }

  theAF = Handle(StepShape_AdvancedFace)::DownCast(theEnt);
  if (theAF.IsNull())
  {
    theEC = Handle(StepShape_EdgeCurve)::DownCast(theEnt);
    for (Interface_EntityIterator aSharingsIter = theGraph.Sharings(theEC);
         aSharingsIter.More() && theAF.IsNull(); aSharingsIter.Next())
    {
      Handle(StepShape_OrientedEdge) anOE = Handle(StepShape_OrientedEdge)::DownCast(aSharingsIter.Value());
      if (anOE.IsNull())
        continue;
      for (Interface_EntityIterator aSubs1 = theGraph.Sharings(anOE);
           aSubs1.More() && theAF.IsNull(); aSubs1.Next())
      {
        Handle(StepShape_EdgeLoop) aEL = Handle(StepShape_EdgeLoop)::DownCast(aSubs1.Value());
        if (aEL.IsNull())
          continue;
        for (Interface_EntityIterator aSubs2 = theGraph.Sharings(aEL);
             aSubs2.More() && theAF.IsNull(); aSubs2.Next())
        {
          Handle(StepShape_FaceBound) aFB = Handle(StepShape_FaceBound)::DownCast(aSubs2.Value());
          if (aFB.IsNull())
            continue;
          for (Interface_EntityIterator aSubs3 = theGraph.Sharings(aFB);
               aSubs3.More() && theAF.IsNull(); aSubs3.Next())
          {
            theAF = Handle(StepShape_AdvancedFace)::DownCast(aSubs3.Value());
>>>>>>> accb2f351 (u)
          }
        }
      }
    }
  }
<<<<<<< HEAD
  if(AF.IsNull()) return Standard_False;

  Interface_EntityIterator subs = aGraph.Sharings(AF);
  for(subs.Start(); subs.More() && PDS.IsNull(); subs.Next()) {
    Handle(StepShape_ConnectedFaceSet) CFS =
      Handle(StepShape_ConnectedFaceSet)::DownCast(subs.Value());
    if(CFS.IsNull()) continue;
    Interface_EntityIterator subs1 = aGraph.Sharings(CFS);
    for(subs1.Start(); subs1.More() && PDS.IsNull(); subs1.Next()) {
      Handle(StepRepr_RepresentationItem) RI = 
        Handle(StepRepr_RepresentationItem)::DownCast(subs1.Value());
      if(RI.IsNull()) continue;
      Interface_EntityIterator subs2 = aGraph.Sharings(RI);
      for(subs2.Start(); subs2.More() && PDS.IsNull(); subs2.Next()) {
        Handle(StepShape_ShapeRepresentation) SR = 
          Handle(StepShape_ShapeRepresentation)::DownCast(subs2.Value());
        if(SR.IsNull()) continue;
        RC = SR->ContextOfItems();
        Interface_EntityIterator subs3 = aGraph.Sharings(SR);
        for(subs3.Start(); subs3.More() && PDS.IsNull(); subs3.Next()) {
          Handle(StepShape_ShapeDefinitionRepresentation) SDR = 
            Handle(StepShape_ShapeDefinitionRepresentation)::DownCast(subs3.Value());
          if(SDR.IsNull()) continue;
          Handle(StepRepr_PropertyDefinition) PropD = SDR->Definition().PropertyDefinition();
          if(PropD.IsNull()) continue;
          PDS = Handle(StepRepr_ProductDefinitionShape)::DownCast(PropD);
=======
  if (theAF.IsNull())
    return Standard_False;

  for (Interface_EntityIterator aSharingsIter = theGraph.Sharings(theAF);
       aSharingsIter.More() && thePDS.IsNull(); aSharingsIter.Next())
  {
    Handle(StepShape_ConnectedFaceSet) aCFS =
      Handle(StepShape_ConnectedFaceSet)::DownCast(aSharingsIter.Value());
    if (aCFS.IsNull())
      continue;
    for (Interface_EntityIterator aSubs1 = theGraph.Sharings(aCFS);
         aSubs1.More() && thePDS.IsNull(); aSubs1.Next())
    {
      Handle(StepRepr_RepresentationItem) aRI =
        Handle(StepRepr_RepresentationItem)::DownCast(aSubs1.Value());
      if (aRI.IsNull())
        continue;
      for (Interface_EntityIterator aSubs2 = theGraph.Sharings(aRI);
           aSubs2.More() && thePDS.IsNull(); aSubs2.Next())
      {
        Handle(StepShape_ShapeRepresentation) aSR =
          Handle(StepShape_ShapeRepresentation)::DownCast(aSubs2.Value());
        if (aSR.IsNull())
          continue;
        theRC = aSR->ContextOfItems();
        for (Interface_EntityIterator aSubs3 = theGraph.Sharings(aSR);
             aSubs3.More() && thePDS.IsNull(); aSubs3.Next())
        {
          Handle(StepShape_ShapeDefinitionRepresentation) aSDR =
            Handle(StepShape_ShapeDefinitionRepresentation)::DownCast(aSubs3.Value());
          if (aSDR.IsNull())
            continue;
          Handle(StepRepr_PropertyDefinition) aPropD = aSDR->Definition().PropertyDefinition();
          if (aPropD.IsNull())
            continue;
          thePDS = Handle(StepRepr_ProductDefinitionShape)::DownCast(aPropD);
>>>>>>> accb2f351 (u)
        }
      }
    }
  }
<<<<<<< HEAD
  
=======
>>>>>>> accb2f351 (u)
  return Standard_True;
}

//=======================================================================
//function : FindPDS
//purpose  : auxiliary: find Product_definition_shape entity for given entity
//=======================================================================
<<<<<<< HEAD
static Handle(StepRepr_ProductDefinitionShape) FindPDS(const Interface_Graph &theGraph,
                                                       const Handle(Standard_Transient) &theEnt,
                                                       Handle(StepRepr_RepresentationContext) &theRC)
=======
static Handle(StepRepr_ProductDefinitionShape) FindPDS(const Interface_Graph& theGraph,
                                                       const Handle(Standard_Transient)& theEnt,
                                                       Handle(StepRepr_RepresentationContext)& theRC)
>>>>>>> accb2f351 (u)
{
  if (theEnt.IsNull())
    return NULL;
  Handle(StepRepr_ProductDefinitionShape) aPDS;

  // try to find shape_representation in sharings
<<<<<<< HEAD
  Interface_EntityIterator anIter = theGraph.Sharings(theEnt);
  for (anIter.Start(); anIter.More() && aPDS.IsNull(); anIter.Next()) {
=======
  for (Interface_EntityIterator anIter = theGraph.Sharings(theEnt);
       anIter.More() && aPDS.IsNull(); anIter.Next())
  {
>>>>>>> accb2f351 (u)
    Handle(StepShape_ShapeRepresentation) aSR = Handle(StepShape_ShapeRepresentation)::DownCast(anIter.Value());
    if (aSR.IsNull())
      continue;
    theRC = aSR->ContextOfItems();
    Interface_EntityIterator aSDRIt = theGraph.Sharings(aSR);
<<<<<<< HEAD
    for (aSDRIt.Start(); aSDRIt.More() && aPDS.IsNull(); aSDRIt.Next()) {
=======
    for (aSDRIt.Start(); aSDRIt.More() && aPDS.IsNull(); aSDRIt.Next())
    {
>>>>>>> accb2f351 (u)
      Handle(StepShape_ShapeDefinitionRepresentation) aSDR =
        Handle(StepShape_ShapeDefinitionRepresentation)::DownCast(aSDRIt.Value());
      if (aSDR.IsNull()) continue;
      Handle(StepRepr_PropertyDefinition) aPropD = aSDR->Definition().PropertyDefinition();
      if (aPropD.IsNull()) continue;
      aPDS = Handle(StepRepr_ProductDefinitionShape)::DownCast(aPropD);
    }
  }
  if (!aPDS.IsNull())
    return aPDS;

<<<<<<< HEAD
  anIter = theGraph.Sharings(theEnt);
  for (anIter.Start(); anIter.More(); anIter.Next()) {
    if (anIter.Value()->IsKind(STANDARD_TYPE(StepShape_TopologicalRepresentationItem)) ||
      anIter.Value()->IsKind(STANDARD_TYPE(StepGeom_GeometricRepresentationItem)))
=======
  for (Interface_EntityIterator anIter = theGraph.Sharings(theEnt);
       anIter.More(); anIter.Next())
  {
    if (anIter.Value()->IsKind(STANDARD_TYPE(StepShape_TopologicalRepresentationItem)) ||
        anIter.Value()->IsKind(STANDARD_TYPE(StepGeom_GeometricRepresentationItem)))
>>>>>>> accb2f351 (u)
    {
      aPDS = FindPDS(theGraph, anIter.Value(), theRC);
      if (!aPDS.IsNull())
        return aPDS;
    }
  }
<<<<<<< HEAD

=======
>>>>>>> accb2f351 (u)
  return aPDS;
}

//=======================================================================
//function : GetUnit
//purpose  : auxiliary
//=======================================================================
static StepBasic_Unit GetUnit(const Handle(StepRepr_RepresentationContext)& theRC,
<<<<<<< HEAD
                              const Standard_Boolean isAngle = Standard_False)
{
  StepBasic_Unit aUnit;
  Handle(StepBasic_NamedUnit) aCurrentUnit;
  if (isAngle) {
    Handle(StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext) aCtx =
      Handle(StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext)::DownCast(theRC);
    if(!aCtx.IsNull()) {
      for(Standard_Integer j = 1; j <= aCtx->NbUnits(); j++) {
        if (aCtx->UnitsValue(j)->IsKind(STANDARD_TYPE(StepBasic_SiUnitAndPlaneAngleUnit)) ||
            aCtx->UnitsValue(j)->IsKind(STANDARD_TYPE(StepBasic_ConversionBasedUnitAndPlaneAngleUnit))) {
          aCurrentUnit = aCtx->UnitsValue(j);
=======
                              const Standard_Boolean theIsAngle = Standard_False)
{
  StepBasic_Unit aUnit;
  Handle(StepBasic_NamedUnit) aCurrentUnit;
  if (theIsAngle)
  {
    Handle(StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext) aCtx =
      Handle(StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext)::DownCast(theRC);
    if (!aCtx.IsNull())
    {
      for (StepBasic_HArray1OfNamedUnit::Iterator aUnitIter(aCtx->Units()->Array1());
           aUnitIter.More(); aUnitIter.Next())
      {
        const Handle(StepBasic_NamedUnit)& aCurUnitValue = aUnitIter.Value();
        if (aCurUnitValue->IsKind(STANDARD_TYPE(StepBasic_SiUnitAndPlaneAngleUnit)) ||
            aCurUnitValue->IsKind(STANDARD_TYPE(StepBasic_ConversionBasedUnitAndPlaneAngleUnit)))
        {
          aCurrentUnit = aCurUnitValue;
>>>>>>> accb2f351 (u)
          break;
        }
      }
    }
<<<<<<< HEAD
    if (aCurrentUnit.IsNull()) {
      Handle(StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx) aCtx1 =
        Handle(StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx)::DownCast(theRC);
      if(!aCtx1.IsNull()) {
        for(Standard_Integer j = 1; j <= aCtx1->NbUnits(); j++) {
          if (aCtx1->UnitsValue(j)->IsKind(STANDARD_TYPE(StepBasic_SiUnitAndPlaneAngleUnit)) ||
              aCtx1->UnitsValue(j)->IsKind(STANDARD_TYPE(StepBasic_ConversionBasedUnitAndPlaneAngleUnit))) {
            aCurrentUnit = aCtx1->UnitsValue(j);
=======
    if (aCurrentUnit.IsNull())
    {
      Handle(StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx) aCtx1 =
        Handle(StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx)::DownCast(theRC);
      if (!aCtx1.IsNull())
      {
        for (StepBasic_HArray1OfNamedUnit::Iterator aUnitIter(aCtx1->Units()->Array1());
             aUnitIter.More(); aUnitIter.Next())
        {
          const Handle(StepBasic_NamedUnit)& aCurUnitValue = aUnitIter.Value();
          if (aCurUnitValue->IsKind(STANDARD_TYPE(StepBasic_SiUnitAndPlaneAngleUnit)) ||
              aCurUnitValue->IsKind(STANDARD_TYPE(StepBasic_ConversionBasedUnitAndPlaneAngleUnit)))
          {
            aCurrentUnit = aCurUnitValue;
>>>>>>> accb2f351 (u)
            break;
          }
        }
      }
    }
    if (aCurrentUnit.IsNull())
      aCurrentUnit = new StepBasic_SiUnitAndPlaneAngleUnit;
  }
<<<<<<< HEAD
  else {
    Handle(StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext) aCtx =
      Handle(StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext)::DownCast(theRC);
    if(!aCtx.IsNull()) {
      for(Standard_Integer j = 1; j <= aCtx->NbUnits(); j++) {
        if (aCtx->UnitsValue(j)->IsKind(STANDARD_TYPE(StepBasic_SiUnitAndLengthUnit)) ||
            aCtx->UnitsValue(j)->IsKind(STANDARD_TYPE(StepBasic_ConversionBasedUnitAndLengthUnit))) {
          aCurrentUnit = aCtx->UnitsValue(j);
=======
  else
  {
    Handle(StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext) aCtx =
      Handle(StepGeom_GeometricRepresentationContextAndGlobalUnitAssignedContext)::DownCast(theRC);
    if (!aCtx.IsNull())
    {
      for (StepBasic_HArray1OfNamedUnit::Iterator aUnitIter(aCtx->Units()->Array1());
           aUnitIter.More(); aUnitIter.Next())
      {
        const Handle(StepBasic_NamedUnit)& aCurUnitValue = aUnitIter.Value();
        if (aCurUnitValue->IsKind(STANDARD_TYPE(StepBasic_SiUnitAndLengthUnit)) ||
            aCurUnitValue->IsKind(STANDARD_TYPE(StepBasic_ConversionBasedUnitAndLengthUnit)))
        {
          aCurrentUnit = aCurUnitValue;
>>>>>>> accb2f351 (u)
          break;
        }
      }
    }
<<<<<<< HEAD
    if (aCurrentUnit.IsNull()) {
      Handle(StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx) aCtx1 =
        Handle(StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx)::DownCast(theRC);
      if(!aCtx1.IsNull()) {
        for(Standard_Integer j = 1; j <= aCtx1->NbUnits(); j++) {
          if (aCtx1->UnitsValue(j)->IsKind(STANDARD_TYPE(StepBasic_SiUnitAndLengthUnit)) ||
              aCtx1->UnitsValue(j)->IsKind(STANDARD_TYPE(StepBasic_ConversionBasedUnitAndLengthUnit))) {
            aCurrentUnit = aCtx1->UnitsValue(j);
=======
    if (aCurrentUnit.IsNull())
    {
      Handle(StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx) aCtx1 =
        Handle(StepGeom_GeomRepContextAndGlobUnitAssCtxAndGlobUncertaintyAssCtx)::DownCast(theRC);
      if (!aCtx1.IsNull())
      {
        for (StepBasic_HArray1OfNamedUnit::Iterator aUnitIter(aCtx1->Units()->Array1());
             aUnitIter.More(); aUnitIter.Next())
        {
          const Handle(StepBasic_NamedUnit)& aCurUnitValue = aUnitIter.Value();
          if (aCurUnitValue->IsKind(STANDARD_TYPE(StepBasic_SiUnitAndLengthUnit)) ||
              aCurUnitValue->IsKind(STANDARD_TYPE(StepBasic_ConversionBasedUnitAndLengthUnit)))
          {
            aCurrentUnit = aCurUnitValue;
>>>>>>> accb2f351 (u)
            break;
          }
        }
      }
    }
    if (aCurrentUnit.IsNull())
      aCurrentUnit = new StepBasic_SiUnitAndLengthUnit;
  }

  aUnit.SetValue(aCurrentUnit);
  return aUnit;
}

//=======================================================================
//function : CreateDimValue
//purpose  : auxiliary
//======================================================================
static Handle(StepRepr_ReprItemAndMeasureWithUnit) CreateDimValue(const Standard_Real theValue,
<<<<<<< HEAD
                                                                  const StepBasic_Unit theUnit,
                                                                  const Handle(TCollection_HAsciiString)& theName,
                                                                  const Standard_CString theMeasureName,
                                                                  const Standard_Boolean isAngle,
                                                                  const Standard_Boolean isQualified = Standard_False,
=======
                                                                  const StepBasic_Unit& theUnit,
                                                                  const Handle(TCollection_HAsciiString)& theName,
                                                                  const Standard_CString theMeasureName,
                                                                  const Standard_Boolean theIsAngle,
                                                                  const Standard_Boolean theIsQualified = Standard_False,
>>>>>>> accb2f351 (u)
                                                                  const Handle(StepShape_QualifiedRepresentationItem)& theQRI = NULL)
{
  Handle(StepRepr_RepresentationItem) aReprItem = new StepRepr_RepresentationItem();
  aReprItem->Init(new TCollection_HAsciiString(theName));
  Handle(StepBasic_MeasureWithUnit) aMWU = new StepBasic_MeasureWithUnit();
  Handle(StepBasic_MeasureValueMember) aValueMember = new StepBasic_MeasureValueMember();
  aValueMember->SetName(theMeasureName);
  aValueMember->SetReal(theValue);
  aMWU->Init(aValueMember, theUnit);
<<<<<<< HEAD
  if (isQualified) {
    if (isAngle) {
      // Angle & with qualifiers
      Handle(StepRepr_ReprItemAndPlaneAngleMeasureWithUnitAndQRI) anItem = 
=======
  if (theIsQualified)
  {
    if (theIsAngle)
    {
      // Angle & with qualifiers
      Handle(StepRepr_ReprItemAndPlaneAngleMeasureWithUnitAndQRI) anItem =
>>>>>>> accb2f351 (u)
        new StepRepr_ReprItemAndPlaneAngleMeasureWithUnitAndQRI();
      anItem->Init(aMWU, aReprItem, theQRI);
      return anItem;
    }
<<<<<<< HEAD
    else {
      // Length & with qualifiers
      Handle(StepRepr_ReprItemAndLengthMeasureWithUnitAndQRI) anItem = 
=======
    else
    {
      // Length & with qualifiers
      Handle(StepRepr_ReprItemAndLengthMeasureWithUnitAndQRI) anItem =
>>>>>>> accb2f351 (u)
        new StepRepr_ReprItemAndLengthMeasureWithUnitAndQRI();
      anItem->Init(aMWU, aReprItem, theQRI);
      return anItem;
    }
  }
<<<<<<< HEAD
  else {
    if (isAngle) {
      // Angle & without qualifiers
      Handle(StepRepr_ReprItemAndPlaneAngleMeasureWithUnit) anItem = 
=======
  else
  {
    if (theIsAngle)
    {
      // Angle & without qualifiers
      Handle(StepRepr_ReprItemAndPlaneAngleMeasureWithUnit) anItem =
>>>>>>> accb2f351 (u)
        new StepRepr_ReprItemAndPlaneAngleMeasureWithUnit();
      anItem->Init(aMWU, aReprItem);
      return anItem;
    }
<<<<<<< HEAD
    else {
      // Length & without qualifiers
      Handle(StepRepr_ReprItemAndLengthMeasureWithUnit) anItem = 
=======
    else
    {
      // Length & without qualifiers
      Handle(StepRepr_ReprItemAndLengthMeasureWithUnit) anItem =
>>>>>>> accb2f351 (u)
        new StepRepr_ReprItemAndLengthMeasureWithUnit();
      anItem->Init(aMWU, aReprItem);
      return anItem;
    }
  }
}

//=======================================================================
<<<<<<< HEAD
//function : WriteShapeAspect
//purpose  : auxiliary (write Shape_Aspect entity for given shape)
//=======================================================================

Handle(StepRepr_ShapeAspect) STEPCAFControl_Writer::WriteShapeAspect (const Handle(XSControl_WorkSession) &WS,
                                                                      const TDF_Label theLabel,
                                                                      const TopoDS_Shape theShape,
                                                                      Handle(StepRepr_RepresentationContext)& theRC,
                                                                      Handle(StepAP242_GeometricItemSpecificUsage)& theGISU)
{
  // Get working data
  const Handle(Interface_InterfaceModel) &Model = WS->Model();
  const Handle(XSControl_TransferWriter) &TW = WS->TransferWriter();
  const Handle(Transfer_FinderProcess) &FP = TW->FinderProcess();
  const Handle(Interface_HGraph) aHGraph = WS->HGraph();
=======
//function : writeShapeAspect
//purpose  : auxiliary (write Shape_Aspect entity for given shape)
//=======================================================================
Handle(StepRepr_ShapeAspect) STEPCAFControl_Writer::writeShapeAspect(const Handle(XSControl_WorkSession)& theWS,
                                                                     const TDF_Label theLabel,
                                                                     const TopoDS_Shape& theShape,
                                                                     Handle(StepRepr_RepresentationContext)& theRC,
                                                                     Handle(StepAP242_GeometricItemSpecificUsage)& theGISU)
{
  // Get working data
  const Handle(Interface_InterfaceModel)& aModel = theWS->Model();
  const Handle(XSControl_TransferWriter)& aTW = theWS->TransferWriter();
  const Handle(Transfer_FinderProcess)& aFP = aTW->FinderProcess();
  const Handle(Interface_HGraph) aHGraph = theWS->HGraph();
>>>>>>> accb2f351 (u)
  if (aHGraph.IsNull())
    return NULL;
  Interface_Graph aGraph = aHGraph->Graph();

  TopLoc_Location aLoc;
  TColStd_SequenceOfTransient aSeqRI;
<<<<<<< HEAD
  FindEntities( FP, theShape, aLoc, aSeqRI );
  if ( aSeqRI.Length() <= 0 ) {
    FP->Messenger()->SendInfo() << "Warning: Cannot find RI for "<<theShape.TShape()->DynamicType()->Name()<<std::endl;
=======
  FindEntities(aFP, theShape, aLoc, aSeqRI);
  if (aSeqRI.Length() <= 0)
  {
    Message::SendTrace() << "Warning: Cannot find RI for " << theShape.TShape()->DynamicType()->Name() << "\n";
>>>>>>> accb2f351 (u)
    return NULL;
  }

  Handle(StepRepr_ProductDefinitionShape) aPDS;
  Handle(StepRepr_RepresentationContext) aRC;
  Handle(Standard_Transient) anEnt = aSeqRI.Value(1);
  aPDS = FindPDS(aGraph, anEnt, aRC);
<<<<<<< HEAD
  if(aPDS.IsNull()) 
=======
  if (aPDS.IsNull())
>>>>>>> accb2f351 (u)
    return NULL;

  theRC = aRC;
  // Shape_Aspect
  Handle(TCollection_HAsciiString) aName = new TCollection_HAsciiString();
  Handle(TDataStd_Name) aNameAttr;
<<<<<<< HEAD
  if (theLabel.FindAttribute(TDataStd_Name::GetID(), aNameAttr)) {
=======
  if (theLabel.FindAttribute(TDataStd_Name::GetID(), aNameAttr))
  {
>>>>>>> accb2f351 (u)
    aName = new TCollection_HAsciiString(TCollection_AsciiString(aNameAttr->Get()));
    Standard_Integer aFirstSpace = aName->Search(" ");
    if (aFirstSpace != -1)
      aName = aName->SubString(aFirstSpace + 1, aName->Length());
    else
      aName = new TCollection_HAsciiString();
  }
  Handle(TCollection_HAsciiString) aDescription = new TCollection_HAsciiString();
  Handle(StepRepr_ShapeAspect) aSA = new StepRepr_ShapeAspect;
  aSA->Init(aName, aDescription, aPDS, StepData_LTrue);

  // Geometric_Item_Specific_Usage
  Handle(StepAP242_GeometricItemSpecificUsage) aGISU = new StepAP242_GeometricItemSpecificUsage();
  StepAP242_ItemIdentifiedRepresentationUsageDefinition aDefinition;
  aDefinition.SetValue(aSA);
  Handle(StepRepr_HArray1OfRepresentationItem) anReprItems = new StepRepr_HArray1OfRepresentationItem(1, 1);
  Handle(StepRepr_RepresentationItem) anIdentifiedItem = Handle(StepRepr_RepresentationItem)::DownCast(anEnt);
  anReprItems->SetValue(1, anIdentifiedItem);
<<<<<<< HEAD
  Interface_EntityIterator subs = aGraph.Sharings(aPDS);
  Handle(StepShape_ShapeDefinitionRepresentation) aSDR;
  for (subs.Start(); subs.More() && aSDR.IsNull(); subs.Next()) {
    Handle(Standard_Transient) anEntity = subs.Value();
=======
  Handle(StepShape_ShapeDefinitionRepresentation) aSDR;
  for (Interface_EntityIterator aSharingIter = aGraph.Sharings(aPDS);
       aSharingIter.More() && aSDR.IsNull(); aSharingIter.Next())
  {
    const Handle(Standard_Transient)& anEntity = aSharingIter.Value();
>>>>>>> accb2f351 (u)
    aSDR = Handle(StepShape_ShapeDefinitionRepresentation)::DownCast(anEntity);
  }
  if (aSDR.IsNull())
    return NULL;

  // Set entities to model
  aGISU->Init(aName, aDescription, aDefinition, aSDR->UsedRepresentation(), anReprItems);
<<<<<<< HEAD
  Model->AddWithRefs(aSA);
  Model->AddWithRefs(aGISU);
=======
  aModel->AddWithRefs(aSA);
  aModel->AddWithRefs(aGISU);
>>>>>>> accb2f351 (u)
  theGISU = aGISU;
  return aSA;
}

//=======================================================================
<<<<<<< HEAD
//function : WritePresentation
//purpose  : auxiliary (write annotation plane and presentation)
//======================================================================
void STEPCAFControl_Writer::WritePresentation(const Handle(XSControl_WorkSession)& WS,
                                              const TopoDS_Shape& thePresentation,
                                              const Handle(TCollection_HAsciiString)& thePrsName,
                                              const Standard_Boolean hasSemantic,
                                              const Standard_Boolean hasPlane,
                                              const gp_Ax2& theAnnotationPlane,
                                              const gp_Pnt& theTextPosition,
                                              const Handle(Standard_Transient) theDimension)
=======
//function : writePresentation
//purpose  : auxiliary (write annotation plane and presentation)
//======================================================================
void STEPCAFControl_Writer::writePresentation(const Handle(XSControl_WorkSession)& theWS,
                                              const TopoDS_Shape& thePresentation,
                                              const Handle(TCollection_HAsciiString)& thePrsName,
                                              const Standard_Boolean theHasSemantic,
                                              const Standard_Boolean theHasPlane,
                                              const gp_Ax2& theAnnotationPlane,
                                              const gp_Pnt& theTextPosition,
                                              const Handle(Standard_Transient)& theDimension)
>>>>>>> accb2f351 (u)
{
  if (thePresentation.IsNull())
    return;
  // Get working data
<<<<<<< HEAD
  const Handle(Interface_InterfaceModel) &aModel = WS->Model();
=======
  const Handle(Interface_InterfaceModel)& aModel = theWS->Model();
>>>>>>> accb2f351 (u)

  // Presentation
  Handle(StepVisual_TessellatedGeometricSet) aGeomSet = STEPCAFControl_GDTProperty::GetTessellation(thePresentation);
  Handle(StepVisual_TessellatedAnnotationOccurrence) aTAO = new StepVisual_TessellatedAnnotationOccurrence();
  aTAO->Init(new TCollection_HAsciiString(), myGDTPrsCurveStyle, aGeomSet);
  StepVisual_DraughtingCalloutElement aDCElement;
  aDCElement.SetValue(aTAO);
  Handle(StepVisual_HArray1OfDraughtingCalloutElement) aTAOs = new StepVisual_HArray1OfDraughtingCalloutElement(1, 1);
  aTAOs->SetValue(1, aDCElement);
  Handle(StepVisual_DraughtingCallout) aDCallout = new StepVisual_DraughtingCallout();
  Handle(TCollection_HAsciiString) aPrsName = thePrsName.IsNull() ? new TCollection_HAsciiString() : thePrsName;
  aDCallout->Init(aPrsName, aTAOs);
  Handle(StepRepr_HArray1OfRepresentationItem) aDCsForDMIA = new StepRepr_HArray1OfRepresentationItem(1, 1);
  aDCsForDMIA->SetValue(1, aDCallout);
  myGDTAnnotations.Append(aDCallout);
  StepAP242_ItemIdentifiedRepresentationUsageDefinition aDimension;
  aDimension.SetValue(theDimension);
  Handle(TCollection_HAsciiString) aDMIAName;
<<<<<<< HEAD
  if (hasSemantic)
=======
  if (theHasSemantic)
>>>>>>> accb2f351 (u)
    aDMIAName = new TCollection_HAsciiString("PMI representation to presentation link");
  else
    aDMIAName = new TCollection_HAsciiString();
  Handle(StepAP242_DraughtingModelItemAssociation) aDMIA =
    new StepAP242_DraughtingModelItemAssociation();
  aDMIA->Init(aDMIAName, new TCollection_HAsciiString(), aDimension, myGDTPresentationDM, aDCsForDMIA);
  aModel->AddWithRefs(aDMIA);

<<<<<<< HEAD
  if (!hasPlane)
=======
  if (!theHasPlane)
>>>>>>> accb2f351 (u)
    return;

  // Annotation plane
  // Presentation Style
  Handle(StepVisual_NullStyleMember) aNullStyle = new StepVisual_NullStyleMember();
  aNullStyle->SetEnumText(0, ".NULL.");
  StepVisual_PresentationStyleSelect aStyleItem;
  aStyleItem.SetValue(aNullStyle);
  Handle(StepVisual_HArray1OfPresentationStyleSelect) aStyles = new StepVisual_HArray1OfPresentationStyleSelect(1, 1);
  aStyles->SetValue(1, aStyleItem);
  Handle(StepVisual_PresentationStyleAssignment) aPrsStyle = new StepVisual_PresentationStyleAssignment();
  aPrsStyle->Init(aStyles);
  Handle(StepVisual_HArray1OfPresentationStyleAssignment) aPrsStyles =
    new StepVisual_HArray1OfPresentationStyleAssignment(1, 1);
  aPrsStyles->SetValue(1, aPrsStyle);
  // Plane
  Handle(StepGeom_Plane) aPlane = new StepGeom_Plane();
  GeomToStep_MakeAxis2Placement3d anAxisMaker(theAnnotationPlane);
<<<<<<< HEAD
  Handle(StepGeom_Axis2Placement3d) anAxis = anAxisMaker.Value();
=======
  const Handle(StepGeom_Axis2Placement3d)& anAxis = anAxisMaker.Value();
>>>>>>> accb2f351 (u)
  // Set text position to plane origin
  Handle(StepGeom_CartesianPoint) aTextPos = new StepGeom_CartesianPoint();
  Handle(TColStd_HArray1OfReal) aCoords = new TColStd_HArray1OfReal(1, 3);
  for (Standard_Integer i = 1; i <= 3; i++)
    aCoords->SetValue(i, theTextPosition.Coord(i));
  aTextPos->Init(new TCollection_HAsciiString(), aCoords);
  anAxis->SetLocation(aTextPos);
  aPlane->Init(new TCollection_HAsciiString(), anAxis);
  // Annotation plane element
  StepVisual_AnnotationPlaneElement aPlaneElement;
  aPlaneElement.SetValue(aDCallout);
  Handle(StepVisual_HArray1OfAnnotationPlaneElement) aDCsForAnnPln = new StepVisual_HArray1OfAnnotationPlaneElement(1, 1);
  aDCsForAnnPln->SetValue(1, aPlaneElement);
  // Init AnnotationPlane entity
  Handle(StepVisual_AnnotationPlane) anAnnPlane = new StepVisual_AnnotationPlane();
  anAnnPlane->Init(new TCollection_HAsciiString(), aPrsStyles, aPlane, aDCsForAnnPln);
  myGDTAnnotations.Append(anAnnPlane);
  aModel->AddWithRefs(anAnnPlane);
}

//=======================================================================
<<<<<<< HEAD
//function : WriteDatumAP242
//purpose  : auxiliary (write Datum entity for given shape or write all 
//           necessary entities and link them to already written datum 
//           in case of multiple features association)
//=======================================================================
Handle(StepDimTol_Datum) STEPCAFControl_Writer::WriteDatumAP242(const Handle(XSControl_WorkSession)& WS,
                                                                const TDF_LabelSequence& theShapeL,
                                                                const TDF_Label& theDatumL,
                                                                const Standard_Boolean isFirstDTarget,
                                                                const Handle(StepDimTol_Datum) theWrittenDatum)
{
  // Get working data
  const Handle(Interface_InterfaceModel) &Model = WS->Model();
  const Handle(XSControl_TransferWriter) &TW = WS->TransferWriter();
  const Handle(Transfer_FinderProcess) &FP = TW->FinderProcess();
  const Handle(Interface_HGraph) aHGraph = WS->HGraph();
=======
//function : writeDatumAP242
//purpose  : auxiliary (write Datum entity for given shape or write all
//           necessary entities and link them to already written datum
//           in case of multiple features association)
//=======================================================================
Handle(StepDimTol_Datum) STEPCAFControl_Writer::writeDatumAP242(const Handle(XSControl_WorkSession)& theWS,
                                                                const TDF_LabelSequence& theShapeL,
                                                                const TDF_Label& theDatumL,
                                                                const Standard_Boolean theIsFirstDTarget,
                                                                const Handle(StepDimTol_Datum)& theWrittenDatum)
{
  // Get working data
  const Handle(Interface_InterfaceModel)& aModel = theWS->Model();
  const Handle(XSControl_TransferWriter)& aTW = theWS->TransferWriter();
  const Handle(Transfer_FinderProcess)& aFP = aTW->FinderProcess();
  const Handle(Interface_HGraph) aHGraph = theWS->HGraph();
>>>>>>> accb2f351 (u)
  if (aHGraph.IsNull())
    return NULL;
  Interface_Graph aGraph = aHGraph->Graph();

  Handle(StepRepr_ShapeAspect) aSA;
  Handle(StepRepr_RepresentationContext) aRC;
  Handle(StepRepr_ProductDefinitionShape) aPDS;
  NCollection_Sequence<Handle(StepRepr_ShapeAspect)> aSASeq;
  Handle(StepAP242_GeometricItemSpecificUsage) aGISU;
  Standard_Integer aSANum = 0, aGISUNum = 0;
  // Link with datum feature
<<<<<<< HEAD
  for (Standard_Integer i = 1; i <= theShapeL.Length(); i++) {
    Handle(Standard_Transient) anEnt;
    TopoDS_Shape aShape;
    TopLoc_Location aLoc;
    TColStd_SequenceOfTransient aSeqRI;

    aShape = XCAFDoc_ShapeTool::GetShape(theShapeL.Value(i));
    FindEntities(FP, aShape, aLoc, aSeqRI);
    if (aSeqRI.Length() <= 0) {
      FP->Messenger()->SendInfo() << "Warning: Cannot find RI for " << aShape.TShape()->DynamicType()->Name() << std::endl;
=======
  for (TDF_LabelSequence::Iterator aLabelIter(theShapeL);
       aLabelIter.More(); aLabelIter.Next())
  {
    Handle(Standard_Transient) anEnt;
    TopLoc_Location aLoc;
    TColStd_SequenceOfTransient aSeqRI;

    TopoDS_Shape aShape = XCAFDoc_ShapeTool::GetShape(aLabelIter.Value());
    FindEntities(aFP, aShape, aLoc, aSeqRI);
    if (aSeqRI.Length() <= 0)
    {
      Message::SendTrace() << "Warning: Cannot find RI for " << aShape.TShape()->DynamicType()->Name() << "\n";
>>>>>>> accb2f351 (u)
      continue;
    }
    anEnt = aSeqRI.Value(1);
    aPDS = FindPDS(aGraph, anEnt, aRC);
    if (aPDS.IsNull())
      continue;

<<<<<<< HEAD
    Handle(StepRepr_ShapeAspect) aCurrentSA = WriteShapeAspect(WS, theDatumL, aShape, aRC, aGISU);
    if (aCurrentSA.IsNull())
      continue;
    aSASeq.Append(aCurrentSA);
    aSANum = Model->Number(aCurrentSA);
    aGISUNum = Model->Number(aGISU);
  }
  if (aPDS.IsNull()) {
=======
    Handle(StepRepr_ShapeAspect) aCurrentSA = writeShapeAspect(theWS, theDatumL, aShape, aRC, aGISU);
    if (aCurrentSA.IsNull())
      continue;
    aSASeq.Append(aCurrentSA);
    aSANum = aModel->Number(aCurrentSA);
    aGISUNum = aModel->Number(aGISU);
  }
  if (aPDS.IsNull())
  {
>>>>>>> accb2f351 (u)
    // Workaround for datums without shape
    aPDS = myGDTCommonPDS;
    Interface_EntityIterator aSDRIt = aGraph.Sharings(aPDS);
    Handle(StepShape_ShapeDefinitionRepresentation) aSDR;
    for (aSDRIt.Start(); aSDRIt.More() && aSDR.IsNull(); aSDRIt.Next())
      aSDR = Handle(StepShape_ShapeDefinitionRepresentation)::DownCast(aSDRIt.Value());
<<<<<<< HEAD
    if (!aSDR.IsNull()) {
=======
    if (!aSDR.IsNull())
    {
>>>>>>> accb2f351 (u)
      Handle(StepRepr_Representation) aRepr = aSDR->UsedRepresentation();
      if (!aRepr.IsNull())
        aRC = aRepr->ContextOfItems();
    }
  }

<<<<<<< HEAD

  // Find if datum has datum targets and get common datum attributes
  Handle(XCAFDoc_Datum) aDatumAttr;
  if (!theDatumL.FindAttribute(XCAFDoc_Datum::GetID(), aDatumAttr)) 
=======
  // Find if datum has datum targets and get common datum attributes
  Handle(XCAFDoc_Datum) aDatumAttr;
  if (!theDatumL.FindAttribute(XCAFDoc_Datum::GetID(), aDatumAttr))
>>>>>>> accb2f351 (u)
    return NULL;
  Handle(XCAFDimTolObjects_DatumObject) anObject = aDatumAttr->GetObject();
  if (anObject.IsNull())
    return NULL;
  Standard_Boolean isSimpleDatum = !anObject->IsDatumTarget();
  Handle(TCollection_HAsciiString) anIdentifier = anObject->GetName();
<<<<<<< HEAD
  Handle(TCollection_HAsciiString) aTargetId = (anObject->GetDatumTargetNumber() == 0 ? 
    new TCollection_HAsciiString() : new TCollection_HAsciiString(anObject->GetDatumTargetNumber()));

  // If datum type is area, but there is no area in object, write as simple datum
  if (anObject->GetDatumTargetType() == XCAFDimTolObjects_DatumTargetType_Area &&
    anObject->GetDatumTarget().IsNull())
    isSimpleDatum = Standard_True;

  // Simple datum
  if (isSimpleDatum) {
    if (aSASeq.Length() == 0) {
=======
  Handle(TCollection_HAsciiString) aTargetId = (anObject->GetDatumTargetNumber() == 0 ?
                                                new TCollection_HAsciiString() : new TCollection_HAsciiString(anObject->GetDatumTargetNumber()));

  // If datum type is area, but there is no area in object, write as simple datum
  if (anObject->GetDatumTargetType() == XCAFDimTolObjects_DatumTargetType_Area &&
      anObject->GetDatumTarget().IsNull())
    isSimpleDatum = Standard_True;

  // Simple datum
  if (isSimpleDatum)
  {
    if (aSASeq.Length() == 0)
    {
>>>>>>> accb2f351 (u)
      // Create empty datum with name and presentation only
      Handle(StepDimTol_DatumFeature) aDF = new StepDimTol_DatumFeature();
      aDF->Init(new TCollection_HAsciiString(), new TCollection_HAsciiString(), aPDS, StepData_LTrue);
      aSA = aDF;
<<<<<<< HEAD
      Model->AddWithRefs(aDF);
    }
    else if (aSASeq.Length() == 1) {
      Handle(StepDimTol_DatumFeature) aDF = new StepDimTol_DatumFeature();
      aDF->Init(new TCollection_HAsciiString(), new TCollection_HAsciiString(), aPDS, StepData_LTrue);
      Model->ReplaceEntity(aSANum, aDF);
=======
      aModel->AddWithRefs(aDF);
    }
    else if (aSASeq.Length() == 1)
    {
      Handle(StepDimTol_DatumFeature) aDF = new StepDimTol_DatumFeature();
      aDF->Init(new TCollection_HAsciiString(), new TCollection_HAsciiString(), aPDS, StepData_LTrue);
      aModel->ReplaceEntity(aSANum, aDF);
>>>>>>> accb2f351 (u)
      aSA = aDF;
      StepAP242_ItemIdentifiedRepresentationUsageDefinition aDefinition;
      aDefinition.SetValue(aDF);
      aGISU->SetDefinition(aDefinition);
<<<<<<< HEAD
      Model->ReplaceEntity(aGISUNum, aGISU);
    }
    else if (aSASeq.Length() > 1) {
      Handle(StepRepr_CompShAspAndDatumFeatAndShAsp) aDF = new StepRepr_CompShAspAndDatumFeatAndShAsp();
      aDF->Init(new TCollection_HAsciiString(), new TCollection_HAsciiString(), aPDS, StepData_LTrue);
      for (Standard_Integer i = 1; i <= aSASeq.Length(); i++) {
        Handle(StepRepr_ShapeAspectRelationship) aSAR = new StepRepr_ShapeAspectRelationship();
        aSAR->Init(new TCollection_HAsciiString(), Standard_False, new TCollection_HAsciiString(), aDF, aSASeq.Value(i));
        Model->AddWithRefs(aSAR);
      }
      aSA = aDF;
      Model->AddWithRefs(aDF);
    }
  }
  // Datum with datum targets
  else {
    XCAFDimTolObjects_DatumTargetType aDatumType = anObject->GetDatumTargetType();
    Handle(StepDimTol_DatumTarget) aDatumTarget;
    // Note: the given way to write such datum type may be incorrect (too little information)
    if (aDatumType == XCAFDimTolObjects_DatumTargetType_Area) {
      TopoDS_Shape aDTShape = anObject->GetDatumTarget();
      Handle(StepAP242_GeometricItemSpecificUsage) anAreaGISU;
      Handle(StepRepr_ShapeAspect) anAreaSA = WriteShapeAspect(WS, theDatumL, aDTShape, aRC, anAreaGISU);
      aSANum = Model->Number(anAreaSA);
      aGISUNum = Model->Number(anAreaGISU);
      Handle(StepDimTol_DatumTarget) aDT = new StepDimTol_DatumTarget();
      aDT->Init(new TCollection_HAsciiString(), new TCollection_HAsciiString("area"), anAreaSA->OfShape(),
        StepData_LTrue, aTargetId);
      Model->ReplaceEntity(aSANum, aDT);
      StepAP242_ItemIdentifiedRepresentationUsageDefinition aDefinition;
      aDefinition.SetValue(aDT);
      anAreaGISU->SetDefinition(aDefinition);
      Model->ReplaceEntity(aGISUNum, anAreaGISU);
    }
    else {
      Handle(StepDimTol_PlacedDatumTargetFeature) aPDTF = new StepDimTol_PlacedDatumTargetFeature();
      aPDTF->Init(new TCollection_HAsciiString(), STEPCAFControl_GDTProperty::GetDatumTargetName(aDatumType),
        aPDS, StepData_LTrue, aTargetId);
      Model->AddWithRefs(aPDTF);
=======
      aModel->ReplaceEntity(aGISUNum, aGISU);
    }
    else if (aSASeq.Length() > 1)
    {
      Handle(StepRepr_CompShAspAndDatumFeatAndShAsp) aDF = new StepRepr_CompShAspAndDatumFeatAndShAsp();
      aDF->Init(new TCollection_HAsciiString(), new TCollection_HAsciiString(), aPDS, StepData_LTrue);
      for (Standard_Integer i = 1; i <= aSASeq.Length(); i++)
      {
        Handle(StepRepr_ShapeAspectRelationship) aSAR = new StepRepr_ShapeAspectRelationship();
        aSAR->Init(new TCollection_HAsciiString(), Standard_False, new TCollection_HAsciiString(), aDF, aSASeq.Value(i));
        aModel->AddWithRefs(aSAR);
      }
      aSA = aDF;
      aModel->AddWithRefs(aDF);
    }
  }
  // Datum with datum targets
  else
  {
    XCAFDimTolObjects_DatumTargetType aDatumType = anObject->GetDatumTargetType();
    Handle(StepDimTol_DatumTarget) aDatumTarget;
    // Note: the given way to write such datum type may be incorrect (too little information)
    if (aDatumType == XCAFDimTolObjects_DatumTargetType_Area)
    {
      TopoDS_Shape aDTShape = anObject->GetDatumTarget();
      Handle(StepAP242_GeometricItemSpecificUsage) anAreaGISU;
      Handle(StepRepr_ShapeAspect) anAreaSA = writeShapeAspect(theWS, theDatumL, aDTShape, aRC, anAreaGISU);
      aSANum = aModel->Number(anAreaSA);
      aGISUNum = aModel->Number(anAreaGISU);
      Handle(StepDimTol_DatumTarget) aDT = new StepDimTol_DatumTarget();
      aDT->Init(new TCollection_HAsciiString(), new TCollection_HAsciiString("area"), anAreaSA->OfShape(),
                StepData_LTrue, aTargetId);
      aModel->ReplaceEntity(aSANum, aDT);
      StepAP242_ItemIdentifiedRepresentationUsageDefinition aDefinition;
      aDefinition.SetValue(aDT);
      anAreaGISU->SetDefinition(aDefinition);
      aModel->ReplaceEntity(aGISUNum, anAreaGISU);
    }
    else
    {
      Handle(StepDimTol_PlacedDatumTargetFeature) aPDTF = new StepDimTol_PlacedDatumTargetFeature();
      aPDTF->Init(new TCollection_HAsciiString(), STEPCAFControl_GDTProperty::GetDatumTargetName(aDatumType),
                  aPDS, StepData_LTrue, aTargetId);
      aModel->AddWithRefs(aPDTF);
>>>>>>> accb2f351 (u)
      aDatumTarget = aPDTF;
      // Datum targets
      Handle(StepRepr_PropertyDefinition) aPD = new StepRepr_PropertyDefinition();
      StepRepr_CharacterizedDefinition aCDefinition;
      aCDefinition.SetValue(aPDTF);
      aPD->Init(new TCollection_HAsciiString(), Standard_False, NULL, aCDefinition);
<<<<<<< HEAD
      if (anObject->HasDatumTargetParams()) {
=======
      if (anObject->HasDatumTargetParams())
      {
>>>>>>> accb2f351 (u)
        // write all parameters of datum target
        Handle(StepShape_ShapeRepresentationWithParameters) aSRWP = new StepShape_ShapeRepresentationWithParameters();
        // Common for all datum targets
        StepBasic_Unit aUnit = GetUnit(aRC);
        gp_Ax2 aDTAxis = anObject->GetDatumTargetAxis();
        GeomToStep_MakeAxis2Placement3d anAxisMaker(aDTAxis);
        Handle(StepGeom_Axis2Placement3d) anA2P3D = anAxisMaker.Value();
        anA2P3D->SetName(new TCollection_HAsciiString("orientation"));
        Handle(StepRepr_HArray1OfRepresentationItem) anItems;
        // Process each datum target type
<<<<<<< HEAD
        if (aDatumType == XCAFDimTolObjects_DatumTargetType_Point) {
          anItems = new StepRepr_HArray1OfRepresentationItem(1, 1);
        }
        else  {
          Handle(TCollection_HAsciiString) aTargetValueName;
          if (aDatumType == XCAFDimTolObjects_DatumTargetType_Line) {
            anItems = new StepRepr_HArray1OfRepresentationItem(1, 2);
            aTargetValueName = new TCollection_HAsciiString("target length");
          }
          else if (aDatumType == XCAFDimTolObjects_DatumTargetType_Rectangle) {
=======
        if (aDatumType == XCAFDimTolObjects_DatumTargetType_Point)
        {
          anItems = new StepRepr_HArray1OfRepresentationItem(1, 1);
        }
        else
        {
          Handle(TCollection_HAsciiString) aTargetValueName;
          if (aDatumType == XCAFDimTolObjects_DatumTargetType_Line)
          {
            anItems = new StepRepr_HArray1OfRepresentationItem(1, 2);
            aTargetValueName = new TCollection_HAsciiString("target length");
          }
          else if (aDatumType == XCAFDimTolObjects_DatumTargetType_Rectangle)
          {
>>>>>>> accb2f351 (u)
            anItems = new StepRepr_HArray1OfRepresentationItem(1, 3);
            aTargetValueName = new TCollection_HAsciiString("target length");
            // Additional value
            Handle(StepRepr_ReprItemAndMeasureWithUnit) aTargetValue = CreateDimValue(anObject->GetDatumTargetWidth(),
<<<<<<< HEAD
              aUnit, new TCollection_HAsciiString("target width"), "POSITIVE_LENGTH_MEASURE", Standard_False);
            anItems->SetValue(2, aTargetValue);
            Model->AddWithRefs(aTargetValue);
          }
          else if (aDatumType == XCAFDimTolObjects_DatumTargetType_Circle) {
=======
                                                                                      aUnit, new TCollection_HAsciiString("target width"), "POSITIVE_LENGTH_MEASURE", Standard_False);
            anItems->SetValue(2, aTargetValue);
            aModel->AddWithRefs(aTargetValue);
          }
          else if (aDatumType == XCAFDimTolObjects_DatumTargetType_Circle)
          {
>>>>>>> accb2f351 (u)
            anItems = new StepRepr_HArray1OfRepresentationItem(1, 2);
            aTargetValueName = new TCollection_HAsciiString("target diameter");
          }
          // Value
          Handle(StepRepr_ReprItemAndMeasureWithUnit) aTargetValue = CreateDimValue(anObject->GetDatumTargetLength(),
<<<<<<< HEAD
            aUnit, aTargetValueName, "POSITIVE_LENGTH_MEASURE", Standard_False);
          anItems->SetValue(1, aTargetValue);
          Model->AddWithRefs(aTargetValue);
=======
                                                                                    aUnit, aTargetValueName, "POSITIVE_LENGTH_MEASURE", Standard_False);
          anItems->SetValue(1, aTargetValue);
          aModel->AddWithRefs(aTargetValue);
>>>>>>> accb2f351 (u)
        }
        anItems->SetValue(anItems->Length(), anA2P3D);
        aSRWP->Init(new TCollection_HAsciiString(), anItems, aRC);
        // Create and write auxiliary entities
        Handle(StepShape_ShapeDefinitionRepresentation) aSDR = new StepShape_ShapeDefinitionRepresentation();
        StepRepr_RepresentedDefinition aRDefinition;
        aRDefinition.SetValue(aPD);
        aSDR->Init(aRDefinition, aSRWP);
<<<<<<< HEAD
        Model->AddWithRefs(aPD);
        Model->AddWithRefs(aSRWP);
        Model->AddWithRefs(aSDR);
=======
        aModel->AddWithRefs(aPD);
        aModel->AddWithRefs(aSRWP);
        aModel->AddWithRefs(aSDR);
>>>>>>> accb2f351 (u)
      }
    }
    // Link datum target to datum feature
    // if aSASeq.Length() == 0 nothing to do
<<<<<<< HEAD
    if (aSASeq.Length() == 1) {
      Handle(StepRepr_FeatureForDatumTargetRelationship) aFFDTR = new StepRepr_FeatureForDatumTargetRelationship();
      aFFDTR->Init(new TCollection_HAsciiString(), Standard_False, NULL, aSASeq.Value(1), aDatumTarget);
      Model->AddWithRefs(aFFDTR);
    }
    else if (aSASeq.Length() > 1) {
      Handle(StepRepr_CompositeShapeAspect) aCompSA = new StepRepr_CompositeShapeAspect();
      aCompSA->Init(new TCollection_HAsciiString(), new TCollection_HAsciiString(), aPDS, aSASeq.Value(1)->ProductDefinitional());
      for (Standard_Integer i = 1; i <= aSASeq.Length(); i++) {
        Handle(StepRepr_ShapeAspectRelationship) aSAR = new StepRepr_ShapeAspectRelationship();
        aSAR->Init(new TCollection_HAsciiString(), Standard_False, new TCollection_HAsciiString(), aCompSA, aSASeq.Value(i));
        Model->AddWithRefs(aSAR);
      }
      Handle(StepRepr_FeatureForDatumTargetRelationship) aFFDTR = new StepRepr_FeatureForDatumTargetRelationship();
      aFFDTR->Init(new TCollection_HAsciiString(), Standard_False, NULL, aCompSA, aDatumTarget);
      Model->AddWithRefs(aFFDTR);
=======
    if (aSASeq.Length() == 1)
    {
      Handle(StepRepr_FeatureForDatumTargetRelationship) aFFDTR = new StepRepr_FeatureForDatumTargetRelationship();
      aFFDTR->Init(new TCollection_HAsciiString(), Standard_False, NULL, aSASeq.Value(1), aDatumTarget);
      aModel->AddWithRefs(aFFDTR);
    }
    else if (aSASeq.Length() > 1)
    {
      Handle(StepRepr_CompositeShapeAspect) aCompSA = new StepRepr_CompositeShapeAspect();
      aCompSA->Init(new TCollection_HAsciiString(), new TCollection_HAsciiString(), aPDS, aSASeq.Value(1)->ProductDefinitional());
      for (Standard_Integer i = 1; i <= aSASeq.Length(); i++)
      {
        Handle(StepRepr_ShapeAspectRelationship) aSAR = new StepRepr_ShapeAspectRelationship();
        aSAR->Init(new TCollection_HAsciiString(), Standard_False, new TCollection_HAsciiString(), aCompSA, aSASeq.Value(i));
        aModel->AddWithRefs(aSAR);
      }
      Handle(StepRepr_FeatureForDatumTargetRelationship) aFFDTR = new StepRepr_FeatureForDatumTargetRelationship();
      aFFDTR->Init(new TCollection_HAsciiString(), Standard_False, NULL, aCompSA, aDatumTarget);
      aModel->AddWithRefs(aFFDTR);
>>>>>>> accb2f351 (u)
    }
    aSA = aDatumTarget;
  }

  // Datum
  Handle(StepDimTol_Datum) aDatum = theWrittenDatum;
<<<<<<< HEAD
  if (isFirstDTarget) {
    aDatum = new StepDimTol_Datum();
    aDatum->Init(new TCollection_HAsciiString(), new TCollection_HAsciiString(), aPDS, StepData_LFalse, anIdentifier);
    Model->AddWithRefs(aDatum);
  }

  // Shape_Aspect_Relationship
  if (!aSA.IsNull()) {
    Handle(StepRepr_ShapeAspectRelationship) aSAR = new StepRepr_ShapeAspectRelationship();
    aSAR->Init(new TCollection_HAsciiString(), Standard_False, NULL, aSA, aDatum);
    Model->AddWithRefs(aSAR);
  }

  //Annotation plane and Presentation
  WritePresentation(WS, anObject->GetPresentation(), anObject->GetPresentationName(), Standard_True, anObject->HasPlane(),
    anObject->GetPlane(), anObject->GetPointTextAttach(), aSA);
=======
  if (theIsFirstDTarget)
  {
    aDatum = new StepDimTol_Datum();
    aDatum->Init(new TCollection_HAsciiString(), new TCollection_HAsciiString(), aPDS, StepData_LFalse, anIdentifier);
    aModel->AddWithRefs(aDatum);
  }

  // Shape_Aspect_Relationship
  if (!aSA.IsNull())
  {
    Handle(StepRepr_ShapeAspectRelationship) aSAR = new StepRepr_ShapeAspectRelationship();
    aSAR->Init(new TCollection_HAsciiString(), Standard_False, NULL, aSA, aDatum);
    aModel->AddWithRefs(aSAR);
  }

  //Annotation plane and Presentation
  writePresentation(theWS, anObject->GetPresentation(), anObject->GetPresentationName(), Standard_True, anObject->HasPlane(),
                    anObject->GetPlane(), anObject->GetPointTextAttach(), aSA);
>>>>>>> accb2f351 (u)

  return aDatum;
}

//=======================================================================
//function : WriteDimValues
<<<<<<< HEAD
//purpose  : auxiliary (write all data for given dimension: values, 
//           qualifiers, modifiers, orientation and tolerance class)
//======================================================================
static void WriteDimValues(const Handle(XSControl_WorkSession) &WS,
                           const Handle(XCAFDimTolObjects_DimensionObject) theObject,
                           const Handle(StepRepr_RepresentationContext) theRC,
                           const StepShape_DimensionalCharacteristic theDimension)
{
  // Get working data
  const Handle(Interface_InterfaceModel) &aModel = WS->Model();
  XCAFDimTolObjects_DimensionModifiersSequence aModifiers = theObject->GetModifiers();
  Handle(Standard_Transient) aDim = theDimension.Value();
  Standard_Boolean isAngle = aDim->IsKind(STANDARD_TYPE(StepShape_AngularLocation)) ||
                             aDim->IsKind(STANDARD_TYPE(StepShape_AngularSize));
=======
//purpose  : auxiliary (write all data for given dimension: values,
//           qualifiers, modifiers, orientation and tolerance class)
//======================================================================
static void WriteDimValues(const Handle(XSControl_WorkSession)& theWS,
                           const Handle(XCAFDimTolObjects_DimensionObject)& theObject,
                           const Handle(StepRepr_RepresentationContext)& theRC,
                           const StepShape_DimensionalCharacteristic& theDimension)
{
  // Get working data
  const Handle(Interface_InterfaceModel)& aModel = theWS->Model();
  XCAFDimTolObjects_DimensionModifiersSequence aModifiers = theObject->GetModifiers();
  const Handle(Standard_Transient)& aDim = theDimension.Value();
  Standard_Boolean isAngle = aDim->IsKind(STANDARD_TYPE(StepShape_AngularLocation)) ||
    aDim->IsKind(STANDARD_TYPE(StepShape_AngularSize));
>>>>>>> accb2f351 (u)

  // Unit
  StepBasic_Unit aUnit = GetUnit(theRC, isAngle);
  Standard_CString aMeasureName;
  if (isAngle)
    aMeasureName = "POSITIVE_PLANE_ANGLE_MEASURE";
  else
    aMeasureName = "POSITIVE_LENGTH_MEASURE";

  // Values
  Handle(StepRepr_HArray1OfRepresentationItem) aValues;
  Standard_Integer aNbItems = 1, aValIt = 1;
  if (theObject->IsDimWithRange())
    aNbItems += 2;
  if (aModifiers.Length() > 0)
    aNbItems++;
  if (theObject->GetType() == XCAFDimTolObjects_DimensionType_Location_Oriented)
    aNbItems++;
  aNbItems += theObject->NbDescriptions();
  aValues = new StepRepr_HArray1OfRepresentationItem(1, aNbItems);

  // Nominal value
  Standard_Real aNominal = theObject->GetValue();
  Standard_Integer aLeftNbDigits, aRightNbDigits;
  theObject->GetNbOfDecimalPlaces(aLeftNbDigits, aRightNbDigits);
  Standard_Integer aNbQualifiers = 0;
  if (theObject->HasQualifier() && !isAngle)
    aNbQualifiers++;
  if (aLeftNbDigits > 0 || aRightNbDigits > 0)
    aNbQualifiers++;
  // With qualifiers
<<<<<<< HEAD
  if (aNbQualifiers > 0) {
    Handle(StepShape_QualifiedRepresentationItem) aQRI = new StepShape_QualifiedRepresentationItem();
    Handle(StepShape_HArray1OfValueQualifier) aQualifiers = new StepShape_HArray1OfValueQualifier(1, aNbQualifiers);
    // Type qualifier
    if (theObject->HasQualifier() && !isAngle) {
=======
  if (aNbQualifiers > 0)
  {
    Handle(StepShape_QualifiedRepresentationItem) aQRI = new StepShape_QualifiedRepresentationItem();
    Handle(StepShape_HArray1OfValueQualifier) aQualifiers = new StepShape_HArray1OfValueQualifier(1, aNbQualifiers);
    // Type qualifier
    if (theObject->HasQualifier() && !isAngle)
    {
>>>>>>> accb2f351 (u)
      StepShape_ValueQualifier anItem;
      Handle(StepShape_TypeQualifier) aType = new StepShape_TypeQualifier();
      XCAFDimTolObjects_DimensionQualifier aQualifier = theObject->GetQualifier();
      aType->Init(STEPCAFControl_GDTProperty::GetDimQualifierName(aQualifier));
      aModel->AddWithRefs(aType);
      anItem.SetValue(aType);
      aQualifiers->SetValue(1, anItem);
    }
    // Number of decimal places
<<<<<<< HEAD
    if (aLeftNbDigits > 0 || aRightNbDigits > 0) {
=======
    if (aLeftNbDigits > 0 || aRightNbDigits > 0)
    {
>>>>>>> accb2f351 (u)
      StepShape_ValueQualifier anItem;
      Handle(StepShape_ValueFormatTypeQualifier) aType = new StepShape_ValueFormatTypeQualifier();
      Handle(TCollection_HAsciiString) aFormatType = new TCollection_HAsciiString("NR2 ");
      aFormatType->AssignCat(new TCollection_HAsciiString(aLeftNbDigits));
      aFormatType->AssignCat(new TCollection_HAsciiString("."));
      aFormatType->AssignCat(new TCollection_HAsciiString(aRightNbDigits));
      aType->Init(aFormatType);
      aModel->AddWithRefs(aType);
      anItem.SetValue(aType);
      aQualifiers->SetValue(aNbQualifiers, anItem);
    }
    // Set qualifiers
    aQRI->SetQualifiers(aQualifiers);
<<<<<<< HEAD
    Handle(StepRepr_ReprItemAndMeasureWithUnit) anItem = CreateDimValue(aNominal, aUnit,
      new TCollection_HAsciiString("nominal value"), aMeasureName, isAngle, Standard_True, aQRI);
=======
    Handle(StepRepr_ReprItemAndMeasureWithUnit) anItem =
      CreateDimValue(aNominal, aUnit,
                     new TCollection_HAsciiString("nominal value"), aMeasureName, isAngle, Standard_True, aQRI);
>>>>>>> accb2f351 (u)
    aValues->SetValue(aValIt, anItem);
    aValIt++;
  }
  // Without qualifiers
<<<<<<< HEAD
  else {
    Handle(StepRepr_ReprItemAndMeasureWithUnit) anItem = CreateDimValue(aNominal, aUnit,
      new TCollection_HAsciiString("nominal value"), aMeasureName, isAngle);
=======
  else
  {
    Handle(StepRepr_ReprItemAndMeasureWithUnit) anItem =
      CreateDimValue(aNominal, aUnit,
                     new TCollection_HAsciiString("nominal value"), aMeasureName, isAngle);
>>>>>>> accb2f351 (u)
    aValues->SetValue(aValIt, anItem);
    aValIt++;
  }

  // Ranges
<<<<<<< HEAD
  if (theObject->IsDimWithRange()) {
    Handle(StepRepr_ReprItemAndMeasureWithUnit) aLowerItem = CreateDimValue(theObject->GetLowerBound(), aUnit,
      new TCollection_HAsciiString("lower limit"), aMeasureName, isAngle);
    Handle(StepRepr_ReprItemAndMeasureWithUnit) anUpperItem = CreateDimValue(theObject->GetUpperBound(), aUnit,
      new TCollection_HAsciiString("upper limit"), aMeasureName, isAngle);
=======
  if (theObject->IsDimWithRange())
  {
    Handle(StepRepr_ReprItemAndMeasureWithUnit) aLowerItem =
      CreateDimValue(theObject->GetLowerBound(), aUnit,
                     new TCollection_HAsciiString("lower limit"), aMeasureName, isAngle);
    Handle(StepRepr_ReprItemAndMeasureWithUnit) anUpperItem =
      CreateDimValue(theObject->GetUpperBound(), aUnit,
                     new TCollection_HAsciiString("upper limit"), aMeasureName, isAngle);
>>>>>>> accb2f351 (u)
    aValues->SetValue(aValIt, aLowerItem);
    aValIt++;
    aValues->SetValue(aValIt, anUpperItem);
    aValIt++;
  }

  // Modifiers
<<<<<<< HEAD
  if (aModifiers.Length() > 0) {
    Handle(StepRepr_CompoundRepresentationItem) aCompoundRI = new StepRepr_CompoundRepresentationItem();
    Handle (StepRepr_HArray1OfRepresentationItem) aModifItems = 
      new StepRepr_HArray1OfRepresentationItem(1, aModifiers.Length());
    for (Standard_Integer i = 1; i <= aModifiers.Length(); i++) {
      XCAFDimTolObjects_DimensionModif aModif = aModifiers.Value(i);
      Handle(StepRepr_DescriptiveRepresentationItem) aModifItem = 
=======
  if (aModifiers.Length() > 0)
  {
    Handle(StepRepr_CompoundRepresentationItem) aCompoundRI = new StepRepr_CompoundRepresentationItem();
    Handle(StepRepr_HArray1OfRepresentationItem) aModifItems =
      new StepRepr_HArray1OfRepresentationItem(1, aModifiers.Length());
    for (Standard_Integer i = 1; i <= aModifiers.Length(); i++)
    {
      XCAFDimTolObjects_DimensionModif aModif = aModifiers.Value(i);
      Handle(StepRepr_DescriptiveRepresentationItem) aModifItem =
>>>>>>> accb2f351 (u)
        new StepRepr_DescriptiveRepresentationItem();
      aModifItem->Init(new TCollection_HAsciiString(), STEPCAFControl_GDTProperty::GetDimModifierName(aModif));
      aModel->AddWithRefs(aModifItem);
      aModifItems->SetValue(i, aModifItem);
    }
    aCompoundRI->Init(new TCollection_HAsciiString(), aModifItems);
    aValues->SetValue(aValIt, aCompoundRI);
    aValIt++;
  }

  // Orientation
<<<<<<< HEAD
  if (theObject->GetType() == XCAFDimTolObjects_DimensionType_Location_Oriented) {
=======
  if (theObject->GetType() == XCAFDimTolObjects_DimensionType_Location_Oriented)
  {
>>>>>>> accb2f351 (u)
    Handle(StepGeom_Axis2Placement3d) anOrientation = new StepGeom_Axis2Placement3d();
    gp_Dir aDir;
    theObject->GetDirection(aDir);
    GeomToStep_MakeCartesianPoint MkPoint(gp_Pnt(0, 0, 0));
<<<<<<< HEAD
    Handle(StepGeom_CartesianPoint) aLoc = MkPoint.Value();
=======
    const Handle(StepGeom_CartesianPoint)& aLoc = MkPoint.Value();
>>>>>>> accb2f351 (u)
    Handle(StepGeom_Direction) anAxis = new StepGeom_Direction();
    Handle(TColStd_HArray1OfReal) aCoords = new TColStd_HArray1OfReal(1, 3);
    aCoords->SetValue(1, aDir.X());
    aCoords->SetValue(2, aDir.Y());
    aCoords->SetValue(3, aDir.Z());
    anAxis->Init(new TCollection_HAsciiString(), aCoords);
    anOrientation->Init(new TCollection_HAsciiString("orientation"), aLoc, Standard_True, anAxis, Standard_False, NULL);
    aValues->SetValue(aValIt, anOrientation);
    aValIt++;
  }

  // Descriptions
<<<<<<< HEAD
  if (theObject->HasDescriptions()) {
    for (Standard_Integer i = 0; i < theObject->NbDescriptions(); i++) {
=======
  if (theObject->HasDescriptions())
  {
    for (Standard_Integer i = 0; i < theObject->NbDescriptions(); i++)
    {
>>>>>>> accb2f351 (u)
      Handle(StepRepr_DescriptiveRepresentationItem) aDRI = new StepRepr_DescriptiveRepresentationItem();
      aDRI->Init(theObject->GetDescriptionName(i), theObject->GetDescription(i));
      aValues->SetValue(aValIt, aDRI);
      aValIt++;
    }
  }

  for (Standard_Integer i = 1; i <= aValues->Length(); i++)
<<<<<<< HEAD
    aModel->AddWithRefs(aValues->Value(i));
=======
  {
    aModel->AddWithRefs(aValues->Value(i));
  }
>>>>>>> accb2f351 (u)

  // Create resulting Shape_Dimension_Representation
  Handle(StepShape_ShapeDimensionRepresentation) aSDR = new StepShape_ShapeDimensionRepresentation();
  aSDR->Init(new TCollection_HAsciiString(), aValues, theRC);
  aModel->AddWithRefs(aSDR);
  Handle(StepShape_DimensionalCharacteristicRepresentation) aDCR = new StepShape_DimensionalCharacteristicRepresentation();
  aDCR->Init(theDimension, aSDR);
  aModel->AddWithRefs(aDCR);

  // Plus_Minus_Tolerance
<<<<<<< HEAD
  if (theObject->IsDimWithPlusMinusTolerance()) {
=======
  if (theObject->IsDimWithPlusMinusTolerance())
  {
>>>>>>> accb2f351 (u)
    Handle(TCollection_HAsciiString) aDummyName = new TCollection_HAsciiString(aMeasureName);
    aDummyName = aDummyName->SubString(9, aDummyName->Length()); //delete "POSITIVE_"
    aMeasureName = aDummyName->ToCString();
    Standard_Real aLowerTolValue = -theObject->GetLowerTolValue(),
<<<<<<< HEAD
                  anUpperTolValue = theObject->GetUpperTolValue();
=======
      anUpperTolValue = theObject->GetUpperTolValue();
>>>>>>> accb2f351 (u)
    // Upper
    Handle(StepBasic_MeasureWithUnit) anUpperMWU = new StepBasic_MeasureWithUnit();
    Handle(StepBasic_MeasureValueMember) anUpperValue = new StepBasic_MeasureValueMember();
    anUpperValue->SetName(aMeasureName);
    anUpperValue->SetReal(anUpperTolValue);
    anUpperMWU->Init(anUpperValue, aUnit);
    aModel->AddWithRefs(anUpperMWU);
    // Lower
    Handle(StepBasic_MeasureWithUnit) aLowerMWU = new StepBasic_MeasureWithUnit();
    Handle(StepBasic_MeasureValueMember) aLowerValue = new StepBasic_MeasureValueMember();
    aLowerValue->SetName(aMeasureName);
    aLowerValue->SetReal(aLowerTolValue);
    aLowerMWU->Init(aLowerValue, aUnit);
    aModel->AddWithRefs(aLowerMWU);
    // Tolerance
    Handle(StepShape_ToleranceValue) aTolValue = new StepShape_ToleranceValue();
    aTolValue->Init(aLowerMWU, anUpperMWU);
    aModel->AddWithRefs(aTolValue);
    StepShape_ToleranceMethodDefinition aMethod;
    aMethod.SetValue(aTolValue);
    Handle(StepShape_PlusMinusTolerance) aPlusMinusTol = new StepShape_PlusMinusTolerance();
    aPlusMinusTol->Init(aMethod, theDimension);
    aModel->AddWithRefs(aPlusMinusTol);
  }
  // Tolerance class
<<<<<<< HEAD
  if (theObject->IsDimWithClassOfTolerance()) {
=======
  if (theObject->IsDimWithClassOfTolerance())
  {
>>>>>>> accb2f351 (u)
    Standard_Boolean isHole;
    XCAFDimTolObjects_DimensionFormVariance aFormVariance;
    XCAFDimTolObjects_DimensionGrade aGrade;
    if (!theObject->GetClassOfTolerance(isHole, aFormVariance, aGrade))
      return;
    Handle(StepShape_LimitsAndFits) aLAF = STEPCAFControl_GDTProperty::GetLimitsAndFits(isHole, aFormVariance, aGrade);
    aModel->AddWithRefs(aLAF);
    StepShape_ToleranceMethodDefinition aMethod;
    aMethod.SetValue(aLAF);
    Handle(StepShape_PlusMinusTolerance) aPlusMinusTol = new StepShape_PlusMinusTolerance();
    aPlusMinusTol->Init(aMethod, theDimension);
    aModel->AddWithRefs(aPlusMinusTol);
  }
}

//=======================================================================
//function : WriteDerivedGeometry
//purpose  : auxiliary (write connection point for dimensions)
//======================================================================
<<<<<<< HEAD
static void WriteDerivedGeometry (const Handle(XSControl_WorkSession) &WS,
                                  const Handle(XCAFDimTolObjects_DimensionObject)& theObject,
                                  const Handle(StepRepr_ConstructiveGeometryRepresentation) theRepr,
                                  Handle(StepRepr_ShapeAspect)& theFirstSA,
                                  Handle(StepRepr_ShapeAspect)& theSecondSA,
                                  NCollection_Vector<Handle(StepGeom_CartesianPoint)>& thePnts)
{
  const Handle(Interface_InterfaceModel) &aModel = WS->Model();
  // First point
  if (theObject->HasPoint()) {
=======
static void WriteDerivedGeometry(const Handle(XSControl_WorkSession)& theWS,
                                 const Handle(XCAFDimTolObjects_DimensionObject)& theObject,
                                 const Handle(StepRepr_ConstructiveGeometryRepresentation)& theRepr,
                                 Handle(StepRepr_ShapeAspect)& theFirstSA,
                                 Handle(StepRepr_ShapeAspect)& theSecondSA,
                                 NCollection_Vector<Handle(StepGeom_CartesianPoint)>& thePnts)
{
  const Handle(Interface_InterfaceModel)& aModel = theWS->Model();
  // First point
  if (theObject->HasPoint())
  {
>>>>>>> accb2f351 (u)
    GeomToStep_MakeCartesianPoint aPointMaker(theObject->GetPoint());
    Handle(StepGeom_CartesianPoint) aPoint = aPointMaker.Value();
    thePnts.Append(aPoint);
    Handle(StepRepr_DerivedShapeAspect) aDSA = new StepRepr_DerivedShapeAspect();
    aDSA->Init(new TCollection_HAsciiString(), new TCollection_HAsciiString(), theFirstSA->OfShape(), StepData_LFalse);
    Handle(StepAP242_GeometricItemSpecificUsage) aGISU = new StepAP242_GeometricItemSpecificUsage();
    StepAP242_ItemIdentifiedRepresentationUsageDefinition aDefinition;
    aDefinition.SetValue(aDSA);
    Handle(StepRepr_HArray1OfRepresentationItem) anItem = new StepRepr_HArray1OfRepresentationItem(1, 1);
    anItem->SetValue(1, aPoint);
    aGISU->Init(new TCollection_HAsciiString(), new TCollection_HAsciiString(), aDefinition, theRepr, anItem);
    Handle(StepRepr_ShapeAspectDerivingRelationship) aSADR = new StepRepr_ShapeAspectDerivingRelationship();
    aSADR->Init(new TCollection_HAsciiString(), Standard_False, new TCollection_HAsciiString(), aDSA, theFirstSA);
    theFirstSA = aDSA;
    aModel->AddWithRefs(aGISU);
    aModel->AddWithRefs(aSADR);
  }
<<<<<<< HEAD
  
  // Second point (for locations)
  if (theObject->HasPoint2()) {
=======

  // Second point (for locations)
  if (theObject->HasPoint2())
  {
>>>>>>> accb2f351 (u)
    GeomToStep_MakeCartesianPoint aPointMaker(theObject->GetPoint2());
    Handle(StepGeom_CartesianPoint) aPoint = aPointMaker.Value();
    thePnts.Append(aPoint);
    Handle(StepRepr_DerivedShapeAspect) aDSA = new StepRepr_DerivedShapeAspect();
    aDSA->Init(new TCollection_HAsciiString(), new TCollection_HAsciiString(), theFirstSA->OfShape(), StepData_LFalse);
    Handle(StepAP242_GeometricItemSpecificUsage) aGISU = new StepAP242_GeometricItemSpecificUsage();
    StepAP242_ItemIdentifiedRepresentationUsageDefinition aDefinition;
    aDefinition.SetValue(aDSA);
    Handle(StepRepr_HArray1OfRepresentationItem) anItem = new StepRepr_HArray1OfRepresentationItem(1, 1);
    anItem->SetValue(1, aPoint);
    aGISU->Init(new TCollection_HAsciiString(), new TCollection_HAsciiString(), aDefinition, theRepr, anItem);
    Handle(StepRepr_ShapeAspectDerivingRelationship) aSADR = new StepRepr_ShapeAspectDerivingRelationship();
    aSADR->Init(new TCollection_HAsciiString(), Standard_False, new TCollection_HAsciiString(), aDSA, theSecondSA);
    theSecondSA = aDSA;
    aModel->AddWithRefs(aGISU);
    aModel->AddWithRefs(aSADR);
  }
}

//=======================================================================
//function : WriteDatumSystem
//purpose  : auxiliary (write Write datum system for given
//           geometric_tolerance)
//======================================================================
<<<<<<< HEAD
static Handle(StepDimTol_HArray1OfDatumSystemOrReference) WriteDatumSystem(const Handle(XSControl_WorkSession) &WS,
                                                                           const TDF_Label theGeomTolL,
                                                                           const TDF_LabelSequence theDatumSeq,
                                                                           const STEPConstruct_DataMapOfAsciiStringTransient theDatumMap,
                                                                           const Handle(StepRepr_RepresentationContext)& theRC)
{
  // Get working data
  const Handle(Interface_InterfaceModel) &Model = WS->Model();
  const Handle(Interface_HGraph) aHGraph = WS->HGraph();
=======
static Handle(StepDimTol_HArray1OfDatumSystemOrReference) WriteDatumSystem(const Handle(XSControl_WorkSession)& theWS,
                                                                           const TDF_Label theGeomTolL,
                                                                           const TDF_LabelSequence& theDatumSeq,
                                                                           const STEPConstruct_DataMapOfAsciiStringTransient& theDatumMap,
                                                                           const Handle(StepRepr_RepresentationContext)& theRC)
{
  // Get working data
  const Handle(Interface_InterfaceModel)& aModel = theWS->Model();
  const Handle(Interface_HGraph) aHGraph = theWS->HGraph();
>>>>>>> accb2f351 (u)
  if (aHGraph.IsNull())
    return NULL;
  Interface_Graph aGraph = aHGraph->Graph();
  Handle(XCAFDoc_GeomTolerance) aGTAttr;
<<<<<<< HEAD
  if (!theGeomTolL.FindAttribute(XCAFDoc_GeomTolerance::GetID(), aGTAttr)) 
=======
  if (!theGeomTolL.FindAttribute(XCAFDoc_GeomTolerance::GetID(), aGTAttr))
>>>>>>> accb2f351 (u)
    return NULL;
  Handle(XCAFDimTolObjects_GeomToleranceObject) anObject = aGTAttr->GetObject();
  if (anObject.IsNull())
    return NULL;

  // Unit
  StepBasic_Unit aUnit = GetUnit(theRC);

  XCAFDimTolObjects_DatumObjectSequence aDatums;
  Standard_Integer aMaxDatumNum = 0;
<<<<<<< HEAD
  for (Standard_Integer i = 1; i <= theDatumSeq.Length(); i++) {
    Handle(XCAFDoc_Datum) aDatumAttr;
    if (!theDatumSeq.Value(i).FindAttribute(XCAFDoc_Datum::GetID(), aDatumAttr)) 
=======

  for (TDF_LabelSequence::Iterator aDatumIter(theDatumSeq);
       aDatumIter.More(); aDatumIter.Next())
  {
    Handle(XCAFDoc_Datum) aDatumAttr;
    if (!aDatumIter.Value().FindAttribute(XCAFDoc_Datum::GetID(), aDatumAttr))
>>>>>>> accb2f351 (u)
      continue;
    Handle(XCAFDimTolObjects_DatumObject) aDatumObj = aDatumAttr->GetObject();
    if (aDatumObj.IsNull())
      continue;
    aDatums.Append(aDatumObj);
    aMaxDatumNum = Max(aMaxDatumNum, aDatumObj->GetPosition());
  }
  if (aMaxDatumNum == 0)
    return NULL;

  Handle(StepDimTol_HArray1OfDatumReferenceCompartment) aConstituents =
    new StepDimTol_HArray1OfDatumReferenceCompartment(1, aMaxDatumNum);
  // Auxiliary datum to initialize attributes in Datum_System
  Handle(StepDimTol_Datum) aFirstDatum;
<<<<<<< HEAD
  Standard_Integer aConstituentsNum = 0;
  for (Standard_Integer i = 1; i <= aMaxDatumNum; i++) {
    // Collect datums with i-th position
    XCAFDimTolObjects_DatumObjectSequence aDatumSeqPos;
    for (Standard_Integer j = 1; j <= aDatums.Length(); j++)
      if (aDatums.Value(j)->GetPosition() == i)
        aDatumSeqPos.Append(aDatums.Value(j));
    if (aDatumSeqPos.Length() < 1)
      continue;

    aConstituentsNum++;
=======
  for (Standard_Integer aConstituentsNum = 1;
       aConstituentsNum <= aMaxDatumNum; aConstituentsNum++)
  {
    // Collect datums with i-th position
    XCAFDimTolObjects_DatumObjectSequence aDatumSeqPos;
    for (XCAFDimTolObjects_DatumObjectSequence::Iterator aDatumIter(aDatums);
         aDatumIter.More(); aDatumIter.Next())
    {
      if (aDatumIter.Value()->GetPosition() == aConstituentsNum)
      {
        aDatumSeqPos.Append(aDatumIter.Value());
      }
    }
    if (aDatumSeqPos.Length() < 1)
      continue;
>>>>>>> accb2f351 (u)
    // Initialize Datum_Reference_Compartment
    StepDimTol_DatumOrCommonDatum aDatumRef;
    Handle(StepDimTol_DatumReferenceCompartment) aCompartment =
      new StepDimTol_DatumReferenceCompartment();
    Handle(StepDimTol_HArray1OfDatumReferenceModifier) aModifiers;
<<<<<<< HEAD
    if (aDatumSeqPos.Length() == 1) {
      // Datum entity
      Handle(Standard_Transient) aFDValue;
      if (theDatumMap.Find(aDatumSeqPos.Value(1)->GetName()->String(), aFDValue) && !aFDValue.IsNull())
        aFirstDatum = Handle(StepDimTol_Datum)::DownCast (aFDValue);
=======
    if (aDatumSeqPos.Length() == 1)
    {
      // Datum entity
      Handle(Standard_Transient) aFDValue;
      if (theDatumMap.Find(aDatumSeqPos.Value(1)->GetName()->String(), aFDValue) && !aFDValue.IsNull())
        aFirstDatum = Handle(StepDimTol_Datum)::DownCast(aFDValue);
>>>>>>> accb2f351 (u)
      aDatumRef.SetValue(aFirstDatum);
      // Modifiers
      XCAFDimTolObjects_DatumModifiersSequence aSimpleModifiers = aDatumSeqPos.Value(1)->GetModifiers();
      XCAFDimTolObjects_DatumModifWithValue aModifWithVal;
      Standard_Real aValue = 0;
      aDatumSeqPos.Value(1)->GetModifierWithValue(aModifWithVal, aValue);
      aModifiers = STEPCAFControl_GDTProperty::GetDatumRefModifiers(aSimpleModifiers, aModifWithVal, aValue, aUnit);
      // Add Datum_Reference_Modifier_With_Value
<<<<<<< HEAD
      if (!aModifiers.IsNull()) {
        Handle(StepDimTol_DatumReferenceModifierWithValue) aDRMWV = 
          aModifiers->Value(aModifiers->Length()).DatumReferenceModifierWithValue();
        if (!aDRMWV.IsNull()) {
          Model->AddWithRefs(aDRMWV);
        }
      }
    }
    else {
      Handle(StepDimTol_HArray1OfDatumReferenceElement) aCommonDatumList = new StepDimTol_HArray1OfDatumReferenceElement(1, aDatumSeqPos.Length());
      for (Standard_Integer j = 1; j <= aDatumSeqPos.Length(); j++) {
        // Datum entity
        Handle(StepDimTol_Datum) aDatum;
        Handle(Standard_Transient) aDValue;
        if (theDatumMap.Find(aDatumSeqPos.Value(j)->GetName()->String(), aDValue))
          aDatum = Handle(StepDimTol_Datum)::DownCast (aDValue);
=======
      if (!aModifiers.IsNull())
      {
        Handle(StepDimTol_DatumReferenceModifierWithValue) aDRMWV =
          aModifiers->Value(aModifiers->Length()).DatumReferenceModifierWithValue();
        if (!aDRMWV.IsNull())
        {
          aModel->AddWithRefs(aDRMWV);
        }
      }
    }
    else
    {
      Standard_Integer aSetInd = 1;
      Handle(StepDimTol_HArray1OfDatumReferenceElement) aCommonDatumList =
        new StepDimTol_HArray1OfDatumReferenceElement(1, aDatumSeqPos.Length());
      for (XCAFDimTolObjects_DatumObjectSequence::Iterator aDatumIter(aDatumSeqPos);
           aDatumIter.More(); aDatumIter.Next())
      {
        // Datum entity
        const Handle(XCAFDimTolObjects_DatumObject)& aDatumObj = aDatumIter.Value();
        Handle(StepDimTol_Datum) aDatum;
        Handle(Standard_Transient) aDValue;
        if (theDatumMap.Find(aDatumObj->GetName()->String(), aDValue))
          aDatum = Handle(StepDimTol_Datum)::DownCast(aDValue);
>>>>>>> accb2f351 (u)
        StepDimTol_DatumOrCommonDatum anElemDatumRef;
        anElemDatumRef.SetValue(aDatum);
        if (aFirstDatum.IsNull())
          aFirstDatum = aDatum;
        // Modifiers
<<<<<<< HEAD
        XCAFDimTolObjects_DatumModifiersSequence aSimpleModifiers = aDatumSeqPos.Value(j)->GetModifiers();
        XCAFDimTolObjects_DatumModifWithValue aModifWithVal;
        Standard_Real aValue = 0;
        aDatumSeqPos.Value(j)->GetModifierWithValue(aModifWithVal, aValue);
        Handle(StepDimTol_HArray1OfDatumReferenceModifier) anElemModifiers =
          STEPCAFControl_GDTProperty::GetDatumRefModifiers(aSimpleModifiers, aModifWithVal, aValue, aUnit);
        // Add Datum_Reference_Modifier_With_Value
        if (!anElemModifiers.IsNull()) {
          Handle(StepDimTol_DatumReferenceModifierWithValue) aDRMWV = 
            anElemModifiers->Value(anElemModifiers->Length()).DatumReferenceModifierWithValue();
          if (!aDRMWV.IsNull()) {
            Model->AddWithRefs(aDRMWV);
=======
        XCAFDimTolObjects_DatumModifiersSequence aSimpleModifiers = aDatumObj->GetModifiers();
        XCAFDimTolObjects_DatumModifWithValue aModifWithVal;
        Standard_Real aValue = 0;
        aDatumObj->GetModifierWithValue(aModifWithVal, aValue);
        Handle(StepDimTol_HArray1OfDatumReferenceModifier) anElemModifiers =
          STEPCAFControl_GDTProperty::GetDatumRefModifiers(aSimpleModifiers, aModifWithVal, aValue, aUnit);
        // Add Datum_Reference_Modifier_With_Value
        if (!anElemModifiers.IsNull())
        {
          Handle(StepDimTol_DatumReferenceModifierWithValue) aDRMWV =
            anElemModifiers->Value(anElemModifiers->Length()).DatumReferenceModifierWithValue();
          if (!aDRMWV.IsNull())
          {
            aModel->AddWithRefs(aDRMWV);
>>>>>>> accb2f351 (u)
          }
        }
        // Datum_Reference_Element
        Handle(StepDimTol_DatumReferenceElement) anElement = new StepDimTol_DatumReferenceElement();
        anElement->Init(new TCollection_HAsciiString(), new TCollection_HAsciiString(), aDatum->OfShape(),
<<<<<<< HEAD
          aDatum->ProductDefinitional(), anElemDatumRef, !anElemModifiers.IsNull(), anElemModifiers);
        Model->AddWithRefs(anElement);
        aCommonDatumList->SetValue(j, anElement);
=======
                        aDatum->ProductDefinitional(), anElemDatumRef, !anElemModifiers.IsNull(), anElemModifiers);
        aModel->AddWithRefs(anElement);
        aCommonDatumList->SetValue(aSetInd++, anElement);
>>>>>>> accb2f351 (u)
      }
      aDatumRef.SetValue(aCommonDatumList);
    }
    aCompartment->Init(new TCollection_HAsciiString(), new TCollection_HAsciiString(), aFirstDatum->OfShape(),
<<<<<<< HEAD
      aFirstDatum->ProductDefinitional(), aDatumRef, !aModifiers.IsNull(), aModifiers);
    Model->AddWithRefs(aCompartment);
=======
                       aFirstDatum->ProductDefinitional(), aDatumRef, !aModifiers.IsNull(), aModifiers);
    aModel->AddWithRefs(aCompartment);
>>>>>>> accb2f351 (u)
    aConstituents->SetValue(aConstituentsNum, aCompartment);
  }
  // Remove null elements from aConstituents
  Standard_Integer aNbConstituents = 0;
<<<<<<< HEAD
  for (Standard_Integer i = 1; i <= aConstituents->Length(); i++)
    if (!aConstituents->Value(i).IsNull())
      aNbConstituents++;
  Handle(StepDimTol_HArray1OfDatumReferenceCompartment) aResConstituents =
    new StepDimTol_HArray1OfDatumReferenceCompartment(1, aNbConstituents);
  Standard_Integer aConstituentsIt = 0;
  for (Standard_Integer i = 1; i <= aConstituents->Length(); i++)
    if (!aConstituents->Value(i).IsNull()) {
      aConstituentsIt++;
      aResConstituents->SetValue(aConstituentsIt, aConstituents->Value(i));
    }
=======
  for (StepDimTol_HArray1OfDatumReferenceCompartment::Iterator aConstituentIter(aConstituents->Array1());
       aConstituentIter.More(); aConstituentIter.Next())
  {
    if (!aConstituentIter.Value().IsNull())
    {
      aNbConstituents++;
    }
  }
  Handle(StepDimTol_HArray1OfDatumReferenceCompartment) aResConstituents =
    new StepDimTol_HArray1OfDatumReferenceCompartment(1, aNbConstituents);
  Standard_Integer aConstituentsIt = 0;
  for (StepDimTol_HArray1OfDatumReferenceCompartment::Iterator aConstituentIter(aConstituents->Array1());
       aConstituentIter.More(); aConstituentIter.Next())
  {
    if (!aConstituentIter.Value().IsNull())
    {
      aConstituentsIt++;
      aResConstituents->SetValue(aConstituentsIt, aConstituentIter.Value());
    }
  }
>>>>>>> accb2f351 (u)

  Handle(StepDimTol_HArray1OfDatumSystemOrReference) aDatumSystem;
  Handle(StepDimTol_DatumSystem) aDS = new StepDimTol_DatumSystem();
  aDS->Init(new TCollection_HAsciiString(), new TCollection_HAsciiString(), aFirstDatum->OfShape(),
<<<<<<< HEAD
    aFirstDatum->ProductDefinitional(), aResConstituents);
  Model->AddWithRefs(aDS);
=======
            aFirstDatum->ProductDefinitional(), aResConstituents);
  aModel->AddWithRefs(aDS);
>>>>>>> accb2f351 (u)
  StepDimTol_DatumSystemOrReference anArrayValue;
  anArrayValue.SetValue(aDS);
  aDatumSystem = new StepDimTol_HArray1OfDatumSystemOrReference(1, 1);
  aDatumSystem->SetValue(1, anArrayValue);

  // Axis
<<<<<<< HEAD
  if (anObject->HasAxis()) {
=======
  if (anObject->HasAxis())
  {
>>>>>>> accb2f351 (u)
    GeomToStep_MakeAxis2Placement3d anAxisMaker(anObject->GetAxis());
    Handle(StepGeom_Axis2Placement3d) anAxis = anAxisMaker.Value();
    anAxis->SetName(new TCollection_HAsciiString("orientation"));
    Handle(StepAP242_GeometricItemSpecificUsage) aGISU = new StepAP242_GeometricItemSpecificUsage();
    StepAP242_ItemIdentifiedRepresentationUsageDefinition aDefinition;
    aDefinition.SetValue(aDS);
    Handle(StepRepr_HArray1OfRepresentationItem) anReprItems = new StepRepr_HArray1OfRepresentationItem(1, 1);
    Handle(StepRepr_RepresentationItem) anIdentifiedItem = anAxis;
    anReprItems->SetValue(1, anIdentifiedItem);
<<<<<<< HEAD
    Interface_EntityIterator subs = aGraph.Sharings(aFirstDatum->OfShape());
    Handle(StepShape_ShapeDefinitionRepresentation) aSDR;
    for (subs.Start(); subs.More() && aSDR.IsNull(); subs.Next()) {
      Handle(Standard_Transient) anEntity = subs.Value();
      aSDR = Handle(StepShape_ShapeDefinitionRepresentation)::DownCast(anEntity);
    }
    if (aSDR.IsNull())
      return aDatumSystem;
    
    aGISU->Init(new TCollection_HAsciiString(), new TCollection_HAsciiString(),
      aDefinition, aSDR->UsedRepresentation(), anReprItems);
    Model->AddWithRefs(anAxis);
    Model->AddWithRefs(aGISU);
=======
    Handle(StepShape_ShapeDefinitionRepresentation) aSDR;
    for (Interface_EntityIterator aSharingsIter = aGraph.Sharings(aFirstDatum->OfShape());
         aSharingsIter.More() && aSDR.IsNull(); aSharingsIter.Next())
    {
      aSDR = Handle(StepShape_ShapeDefinitionRepresentation)::DownCast(aSharingsIter.Value());
    }
    if (aSDR.IsNull())
      return aDatumSystem;

    aGISU->Init(new TCollection_HAsciiString(), new TCollection_HAsciiString(),
                aDefinition, aSDR->UsedRepresentation(), anReprItems);
    aModel->AddWithRefs(anAxis);
    aModel->AddWithRefs(aGISU);
>>>>>>> accb2f351 (u)
  }

  return aDatumSystem;
}

//=======================================================================
<<<<<<< HEAD
//function : WriteToleranceZone
//purpose  : auxiliary (write tolerace zones)
//=======================================================================
void STEPCAFControl_Writer::WriteToleranceZone (const Handle(XSControl_WorkSession) &WS,
                                                const Handle(XCAFDimTolObjects_GeomToleranceObject)& theObject,
                                                const Handle(StepDimTol_GeometricTolerance)& theEntity,
                                                const Handle(StepRepr_RepresentationContext)& theRC)
{
  // Get working data
  const Handle(Interface_InterfaceModel) &Model = WS->Model();
=======
//function : writeToleranceZone
//purpose  : auxiliary (write tolerace zones)
//=======================================================================
void STEPCAFControl_Writer::writeToleranceZone(const Handle(XSControl_WorkSession)& theWS,
                                               const Handle(XCAFDimTolObjects_GeomToleranceObject)& theObject,
                                               const Handle(StepDimTol_GeometricTolerance)& theEntity,
                                               const Handle(StepRepr_RepresentationContext)& theRC)
{
  // Get working data
  const Handle(Interface_InterfaceModel)& aModel = theWS->Model();
>>>>>>> accb2f351 (u)
  if (theEntity.IsNull() || theObject.IsNull())
    return;

  // Return if there is no tolerance zones
  if (theObject->GetTypeOfValue() == XCAFDimTolObjects_GeomToleranceTypeValue_None &&
      theObject->GetZoneModifier() != XCAFDimTolObjects_GeomToleranceZoneModif_Runout)
<<<<<<< HEAD
    return;

  // Create Tolerance_Zone
  Handle(StepDimTol_ToleranceZoneForm) aForm = new StepDimTol_ToleranceZoneForm();
  Model->AddWithRefs(aForm);
=======
  {
    return;
  }

  // Create Tolerance_Zone
  Handle(StepDimTol_ToleranceZoneForm) aForm = new StepDimTol_ToleranceZoneForm();
  aModel->AddWithRefs(aForm);
>>>>>>> accb2f351 (u)
  aForm->Init(STEPCAFControl_GDTProperty::GetTolValueType(theObject->GetTypeOfValue()));
  Handle(StepDimTol_HArray1OfToleranceZoneTarget) aZoneTargetArray = new StepDimTol_HArray1OfToleranceZoneTarget(1, 1);
  StepDimTol_ToleranceZoneTarget aTarget;
  aTarget.SetValue(theEntity);
  aZoneTargetArray->SetValue(1, aTarget);
  Handle(StepDimTol_ToleranceZone) aZone = new StepDimTol_ToleranceZone();
  aZone->Init(new TCollection_HAsciiString(), new TCollection_HAsciiString(),
<<<<<<< HEAD
    theEntity->TolerancedShapeAspect().ShapeAspect()->OfShape(), StepData_LFalse,
    aZoneTargetArray, aForm);
  Model->AddWithRefs(aZone);
=======
              theEntity->TolerancedShapeAspect().ShapeAspect()->OfShape(), StepData_LFalse,
              aZoneTargetArray, aForm);
  aModel->AddWithRefs(aZone);
>>>>>>> accb2f351 (u)

  // Runout_Tolerance_Zone
  Handle(StepBasic_PlaneAngleMeasureWithUnit) aPAMWU = new StepBasic_PlaneAngleMeasureWithUnit();
  Handle(StepBasic_MeasureValueMember) aValueMember = new StepBasic_MeasureValueMember();
  aValueMember->SetName("PLANE_ANGLE_MEASURE");
  aValueMember->SetReal(theObject->GetValueOfZoneModifier());
  aPAMWU->Init(aValueMember, GetUnit(theRC, Standard_True));
  Handle(StepDimTol_RunoutZoneOrientation) anOrientation = new StepDimTol_RunoutZoneOrientation();
  anOrientation->Init(aPAMWU);
  Handle(StepDimTol_RunoutZoneDefinition) aDefinition = new StepDimTol_RunoutZoneDefinition();
  aDefinition->Init(aZone, NULL, anOrientation);
<<<<<<< HEAD
  Model->AddWithRefs(aDefinition);
  Model->AddWithRefs(anOrientation);
  Model->AddWithRefs(aPAMWU);
}

//=======================================================================
//function : WriteGeomTolerance
//purpose  : auxiliary (write Geometric_Tolerance entity for given shapes,
//           label and datum system)
//======================================================================
void STEPCAFControl_Writer::WriteGeomTolerance (const Handle(XSControl_WorkSession) &WS,
                                                const TDF_LabelSequence& theShapeSeqL,
                                                const TDF_Label& theGeomTolL,
                                                const Handle(StepDimTol_HArray1OfDatumSystemOrReference)& theDatumSystem,
                                                const Handle(StepRepr_RepresentationContext)& theRC)
{
  // Get working data
  const Handle(Interface_InterfaceModel) &Model = WS->Model();
  Handle(XCAFDoc_GeomTolerance) aGTAttr;
  if (!theGeomTolL.FindAttribute(XCAFDoc_GeomTolerance::GetID(), aGTAttr)) 
=======
  aModel->AddWithRefs(aDefinition);
  aModel->AddWithRefs(anOrientation);
  aModel->AddWithRefs(aPAMWU);
}

//=======================================================================
//function : writeGeomTolerance
//purpose  : auxiliary (write Geometric_Tolerance entity for given shapes,
//           label and datum system)
//======================================================================
void STEPCAFControl_Writer::writeGeomTolerance(const Handle(XSControl_WorkSession)& theWS,
                                               const TDF_LabelSequence& theShapeSeqL,
                                               const TDF_Label& theGeomTolL,
                                               const Handle(StepDimTol_HArray1OfDatumSystemOrReference)& theDatumSystem,
                                               const Handle(StepRepr_RepresentationContext)& theRC)
{
  // Get working data
  const Handle(Interface_InterfaceModel)& aModel = theWS->Model();
  Handle(XCAFDoc_GeomTolerance) aGTAttr;
  if (!theGeomTolL.FindAttribute(XCAFDoc_GeomTolerance::GetID(), aGTAttr))
>>>>>>> accb2f351 (u)
    return;
  Handle(XCAFDimTolObjects_GeomToleranceObject) anObject = aGTAttr->GetObject();
  if (anObject.IsNull())
    return;

  // Value
  Handle(StepBasic_LengthMeasureWithUnit) aLMWU = new StepBasic_LengthMeasureWithUnit();
  StepBasic_Unit aUnit = GetUnit(theRC);
  Handle(StepBasic_MeasureValueMember) aValueMember = new StepBasic_MeasureValueMember();
  aValueMember->SetName("LENGTH_MEASURE");
  aValueMember->SetReal(anObject->GetValue());
  aLMWU->Init(aValueMember, aUnit);
<<<<<<< HEAD
  Model->AddWithRefs(aLMWU);
=======
  aModel->AddWithRefs(aLMWU);
>>>>>>> accb2f351 (u)

  // Geometric_Tolerance target
  Handle(StepRepr_ShapeAspect) aMainSA;
  Handle(StepRepr_RepresentationContext) dummyRC;
  Handle(StepAP242_GeometricItemSpecificUsage) dummyGISU;
<<<<<<< HEAD
  if (theShapeSeqL.Length() == 1) {
    TopoDS_Shape aShape = XCAFDoc_ShapeTool::GetShape(theShapeSeqL.Value(1));
    aMainSA = WriteShapeAspect(WS, theGeomTolL, aShape, dummyRC, dummyGISU);
    Model->AddWithRefs(aMainSA);
  }
  else {
    Handle(StepRepr_CompositeShapeAspect) aCSA;
    for (Standard_Integer i = 1; i <= theShapeSeqL.Length(); i++) {
      TopoDS_Shape aShape = XCAFDoc_ShapeTool::GetShape(theShapeSeqL.Value(i));
      Handle(StepRepr_ShapeAspect) aSA = WriteShapeAspect(WS, theGeomTolL, aShape, dummyRC, dummyGISU);
      if (aSA.IsNull())
        continue;
      if (aCSA.IsNull()) {
        aCSA = new StepRepr_CompositeShapeAspect();
        aCSA->Init(aSA->Name(), aSA->Description(), aSA->OfShape(), aSA->ProductDefinitional());
        Model->AddWithRefs(aCSA);
      }
      Handle(StepRepr_ShapeAspectRelationship) aSAR = new StepRepr_ShapeAspectRelationship();
      aSAR->Init(new TCollection_HAsciiString(), Standard_False, NULL, aCSA, aSA);
      Model->AddWithRefs(aSAR);
=======
  if (theShapeSeqL.Length() == 1)
  {
    TopoDS_Shape aShape = XCAFDoc_ShapeTool::GetShape(theShapeSeqL.Value(1));
    aMainSA = writeShapeAspect(theWS, theGeomTolL, aShape, dummyRC, dummyGISU);
    aModel->AddWithRefs(aMainSA);
  }
  else
  {
    Handle(StepRepr_CompositeShapeAspect) aCSA;
    for (TDF_LabelSequence::Iterator aShIter(theShapeSeqL);
         aShIter.More(); aShIter.Next())
    {
      TopoDS_Shape aShape = XCAFDoc_ShapeTool::GetShape(aShIter.Value());
      Handle(StepRepr_ShapeAspect) aSA = writeShapeAspect(theWS, theGeomTolL, aShape, dummyRC, dummyGISU);
      if (aSA.IsNull())
        continue;
      if (aCSA.IsNull())
      {
        aCSA = new StepRepr_CompositeShapeAspect();
        aCSA->Init(aSA->Name(), aSA->Description(), aSA->OfShape(), aSA->ProductDefinitional());
        aModel->AddWithRefs(aCSA);
      }
      Handle(StepRepr_ShapeAspectRelationship) aSAR = new StepRepr_ShapeAspectRelationship();
      aSAR->Init(new TCollection_HAsciiString(), Standard_False, NULL, aCSA, aSA);
      aModel->AddWithRefs(aSAR);
>>>>>>> accb2f351 (u)
    }
    aMainSA = aCSA;
  }
  StepDimTol_GeometricToleranceTarget aGTTarget;
  aGTTarget.SetValue(aMainSA);

  Standard_Boolean isWithModif = Standard_False,
<<<<<<< HEAD
                   isWithDatRef = Standard_False,
                   isWithMaxTol = Standard_False;
=======
    isWithDatRef = Standard_False,
    isWithMaxTol = Standard_False;
>>>>>>> accb2f351 (u)
  // Modifiers
  // Simple modifiers
  XCAFDimTolObjects_GeomToleranceModifiersSequence aModifiers = anObject->GetModifiers();
  Handle(StepDimTol_HArray1OfGeometricToleranceModifier) aModifArray;
  Handle(StepBasic_LengthMeasureWithUnit) aMaxLMWU;
  Standard_Integer aModifNb = aModifiers.Length();
  if (anObject->GetMaterialRequirementModifier() != XCAFDimTolObjects_GeomToleranceMatReqModif_None)
<<<<<<< HEAD
      aModifNb++;
  for (Standard_Integer i = 1; i <= aModifiers.Length(); i++)
    if (aModifiers.Value(i) == XCAFDimTolObjects_GeomToleranceModif_All_Around ||
        aModifiers.Value(i) == XCAFDimTolObjects_GeomToleranceModif_All_Over)
        aModifNb--;
  if (aModifNb > 0) {
    isWithModif = Standard_True;
    aModifArray = new StepDimTol_HArray1OfGeometricToleranceModifier(1, aModifNb);
    Standard_Integer k = 1;
    for (Standard_Integer i = 1; i <= aModifiers.Length(); i++) {
      if (aModifiers.Value(i) == XCAFDimTolObjects_GeomToleranceModif_All_Around ||
        aModifiers.Value(i) == XCAFDimTolObjects_GeomToleranceModif_All_Over)
        continue;
      StepDimTol_GeometricToleranceModifier aModif = 
=======
    aModifNb++;
  for (Standard_Integer i = 1; i <= aModifiers.Length(); i++)
  {
    if (aModifiers.Value(i) == XCAFDimTolObjects_GeomToleranceModif_All_Around ||
        aModifiers.Value(i) == XCAFDimTolObjects_GeomToleranceModif_All_Over)
    {
      aModifNb--;
    }
  }
  if (aModifNb > 0)
  {
    isWithModif = Standard_True;
    aModifArray = new StepDimTol_HArray1OfGeometricToleranceModifier(1, aModifNb);
    Standard_Integer k = 1;
    for (Standard_Integer i = 1; i <= aModifiers.Length(); i++)
    {
      if (aModifiers.Value(i) == XCAFDimTolObjects_GeomToleranceModif_All_Around ||
          aModifiers.Value(i) == XCAFDimTolObjects_GeomToleranceModif_All_Over)
      {
        continue;
      }
      StepDimTol_GeometricToleranceModifier aModif =
>>>>>>> accb2f351 (u)
        STEPCAFControl_GDTProperty::GetGeomToleranceModifier(aModifiers.Value(i));
      aModifArray->SetValue(k, aModif);
      k++;
    }
<<<<<<< HEAD
    if (anObject->GetMaterialRequirementModifier() == XCAFDimTolObjects_GeomToleranceMatReqModif_L) {
      aModifArray->SetValue(aModifNb, StepDimTol_GTMLeastMaterialRequirement);
    }
    else if (anObject->GetMaterialRequirementModifier() == XCAFDimTolObjects_GeomToleranceMatReqModif_M) {
      aModifArray->SetValue(aModifNb, StepDimTol_GTMMaximumMaterialRequirement);
    }
    // Modifier with value
    if (anObject->GetMaxValueModifier() != 0) {
=======
    if (anObject->GetMaterialRequirementModifier() == XCAFDimTolObjects_GeomToleranceMatReqModif_L)
    {
      aModifArray->SetValue(aModifNb, StepDimTol_GTMLeastMaterialRequirement);
    }
    else if (anObject->GetMaterialRequirementModifier() == XCAFDimTolObjects_GeomToleranceMatReqModif_M)
    {
      aModifArray->SetValue(aModifNb, StepDimTol_GTMMaximumMaterialRequirement);
    }
    // Modifier with value
    if (anObject->GetMaxValueModifier() != 0)
    {
>>>>>>> accb2f351 (u)
      isWithMaxTol = Standard_True;
      aMaxLMWU = new StepBasic_LengthMeasureWithUnit();
      Handle(StepBasic_MeasureValueMember) aModifierValueMember = new StepBasic_MeasureValueMember();
      aModifierValueMember->SetName("LENGTH_MEASURE");
      aModifierValueMember->SetReal(anObject->GetMaxValueModifier());
      aMaxLMWU->Init(aModifierValueMember, aUnit);
<<<<<<< HEAD
      Model->AddWithRefs(aMaxLMWU);
=======
      aModel->AddWithRefs(aMaxLMWU);
>>>>>>> accb2f351 (u)
    }
  }

  // Datum Reference
  isWithDatRef = !theDatumSystem.IsNull();

  // Collect all attributes
  Handle(TCollection_HAsciiString) aName = new TCollection_HAsciiString(),
<<<<<<< HEAD
                                  aDescription = new TCollection_HAsciiString();
  Handle(StepDimTol_GeometricToleranceWithDatumReference) aGTWDR = 
    new StepDimTol_GeometricToleranceWithDatumReference();
  aGTWDR->SetDatumSystem(theDatumSystem);
  Handle(StepDimTol_GeometricToleranceWithModifiers) aGTWM = 
    new StepDimTol_GeometricToleranceWithModifiers();
  aGTWM->SetModifiers(aModifArray);
  StepDimTol_GeometricToleranceType aType = 
=======
    aDescription = new TCollection_HAsciiString();
  Handle(StepDimTol_GeometricToleranceWithDatumReference) aGTWDR =
    new StepDimTol_GeometricToleranceWithDatumReference();
  aGTWDR->SetDatumSystem(theDatumSystem);
  Handle(StepDimTol_GeometricToleranceWithModifiers) aGTWM =
    new StepDimTol_GeometricToleranceWithModifiers();
  aGTWM->SetModifiers(aModifArray);
  StepDimTol_GeometricToleranceType aType =
>>>>>>> accb2f351 (u)
    STEPCAFControl_GDTProperty::GetGeomToleranceType(anObject->GetType());

  // Init and write necessary subtype of Geometric_Tolerance entity
  Handle(StepDimTol_GeometricTolerance) aGeomTol;
<<<<<<< HEAD
  if (isWithModif) {
    if (isWithMaxTol) {
      if (isWithDatRef) {
        // Geometric_Tolerance & Geometric_Tolerance_With_Datum_Reference & 
        //Geometric_Tolerance_With_Maximum_Tolerance & Geometric_Tolerance_With_Modifiers
=======
  if (isWithModif)
  {
    if (isWithMaxTol)
    {
      if (isWithDatRef)
      {
        // Geometric_Tolerance & Geometric_Tolerance_With_Datum_Reference &
        // Geometric_Tolerance_With_Maximum_Tolerance & Geometric_Tolerance_With_Modifiers
>>>>>>> accb2f351 (u)
        Handle(StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMaxTol) aResult =
          new StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMaxTol();
        aResult->Init(aName, aDescription, aLMWU, aGTTarget, aGTWDR, aGTWM, aMaxLMWU, aType);
        aGeomTol = aResult;
      }
<<<<<<< HEAD
      else {
=======
      else
      {
>>>>>>> accb2f351 (u)
        // Geometric_Tolerance & Geometric_Tolerance_With_Maximum_Tolerance & Geometric_Tolerance_With_Modifiers
        Handle(StepDimTol_GeoTolAndGeoTolWthMaxTol) aResult =
          new StepDimTol_GeoTolAndGeoTolWthMaxTol();
        aResult->Init(aName, aDescription, aLMWU, aGTTarget, aGTWM, aMaxLMWU, aType);
        aGeomTol = aResult;
      }
    }
<<<<<<< HEAD
    else {
      if (isWithDatRef) {
=======
    else
    {
      if (isWithDatRef)
      {
>>>>>>> accb2f351 (u)
        // Geometric_Tolerance & Geometric_Tolerance_With_Datum_Reference & Geometric_Tolerance_With_Modifiers
        Handle(StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMod) aResult =
          new StepDimTol_GeoTolAndGeoTolWthDatRefAndGeoTolWthMod();
        aResult->Init(aName, aDescription, aLMWU, aGTTarget, aGTWDR, aGTWM, aType);
        aGeomTol = aResult;
      }
<<<<<<< HEAD
      else {
=======
      else
      {
>>>>>>> accb2f351 (u)
        // Geometric_Tolerance & Geometric_Tolerance_With_Modifiers
        Handle(StepDimTol_GeoTolAndGeoTolWthMod) aResult =
          new StepDimTol_GeoTolAndGeoTolWthMod();
        aResult->Init(aName, aDescription, aLMWU, aGTTarget, aGTWM, aType);
        aGeomTol = aResult;
      }
    }
  }
<<<<<<< HEAD
  else {
    if (isWithDatRef) {
      // Geometric_Tolerance & Geometric_Tolerance_With_Datum_Reference
      Handle(StepDimTol_GeoTolAndGeoTolWthDatRef) aResult =
          new StepDimTol_GeoTolAndGeoTolWthDatRef();
        aResult->Init(aName, aDescription, aLMWU, aGTTarget, aGTWDR, aType);
        aGeomTol = aResult;
    }
    else {
      // Geometric_Tolerance
      Handle(StepDimTol_GeometricTolerance) aResult = 
        STEPCAFControl_GDTProperty::GetGeomTolerance(anObject->GetType());
      if (!aResult.IsNull()) {
=======
  else
  {
    if (isWithDatRef)
    {
      // Geometric_Tolerance & Geometric_Tolerance_With_Datum_Reference
      Handle(StepDimTol_GeoTolAndGeoTolWthDatRef) aResult =
        new StepDimTol_GeoTolAndGeoTolWthDatRef();
      aResult->Init(aName, aDescription, aLMWU, aGTTarget, aGTWDR, aType);
      aGeomTol = aResult;
    }
    else
    {
      // Geometric_Tolerance
      Handle(StepDimTol_GeometricTolerance) aResult =
        STEPCAFControl_GDTProperty::GetGeomTolerance(anObject->GetType());
      if (!aResult.IsNull())
      {
>>>>>>> accb2f351 (u)
        aResult->Init(aName, aDescription, aLMWU, aGTTarget);
        aGeomTol = aResult;
      }
    }
  }
<<<<<<< HEAD
  Model->AddWithRefs(aGeomTol);
  WriteToleranceZone(WS, anObject, aGeomTol, theRC);
  //Annotation plane and Presentation
  WritePresentation(WS, anObject->GetPresentation(), anObject->GetPresentationName(), Standard_True, anObject->HasPlane(),
    anObject->GetPlane(), anObject->GetPointTextAttach(), aGeomTol);
}

//=======================================================================
//function : WriteDGTs
//purpose  : 
//=======================================================================
Standard_Boolean STEPCAFControl_Writer::WriteDGTs (const Handle(XSControl_WorkSession) &WS,
                                                   const TDF_LabelSequence  &labels ) const
{
  
  if ( labels.Length() <=0 ) return Standard_False;
  
  // get working data
  const Handle(Interface_InterfaceModel) &Model = WS->Model();
  const Handle(XSControl_TransferWriter) &TW = WS->TransferWriter();
  const Handle(Transfer_FinderProcess) &FP = TW->FinderProcess();

  const Handle(Interface_HGraph) aHGraph = WS->HGraph();
  if(aHGraph.IsNull())
    return Standard_False;

  Interface_Graph aGraph = aHGraph->Graph();
  Handle(XCAFDoc_DimTolTool) DGTTool = XCAFDoc_DocumentTool::DimTolTool( labels(1) );
  if(DGTTool.IsNull() ) return Standard_False;

  TDF_LabelSequence DGTLabels;

  STEPConstruct_DataMapOfAsciiStringTransient DatumMap;

  // write Datums
  DGTLabels.Clear();
  DGTTool->GetDatumLabels(DGTLabels);
  if(DGTLabels.Length()<=0) return Standard_False;
  Standard_Integer i;
  for(i=1; i<=DGTLabels.Length(); i++) {
    TDF_Label DatumL = DGTLabels.Value(i);
    TDF_LabelSequence ShapeL;
    TDF_LabelSequence aNullSeq;
    if(!DGTTool->GetRefShapeLabel(DatumL,ShapeL,aNullSeq)) continue;
    // find target shape
    TopoDS_Shape aShape = XCAFDoc_ShapeTool::GetShape(ShapeL.Value(1));
    TopLoc_Location Loc;
    TColStd_SequenceOfTransient seqRI;
    FindEntities( FP, aShape, Loc, seqRI );
    if ( seqRI.Length() <= 0 ) {
      FP->Messenger()->SendInfo() << "Warning: Cannot find RI for "<<aShape.TShape()->DynamicType()->Name()<<std::endl;
      continue;
    }
    Handle(StepRepr_ProductDefinitionShape) PDS;
    Handle(StepRepr_RepresentationContext) RC;
    Handle(Standard_Transient) ent = seqRI.Value(1);
    Handle(StepShape_AdvancedFace) AF;
    Handle(StepShape_EdgeCurve) EC;
    FindPDSforDGT(aGraph,ent,PDS,RC,AF,EC);
    if(PDS.IsNull()) continue;
    //std::cout<<"Model->Number(PDS)="<<Model->Number(PDS)<<std::endl;
    Handle(XCAFDoc_Datum) DatumAttr;
    if(!DatumL.FindAttribute(XCAFDoc_Datum::GetID(),DatumAttr)) continue;
    Handle(TCollection_HAsciiString) aName = DatumAttr->GetName();
    Handle(TCollection_HAsciiString) anIdentification = DatumAttr->GetIdentification();
    Handle(TCollection_HAsciiString) aDescription = DatumAttr->GetDescription();
=======
  aModel->AddWithRefs(aGeomTol);
  writeToleranceZone(theWS, anObject, aGeomTol, theRC);
  //Annotation plane and Presentation
  writePresentation(theWS, anObject->GetPresentation(), anObject->GetPresentationName(), Standard_True, anObject->HasPlane(),
                    anObject->GetPlane(), anObject->GetPointTextAttach(), aGeomTol);
}

//=======================================================================
//function : writeDGTs
//purpose  :
//=======================================================================
Standard_Boolean STEPCAFControl_Writer::writeDGTs(const Handle(XSControl_WorkSession)& theWS,
                                                  const TDF_LabelSequence& theLabels) const
{

  if (theLabels.IsEmpty())
    return Standard_False;

  // get working data
  const Handle(Interface_InterfaceModel)& aModel = theWS->Model();
  const Handle(XSControl_TransferWriter)& aTW = theWS->TransferWriter();
  const Handle(Transfer_FinderProcess)& aFP = aTW->FinderProcess();

  const Handle(Interface_HGraph) aHGraph = theWS->HGraph();
  if (aHGraph.IsNull())
    return Standard_False;

  Interface_Graph aGraph = aHGraph->Graph();
  STEPConstruct_DataMapOfAsciiStringTransient aDatumMap;

  TDF_LabelSequence aDGTLabels;
  // Iterate on requested shapes collect Tools
  for (TDF_LabelMap::Iterator aLabelIter(myRootLabels);
       aLabelIter.More(); aLabelIter.Next())
  {
    const TDF_Label& aLabel = aLabelIter.Value();
    Handle(XCAFDoc_DimTolTool) aDGTTool = XCAFDoc_DocumentTool::DimTolTool(aLabel);
    TDF_LabelSequence aDGTLS;
    aDGTTool->GetDatumLabels(aDGTLS);
    aDGTLabels.Append(aDGTLS);
  }

  if (aDGTLabels.IsEmpty())
    return Standard_False;

  for (TDF_LabelSequence::Iterator aDGTIter(aDGTLabels);
       aDGTIter.More(); aDGTIter.Next())
  {
    const TDF_Label& aDatumL = aDGTIter.Value();
    TDF_LabelSequence aShapeL;
    TDF_LabelSequence aNullSeq;
    if (!XCAFDoc_DimTolTool::GetRefShapeLabel(aDatumL, aShapeL, aNullSeq)) continue;
    // find target shape
    TopoDS_Shape aShape = XCAFDoc_ShapeTool::GetShape(aShapeL.Value(1));
    TopLoc_Location aLoc;
    TColStd_SequenceOfTransient aSeqRI;
    FindEntities(aFP, aShape, aLoc, aSeqRI);
    if (aSeqRI.IsEmpty())
    {
      Message::SendTrace() << "Warning: Cannot find RI for " << aShape.TShape()->DynamicType()->Name() << "\n";
      continue;
    }
    Handle(StepRepr_ProductDefinitionShape) aPDS;
    Handle(StepRepr_RepresentationContext) aRC;
    Handle(Standard_Transient) anEnt = aSeqRI.Value(1);
    Handle(StepShape_AdvancedFace) anAF;
    Handle(StepShape_EdgeCurve) anEC;
    FindPDSforDGT(aGraph, anEnt, aPDS, aRC, anAF, anEC);
    if (aPDS.IsNull())
      continue;
    Handle(XCAFDoc_Datum) aDatumAttr;
    if (!aDatumL.FindAttribute(XCAFDoc_Datum::GetID(), aDatumAttr))
      continue;
    Handle(TCollection_HAsciiString) aName = aDatumAttr->GetName();
    Handle(TCollection_HAsciiString) anIdentification = aDatumAttr->GetIdentification();
    Handle(TCollection_HAsciiString) aDescription = aDatumAttr->GetDescription();
>>>>>>> accb2f351 (u)
    if (aDescription.IsNull())
    {
      aDescription = new TCollection_HAsciiString();
    }
<<<<<<< HEAD
    Handle(StepDimTol_DatumFeature) DF = new StepDimTol_DatumFeature;
    Handle(StepDimTol_Datum) aDatum = new StepDimTol_Datum;
    DF->Init(aName, new TCollection_HAsciiString, PDS, StepData_LTrue);
    Model->AddWithRefs(DF);
    aDatum->Init(aName, new TCollection_HAsciiString, PDS, StepData_LFalse, anIdentification);
    Model->AddWithRefs(aDatum);
    Handle(StepRepr_ShapeAspectRelationship) SAR = new StepRepr_ShapeAspectRelationship;
    SAR->SetName(aName);
    SAR->SetRelatingShapeAspect(DF);
    SAR->SetRelatedShapeAspect(aDatum);
    Model->AddWithRefs(SAR);
    // write chain for DatumFeature
    StepRepr_CharacterizedDefinition CD;
    CD.SetValue(DF);
    Handle(StepRepr_PropertyDefinition) PropD = new StepRepr_PropertyDefinition;
    PropD->Init(aName,Standard_True,aDescription,CD);
    Model->AddWithRefs(PropD);
    StepRepr_RepresentedDefinition RD;
    RD.SetValue(PropD);
    Handle(StepShape_ShapeRepresentation) SR = new StepShape_ShapeRepresentation;
    Handle(StepRepr_HArray1OfRepresentationItem) HARI =
      new StepRepr_HArray1OfRepresentationItem(1,1);
    HARI->SetValue(1,AF);
    SR->Init(aName,HARI,RC);
    Handle(StepShape_ShapeDefinitionRepresentation) SDR = new StepShape_ShapeDefinitionRepresentation;
    SDR->Init(RD,SR);
    Model->AddWithRefs(SDR);
    // write chain for Datum 
    StepRepr_CharacterizedDefinition CD1;
    CD1.SetValue(aDatum);
    Handle(StepRepr_PropertyDefinition) PropD1 = new StepRepr_PropertyDefinition;
    PropD1->Init(aName,Standard_True,aDescription,CD1);
    Model->AddWithRefs(PropD1);
    StepRepr_RepresentedDefinition RD1;
    RD1.SetValue(PropD1);
    Handle(StepShape_ShapeRepresentation) SR1 = new StepShape_ShapeRepresentation;
    Handle(StepRepr_HArray1OfRepresentationItem) HARI1 =
      new StepRepr_HArray1OfRepresentationItem(1,1);
    HARI1->SetValue(1,AF->FaceGeometry());
    SR1->Init(aName,HARI1,RC);
    Model->AddWithRefs(SR1);
    Handle(StepShape_ShapeDefinitionRepresentation) SDR1 = new StepShape_ShapeDefinitionRepresentation;
    SDR1->Init(RD1,SR1);
    Model->AddWithRefs(SDR1);
    // add created Datum into Map
    TCollection_AsciiString stmp(aName->ToCString());
    stmp.AssignCat(aDescription->ToCString());
    stmp.AssignCat(anIdentification->ToCString());
    DatumMap.Bind(stmp,aDatum);
  }

  // write Tolerances and Dimensions
  DGTLabels.Clear();
  DGTTool->GetDimTolLabels(DGTLabels);
  if(DGTLabels.Length()<=0) return Standard_False;
  for(i=1; i<=DGTLabels.Length(); i++) {
    TDF_Label DimTolL = DGTLabels.Value(i);
    TDF_LabelSequence ShapeL;
    TDF_LabelSequence aNullSeq;
    if(!DGTTool->GetRefShapeLabel(DimTolL,ShapeL,aNullSeq)) continue;
    // find target shape
    TopoDS_Shape aShape = XCAFDoc_ShapeTool::GetShape(ShapeL.Value(1));
    TopLoc_Location Loc;
    TColStd_SequenceOfTransient seqRI;
    FindEntities( FP, aShape, Loc, seqRI );
    if ( seqRI.Length() <= 0 ) {
      FP->Messenger()->SendInfo() << "Warning: Cannot find RI for "<<aShape.TShape()->DynamicType()->Name()<<std::endl;
      continue;
    }
    Handle(StepRepr_ProductDefinitionShape) PDS;
    Handle(StepRepr_RepresentationContext) RC;
    Handle(Standard_Transient) ent = seqRI.Value(1);
    Handle(StepShape_AdvancedFace) AF;
    Handle(StepShape_EdgeCurve) EC;
    FindPDSforDGT(aGraph,ent,PDS,RC,AF,EC);
    if(PDS.IsNull()) continue;
    //std::cout<<"Model->Number(PDS)="<<Model->Number(PDS)<<std::endl;

    Handle(XCAFDoc_DimTol) DimTolAttr;
    if(!DimTolL.FindAttribute(XCAFDoc_DimTol::GetID(),DimTolAttr)) continue;
    Standard_Integer kind = DimTolAttr->GetKind();
    Handle(TColStd_HArray1OfReal) aVal = DimTolAttr->GetVal();
    Handle(TCollection_HAsciiString) aName = DimTolAttr->GetName();
    Handle(TCollection_HAsciiString) aDescription = DimTolAttr->GetDescription();

    // common part of writing D&GT entities
    StepRepr_CharacterizedDefinition CD;
    Handle(StepRepr_ShapeAspect) SA = new StepRepr_ShapeAspect;
    SA->Init(aName, new TCollection_HAsciiString, PDS, StepData_LTrue);
    Model->AddWithRefs(SA);
    CD.SetValue(SA);
    Handle(StepRepr_PropertyDefinition) PropD = new StepRepr_PropertyDefinition;
    PropD->Init(aName,Standard_True,aDescription,CD);
    Model->AddWithRefs(PropD);
    StepRepr_RepresentedDefinition RD;
    RD.SetValue(PropD);
    Handle(StepShape_ShapeRepresentation) SR = new StepShape_ShapeRepresentation;
    Handle(StepRepr_HArray1OfRepresentationItem) HARI =
      new StepRepr_HArray1OfRepresentationItem(1,1);
    if(kind<20) 
      HARI->SetValue(1,EC);
    else
      HARI->SetValue(1,AF);
    SR->Init(aName,HARI,RC);
    Handle(StepShape_ShapeDefinitionRepresentation) SDR = new StepShape_ShapeDefinitionRepresentation;
    SDR->Init(RD,SR);
    Model->AddWithRefs(SDR);
    // define aUnit for creation LengthMeasureWithUnit (common for all)
    StepBasic_Unit aUnit;
    aUnit = GetUnit(RC);

    // specific part of writing D&GT entities
    if(kind<20) { //dimension
      Handle(StepShape_DimensionalSize) DimSize = new StepShape_DimensionalSize;
      DimSize->Init(SA,aDescription);
      Model->AddWithRefs(DimSize);
      if(aVal->Length()>1) {
        // create MeasureWithUnits
        Handle(StepBasic_MeasureValueMember) MVM1 = new StepBasic_MeasureValueMember;
        MVM1->SetName("POSITIVE_LENGTH_MEASURE");
        MVM1->SetReal(aVal->Value(1));
        Handle(StepBasic_MeasureWithUnit) MWU1 = new StepBasic_MeasureWithUnit;
        MWU1->Init(MVM1,aUnit);
        Handle(StepBasic_MeasureValueMember) MVM2 = new StepBasic_MeasureValueMember;
        MVM2->SetName("POSITIVE_LENGTH_MEASURE");
        MVM2->SetReal(aVal->Value(2));
        Handle(StepBasic_MeasureWithUnit) MWU2 = new StepBasic_MeasureWithUnit;
        MWU2->Init(MVM2,aUnit);
        Handle(StepRepr_RepresentationItem) RI1 = new StepRepr_RepresentationItem;
        RI1->Init(new TCollection_HAsciiString("lower limit"));
        Handle(StepRepr_RepresentationItem) RI2 = new StepRepr_RepresentationItem;
        RI2->Init(new TCollection_HAsciiString("upper limit"));
        Handle(StepRepr_ReprItemAndLengthMeasureWithUnit) RILMU1 =
          new StepRepr_ReprItemAndLengthMeasureWithUnit;
        RILMU1->Init(MWU1,RI1);
        Handle(StepRepr_ReprItemAndLengthMeasureWithUnit) RILMU2 =
          new StepRepr_ReprItemAndLengthMeasureWithUnit;
        RILMU2->Init(MWU2,RI2);
        Model->AddWithRefs(RILMU1);
        Model->AddWithRefs(RILMU2);
        //Handle(StepRepr_CompoundItemDefinitionMember) CIDM =
        //  new StepRepr_CompoundItemDefinitionMember;
        //Handle(TColStd_HArray1OfTransient) ArrTr = new TColStd_HArray1OfTransient(1,2);
        //ArrTr->SetValue(1,RILMU1);
        //ArrTr->SetValue(2,RILMU2);
        //CIDM->SetArrTransient(ArrTr);
        //CIDM->SetName("SET_REPRESENTATION_ITEM");
        //StepRepr_CompoundItemDefinition CID;
        //CID.SetValue(CIDM);
        Handle(StepRepr_HArray1OfRepresentationItem) HARIVR =
          new StepRepr_HArray1OfRepresentationItem(1,2);
        HARIVR->SetValue(1,RILMU1);
        HARIVR->SetValue(2,RILMU2);
        Handle(StepRepr_ValueRange) VR = new StepRepr_ValueRange;
        //VR->Init(aName,CID);
        VR->Init(aName,HARIVR);
        Model->AddEntity(VR);
        Handle(StepShape_ShapeDimensionRepresentation) SDimR =
          new StepShape_ShapeDimensionRepresentation;
        Handle(StepRepr_HArray1OfRepresentationItem) aHARI =
          new StepRepr_HArray1OfRepresentationItem(1,1);
        aHARI->SetValue(1,VR);
        SDimR->Init(aName,aHARI,RC);
        Model->AddWithRefs(SDimR);
        Handle(StepShape_DimensionalCharacteristicRepresentation) DimCharR =
          new StepShape_DimensionalCharacteristicRepresentation;
        StepShape_DimensionalCharacteristic DimChar;
        DimChar.SetValue(DimSize);
        DimCharR->Init(DimChar,SDimR);
        Model->AddEntity(DimCharR);
      }
    }
    else if(kind<50) { //tolerance
      if(kind<35) { // tolerance with datum system
        TDF_LabelSequence DatumLabels;
        DGTTool->GetDatumOfTolerLabels(DimTolL,DatumLabels);
        Standard_Integer NbDR = DatumLabels.Length();
        Handle(StepDimTol_HArray1OfDatumReference) HADR = new StepDimTol_HArray1OfDatumReference(1,NbDR);
        for(Standard_Integer j=1; j<=NbDR; j++) {
          Handle(XCAFDoc_Datum) DatumAttr;
          TDF_Label DatumL = DatumLabels.Value(j);
          if(!DatumL.FindAttribute(XCAFDoc_Datum::GetID(),DatumAttr)) continue;
          Handle(TCollection_HAsciiString) aNameD = DatumAttr->GetName();
          Handle(TCollection_HAsciiString) aDescriptionD = DatumAttr->GetDescription();
          Handle(TCollection_HAsciiString) anIdentificationD = DatumAttr->GetIdentification();
          TCollection_AsciiString stmp(aNameD->ToCString());
          stmp.AssignCat(aDescriptionD->ToCString());
          stmp.AssignCat(anIdentificationD->ToCString());
          if(DatumMap.IsBound(stmp)) {
            Handle(StepDimTol_Datum) aDatum = 
              Handle(StepDimTol_Datum)::DownCast(DatumMap.Find(stmp));
            Handle(StepDimTol_DatumReference) DR = new StepDimTol_DatumReference;
            DR->Init(j,aDatum);
            Model->AddWithRefs(DR);
            HADR->SetValue(j,DR);
          }
        }
        // create LengthMeasureWithUnit
        Handle(StepBasic_MeasureValueMember) MVM = new StepBasic_MeasureValueMember;
        MVM->SetName("LENGTH_MEASURE");
        MVM->SetReal(aVal->Value(1));
        Handle(StepBasic_LengthMeasureWithUnit) LMWU = new StepBasic_LengthMeasureWithUnit;
        LMWU->Init(MVM,aUnit);
        // create tolerance by it's type
        if(kind<24) {
          Handle(StepDimTol_GeometricToleranceWithDatumReference) GTWDR =
            new StepDimTol_GeometricToleranceWithDatumReference;
          GTWDR->SetDatumSystem(HADR);
          Handle(StepDimTol_ModifiedGeometricTolerance) MGT =
            new StepDimTol_ModifiedGeometricTolerance;
          if(kind==21) MGT->SetModifier(StepDimTol_MaximumMaterialCondition);
          else if(kind==22) MGT->SetModifier(StepDimTol_LeastMaterialCondition);
          else if(kind==23) MGT->SetModifier(StepDimTol_RegardlessOfFeatureSize);
          Handle(StepDimTol_GeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol) GTComplex =
            new StepDimTol_GeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol;
          GTComplex->Init(aName,aDescription,LMWU,SA,GTWDR,MGT);
          Model->AddWithRefs(GTComplex);
        }
        else if(kind==24) {
          Handle(StepDimTol_AngularityTolerance) aToler =
            new StepDimTol_AngularityTolerance;
          aToler->Init(aName,aDescription,LMWU,SA,HADR);
          Model->AddWithRefs(aToler);
        }
        else if(kind==25) {
          Handle(StepDimTol_CircularRunoutTolerance) aToler =
            new StepDimTol_CircularRunoutTolerance;
          aToler->Init(aName,aDescription,LMWU,SA,HADR);
          Model->AddWithRefs(aToler);
        }
        else if(kind==26) {
          Handle(StepDimTol_CoaxialityTolerance) aToler =
            new StepDimTol_CoaxialityTolerance;
          aToler->Init(aName,aDescription,LMWU,SA,HADR);
          Model->AddWithRefs(aToler);
        }
        else if(kind==27) {
          Handle(StepDimTol_ConcentricityTolerance) aToler =
            new StepDimTol_ConcentricityTolerance;
          aToler->Init(aName,aDescription,LMWU,SA,HADR);
          Model->AddWithRefs(aToler);
        }
        else if(kind==28) {
          Handle(StepDimTol_ParallelismTolerance) aToler =
            new StepDimTol_ParallelismTolerance;
          aToler->Init(aName,aDescription,LMWU,SA,HADR);
          Model->AddWithRefs(aToler);
        }
        else if(kind==29) {
          Handle(StepDimTol_PerpendicularityTolerance) aToler =
            new StepDimTol_PerpendicularityTolerance;
          aToler->Init(aName,aDescription,LMWU,SA,HADR);
          Model->AddWithRefs(aToler);
        }
        else if(kind==30) {
          Handle(StepDimTol_SymmetryTolerance) aToler =
            new StepDimTol_SymmetryTolerance;
          aToler->Init(aName,aDescription,LMWU,SA,HADR);
          Model->AddWithRefs(aToler);
        }
        else if(kind==31) {
          Handle(StepDimTol_TotalRunoutTolerance) aToler =
            new StepDimTol_TotalRunoutTolerance;
          aToler->Init(aName,aDescription,LMWU,SA,HADR);
          Model->AddWithRefs(aToler);
=======
    Handle(StepDimTol_DatumFeature) aDF = new StepDimTol_DatumFeature;
    Handle(StepDimTol_Datum) aDatum = new StepDimTol_Datum;
    aDF->Init(aName, new TCollection_HAsciiString, aPDS, StepData_LTrue);
    aModel->AddWithRefs(aDF);
    aDatum->Init(aName, new TCollection_HAsciiString, aPDS, StepData_LFalse, anIdentification);
    aModel->AddWithRefs(aDatum);
    Handle(StepRepr_ShapeAspectRelationship) aSAR = new StepRepr_ShapeAspectRelationship;
    aSAR->SetName(aName);
    aSAR->SetRelatingShapeAspect(aDF);
    aSAR->SetRelatedShapeAspect(aDatum);
    aModel->AddWithRefs(aSAR);
    // write chain for DatumFeature
    StepRepr_CharacterizedDefinition aCD;
    aCD.SetValue(aDF);
    Handle(StepRepr_PropertyDefinition) aPropD = new StepRepr_PropertyDefinition;
    aPropD->Init(aName, Standard_True, aDescription, aCD);
    aModel->AddWithRefs(aPropD);
    StepRepr_RepresentedDefinition aRD;
    aRD.SetValue(aPropD);
    Handle(StepShape_ShapeRepresentation) aSR = new StepShape_ShapeRepresentation;
    Handle(StepRepr_HArray1OfRepresentationItem) aHARI =
      new StepRepr_HArray1OfRepresentationItem(1, 1);
    aHARI->SetValue(1, anAF);
    aSR->Init(aName, aHARI, aRC);
    Handle(StepShape_ShapeDefinitionRepresentation) aSDR = new StepShape_ShapeDefinitionRepresentation;
    aSDR->Init(aRD, aSR);
    aModel->AddWithRefs(aSDR);
    // write chain for Datum
    StepRepr_CharacterizedDefinition aCD1;
    aCD1.SetValue(aDatum);
    Handle(StepRepr_PropertyDefinition) aPropD1 = new StepRepr_PropertyDefinition;
    aPropD1->Init(aName, Standard_True, aDescription, aCD1);
    aModel->AddWithRefs(aPropD1);
    StepRepr_RepresentedDefinition aRD1;
    aRD1.SetValue(aPropD1);
    Handle(StepShape_ShapeRepresentation) aSR1 = new StepShape_ShapeRepresentation;
    Handle(StepRepr_HArray1OfRepresentationItem) aHARI1 =
      new StepRepr_HArray1OfRepresentationItem(1, 1);
    aHARI1->SetValue(1, anAF->FaceGeometry());
    aSR1->Init(aName, aHARI1, aRC);
    aModel->AddWithRefs(aSR1);
    Handle(StepShape_ShapeDefinitionRepresentation) aSDR1 = new StepShape_ShapeDefinitionRepresentation;
    aSDR1->Init(aRD1, aSR1);
    aModel->AddWithRefs(aSDR1);
    // add created Datum into Map
    TCollection_AsciiString aStmp(aName->ToCString());
    aStmp.AssignCat(aDescription->ToCString());
    aStmp.AssignCat(anIdentification->ToCString());
    aDatumMap.Bind(aStmp, aDatum);
  }

  // write Tolerances and Dimensions
  aDGTLabels.Clear();
  // Iterate on requested shapes collect Tools
  for (TDF_LabelMap::Iterator aLabelIter(myRootLabels);
       aLabelIter.More(); aLabelIter.Next())
  {
    const TDF_Label& aLabel = aLabelIter.Value();
    Handle(XCAFDoc_DimTolTool) aDGTTool = XCAFDoc_DocumentTool::DimTolTool(aLabel);
    TDF_LabelSequence aaDGTLS;
    aDGTTool->GetDimTolLabels(aDGTLabels);
    aDGTLabels.Append(aaDGTLS);
  }

  if (aDGTLabels.IsEmpty())
    return Standard_False;
  for (TDF_LabelSequence::Iterator aDGTIter(aDGTLabels);
       aDGTIter.More(); aDGTIter.Next())
  {
    const TDF_Label& aDimTolL = aDGTIter.Value();
    TDF_LabelSequence aShapeL;
    TDF_LabelSequence aNullSeq;
    if (!XCAFDoc_DimTolTool::GetRefShapeLabel(aDimTolL, aShapeL, aNullSeq))
      continue;
    // find target shape
    TopoDS_Shape aShape = XCAFDoc_ShapeTool::GetShape(aShapeL.Value(1));
    TopLoc_Location aLoc;
    TColStd_SequenceOfTransient seqRI;
    FindEntities(aFP, aShape, aLoc, seqRI);
    if (seqRI.IsEmpty())
    {
      Message::SendTrace() << "Warning: Cannot find RI for " << aShape.TShape()->DynamicType()->Name() << "\n";
      continue;
    }
    Handle(StepRepr_ProductDefinitionShape) aPDS;
    Handle(StepRepr_RepresentationContext) aRC;
    Handle(Standard_Transient) anEnt = seqRI.Value(1);
    Handle(StepShape_AdvancedFace) anAF;
    Handle(StepShape_EdgeCurve) anEC;
    FindPDSforDGT(aGraph, anEnt, aPDS, aRC, anAF, anEC);
    if (aPDS.IsNull())
      continue;

    Handle(XCAFDoc_DimTol) aDimTolAttr;
    if (!aDimTolL.FindAttribute(XCAFDoc_DimTol::GetID(), aDimTolAttr))
      continue;
    Standard_Integer aKind = aDimTolAttr->GetKind();
    Handle(TColStd_HArray1OfReal) aVal = aDimTolAttr->GetVal();
    Handle(TCollection_HAsciiString) aName = aDimTolAttr->GetName();
    Handle(TCollection_HAsciiString) aDescription = aDimTolAttr->GetDescription();

    // common part of writing D&GT entities
    StepRepr_CharacterizedDefinition aCD;
    Handle(StepRepr_ShapeAspect) aSA = new StepRepr_ShapeAspect;
    aSA->Init(aName, new TCollection_HAsciiString, aPDS, StepData_LTrue);
    aModel->AddWithRefs(aSA);
    aCD.SetValue(aSA);
    Handle(StepRepr_PropertyDefinition) aPropD = new StepRepr_PropertyDefinition;
    aPropD->Init(aName, Standard_True, aDescription, aCD);
    aModel->AddWithRefs(aPropD);
    StepRepr_RepresentedDefinition aRD;
    aRD.SetValue(aPropD);
    Handle(StepShape_ShapeRepresentation) aSR = new StepShape_ShapeRepresentation;
    Handle(StepRepr_HArray1OfRepresentationItem) aHARI =
      new StepRepr_HArray1OfRepresentationItem(1, 1);
    if (aKind < 20)
      aHARI->SetValue(1, anEC);
    else
      aHARI->SetValue(1, anAF);
    aSR->Init(aName, aHARI, aRC);
    Handle(StepShape_ShapeDefinitionRepresentation) aSDR = new StepShape_ShapeDefinitionRepresentation;
    aSDR->Init(aRD, aSR);
    aModel->AddWithRefs(aSDR);
    // define aUnit for creation LengthMeasureWithUnit (common for all)
    StepBasic_Unit aUnit;
    aUnit = GetUnit(aRC);

    // specific part of writing D&GT entities
    if (aKind < 20)
    { //dimension
      Handle(StepShape_DimensionalSize) aDimSize = new StepShape_DimensionalSize;
      aDimSize->Init(aSA, aDescription);
      aModel->AddWithRefs(aDimSize);
      if (aVal->Length() > 1)
      {
        // create MeasureWithUnits
        Handle(StepBasic_MeasureValueMember) aMVM1 = new StepBasic_MeasureValueMember;
        aMVM1->SetName("POSITIVE_LENGTH_MEASURE");
        aMVM1->SetReal(aVal->Value(1));
        Handle(StepBasic_MeasureWithUnit) aMWU1 = new StepBasic_MeasureWithUnit;
        aMWU1->Init(aMVM1, aUnit);
        Handle(StepBasic_MeasureValueMember) aMVM2 = new StepBasic_MeasureValueMember;
        aMVM2->SetName("POSITIVE_LENGTH_MEASURE");
        aMVM2->SetReal(aVal->Value(2));
        Handle(StepBasic_MeasureWithUnit) aMWU2 = new StepBasic_MeasureWithUnit;
        aMWU2->Init(aMVM2, aUnit);
        Handle(StepRepr_RepresentationItem) aRI1 = new StepRepr_RepresentationItem;
        aRI1->Init(new TCollection_HAsciiString("lower limit"));
        Handle(StepRepr_RepresentationItem) aRI2 = new StepRepr_RepresentationItem;
        aRI2->Init(new TCollection_HAsciiString("upper limit"));
        Handle(StepRepr_ReprItemAndLengthMeasureWithUnit) aRILMU1 =
          new StepRepr_ReprItemAndLengthMeasureWithUnit;
        aRILMU1->Init(aMWU1, aRI1);
        Handle(StepRepr_ReprItemAndLengthMeasureWithUnit) aRILMU2 =
          new StepRepr_ReprItemAndLengthMeasureWithUnit;
        aRILMU2->Init(aMWU2, aRI2);
        aModel->AddWithRefs(aRILMU1);
        aModel->AddWithRefs(aRILMU2);
        Handle(StepRepr_HArray1OfRepresentationItem) aHARIVR =
          new StepRepr_HArray1OfRepresentationItem(1, 2);
        aHARIVR->SetValue(1, aRILMU1);
        aHARIVR->SetValue(2, aRILMU2);
        Handle(StepRepr_ValueRange) aVR = new StepRepr_ValueRange;
        //VR->Init(aName,CID);
        aVR->Init(aName, aHARIVR);
        aModel->AddEntity(aVR);
        Handle(StepShape_ShapeDimensionRepresentation) aSDimR =
          new StepShape_ShapeDimensionRepresentation;
        Handle(StepRepr_HArray1OfRepresentationItem) aHARI1 =
          new StepRepr_HArray1OfRepresentationItem(1, 1);
        aHARI1->SetValue(1, aVR);
        aSDimR->Init(aName, aHARI1, aRC);
        aModel->AddWithRefs(aSDimR);
        Handle(StepShape_DimensionalCharacteristicRepresentation) aDimCharR =
          new StepShape_DimensionalCharacteristicRepresentation;
        StepShape_DimensionalCharacteristic aDimChar;
        aDimChar.SetValue(aDimSize);
        aDimCharR->Init(aDimChar, aSDimR);
        aModel->AddEntity(aDimCharR);
      }
    }
    else if (aKind < 50)
    { //tolerance
      if (aKind < 35)
      { // tolerance with datum system
        TDF_LabelSequence aDatumLabels;
        XCAFDoc_DimTolTool::GetDatumOfTolerLabels(aDimTolL, aDatumLabels);
        Standard_Integer aSetDatumInd = 1;
        Handle(StepDimTol_HArray1OfDatumReference) aHADR =
          new StepDimTol_HArray1OfDatumReference(1, aDatumLabels.Length());
        for (TDF_LabelSequence::Iterator aDatumIter(aDatumLabels);
             aDatumIter.More(); aDatumIter.Next(), aSetDatumInd++)
        {
          Handle(XCAFDoc_Datum) aDatumAttr;
          const TDF_Label& aDatumL = aDatumIter.Value();
          if (!aDatumL.FindAttribute(XCAFDoc_Datum::GetID(), aDatumAttr))
            continue;
          Handle(TCollection_HAsciiString) aNameD = aDatumAttr->GetName();
          Handle(TCollection_HAsciiString) aDescriptionD = aDatumAttr->GetDescription();
          Handle(TCollection_HAsciiString) anIdentificationD = aDatumAttr->GetIdentification();
          TCollection_AsciiString aStmp(aNameD->ToCString());
          aStmp.AssignCat(aDescriptionD->ToCString());
          aStmp.AssignCat(anIdentificationD->ToCString());
          if (aDatumMap.IsBound(aStmp))
          {
            Handle(StepDimTol_Datum) aDatum =
              Handle(StepDimTol_Datum)::DownCast(aDatumMap.Find(aStmp));
            Handle(StepDimTol_DatumReference) aDR = new StepDimTol_DatumReference;
            aDR->Init(aSetDatumInd, aDatum);
            aModel->AddWithRefs(aDR);
            aHADR->SetValue(aSetDatumInd, aDR);
          }
        }
        // create LengthMeasureWithUnit
        Handle(StepBasic_MeasureValueMember) aMVM = new StepBasic_MeasureValueMember;
        aMVM->SetName("LENGTH_MEASURE");
        aMVM->SetReal(aVal->Value(1));
        Handle(StepBasic_LengthMeasureWithUnit) aLMWU = new StepBasic_LengthMeasureWithUnit;
        aLMWU->Init(aMVM, aUnit);
        // create tolerance by it's type
        if (aKind < 24)
        {
          Handle(StepDimTol_GeometricToleranceWithDatumReference) aGTWDR =
            new StepDimTol_GeometricToleranceWithDatumReference;
          aGTWDR->SetDatumSystem(aHADR);
          Handle(StepDimTol_ModifiedGeometricTolerance) aMGT =
            new StepDimTol_ModifiedGeometricTolerance;
          if (aKind == 21)
            aMGT->SetModifier(StepDimTol_MaximumMaterialCondition);
          else if (aKind == 22)
            aMGT->SetModifier(StepDimTol_LeastMaterialCondition);
          else if (aKind == 23)
            aMGT->SetModifier(StepDimTol_RegardlessOfFeatureSize);
          Handle(StepDimTol_GeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol) aGTComplex =
            new StepDimTol_GeoTolAndGeoTolWthDatRefAndModGeoTolAndPosTol;
          aGTComplex->Init(aName, aDescription, aLMWU, aSA, aGTWDR, aMGT);
          aModel->AddWithRefs(aGTComplex);
        }
        else if (aKind == 24)
        {
          Handle(StepDimTol_AngularityTolerance) aToler =
            new StepDimTol_AngularityTolerance;
          aToler->Init(aName, aDescription, aLMWU, aSA, aHADR);
          aModel->AddWithRefs(aToler);
        }
        else if (aKind == 25)
        {
          Handle(StepDimTol_CircularRunoutTolerance) aToler =
            new StepDimTol_CircularRunoutTolerance;
          aToler->Init(aName, aDescription, aLMWU, aSA, aHADR);
          aModel->AddWithRefs(aToler);
        }
        else if (aKind == 26)
        {
          Handle(StepDimTol_CoaxialityTolerance) aToler =
            new StepDimTol_CoaxialityTolerance;
          aToler->Init(aName, aDescription, aLMWU, aSA, aHADR);
          aModel->AddWithRefs(aToler);
        }
        else if (aKind == 27)
        {
          Handle(StepDimTol_ConcentricityTolerance) aToler =
            new StepDimTol_ConcentricityTolerance;
          aToler->Init(aName, aDescription, aLMWU, aSA, aHADR);
          aModel->AddWithRefs(aToler);
        }
        else if (aKind == 28)
        {
          Handle(StepDimTol_ParallelismTolerance) aToler =
            new StepDimTol_ParallelismTolerance;
          aToler->Init(aName, aDescription, aLMWU, aSA, aHADR);
          aModel->AddWithRefs(aToler);
        }
        else if (aKind == 29)
        {
          Handle(StepDimTol_PerpendicularityTolerance) aToler =
            new StepDimTol_PerpendicularityTolerance;
          aToler->Init(aName, aDescription, aLMWU, aSA, aHADR);
          aModel->AddWithRefs(aToler);
        }
        else if (aKind == 30)
        {
          Handle(StepDimTol_SymmetryTolerance) aToler =
            new StepDimTol_SymmetryTolerance;
          aToler->Init(aName, aDescription, aLMWU, aSA, aHADR);
          aModel->AddWithRefs(aToler);
        }
        else if (aKind == 31)
        {
          Handle(StepDimTol_TotalRunoutTolerance) aToler =
            new StepDimTol_TotalRunoutTolerance;
          aToler->Init(aName, aDescription, aLMWU, aSA, aHADR);
          aModel->AddWithRefs(aToler);
>>>>>>> accb2f351 (u)
        }
      }
    }
  }

  return Standard_True;
}

//=======================================================================
<<<<<<< HEAD
//function : WriteDGTsAP242
//purpose  : 
//=======================================================================

Standard_Boolean STEPCAFControl_Writer::WriteDGTsAP242 (const Handle(XSControl_WorkSession) &WS,
                                                        const TDF_LabelSequence  &labels )
{
  // Get working data
  const Handle(Interface_InterfaceModel) &aModel = WS->Model();

  const Handle(Interface_HGraph) aHGraph = WS->HGraph();
  if(aHGraph.IsNull())
    return Standard_False;

  Interface_Graph aGraph = aHGraph->Graph();
  Handle(XCAFDoc_DimTolTool) DGTTool = XCAFDoc_DocumentTool::DimTolTool(labels(1));
  if(DGTTool.IsNull())
    return Standard_False;

  // Common entities for presentation
  STEPConstruct_Styles aStyles (WS);
  Handle(StepVisual_Colour) aCurvColor = aStyles.EncodeColor(Quantity_NOC_WHITE);
  Handle(StepRepr_RepresentationItem) anItem = NULL;
  myGDTPrsCurveStyle->SetValue(1, aStyles.MakeColorPSA(anItem, aCurvColor, aCurvColor, aCurvColor, 0.0));
  Interface_EntityIterator aModelIter = aModel->Entities();
  for (; aModelIter.More() && myGDTCommonPDS.IsNull(); aModelIter.Next())
    myGDTCommonPDS = Handle(StepRepr_ProductDefinitionShape)::DownCast(aModelIter.Value());

  TDF_LabelSequence aDGTLabels;
  STEPConstruct_DataMapOfAsciiStringTransient aDatumMap;
  Handle(StepRepr_RepresentationContext) aRC;

  //------------- //
  // write Datums //
  //--------------//
  DGTTool->GetDatumLabels(aDGTLabels);
  // Find all shapes with datums
  TColStd_MapOfAsciiString aNameIdMap;
  for(Standard_Integer i = 1; i <= aDGTLabels.Length(); i++) {
    TDF_Label aDatumL = aDGTLabels.Value(i);
    TDF_LabelSequence aShapeL, aNullSeq;
    DGTTool->GetRefShapeLabel(aDatumL, aShapeL, aNullSeq);
=======
//function : writeDGTsAP242
//purpose  :
//=======================================================================
Standard_Boolean STEPCAFControl_Writer::writeDGTsAP242(const Handle(XSControl_WorkSession)& theWS,
                                                       const TDF_LabelSequence& theLabels)
{
  (void)theLabels;
  // Get working data
  const Handle(Interface_InterfaceModel)& aModel = theWS->Model();

  const Handle(Interface_HGraph) aHGraph = theWS->HGraph();
  if (aHGraph.IsNull())
    return Standard_False;

  Interface_Graph aGraph = aHGraph->Graph();

  // Common entities for presentation
  STEPConstruct_Styles aStyles(theWS);
  Handle(StepVisual_Colour) aCurvColor = aStyles.EncodeColor(Quantity_NOC_WHITE);
  Handle(StepRepr_RepresentationItem) anItem = NULL;
  myGDTPrsCurveStyle->SetValue(1, aStyles.MakeColorPSA(anItem, aCurvColor, aCurvColor, aCurvColor, 0.0));
  for (Interface_EntityIterator aModelIter = aModel->Entities();
       aModelIter.More() && myGDTCommonPDS.IsNull(); aModelIter.Next())
  {
    myGDTCommonPDS = Handle(StepRepr_ProductDefinitionShape)::DownCast(aModelIter.Value());
  }

  STEPConstruct_DataMapOfAsciiStringTransient aDatumMap;
  Handle(StepRepr_RepresentationContext) aRC;

  TDF_LabelSequence aDGTLabels;
  // Iterate on requested shapes collect Tools
  for (TDF_LabelMap::Iterator aLabelIter(myRootLabels);
       aLabelIter.More(); aLabelIter.Next())
  {
    const TDF_Label& aLabel = aLabelIter.Value();
    Handle(XCAFDoc_DimTolTool) aDGTTool = XCAFDoc_DocumentTool::DimTolTool(aLabel);
    TDF_LabelSequence aaDGTLS;
    aDGTTool->GetDatumLabels(aDGTLabels);
    aDGTLabels.Append(aaDGTLS);
  }

  // Find all shapes with datums
  TColStd_MapOfAsciiString aNameIdMap;
  for (TDF_LabelSequence::Iterator aDGTIter(aDGTLabels);
       aDGTIter.More(); aDGTIter.Next())
  {
    const TDF_Label& aDatumL = aDGTIter.Value();
    TDF_LabelSequence aShapeL, aNullSeq;
    XCAFDoc_DimTolTool::GetRefShapeLabel(aDatumL, aShapeL, aNullSeq);
>>>>>>> accb2f351 (u)
    Handle(XCAFDoc_Datum) aDatumAttr;
    aDatumL.FindAttribute(XCAFDoc_Datum::GetID(), aDatumAttr);
    Handle(XCAFDimTolObjects_DatumObject) anObject = aDatumAttr->GetObject();
    TCollection_AsciiString aDatumName = anObject->GetName()->String();
    TCollection_AsciiString aDatumTargetId = TCollection_AsciiString(anObject->GetDatumTargetNumber());
    if (!aNameIdMap.Add(aDatumName.Cat(aDatumTargetId)))
      continue;
    Handle(Standard_Transient) aWrittenDatum;
    Standard_Boolean isFirstDT = !aDatumMap.Find(aDatumName, aWrittenDatum);
<<<<<<< HEAD
    Handle(StepDimTol_Datum) aDatum = WriteDatumAP242(WS, aShapeL, aDatumL, isFirstDT, 
                                                      Handle(StepDimTol_Datum)::DownCast (aWrittenDatum));
=======
    Handle(StepDimTol_Datum) aDatum = writeDatumAP242(theWS, aShapeL, aDatumL, isFirstDT,
                                                      Handle(StepDimTol_Datum)::DownCast(aWrittenDatum));
>>>>>>> accb2f351 (u)
    // Add created Datum into Map
    aDatumMap.Bind(aDatumName, aDatum);
  }

<<<<<<< HEAD
  //----------------- //
  // write Dimensions //
  //------------------//
  aDGTLabels.Clear();
  DGTTool->GetDimensionLabels(aDGTLabels);
=======
  // write Dimensions
  aDGTLabels.Clear();
  for (TDF_LabelMap::Iterator aLabelIter(myRootLabels);
       aLabelIter.More(); aLabelIter.Next())
  {
    const TDF_Label& aLabel = aLabelIter.Value();
    Handle(XCAFDoc_DimTolTool) aDGTTool = XCAFDoc_DocumentTool::DimTolTool(aLabel);
    TDF_LabelSequence aaDGTLS;
    aDGTTool->GetDimensionLabels(aDGTLabels);
    aDGTLabels.Append(aaDGTLS);
  }

>>>>>>> accb2f351 (u)
  // Auxiliary entities for derived geometry
  Handle(StepRepr_ConstructiveGeometryRepresentation) aCGRepr =
    new StepRepr_ConstructiveGeometryRepresentation();
  Handle(StepRepr_ConstructiveGeometryRepresentationRelationship) aCGReprRel =
    new StepRepr_ConstructiveGeometryRepresentationRelationship();
  NCollection_Vector<Handle(StepGeom_CartesianPoint)> aConnectionPnts;
  Handle(StepRepr_RepresentationContext) dummyRC;
  Handle(StepAP242_GeometricItemSpecificUsage) dummyGISU;
<<<<<<< HEAD
  for (Standard_Integer i = 1; i <= aDGTLabels.Length(); i++) {
    TDF_Label aDimensionL = aDGTLabels.Value(i);
    TDF_LabelSequence aFirstShapeL, aSecondShapeL;
    Handle(XCAFDoc_Dimension) aDimAttr;
    if (!aDimensionL.FindAttribute(XCAFDoc_Dimension::GetID(),aDimAttr)) 
=======
  for (TDF_LabelSequence::Iterator aDGTIter(aDGTLabels);
       aDGTIter.More(); aDGTIter.Next())
  {
    const TDF_Label& aDimensionL = aDGTIter.Value();
    TDF_LabelSequence aFirstShapeL, aSecondShapeL;
    Handle(XCAFDoc_Dimension) aDimAttr;
    if (!aDimensionL.FindAttribute(XCAFDoc_Dimension::GetID(), aDimAttr))
>>>>>>> accb2f351 (u)
      continue;
    Handle(XCAFDimTolObjects_DimensionObject) anObject = aDimAttr->GetObject();
    if (anObject.IsNull())
      continue;
    if (anObject->GetType() == XCAFDimTolObjects_DimensionType_CommonLabel)
    {
      Handle(StepRepr_ShapeAspect) aSA = new StepRepr_ShapeAspect();
      aSA->Init(new TCollection_HAsciiString(), new TCollection_HAsciiString(), myGDTCommonPDS, StepData_LTrue);
      aModel->AddWithRefs(aSA);
<<<<<<< HEAD
      WritePresentation(WS, anObject->GetPresentation(), anObject->GetPresentationName(), anObject->HasPlane(),
        Standard_False, anObject->GetPlane(), anObject->GetPointTextAttach(), aSA);
    }

    if (!DGTTool->GetRefShapeLabel(aDimensionL, aFirstShapeL, aSecondShapeL))
=======
      writePresentation(theWS, anObject->GetPresentation(), anObject->GetPresentationName(), anObject->HasPlane(),
                        Standard_False, anObject->GetPlane(), anObject->GetPointTextAttach(), aSA);
    }

    if (!XCAFDoc_DimTolTool::GetRefShapeLabel(aDimensionL, aFirstShapeL, aSecondShapeL))
>>>>>>> accb2f351 (u)
      continue;

    // Write links with shapes
    Handle(StepRepr_ShapeAspect) aFirstSA, aSecondSA;
<<<<<<< HEAD
    if (aFirstShapeL.Length() == 1) {
      TopoDS_Shape aShape = XCAFDoc_ShapeTool::GetShape(aFirstShapeL.Value(1));
      aFirstSA = WriteShapeAspect(WS, aDimensionL, aShape, dummyRC, dummyGISU);
      if (aRC.IsNull() && !dummyRC.IsNull())
        aRC = dummyRC;
    }
    else if (aFirstShapeL.Length() > 1) {
      Handle(StepRepr_CompositeShapeAspect) aCSA;
      for (Standard_Integer shIt = 1; shIt <= aFirstShapeL.Length(); shIt++) {
        TopoDS_Shape aShape = XCAFDoc_ShapeTool::GetShape(aFirstShapeL.Value(shIt));
        Handle(StepRepr_ShapeAspect) aSA = WriteShapeAspect(WS, aDimensionL, aShape, dummyRC, dummyGISU);
        if (aSA.IsNull())
          continue;
        if (aCSA.IsNull()) {
=======
    if (aFirstShapeL.Length() == 1)
    {
      TopoDS_Shape aShape = XCAFDoc_ShapeTool::GetShape(aFirstShapeL.Value(1));
      aFirstSA = writeShapeAspect(theWS, aDimensionL, aShape, dummyRC, dummyGISU);
      if (aRC.IsNull() && !dummyRC.IsNull())
        aRC = dummyRC;
    }
    else if (aFirstShapeL.Length() > 1)
    {
      Handle(StepRepr_CompositeShapeAspect) aCSA;
      for (Standard_Integer shIt = 1; shIt <= aFirstShapeL.Length(); shIt++)
      {
        TopoDS_Shape aShape = XCAFDoc_ShapeTool::GetShape(aFirstShapeL.Value(shIt));
        Handle(StepRepr_ShapeAspect) aSA = writeShapeAspect(theWS, aDimensionL, aShape, dummyRC, dummyGISU);
        if (aSA.IsNull())
          continue;
        if (aCSA.IsNull())
        {
>>>>>>> accb2f351 (u)
          aCSA = new StepRepr_CompositeShapeAspect();
          aCSA->Init(aSA->Name(), aSA->Description(), aSA->OfShape(), aSA->ProductDefinitional());
          aModel->AddWithRefs(aCSA);
        }
        Handle(StepRepr_ShapeAspectRelationship) aSAR = new StepRepr_ShapeAspectRelationship();
        aSAR->Init(new TCollection_HAsciiString(), Standard_False, new TCollection_HAsciiString(), aCSA, aSA);
        aModel->AddWithRefs(aSAR);
        if (aRC.IsNull() && !dummyRC.IsNull())
          aRC = dummyRC;
      }
      aFirstSA = aCSA;
    }
<<<<<<< HEAD
    if (aSecondShapeL.Length() == 1) {
      TopoDS_Shape aShape = XCAFDoc_ShapeTool::GetShape(aSecondShapeL.Value(1));
      aSecondSA = WriteShapeAspect(WS, aDimensionL, aShape, dummyRC, dummyGISU);
      if (aRC.IsNull() && !dummyRC.IsNull())
        aRC = dummyRC;
    }
    else if (aSecondShapeL.Length() > 1) {
      Handle(StepRepr_CompositeShapeAspect) aCSA;
      for (Standard_Integer shIt = 1; shIt <= aSecondShapeL.Length(); shIt++) {
        TopoDS_Shape aShape = XCAFDoc_ShapeTool::GetShape(aSecondShapeL.Value(shIt));
        Handle(StepRepr_ShapeAspect) aSA = WriteShapeAspect(WS, aDimensionL, aShape, dummyRC, dummyGISU);
=======
    if (aSecondShapeL.Length() == 1)
    {
      TopoDS_Shape aShape = XCAFDoc_ShapeTool::GetShape(aSecondShapeL.Value(1));
      aSecondSA = writeShapeAspect(theWS, aDimensionL, aShape, dummyRC, dummyGISU);
      if (aRC.IsNull() && !dummyRC.IsNull())
        aRC = dummyRC;
    }
    else if (aSecondShapeL.Length() > 1)
    {
      Handle(StepRepr_CompositeShapeAspect) aCSA;
      for (Standard_Integer shIt = 1; shIt <= aSecondShapeL.Length(); shIt++)
      {
        TopoDS_Shape aShape = XCAFDoc_ShapeTool::GetShape(aSecondShapeL.Value(shIt));
        Handle(StepRepr_ShapeAspect) aSA = writeShapeAspect(theWS, aDimensionL, aShape, dummyRC, dummyGISU);
>>>>>>> accb2f351 (u)
        if (aCSA.IsNull() && !aSA.IsNull())
        {
          aCSA = new StepRepr_CompositeShapeAspect();
        }
        aCSA->Init(aSA->Name(), aSA->Description(), aSA->OfShape(), aSA->ProductDefinitional());
<<<<<<< HEAD
        if (!aSA.IsNull()) {
=======
        if (!aSA.IsNull())
        {
>>>>>>> accb2f351 (u)
          Handle(StepRepr_ShapeAspectRelationship) aSAR = new StepRepr_ShapeAspectRelationship();
          aSAR->Init(new TCollection_HAsciiString(), Standard_False, new TCollection_HAsciiString(), aCSA, aSA);
          aModel->AddWithRefs(aSAR);
        }
        if (aRC.IsNull() && !dummyRC.IsNull())
          aRC = dummyRC;
      }
      aSecondSA = aCSA;
    }

    if (anObject->GetType() == XCAFDimTolObjects_DimensionType_DimensionPresentation)
    {
<<<<<<< HEAD
      WritePresentation(WS, anObject->GetPresentation(), anObject->GetPresentationName(), anObject->HasPlane(),
        Standard_False, anObject->GetPlane(), anObject->GetPointTextAttach(), aFirstSA);
=======
      writePresentation(theWS, anObject->GetPresentation(), anObject->GetPresentationName(), anObject->HasPlane(),
                        Standard_False, anObject->GetPlane(), anObject->GetPointTextAttach(), aFirstSA);
>>>>>>> accb2f351 (u)
      continue;
    }

    // Write dimensions
    StepShape_DimensionalCharacteristic aDimension;
    if (anObject->HasPoint() || anObject->HasPoint2())
<<<<<<< HEAD
      WriteDerivedGeometry(WS, anObject, aCGRepr, aFirstSA, aSecondSA, aConnectionPnts);
    XCAFDimTolObjects_DimensionType aDimType = anObject->GetType();
    if (STEPCAFControl_GDTProperty::IsDimensionalLocation(aDimType)) {
=======
      WriteDerivedGeometry(theWS, anObject, aCGRepr, aFirstSA, aSecondSA, aConnectionPnts);
    XCAFDimTolObjects_DimensionType aDimType = anObject->GetType();
    if (STEPCAFControl_GDTProperty::IsDimensionalLocation(aDimType))
    {
>>>>>>> accb2f351 (u)
      // Dimensional_Location
      Handle(StepShape_DimensionalLocation) aDim = new StepShape_DimensionalLocation();
      aDim->Init(STEPCAFControl_GDTProperty::GetDimTypeName(aDimType), Standard_False, NULL, aFirstSA, aSecondSA);
      aDimension.SetValue(aDim);
    }
<<<<<<< HEAD
    else if (aDimType == XCAFDimTolObjects_DimensionType_Location_Angular) {
      // Angular_Location
      Handle(StepShape_AngularLocation) aDim = new StepShape_AngularLocation();
      StepShape_AngleRelator aRelator = StepShape_Equal;
      if (anObject->HasQualifier()) {
        XCAFDimTolObjects_AngularQualifier aQualifier = anObject->GetAngularQualifier();
        switch (aQualifier) {
          case XCAFDimTolObjects_AngularQualifier_Small : aRelator = StepShape_Small;
            break;
          case XCAFDimTolObjects_AngularQualifier_Large : aRelator = StepShape_Large;
=======
    else if (aDimType == XCAFDimTolObjects_DimensionType_Location_Angular)
    {
      // Angular_Location
      Handle(StepShape_AngularLocation) aDim = new StepShape_AngularLocation();
      StepShape_AngleRelator aRelator = StepShape_Equal;
      if (anObject->HasQualifier())
      {
        XCAFDimTolObjects_AngularQualifier aQualifier = anObject->GetAngularQualifier();
        switch (aQualifier)
        {
          case XCAFDimTolObjects_AngularQualifier_Small: aRelator = StepShape_Small;
            break;
          case XCAFDimTolObjects_AngularQualifier_Large: aRelator = StepShape_Large;
>>>>>>> accb2f351 (u)
            break;
          default: aRelator = StepShape_Equal;
        }
      }
      aDim->Init(new TCollection_HAsciiString(), Standard_False, NULL, aFirstSA, aSecondSA, aRelator);
      aDimension.SetValue(aDim);
    }
<<<<<<< HEAD
    else if (aDimType == XCAFDimTolObjects_DimensionType_Location_WithPath) {
      // Dimensional_Location_With_Path
      Handle(StepShape_DimensionalLocationWithPath) aDim = new StepShape_DimensionalLocationWithPath();
      Handle(StepRepr_ShapeAspect) aPathSA = WriteShapeAspect(WS, aDimensionL, anObject->GetPath(), dummyRC, dummyGISU);
      aDim->Init(new TCollection_HAsciiString(), Standard_False, NULL, aFirstSA, aSecondSA, aPathSA);
      aDimension.SetValue(aDim);
    }
    else if (STEPCAFControl_GDTProperty::IsDimensionalSize(aDimType)) {
=======
    else if (aDimType == XCAFDimTolObjects_DimensionType_Location_WithPath)
    {
      // Dimensional_Location_With_Path
      Handle(StepShape_DimensionalLocationWithPath) aDim = new StepShape_DimensionalLocationWithPath();
      Handle(StepRepr_ShapeAspect) aPathSA = writeShapeAspect(theWS, aDimensionL, anObject->GetPath(), dummyRC, dummyGISU);
      aDim->Init(new TCollection_HAsciiString(), Standard_False, NULL, aFirstSA, aSecondSA, aPathSA);
      aDimension.SetValue(aDim);
    }
    else if (STEPCAFControl_GDTProperty::IsDimensionalSize(aDimType))
    {
>>>>>>> accb2f351 (u)
      // Dimensional_Size
      Handle(StepShape_DimensionalSize) aDim = new StepShape_DimensionalSize();
      aDim->Init(aFirstSA, STEPCAFControl_GDTProperty::GetDimTypeName(aDimType));
      aDimension.SetValue(aDim);
    }
<<<<<<< HEAD
    else if (aDimType == XCAFDimTolObjects_DimensionType_Size_Angular) {
      // Angular_Size
      Handle(StepShape_AngularSize) aDim = new StepShape_AngularSize();
      StepShape_AngleRelator aRelator = StepShape_Equal;
      if (anObject->HasQualifier()) {
        XCAFDimTolObjects_AngularQualifier aQualifier = anObject->GetAngularQualifier();
        switch (aQualifier) {
=======
    else if (aDimType == XCAFDimTolObjects_DimensionType_Size_Angular)
    {
      // Angular_Size
      Handle(StepShape_AngularSize) aDim = new StepShape_AngularSize();
      StepShape_AngleRelator aRelator = StepShape_Equal;
      if (anObject->HasQualifier())
      {
        XCAFDimTolObjects_AngularQualifier aQualifier = anObject->GetAngularQualifier();
        switch (aQualifier)
        {
>>>>>>> accb2f351 (u)
          case XCAFDimTolObjects_AngularQualifier_Small: aRelator = StepShape_Small;
            break;
          case XCAFDimTolObjects_AngularQualifier_Large: aRelator = StepShape_Large;
            break;
          default: aRelator = StepShape_Equal;
        }
      }
      aDim->Init(aFirstSA, new TCollection_HAsciiString(), aRelator);
      aDimension.SetValue(aDim);
    }
<<<<<<< HEAD
    else if (aDimType == XCAFDimTolObjects_DimensionType_Size_WithPath) {
      // Dimensional_Size_With_Path
      Handle(StepShape_DimensionalSizeWithPath) aDim = new StepShape_DimensionalSizeWithPath();
      Handle(StepRepr_ShapeAspect) aPathSA = WriteShapeAspect(WS, aDimensionL, anObject->GetPath(), dummyRC, dummyGISU);
=======
    else if (aDimType == XCAFDimTolObjects_DimensionType_Size_WithPath)
    {
      // Dimensional_Size_With_Path
      Handle(StepShape_DimensionalSizeWithPath) aDim = new StepShape_DimensionalSizeWithPath();
      Handle(StepRepr_ShapeAspect) aPathSA = writeShapeAspect(theWS, aDimensionL, anObject->GetPath(), dummyRC, dummyGISU);
>>>>>>> accb2f351 (u)
      aDim->Init(aFirstSA, new TCollection_HAsciiString(), aPathSA);
      aDimension.SetValue(aDim);
    }

    // Write values
<<<<<<< HEAD
    WriteDimValues(WS, anObject, aRC, aDimension);
    //Annotation plane and Presentation
    WritePresentation(WS, anObject->GetPresentation(), anObject->GetPresentationName(), Standard_True, anObject->HasPlane(),
      anObject->GetPlane(), anObject->GetPointTextAttach(), aDimension.Value());
  }
  // Write Derived geometry
  if (aConnectionPnts.Length() > 0) {
=======
    WriteDimValues(theWS, anObject, aRC, aDimension);
    //Annotation plane and Presentation
    writePresentation(theWS, anObject->GetPresentation(), anObject->GetPresentationName(), Standard_True, anObject->HasPlane(),
                      anObject->GetPlane(), anObject->GetPointTextAttach(), aDimension.Value());
  }
  // Write Derived geometry
  if (aConnectionPnts.Length() > 0)
  {
>>>>>>> accb2f351 (u)
    Handle(StepRepr_HArray1OfRepresentationItem) anItems = new StepRepr_HArray1OfRepresentationItem(1, aConnectionPnts.Length());
    for (Standard_Integer i = 0; i < aConnectionPnts.Length(); i++)
      anItems->SetValue(i + 1, aConnectionPnts(i));
    aCGRepr->Init(new TCollection_HAsciiString(), anItems, dummyRC);
    aCGReprRel->Init(new TCollection_HAsciiString(), new TCollection_HAsciiString(), dummyGISU->UsedRepresentation(), aCGRepr);
    aModel->AddWithRefs(aCGReprRel);
  }

<<<<<<< HEAD
  //----------------------------//
  // write Geometric Tolerances //
  //----------------------------//
  aDGTLabels.Clear();
  DGTTool->GetGeomToleranceLabels(aDGTLabels);
  for (Standard_Integer i = 1; i <= aDGTLabels.Length(); i++) {
    TDF_Label aGeomTolL = aDGTLabels.Value(i);
    TDF_LabelSequence aFirstShapeL, aNullSeqL;
    if (!DGTTool->GetRefShapeLabel(aGeomTolL, aFirstShapeL, aNullSeqL))
      continue;
    TDF_LabelSequence aDatumSeq;
    DGTTool->GetDatumWithObjectOfTolerLabels(aGeomTolL, aDatumSeq);
    Handle(StepDimTol_HArray1OfDatumSystemOrReference) aDatumSystem;
    if (aDatumSeq.Length() > 0)
      aDatumSystem = WriteDatumSystem(WS, aGeomTolL, aDatumSeq, aDatumMap, aRC);
    WriteGeomTolerance(WS, aFirstShapeL, aGeomTolL, aDatumSystem, aRC);
=======
  // write Geometric Tolerances
  aDGTLabels.Clear();
  for (TDF_LabelMap::Iterator aLabelIter(myRootLabels);
       aLabelIter.More(); aLabelIter.Next())
  {
    const TDF_Label& aLabel = aLabelIter.Value();
    Handle(XCAFDoc_DimTolTool) aDGTTool = XCAFDoc_DocumentTool::DimTolTool(aLabel);
    TDF_LabelSequence aaDGTLS;
    aDGTTool->GetGeomToleranceLabels(aDGTLabels);
    aDGTLabels.Append(aaDGTLS);
  }
  for (TDF_LabelSequence::Iterator aDGTIter(aDGTLabels);
       aDGTIter.More(); aDGTIter.Next())
  {
    const TDF_Label aGeomTolL = aDGTIter.Value();
    TDF_LabelSequence aFirstShapeL, aNullSeqL;
    if (!XCAFDoc_DimTolTool::GetRefShapeLabel(aGeomTolL, aFirstShapeL, aNullSeqL))
      continue;
    TDF_LabelSequence aDatumSeq;
    XCAFDoc_DimTolTool::GetDatumWithObjectOfTolerLabels(aGeomTolL, aDatumSeq);
    Handle(StepDimTol_HArray1OfDatumSystemOrReference) aDatumSystem;
    if (aDatumSeq.Length() > 0)
      aDatumSystem = WriteDatumSystem(theWS, aGeomTolL, aDatumSeq, aDatumMap, aRC);
    writeGeomTolerance(theWS, aFirstShapeL, aGeomTolL, aDatumSystem, aRC);
>>>>>>> accb2f351 (u)
  }

  // Write Draughting model for Annotation Planes
  if (myGDTAnnotations.Length() == 0)
    return Standard_True;

  Handle(StepRepr_HArray1OfRepresentationItem) aItems =
    new StepRepr_HArray1OfRepresentationItem(1, myGDTAnnotations.Length());
<<<<<<< HEAD
  for (Standard_Integer i = 1; i <= aItems->Length(); i++) {
=======
  for (Standard_Integer i = 1; i <= aItems->Length(); i++)
  {
>>>>>>> accb2f351 (u)
    aItems->SetValue(i, myGDTAnnotations.Value(i - 1));
  }
  myGDTPresentationDM->Init(new TCollection_HAsciiString(), aItems, aRC);
  aModel->AddWithRefs(myGDTPresentationDM);

  return Standard_True;
}

//=======================================================================
//function : FindPDSforRI
<<<<<<< HEAD
//purpose  : auxiliary: 
//=======================================================================
static Standard_Boolean FindPDSforRI(const Interface_Graph &aGraph,
                                     const Handle(Standard_Transient) &ent,
                                     Handle(StepRepr_ProductDefinitionShape) &PDS,
                                     Handle(StepRepr_RepresentationContext) &RC)
{
  if(ent.IsNull() || !ent->IsKind(STANDARD_TYPE(StepRepr_RepresentationItem)))
    return Standard_False;
  Interface_EntityIterator subs = aGraph.Sharings(ent);
  for(subs.Start(); subs.More() && PDS.IsNull(); subs.Next()) {
    Handle(StepShape_ShapeRepresentation) SR = 
      Handle(StepShape_ShapeRepresentation)::DownCast(subs.Value());
    if(SR.IsNull()) continue;
    RC = SR->ContextOfItems();
    Interface_EntityIterator subs1 = aGraph.Sharings(SR);
    for(subs1.Start(); subs1.More() && PDS.IsNull(); subs1.Next()) {
      Handle(StepShape_ShapeDefinitionRepresentation) SDR = 
        Handle(StepShape_ShapeDefinitionRepresentation)::DownCast(subs1.Value());
      if(SDR.IsNull()) continue;
      Handle(StepRepr_PropertyDefinition) PropD = SDR->Definition().PropertyDefinition();
      if(PropD.IsNull()) continue;
      PDS = Handle(StepRepr_ProductDefinitionShape)::DownCast(PropD);
=======
//purpose  : auxiliary:
//=======================================================================
static Standard_Boolean FindPDSforRI(const Interface_Graph& theGraph,
                                     const Handle(Standard_Transient)& theEnt,
                                     Handle(StepRepr_ProductDefinitionShape)& thePDS,
                                     Handle(StepRepr_RepresentationContext)& theRC)
{
  if (theEnt.IsNull() || !theEnt->IsKind(STANDARD_TYPE(StepRepr_RepresentationItem)))
    return Standard_False;
  for (Interface_EntityIterator aSharingIter = theGraph.Sharings(theEnt);
       aSharingIter.More() && thePDS.IsNull(); aSharingIter.Next())
  {
    Handle(StepShape_ShapeRepresentation) aSR =
      Handle(StepShape_ShapeRepresentation)::DownCast(aSharingIter.Value());
    if (aSR.IsNull())
      continue;
    theRC = aSR->ContextOfItems();
    for (Interface_EntityIterator aSubs1 = theGraph.Sharings(aSR);
         aSubs1.More() && thePDS.IsNull(); aSubs1.Next())
    {
      Handle(StepShape_ShapeDefinitionRepresentation) aSDR =
        Handle(StepShape_ShapeDefinitionRepresentation)::DownCast(aSubs1.Value());
      if (aSDR.IsNull())
        continue;
      Handle(StepRepr_PropertyDefinition) aPropD = aSDR->Definition().PropertyDefinition();
      if (aPropD.IsNull())
        continue;
      thePDS = Handle(StepRepr_ProductDefinitionShape)::DownCast(aPropD);
>>>>>>> accb2f351 (u)
    }
  }
  return Standard_True;
}

<<<<<<< HEAD

//=======================================================================
//function : WriteMaterials
//purpose  : 
//=======================================================================

Standard_Boolean STEPCAFControl_Writer::WriteMaterials (const Handle(XSControl_WorkSession) &WS,
                                                        const TDF_LabelSequence  &labels ) const
{
  
  if ( labels.Length() <=0 ) return Standard_False;

  // get working data
  const Handle(Interface_InterfaceModel) &Model = WS->Model();
  const Handle(XSControl_TransferWriter) &TW = WS->TransferWriter();
  const Handle(Transfer_FinderProcess) &FP = TW->FinderProcess();

  const Handle(Interface_HGraph) aHGraph = WS->HGraph();
  if(aHGraph.IsNull())
    return Standard_False;

  Interface_Graph aGraph = WS->HGraph()->Graph();
  Handle(XCAFDoc_ShapeTool) ShTool = XCAFDoc_DocumentTool::ShapeTool( labels(1) );
  if(ShTool.IsNull() ) return Standard_False;
  Handle(XCAFDoc_MaterialTool) MatTool = XCAFDoc_DocumentTool::MaterialTool( labels(1) );
  if(MatTool.IsNull() ) return Standard_False;

  STEPConstruct_DataMapOfAsciiStringTransient MapDRI,MapMRI;
  TDF_LabelSequence TopLabels;
  ShTool->GetShapes(TopLabels);
  for(Standard_Integer i=1; i<=TopLabels.Length(); i++) {
    TDF_Label ShL = TopLabels.Value(i);
    Handle(TDataStd_TreeNode) Node;
    if( ShL.FindAttribute(XCAFDoc::MaterialRefGUID(),Node) && Node->HasFather() ) {
      // find PDS for current shape
      TopoDS_Shape aShape = XCAFDoc_ShapeTool::GetShape(ShL);
      TopLoc_Location Loc;
      TColStd_SequenceOfTransient seqRI;
      FindEntities( FP, aShape, Loc, seqRI );
      if(seqRI.Length()<=0) continue;
      Handle(StepRepr_ProductDefinitionShape) PDS;
      Handle(StepRepr_RepresentationContext) RC;
      Handle(Standard_Transient) ent = seqRI.Value(1);
      FindPDSforRI(aGraph,ent,PDS,RC);
      if(PDS.IsNull()) continue;
      Handle(StepBasic_ProductDefinition) aProdDef = 
        PDS->Definition().ProductDefinition();
      if(aProdDef.IsNull())
        continue;
      // write material entities
      TDF_Label MatL = Node->Father()->Label();
      Handle(TCollection_HAsciiString) aName;
      Handle(TCollection_HAsciiString) aDescription;
      Standard_Real aDensity;
      Handle(TCollection_HAsciiString) aDensName;
      Handle(TCollection_HAsciiString) aDensValType;
      Handle(StepRepr_Representation) RepDRI;
      Handle(StepRepr_Representation) RepMRI;
      if(MatTool->GetMaterial(MatL,aName,aDescription,aDensity,aDensName,aDensValType)) {
        if(aName->Length()==0) continue;
        TCollection_AsciiString aKey(aName->ToCString());
        if(MapDRI.IsBound(aKey)) {
          RepDRI = Handle(StepRepr_Representation)::DownCast(MapDRI.Find(aKey));
          if(MapMRI.IsBound(aKey)) {
            RepMRI = Handle(StepRepr_Representation)::DownCast(MapMRI.Find(aKey));
          }
        }
        else {
          // write DRI
          Handle(StepRepr_DescriptiveRepresentationItem) DRI = new StepRepr_DescriptiveRepresentationItem;
          DRI->Init(aName,aDescription);
          Handle(StepRepr_HArray1OfRepresentationItem) HARI = new StepRepr_HArray1OfRepresentationItem(1,1);
          HARI->SetValue(1,DRI);
          RepDRI = new StepRepr_Representation();
          RepDRI->Init(new TCollection_HAsciiString("material name"),HARI,RC);
          Model->AddWithRefs(RepDRI);
          // write MRI
          if( aDensity > 0 ) {
            // mass
            Handle(StepBasic_SiUnitAndMassUnit) SMU = new StepBasic_SiUnitAndMassUnit;
            SMU->SetName(StepBasic_sunGram);
            Handle(StepBasic_DerivedUnitElement) DUE1 = new StepBasic_DerivedUnitElement;
            DUE1->Init(SMU,3.0);
            // length
            Handle(StepBasic_SiUnitAndLengthUnit) SLU = new StepBasic_SiUnitAndLengthUnit;
            SLU->Init(Standard_True,StepBasic_spCenti,StepBasic_sunMetre);
            Handle(StepBasic_DerivedUnitElement) DUE2 = new StepBasic_DerivedUnitElement;
            DUE2->Init(SLU,2.0);
            // other
            Handle(StepBasic_HArray1OfDerivedUnitElement) HADUE = new StepBasic_HArray1OfDerivedUnitElement(1,2);
            HADUE->SetValue(1,DUE1);
            HADUE->SetValue(2,DUE2);
            Handle(StepBasic_DerivedUnit) DU = new StepBasic_DerivedUnit;
            DU->Init(HADUE);
            Model->AddWithRefs(DU);
            StepBasic_Unit aUnit;
            aUnit.SetValue(DU);
            Handle(StepBasic_MeasureValueMember) MVM = new StepBasic_MeasureValueMember;
            MVM->SetName(aDensValType->ToCString());
            MVM->SetReal(aDensity);
            Handle(StepRepr_MeasureRepresentationItem) MRI = new StepRepr_MeasureRepresentationItem;
            MRI->Init(aDensName,MVM,aUnit);
            HARI = new StepRepr_HArray1OfRepresentationItem(1,1);
            HARI->SetValue(1,MRI);
            RepMRI = new StepRepr_Representation();
            RepMRI->Init(new TCollection_HAsciiString("density"),HARI,RC);
            Model->AddWithRefs(RepMRI);
          }
          //WriteNewMaterial(Model,aName,aDescription,aDensity,aDensName,aDensValType,RC,RepDRI,RepMRI);
          MapDRI.Bind(aKey,RepDRI);
          if ( !RepMRI.IsNull() ) MapMRI.Bind (aKey, RepMRI);
        }
      }
      
      if( !RepDRI.IsNull() )
      {
        StepRepr_CharacterizedDefinition CD1;
        CD1.SetValue(aProdDef);
        Handle(StepRepr_PropertyDefinition) PropD1 = new StepRepr_PropertyDefinition;
        PropD1->Init(new TCollection_HAsciiString("material property"),Standard_True,
          new TCollection_HAsciiString("material name"),CD1);
        Model->AddWithRefs(PropD1);
        StepRepr_RepresentedDefinition RD1;
        RD1.SetValue(PropD1);
        Handle(StepRepr_PropertyDefinitionRepresentation) PDR1 =
          new StepRepr_PropertyDefinitionRepresentation;
        PDR1->Init(RD1,RepDRI);
        Model->AddWithRefs(PDR1);

        if( !RepMRI.IsNull() )
        {
          StepRepr_CharacterizedDefinition CD2;
          CD2.SetValue (aProdDef);
          Handle (StepRepr_PropertyDefinition) PropD2 = new StepRepr_PropertyDefinition;
          PropD2->Init (new TCollection_HAsciiString ("material property"), Standard_True,
            new TCollection_HAsciiString ("density"), CD2);
          Model->AddWithRefs (PropD2);
          StepRepr_RepresentedDefinition RD2;
          RD2.SetValue (PropD2);
          Handle (StepRepr_PropertyDefinitionRepresentation) PDR2 =
            new StepRepr_PropertyDefinitionRepresentation;
          PDR2->Init (RD2, RepMRI);
          Model->AddWithRefs (PDR2);
        }
=======
//=======================================================================
//function : writeMaterials
//purpose  :
//=======================================================================
Standard_Boolean STEPCAFControl_Writer::writeMaterials(const Handle(XSControl_WorkSession)& theWS,
                                                       const TDF_LabelSequence& theLabels) const
{

  if (theLabels.IsEmpty())
    return Standard_False;

  // get working data
  const Handle(Interface_InterfaceModel)& aModel = theWS->Model();
  const Handle(XSControl_TransferWriter)& aTW = theWS->TransferWriter();
  const Handle(Transfer_FinderProcess)& aFP = aTW->FinderProcess();

  const Handle(Interface_HGraph) aHGraph = theWS->HGraph();
  if (aHGraph.IsNull())
    return Standard_False;

  Interface_Graph aGraph = theWS->HGraph()->Graph();

  STEPConstruct_DataMapOfAsciiStringTransient aMapDRI, aMapMRI;
  TDF_LabelSequence aTopLabels;
  // Iterate on requested shapes collect Tools
  for (TDF_LabelMap::Iterator aLabelIter(myRootLabels);
       aLabelIter.More(); aLabelIter.Next())
  {
    const TDF_Label& aLabel = aLabelIter.Value();
    Handle(XCAFDoc_ShapeTool) aShTool = XCAFDoc_DocumentTool::ShapeTool(aLabel);
    TDF_LabelSequence aTopInterLabels;
    aShTool->GetShapes(aTopInterLabels);
    aTopLabels.Append(aTopInterLabels);
  }
  for (TDF_LabelSequence::Iterator aTopLIter(aTopLabels);
       aTopLIter.More(); aTopLIter.Next())
  {
    const TDF_Label& aShL = aTopLIter.Value();
    Handle(TDataStd_TreeNode) aNode;
    if (!aShL.FindAttribute(XCAFDoc::MaterialRefGUID(), aNode) || !aNode->HasFather())
    {
      continue;
    }
    // find PDS for current shape
    TopoDS_Shape aShape = XCAFDoc_ShapeTool::GetShape(aShL);
    TopLoc_Location aLocation;
    TColStd_SequenceOfTransient aSeqRI;
    FindEntities(aFP, aShape, aLocation, aSeqRI);
    if (aSeqRI.Length() <= 0) continue;
    Handle(StepRepr_ProductDefinitionShape) aPDS;
    Handle(StepRepr_RepresentationContext) aRC;
    Handle(Standard_Transient) anEnt = aSeqRI.Value(1);
    FindPDSforRI(aGraph, anEnt, aPDS, aRC);
    if (aPDS.IsNull())
      continue;
    Handle(StepBasic_ProductDefinition) aProdDef =
      aPDS->Definition().ProductDefinition();
    if (aProdDef.IsNull())
      continue;
    // write material entities
    TDF_Label aMatL = aNode->Father()->Label();
    Handle(TCollection_HAsciiString) aName;
    Handle(TCollection_HAsciiString) aDescription;
    Standard_Real aDensity;
    Handle(TCollection_HAsciiString) aDensName;
    Handle(TCollection_HAsciiString) aDensValType;
    Handle(StepRepr_Representation) aRepDRI;
    Handle(StepRepr_Representation) aRepMRI;
    if (XCAFDoc_MaterialTool::GetMaterial(aMatL, aName, aDescription, aDensity, aDensName, aDensValType))
    {
      if (aName->Length() == 0)
        continue;
      TCollection_AsciiString aKey(aName->ToCString());
      if (aMapDRI.IsBound(aKey))
      {
        aRepDRI = Handle(StepRepr_Representation)::DownCast(aMapDRI.Find(aKey));
        if (aMapMRI.IsBound(aKey))
        {
          aRepMRI = Handle(StepRepr_Representation)::DownCast(aMapMRI.Find(aKey));
        }
      }
      else
      {
        // write DRI
        Handle(StepRepr_DescriptiveRepresentationItem) aDRI = new StepRepr_DescriptiveRepresentationItem;
        aDRI->Init(aName, aDescription);
        Handle(StepRepr_HArray1OfRepresentationItem) aHARI = new StepRepr_HArray1OfRepresentationItem(1, 1);
        aHARI->SetValue(1, aDRI);
        aRepDRI = new StepRepr_Representation();
        aRepDRI->Init(new TCollection_HAsciiString("material name"), aHARI, aRC);
        aModel->AddWithRefs(aRepDRI);
        // write MRI
        if (aDensity > 0)
        {
          // mass
          Handle(StepBasic_SiUnitAndMassUnit) aSMU = new StepBasic_SiUnitAndMassUnit;
          aSMU->SetName(StepBasic_sunGram);
          Handle(StepBasic_DerivedUnitElement) aDUE1 = new StepBasic_DerivedUnitElement;
          aDUE1->Init(aSMU, 3.0);
          // length
          Handle(StepBasic_SiUnitAndLengthUnit) aSLU = new StepBasic_SiUnitAndLengthUnit;
          aSLU->Init(Standard_True, StepBasic_spCenti, StepBasic_sunMetre);
          Handle(StepBasic_DerivedUnitElement) aDUE2 = new StepBasic_DerivedUnitElement;
          aDUE2->Init(aSLU, 2.0);
          // other
          Handle(StepBasic_HArray1OfDerivedUnitElement) aHADUE = new StepBasic_HArray1OfDerivedUnitElement(1, 2);
          aHADUE->SetValue(1, aDUE1);
          aHADUE->SetValue(2, aDUE2);
          Handle(StepBasic_DerivedUnit) aDU = new StepBasic_DerivedUnit;
          aDU->Init(aHADUE);
          aModel->AddWithRefs(aDU);
          StepBasic_Unit aUnit;
          aUnit.SetValue(aDU);
          Handle(StepBasic_MeasureValueMember) aMVM = new StepBasic_MeasureValueMember;
          aMVM->SetName(aDensValType->ToCString());
          aMVM->SetReal(aDensity);
          Handle(StepRepr_MeasureRepresentationItem) aMRI = new StepRepr_MeasureRepresentationItem;
          aMRI->Init(aDensName, aMVM, aUnit);
          aHARI = new StepRepr_HArray1OfRepresentationItem(1, 1);
          aHARI->SetValue(1, aMRI);
          aRepMRI = new StepRepr_Representation();
          aRepMRI->Init(new TCollection_HAsciiString("density"), aHARI, aRC);
          aModel->AddWithRefs(aRepMRI);
        }
        //WriteNewMaterial(Model,aName,aDescription,aDensity,aDensName,aDensValType,RC,RepDRI,RepMRI);
        aMapDRI.Bind(aKey, aRepDRI);
        if (!aRepMRI.IsNull())
          aMapMRI.Bind(aKey, aRepMRI);
      }
    }

    if (!aRepDRI.IsNull())
    {
      StepRepr_CharacterizedDefinition aCD1;
      aCD1.SetValue(aProdDef);
      Handle(StepRepr_PropertyDefinition) aPropD1 = new StepRepr_PropertyDefinition;
      aPropD1->Init(new TCollection_HAsciiString("material property"), Standard_True,
                    new TCollection_HAsciiString("material name"), aCD1);
      aModel->AddWithRefs(aPropD1);
      StepRepr_RepresentedDefinition aRD1;
      aRD1.SetValue(aPropD1);
      Handle(StepRepr_PropertyDefinitionRepresentation) aPDR1 =
        new StepRepr_PropertyDefinitionRepresentation;
      aPDR1->Init(aRD1, aRepDRI);
      aModel->AddWithRefs(aPDR1);

      if (!aRepMRI.IsNull())
      {
        StepRepr_CharacterizedDefinition aCD2;
        aCD2.SetValue(aProdDef);
        Handle(StepRepr_PropertyDefinition) aPropD2 = new StepRepr_PropertyDefinition;
        aPropD2->Init(new TCollection_HAsciiString("material property"), Standard_True,
                      new TCollection_HAsciiString("density"), aCD2);
        aModel->AddWithRefs(aPropD2);
        StepRepr_RepresentedDefinition aRD2;
        aRD2.SetValue(aPropD2);
        Handle(StepRepr_PropertyDefinitionRepresentation) aPDR2 =
          new StepRepr_PropertyDefinitionRepresentation;
        aPDR2->Init(aRD2, aRepMRI);
        aModel->AddWithRefs(aPDR2);
>>>>>>> accb2f351 (u)
      }
    }
  }

  return Standard_True;
}
<<<<<<< HEAD


//=======================================================================
//function : SetColorMode
//purpose  : 
//=======================================================================

void STEPCAFControl_Writer::SetColorMode (const Standard_Boolean colormode)
{
  myColorMode = colormode;
}


//=======================================================================
//function : GetColorMode
//purpose  : 
//=======================================================================

Standard_Boolean STEPCAFControl_Writer::GetColorMode () const
{
  return myColorMode;
}


//=======================================================================
//function : SetNameMode
//purpose  : 
//=======================================================================

void STEPCAFControl_Writer::SetNameMode (const Standard_Boolean namemode)
{
  myNameMode = namemode;
}


//=======================================================================
//function : GetNameMode
//purpose  : 
//=======================================================================

Standard_Boolean STEPCAFControl_Writer::GetNameMode () const
{
  return myNameMode;
}


//=======================================================================
//function : SetLayerMode
//purpose  : 
//=======================================================================

void STEPCAFControl_Writer::SetLayerMode (const Standard_Boolean layermode)
{
  myLayerMode = layermode;
}


//=======================================================================
//function : GetLayerMode
//purpose  : 
//=======================================================================

Standard_Boolean STEPCAFControl_Writer::GetLayerMode () const
{
  return myLayerMode;
}


//=======================================================================
//function : SetPropsMode
//purpose  : 
//=======================================================================

void STEPCAFControl_Writer::SetPropsMode (const Standard_Boolean propsmode)
{
  myPropsMode = propsmode;
}


//=======================================================================
//function : GetPropsMode
//purpose  : 
//=======================================================================

Standard_Boolean STEPCAFControl_Writer::GetPropsMode () const
{
  return myPropsMode;
}


//=======================================================================
//function : SetSHUOMode
//purpose  : 
//=======================================================================

void STEPCAFControl_Writer::SetSHUOMode (const Standard_Boolean mode)
{
  mySHUOMode = mode;
}


//=======================================================================
//function : GetSHUOMode
//purpose  : 
//=======================================================================

Standard_Boolean STEPCAFControl_Writer::GetSHUOMode () const
{
  return mySHUOMode;
}


//=======================================================================
//function : SetDimTolMode
//purpose  : 
//=======================================================================

void STEPCAFControl_Writer::SetDimTolMode(const Standard_Boolean dimtolmode)
{
  myGDTMode = dimtolmode;
}


//=======================================================================
//function : GetDimTolMode
//purpose  : 
//=======================================================================

Standard_Boolean STEPCAFControl_Writer::GetDimTolMode() const
{
  return myGDTMode;
}


//=======================================================================
//function : SetMaterialMode
//purpose  : 
//=======================================================================

void STEPCAFControl_Writer::SetMaterialMode(const Standard_Boolean matmode)
{
  myMatMode = matmode;
}


//=======================================================================
//function : GetMaterialMode
//purpose  : 
//=======================================================================

Standard_Boolean STEPCAFControl_Writer::GetMaterialMode() const
{
  return myMatMode;
}
=======
>>>>>>> accb2f351 (u)
