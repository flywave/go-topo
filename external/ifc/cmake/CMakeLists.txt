cmake_minimum_required (VERSION 2.6)
project (ifc)
include(CheckCXXCompilerFlag)
# CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
# CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
# if(COMPILER_SUPPORTS_CXX11)
# 	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-gnu-designator")
# elseif(COMPILER_SUPPORTS_CXX0X)
# 	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wno-gnu-designator")
# else()
#         message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
# endif()

IF(APPLE)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")
ELSE()
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
ENDIF()
 
IF(NOT CMAKE_BUILD_TYPE)
 	SET(CMAKE_BUILD_TYPE "Release")
ENDIF(NOT CMAKE_BUILD_TYPE)

set(SCHEMA_VERSIONS "2x3" "4" "4x1" "4x2" "4x3_rc1")


IF(MSVC)
    ADD_DEFINITIONS(-D_UNICODE)
ElSE(MSVC)
    ADD_DEFINITIONS(-fPIC -Wno-non-virtual-dtor)
ENDIF(MSVC)

set(OGG_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/../../ogg/include")

# 添加所有子目录（按模块分类）
set(OGG_SRC_SUBDIRS
    FSD OSD Plugin Quantity Resource Standard StdFail Storage
    TColStd TCollection TShort Units UnitsAPI UnitsMethods
    NCollection Message FlexLexer math ElCLib ElSLib
    BSplCLib BSplSLib PLib Precision GeomAbs Poly CSLib
    Convert Bnd BVH gp TColgp TopLoc Expr ExprIntrp
    Geom2d LProp TColGeom2d Adaptor2d Geom2dLProp
    Geom2dAdaptor Geom2dEvaluator Geom TColGeom GeomAdaptor
    AdvApprox GeomLProp Adaptor3d LProp3d TopAbs GeomEvaluator
    GProp ProjLib GeomProjLib GCPnts CPnts Approx AppParCurves
    FEmTool AppCont Extrema IntAna IntAna2d GeomConvert
    AdvApp2Var GeomLib Geom2dConvert Hermit BndLib AppDef
    GeomTools GC GCE2d gce TopoDS TopExp TopTools BRep
    BRepLProp BRepAdaptor BRepTools BinTools Aspect Graphic3d
    Xw Image Media Wasm WNT Cocoa Font V3d Select3D Prs3d
    StdPrs SelectBasics SelectMgr PrsMgr AIS StdSelect
    DsgPrs PrsDim ShapeBuild ShapeExtend ShapeConstruct
    ShapeCustom ShapeAnalysis ShapeFix ShapeUpgrade ShapeAlgo
    ShapeProcess ShapeProcessAPI IntCurvesFace MAT MAT2d
    Bisector BRepMAT2d BRepCheck BRepBndLib BRepExtrema
    BRepClass BRepClass3d BRepLib BRepGProp BRepIntCurveSurface
    BRepTopAdaptor BRepBuilderAPI BRepApprox IMeshData IMeshTools
    BRepMeshData BRepMesh Hatch GeomInt IntStart IntWalk IntImp
    IntCurveSurface IntSurf IntPatch Geom2dInt IntImpParGen
    IntRes2d IntCurve TopTrans Intf ApproxInt GccAna GccEnt
    GccInt HatchGen Geom2dHatch Law AppBlend Plate GeomPlate
    LocalAnalysis GeomAPI GeomFill Geom2dAPI Geom2dGcc FairCurve
    NLPlate IntPolyh TopClass HLRTopoBRep HLRBRep HLRAlgo
    HLRAppli Intrv TopBas TopCnx Contap MeshVS CDM PCDM
    CDF UTL LDOM TDF TDataStd TFunction TDocStd AppStdL
    TDataXtd TNaming AppStd IntTools BRepAlgoAPI BOPDS BOPAlgo
    BOPTools BRepPrim BRepSweep Sweep BRepPreviewAPI BRepPrimAPI
    BinMDF BinMDataStd BinMFunction BinMDocStd BinObjMgt
    BinLDrivers XmlLDrivers XmlMDF XmlMDataStd XmlMDocStd
    XmlMFunction XmlObjMgt BinDrivers BinMDataXtd BinMNaming
    XmlDrivers XmlMDataXtd XmlMNaming StdLDrivers StdLPersistent
    StdObjMgt StdDrivers StdObject StdPersistent StdStorage
    ShapePersistent TObj BinTObjDrivers XmlTObjDrivers TPrsStd
    DE Interface Transfer IFGraph IFSelect TransferBRep
    XSControl StepData StepFile HeaderSection RWHeaderSection
    APIHeaderSection StepSelect XSAlgo LibCtl MoniTool StepBasic
    RWStepBasic StepRepr RWStepRepr StepGeom RWStepGeom StepShape
    RWStepShape StepVisual RWStepVisual StepDimTol RWStepDimTol
    StepKinematics RWStepKinematics StepElement StepFEA
    RWStepElement RWStepFEA StepAP214 RWStepAP214 StepAP203
    RWStepAP203 STEPConstruct STEPEdit GeomToStep StepToGeom
    StepToTopoDS TopoDSToStep STEPControl STEPSelections StepAP209
    RWStepAP242 StepAP242 IGESData IGESFile IGESBasic IGESGraph
    IGESGeom IGESDimen IGESDraw IGESSolid IGESDefs IGESAppli
    IGESConvGeom IGESSelect IGESToBRep GeomToIGES Geom2dToIGES
    BRepToIGES BRepToIGESBRep IGESControl TopOpeBRep TopOpeBRepDS
    TopOpeBRepBuild TopOpeBRepTool BRepAlgo BRepFill BRepProj
    XCAFApp XCAFDimTolObjects XCAFNoteObjects XCAFDoc XCAFPrs
    XCAFView IGESCAFControl STEPCAFControl StlAPI RWStl
    VrmlConverter VrmlAPI Vrml VrmlData RWGltf RWMesh RWObj
    RWPly XmlXCAFDrivers XmlMXCAFDoc BinXCAFDrivers BinMXCAFDoc
    DEBRepCascade DEXCAFCascade Express BRepFilletAPI BRepOffsetAPI
    BRepBuilderAPI BRepPreviewAPI BRepPrimAPI BRepAlgoAPI
    ShapeProcessAPI ChFi2d BRepFeat LocOpe ChFi3d ChFiDS
    BlendFunc Draft BRepOffset
)

# 批量添加所有子目录
foreach(SUBDIR ${OGG_SRC_SUBDIRS})
    list(APPEND OGG_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../ogg/src/${SUBDIR}")
endforeach()

INCLUDE_DIRECTORIES(
    ${INCLUDE_DIRECTORIES}
    "${CMAKE_CURRENT_SOURCE_DIR}/../../libboost/boost_1_67_0"
    ${OGG_INCLUDE_DIR}
)

ADD_LIBRARY(ifc23 STATIC ../src/ifc23.cc)
ADD_LIBRARY(ifc4 STATIC ../src/ifc4.cc)
ADD_LIBRARY(ifc41 STATIC ../src/ifc41.cc)
ADD_LIBRARY(ifc42 STATIC ../src/ifc42.cc)
ADD_LIBRARY(ifc43_rc1 STATIC ../src/ifc43_rc1.cc)

 
file(GLOB include_files_geom
    ../src/ifcgeom/*.h     
)

file(GLOB include_files_parse
    ../src/ifcparse/*.h
)

file(GLOB include_files_geom_scheme
    ../src/ifcgeom_schema_agnostic/*.h
)
 
SET_TARGET_PROPERTIES(ifc23 PROPERTIES
ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/../
ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/../)
SET_TARGET_PROPERTIES(ifc23 PROPERTIES 
LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/../
LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/../)
SET_TARGET_PROPERTIES(ifc23 PROPERTIES
RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/../
RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/../)

SET_TARGET_PROPERTIES(ifc4 PROPERTIES
ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/../
ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/../)
SET_TARGET_PROPERTIES(ifc4 PROPERTIES 
LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/../
LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/../)
SET_TARGET_PROPERTIES(ifc4 PROPERTIES
RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/../
RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/../)

SET_TARGET_PROPERTIES(ifc41 PROPERTIES
ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/../
ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/../)
SET_TARGET_PROPERTIES(ifc41 PROPERTIES 
LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/../
LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/../)
SET_TARGET_PROPERTIES(ifc41 PROPERTIES
RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/../
RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/../)

SET_TARGET_PROPERTIES(ifc42 PROPERTIES
ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/../
ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/../)
SET_TARGET_PROPERTIES(ifc42 PROPERTIES 
LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/../
LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/../)
SET_TARGET_PROPERTIES(ifc42 PROPERTIES
RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/../
RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/../)

SET_TARGET_PROPERTIES(ifc43_rc1 PROPERTIES
ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/../
ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/../)
SET_TARGET_PROPERTIES(ifc43_rc1 PROPERTIES 
LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/../
LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/../)
SET_TARGET_PROPERTIES(ifc43_rc1 PROPERTIES
RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/../
RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/../)
 
IF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
    SET_TARGET_PROPERTIES(ifc23 PROPERTIES FOLDER external)
    SET_TARGET_PROPERTIES(ifc4 PROPERTIES FOLDER external)
    SET_TARGET_PROPERTIES(ifc41 PROPERTIES FOLDER external)
    SET_TARGET_PROPERTIES(ifc42 PROPERTIES FOLDER external)
    SET_TARGET_PROPERTIES(ifc43_rc1 PROPERTIES FOLDER external)
ENDIF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
