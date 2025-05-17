cmake_minimum_required (VERSION 2.6)
project (ifc)
include(CheckCXXCompilerFlag)

IF(APPLE)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")
ELSE()
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
ENDIF()
 
IF(NOT CMAKE_BUILD_TYPE)
 	SET(CMAKE_BUILD_TYPE "Release")
ENDIF(NOT CMAKE_BUILD_TYPE)

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
    "${CMAKE_CURRENT_SOURCE_DIR}/../../eigen"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../eigen/unsupported"
    ${OGG_INCLUDE_DIR}
    "${CMAKE_CURRENT_SOURCE_DIR}/../src"
)

if(NOT SCHEMA_VERSIONS)
    if(WASM_BUILD)
        # super arbitrarily try to keep size down at least a little bit
        set(SCHEMA_VERSIONS "2x3" "4")
    else()
        set(SCHEMA_VERSIONS "2x3" "4" "4x1" "4x2" "4x3" "4x3_tc1" "4x3_add1" "4x3_add2")
    endif()
endif()

message(STATUS "IFC SCHEMA_VERSIONS that will be used for the build: ${SCHEMA_VERSIONS}.")

foreach(schema ${SCHEMA_VERSIONS})
    add_definitions(-DHAS_SCHEMA_${schema})
endforeach()

string(REPLACE ";" ")(" schema_version_seq "(${SCHEMA_VERSIONS})")
add_definitions(-DSCHEMA_SEQ=${schema_version_seq})


file(GLOB src_files_geom
    ../src/ifcgeom/*.cpp     
)

file(GLOB src_files_geom_mapping
    ../src/ifcgeom/mapping/*.cpp     
)

file(GLOB src_files_geom_kernel
    ../src/ifcgeom/kernel/*.cpp     
)

set(src_files_geom_serialize 
    ../src/ifcgeom/Serialization/Serialization.cpp
)

file(GLOB src_files_parser
    ../src/ifcparse/*.cpp     
)

foreach(file ${src_files_parser})
    get_filename_component(filename "${file}" NAME)

    if(NOT "${filename}" MATCHES "[0-9]")
        list(APPEND IFCPARSE_CPP_FILES "${file}")
    endif()
endforeach()

foreach(schema ${SCHEMA_VERSIONS})
    list(APPEND IFCPARSE_CPP_FILES
        ../src/ifcparse/Ifc${schema}.cpp
        ../src/ifcparse/Ifc${schema}-schema.cpp
    )
endforeach()

set(IFCPARSE_FILES ${IFCPARSE_CPP_FILES})

foreach(schema ${SCHEMA_VERSIONS})
set(GEOM_SERIALIZER_SCHEMA_LIBRARIES ${GEOM_SERIALIZER_SCHEMA_LIBRARIES} GeometrySerializers_ifc${schema})

add_library(geometry_serializer_ifc${schema} STATIC ../src/ifcgeom/Serialization/schema/Serialization.cpp)
set_target_properties(geometry_serializer_ifc${schema} PROPERTIES COMPILE_FLAGS "-DIFC_GEOM_EXPORTS -DIfcSchema=Ifc${schema}")
list(APPEND geometry_serializer_libraries geometry_serializer_ifc${schema})
endforeach()

add_library(ifc STATIC
    ${src_files_geom}
    ${src_files_geom_mapping}
    ${src_files_geom_kernel}
    ${src_files_geom_serialize}
    ${src_files_parser}
)

SET_TARGET_PROPERTIES(ifc PROPERTIES
ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/../
ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/../)
SET_TARGET_PROPERTIES(ifc PROPERTIES 
LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/../
LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/../)
SET_TARGET_PROPERTIES(ifc PROPERTIES
RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/../
RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/../)

IF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
    SET_TARGET_PROPERTIES(ifc PROPERTIES FOLDER external)
ENDIF(FLYWAVE_ENABLE_SOLUTION_FOLDERS)
