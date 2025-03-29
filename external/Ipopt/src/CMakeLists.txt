
get_ac_init_version(${Ipopt_DIR}/configure.ac IPOPT)

set(IPOPT_VERSION_MAJOR   "${IPOPT_MAJOR_VERSION}"  CACHE STRING "The IpOpt major version number")
set(IPOPT_VERSION_MINOR   "${IPOPT_MINOR_VERSION}"  CACHE STRING "The IpOpt minor version number")
set(IPOPT_VERSION_RELEASE "${IPOPT_PATCH_VERSION}"  CACHE STRING "The IpOpt patch version number")
set(IPOPT_VERSION         "${IPOPT_VERSION_STRING}" CACHE STRING "The IpOpt version")

set(IPOPT_WC_REVISION "0")

message(STATUS "Current IPOPT revision is ${IPOPT_WC_REVISION}")
set(IPOPT_SVN_REV "${IPOPT_WC_REVISION}" CACHE STRING "The IPOPT subversion revision" FORCE)

mark_as_advanced(IPOPT_VERSION_MAJOR
        IPOPT_VERSION_MINOR
        IPOPT_VERSION_RELEASE
        IPOPT_VERSION
        IPOPT_SVN_REV)

add_definitions(-DIPOPTLIB_BUILD)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Interfaces/config.h.in       ${CMAKE_CURRENT_BINARY_DIR}/Interfaces/config.h)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Interfaces/config_ipopt.h.in ${CMAKE_CURRENT_BINARY_DIR}/Interfaces/config_ipopt.h)

#
# pkg-config file generation
#
set(prefix               "${CMAKE_INSTALL_PREFIX}")
set(exec_prefix          "\${prefix}")
set(IPOPTLIB_LFLAGS_NOPC "-lm -ldl")
set(IPOPTLIB_PCFILES     "")
if (COIN_HAS_LAPACK OR COIN_USE_SYSTEM_LAPACK)
    set(IPOPTLIB_PCFILES "${IPOPTLIB_PCFILES} -llapack")
endif ()
if (COIN_HAS_BLAS OR COIN_USE_BLAS)
    set(IPOPTLIB_PCFILES "${IPOPTLIB_PCFILES} -lblas")
endif ()
if (COIN_ENABLE_DOWNLOAD_CLAPACK)
    set(IPOPTLIB_PCFILES "${IPOPTLIB_PCFILES} -lf2c")
endif ()
set(PACKAGE_VERSION "${IPOPT_VERSION}")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/ipopt.pc.in ${CMAKE_CURRENT_BINARY_DIR}/ipopt.pc @ONLY)

#
# Build
#
set (IPOPT_SRC_ALGORITHM_LIST ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpAdaptiveMuUpdate.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpAlgBuilder.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpAlgorithmRegOp.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpAugRestoSystemSolver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpBacktrackingLineSearch.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpDefaultIterateInitializer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpEquilibrationScaling.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpExactHessianUpdater.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpFilter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpFilterLSAcceptor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpGenAugSystemSolver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpGradientScaling.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpIpoptAlg.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpIpoptCalculatedQuantities.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpIpoptData.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpIteratesVector.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpLeastSquareMults.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpLimMemQuasiNewtonUpdater.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpLoqoMuOracle.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpLowRankAugSystemSolver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpLowRankSSAugSystemSolver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpMonotoneMuUpdate.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpNLPBoundsRemover.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpNLPScaling.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpOptErrorConvCheck.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpOrigIpoptNLP.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpOrigIterationOutput.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpPDFullSpaceSolver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpPDPerturbationHandler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpPDSearchDirCalc.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpPenaltyLSAcceptor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpProbingMuOracle.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpQualityFunctionMuOracle.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpRestoConvCheck.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpRestoFilterConvCheck.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpRestoIpoptNLP.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpRestoIterateInitializer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpRestoIterationOutput.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpRestoMinC_1Nrm.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpRestoPenaltyConvCheck.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpRestoRestoPhase.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpStdAugSystemSolver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpTimingStatistics.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpUserScaling.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/IpWarmStartIterateInitializer.cpp
        )

set (IPOPT_SRC_ALGORITHM_INEXACT_LIST ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Inexact/IpInexactAlgBuilder.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Inexact/IpInexactCq.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Inexact/IpInexactData.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Inexact/IpInexactDoglegNormal.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Inexact/IpInexactLSAcceptor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Inexact/IpInexactNewtonNormal.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Inexact/IpInexactNormalTerminationTester.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Inexact/IpInexactRegOp.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Inexact/IpInexactSearchDirCalc.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Inexact/IpInexactTSymScalingMethod.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Inexact/IpIterativeSolverTerminationTester.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Inexact/IpInexactPDSolver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Inexact/IpInexactPDTerminationTester.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Inexact/IpIterativePardisoSolverInterface.cpp)

set (IPOPT_SRC_ALGORITHM_LINEARSOLVERS_LIST ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/LinearSolvers/IpLinearSolversRegOp.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/LinearSolvers/IpLinearSolvers.c
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/LinearSolvers/IpSlackBasedTSymScalingMethod.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/LinearSolvers/IpTripletToCSRConverter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/LinearSolvers/IpTSymDependencyDetector.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/LinearSolvers/IpTSymLinearSolver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/LinearSolvers/IpMa27TSolverInterface.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/LinearSolvers/IpMa57TSolverInterface.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/LinearSolvers/IpMa86SolverInterface.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/LinearSolvers/IpMa97SolverInterface.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/LinearSolvers/IpMc19TSymScalingMethod.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/LinearSolvers/IpMa28TDependencyDetector.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/LinearSolvers/IpMa77SolverInterface.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/LinearSolvers/IpPardisoSolverInterface.cpp)

enable_language(Fortran)

set (IPOPT_SRC_APPS_CUTERINTERFACE_LIST )
set (IPOPT_SRC_APPS_AMPLSOLVER_LIST )

set (IPOPT_SRC_CONTRIB_CGPENALTY_LIST ${CMAKE_CURRENT_SOURCE_DIR}/contrib/CGPenalty/IpCGPenaltyCq.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/contrib/CGPenalty/IpCGPenaltyData.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/contrib/CGPenalty/IpCGPenaltyLSAcceptor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/contrib/CGPenalty/IpCGPenaltyRegOp.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/contrib/CGPenalty/IpCGPerturbationHandler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/contrib/CGPenalty/IpCGSearchDirCalc.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/contrib/CGPenalty/IpPiecewisePenalty.cpp)

set (IPOPT_SRC_COMMON_LIST ${CMAKE_CURRENT_SOURCE_DIR}/Common/IpJournalist.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Common/IpDebug.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Common/IpObserver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Common/IpOptionsList.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Common/IpRegOptions.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Common/IpTaggedObject.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Common/IpUtils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Common/IpLibraryLoader.cpp)

set (IPOPT_SRC_INTERFACES_LIST ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces/IpInterfacesRegOp.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces/IpIpoptApplication.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces/IpSolveStatistics.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces/IpStdCInterface.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces/IpStdFInterface.c
        ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces/IpStdInterfaceTNLP.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces/IpTNLP.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces/IpTNLPAdapter.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces/IpTNLPReducer.cpp)

set (IPOPT_SRC_LINALG_LIST ${CMAKE_CURRENT_SOURCE_DIR}/LinAlg/IpBlas.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinAlg/IpCompoundMatrix.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinAlg/IpCompoundSymMatrix.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinAlg/IpCompoundVector.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinAlg/IpDenseGenMatrix.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinAlg/IpDenseSymMatrix.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinAlg/IpDenseVector.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinAlg/IpDiagMatrix.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinAlg/IpExpandedMultiVectorMatrix.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinAlg/IpExpansionMatrix.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinAlg/IpIdentityMatrix.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinAlg/IpLapack.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinAlg/IpLowRankUpdateSymMatrix.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinAlg/IpMatrix.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinAlg/IpMultiVectorMatrix.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinAlg/IpScaledMatrix.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinAlg/IpSumMatrix.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinAlg/IpSumSymMatrix.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinAlg/IpSymScaledMatrix.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinAlg/IpTransposeMatrix.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinAlg/IpVector.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinAlg/IpZeroMatrix.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinAlg/IpZeroSymMatrix.cpp)

set (IPOPT_SRC_LINALG_TMATRICES ${CMAKE_CURRENT_SOURCE_DIR}/LinAlg/TMatrices/IpGenTMatrix.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinAlg/TMatrices/IpSymTMatrix.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/LinAlg/TMatrices/IpTripletHelper.cpp)

if (IPOPT_HAS_MUMPS)
        set (IPOPT_SRC_ALGORITHM_LINEARSOLVERS_LIST ${IPOPT_SRC_ALGORITHM_LINEARSOLVERS_LIST}
                ${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/LinearSolvers/IpMumpsSolverInterface.cpp)
endif ()
    
set (IPOPT_SRC_LIST ${IPOPT_SRC_ALGORITHM_LIST}
        ${IPOPT_SRC_ALGORITHM_LINEARSOLVERS_LIST}
        ${IPOPT_SRC_APPS_CUTERINTERFACE_LIST}
        ${IPOPT_SRC_APPS_AMPLSOLVER_LIST}
        ${IPOPT_SRC_CONTRIB_CGPENALTY_LIST}
        ${IPOPT_SRC_COMMON_LIST}
        ${IPOPT_SRC_INTERFACES_LIST}
        ${IPOPT_SRC_LINALG_LIST}
        ${IPOPT_SRC_LINALG_TMATRICES})

if (IPOPT_ENABLE_INEXACT)
    set(IPOPT_SRC_LIST ${IPOPT_SRC_LIST}
            ${IPOPT_SRC_ALGORITHM_INEXACT_LIST})
endif ()

macro(set_include_directories TARGET)
    target_include_directories(${TARGET} BEFORE PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/Interfaces)
endmacro ()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Algorithm)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/LinearSolvers)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Algorithm/Inexact)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/contrib/CGPenalty)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/contrib/LinearSolverLoader)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Interfaces)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Common)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/LinAlg)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Apps/AmplSolver)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/LinAlg/TMatrices)

if (WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_DEPRECATE)
endif ()

if (ENABLE_SHARED_LIBRARIES)
    add_library(ipopt SHARED ${IPOPT_SRC_LIST})
else ()
    add_library(ipopt STATIC ${IPOPT_SRC_LIST})
    target_link_libraries(ipopt)
endif ()
if (COIN_COMPILE_LTO)
    set_target_properties(ipopt PROPERTIES INTERPROCEDURAL_OPTIMIZATION true)
endif ()
set_include_directories(ipopt)


SET_TARGET_PROPERTIES(ipopt PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
SET_TARGET_PROPERTIES(ipopt PROPERTIES 
    LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
    LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
SET_TARGET_PROPERTIES(ipopt PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})