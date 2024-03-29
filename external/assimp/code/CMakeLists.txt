# Listing and grouping of all the source files.
# 1) Set the file lists for each component
# 2) Create a Source Group for each component, for IDE project orginization
# 3) Add libassimp using the file lists (eliminates duplication of file names between
#    source groups and library command)
#
cmake_minimum_required( VERSION 2.6 )
SET( HEADER_PATH ../include/assimp )

SET( COMPILER_HEADERS
  ${HEADER_PATH}/Compiler/pushpack1.h
  ${HEADER_PATH}/Compiler/poppack1.h
  ${HEADER_PATH}/Compiler/pstdint.h
)
SOURCE_GROUP( Compiler FILES ${COMPILER_HEADERS})

SET( PUBLIC_HEADERS
  ${HEADER_PATH}/anim.h
  ${HEADER_PATH}/ai_assert.h
  ${HEADER_PATH}/camera.h
  ${HEADER_PATH}/color4.h
  ${HEADER_PATH}/color4.inl
  ${HEADER_PATH}/config.h
  ${HEADER_PATH}/defs.h
  ${HEADER_PATH}/cfileio.h
  ${HEADER_PATH}/light.h
  ${HEADER_PATH}/material.h
  ${HEADER_PATH}/material.inl
  ${HEADER_PATH}/matrix3x3.h
  ${HEADER_PATH}/matrix3x3.inl
  ${HEADER_PATH}/matrix4x4.h
  ${HEADER_PATH}/matrix4x4.inl
  ${HEADER_PATH}/mesh.h
  ${HEADER_PATH}/postprocess.h
  ${HEADER_PATH}/quaternion.h
  ${HEADER_PATH}/quaternion.inl
  ${HEADER_PATH}/scene.h
  ${HEADER_PATH}/metadata.h
  ${HEADER_PATH}/texture.h
  ${HEADER_PATH}/types.h
  ${HEADER_PATH}/vector2.h
  ${HEADER_PATH}/vector2.inl
  ${HEADER_PATH}/vector3.h
  ${HEADER_PATH}/vector3.inl
  ${HEADER_PATH}/version.h
  ${HEADER_PATH}/cimport.h
  ${HEADER_PATH}/importerdesc.h
  ${HEADER_PATH}/Importer.hpp
  ${HEADER_PATH}/DefaultLogger.hpp
  ${HEADER_PATH}/ProgressHandler.hpp
  ${HEADER_PATH}/IOStream.hpp
  ${HEADER_PATH}/IOSystem.hpp
  ${HEADER_PATH}/Logger.hpp
  ${HEADER_PATH}/LogStream.hpp
  ${HEADER_PATH}/NullLogger.hpp
  ${HEADER_PATH}/cexport.h
  ${HEADER_PATH}/Exporter.hpp
)

SET( Core_SRCS
  Assimp.cpp
)

SET( Boost_SRCS
  BoostWorkaround/boost/math/common_factor_rt.hpp
  BoostWorkaround/boost/foreach.hpp
  BoostWorkaround/boost/format.hpp
  BoostWorkaround/boost/scoped_array.hpp
  BoostWorkaround/boost/scoped_ptr.hpp
  BoostWorkaround/boost/shared_array.hpp
  BoostWorkaround/boost/shared_ptr.hpp
  BoostWorkaround/boost/make_shared.hpp
  BoostWorkaround/boost/static_assert.hpp
  BoostWorkaround/boost/tuple/tuple.hpp
)
SOURCE_GROUP(Boost FILES ${Boost_SRCS})

SET( Logging_SRCS
  ${HEADER_PATH}/DefaultLogger.hpp
  ${HEADER_PATH}/LogStream.hpp
  ${HEADER_PATH}/Logger.hpp
  ${HEADER_PATH}/NullLogger.hpp
  Win32DebugLogStream.h
  DefaultLogger.cpp
  FileLogStream.h
  StdOStreamLogStream.h
)
SOURCE_GROUP(Logging FILES ${Logging_SRCS})

SET( Common_SRCS
  fast_atof.h
  qnan.h
  BaseImporter.cpp
  BaseImporter.h
  BaseProcess.cpp
  BaseProcess.h
  Importer.h
  ScenePrivate.h
  PostStepRegistry.cpp
  ImporterRegistry.cpp
  ByteSwapper.h
  DefaultProgressHandler.h
  DefaultIOStream.cpp
  DefaultIOStream.h
  DefaultIOSystem.cpp
  DefaultIOSystem.h
  CInterfaceIOWrapper.h
  Hash.h
  Importer.cpp
  IFF.h
  MemoryIOWrapper.h
  ParsingUtils.h
  StreamReader.h
  StreamWriter.h
  StringComparison.h
  SGSpatialSort.cpp
  SGSpatialSort.h
  VertexTriangleAdjacency.cpp
  VertexTriangleAdjacency.h
  GenericProperty.h
  SpatialSort.cpp
  SpatialSort.h
  SceneCombiner.cpp
  SceneCombiner.h
  ScenePreprocessor.cpp
  ScenePreprocessor.h
  SkeletonMeshBuilder.cpp
  SkeletonMeshBuilder.h
  SplitByBoneCountProcess.cpp
  SplitByBoneCountProcess.h
  SmoothingGroups.h
  StandardShapes.cpp
  StandardShapes.h
  TargetAnimation.cpp
  TargetAnimation.h
  RemoveComments.cpp
  RemoveComments.h
  Subdivision.cpp
  Subdivision.h
  Vertex.h
  LineSplitter.h
  TinyFormatter.h
  Profiler.h
  LogAux.h
  Bitmap.cpp
  Bitmap.h
  XMLTools.h
  Version.cpp
)
SOURCE_GROUP(Common FILES ${Common_SRCS})

IF ( ASSIMP_BUILD_NONFREE_C4D_IMPORTER )
  SET( C4D_SRCS
    C4DImporter.cpp
    C4DImporter.h
  )
  SOURCE_GROUP( C4D FILES ${C4D_SRCS})
ENDIF ( ASSIMP_BUILD_NONFREE_C4D_IMPORTER )

# macro to add the CMake Option ADD_ASSIMP_IMPORTER_<name> which enables compile of loader
# this way selective loaders can be compiled (reduces filesize + compile time)
MACRO(ADD_ASSIMP_IMPORTER name)
  OPTION(ASSIMP_BUILD_${name}_IMPORTER "build the ${name} importer" TRUE)
  IF(ASSIMP_BUILD_${name}_IMPORTER)
    LIST(APPEND ASSIMP_LOADER_SRCS ${ARGN})
    SET(ASSIMP_IMPORTERS_ENABLED "${ASSIMP_IMPORTERS_ENABLED} ${name}")
    SET(${name}_SRCS ${ARGN})
    SOURCE_GROUP(${name} FILES ${ARGN})
  ELSE()
    SET(${name}_SRC "")
    SET(ASSIMP_IMPORTERS_DISABLED "${ASSIMP_IMPORTERS_DISABLED} ${name}")
    add_definitions(-DASSIMP_BUILD_NO_${name}_IMPORTER)
  ENDIF()
ENDMACRO()

SET(ASSIMP_LOADER_SRCS "")
SET(ASSIMP_IMPORTERS_ENABLED "") # list of enabled importers
SET(ASSIMP_IMPORTERS_DISABLED "") # disabled list (used to print)

ADD_ASSIMP_IMPORTER(3DS
  3DSConverter.cpp
  3DSHelper.h
  3DSLoader.cpp
  3DSLoader.h
  3DSExporter.h
  3DSExporter.cpp
)

ADD_ASSIMP_IMPORTER(AC
  ACLoader.cpp
  ACLoader.h
)

ADD_ASSIMP_IMPORTER(ASE
  ASELoader.cpp
  ASELoader.h
  ASEParser.cpp
  ASEParser.h
)

ADD_ASSIMP_IMPORTER(ASSBIN
  AssbinExporter.h
  AssbinExporter.cpp
  AssbinLoader.h
  AssbinLoader.cpp
)

ADD_ASSIMP_IMPORTER(ASSXML
  AssxmlExporter.h
  AssxmlExporter.cpp
)

ADD_ASSIMP_IMPORTER(B3D
  B3DImporter.cpp
  B3DImporter.h
)

ADD_ASSIMP_IMPORTER(BVH
  BVHLoader.cpp
  BVHLoader.h
)

ADD_ASSIMP_IMPORTER(COLLADA
  ColladaHelper.h
  ColladaLoader.cpp
  ColladaLoader.h
  ColladaParser.cpp
  ColladaParser.h
  ColladaExporter.h
  ColladaExporter.cpp
)

ADD_ASSIMP_IMPORTER(DXF
  DXFLoader.cpp
  DXFLoader.h
  DXFHelper.h
)

ADD_ASSIMP_IMPORTER(CSM
  CSMLoader.cpp
  CSMLoader.h
)

ADD_ASSIMP_IMPORTER(HMP
  HMPFileData.h
  HMPLoader.cpp
  HMPLoader.h
  HalfLifeFileData.h
)

#FIXME: allow to set IRRMESH by option
ADD_ASSIMP_IMPORTER(IRR
  IRRLoader.cpp
  IRRLoader.h
  IRRMeshLoader.cpp
  IRRMeshLoader.h
  IRRShared.cpp
  IRRShared.h
)

ADD_ASSIMP_IMPORTER(LWO
  LWOAnimation.cpp
  LWOAnimation.h
  LWOBLoader.cpp
  LWOFileData.h
  LWOLoader.cpp
  LWOLoader.h
  LWOMaterial.cpp
)

ADD_ASSIMP_IMPORTER(LWS
  LWSLoader.cpp
  LWSLoader.h
)

ADD_ASSIMP_IMPORTER(MD2
  MD2FileData.h
  MD2Loader.cpp
  MD2Loader.h
  MD2NormalTable.h
)

ADD_ASSIMP_IMPORTER(MD3
  MD3FileData.h
  MD3Loader.cpp
  MD3Loader.h
)

ADD_ASSIMP_IMPORTER(MD5
  MD5Loader.cpp
  MD5Loader.h
  MD5Parser.cpp
  MD5Parser.h
)

ADD_ASSIMP_IMPORTER(MDC
  MDCFileData.h
  MDCLoader.cpp
  MDCLoader.h
  MDCNormalTable.h
)

ADD_ASSIMP_IMPORTER(MDL
  MDLDefaultColorMap.h
  MDLFileData.h
  MDLLoader.cpp
  MDLLoader.h
  MDLMaterialLoader.cpp
)

SET( MaterialSystem_SRCS
  MaterialSystem.cpp
  MaterialSystem.h
)
SOURCE_GROUP( MaterialSystem FILES ${MaterialSystem_SRCS})

ADD_ASSIMP_IMPORTER(NFF
  NFFLoader.cpp
  NFFLoader.h
)

ADD_ASSIMP_IMPORTER(NDO
  NDOLoader.cpp
  NDOLoader.h
)

ADD_ASSIMP_IMPORTER(OFF
  OFFLoader.cpp
  OFFLoader.h
)

ADD_ASSIMP_IMPORTER(OBJ
  ObjFileData.h
  ObjFileImporter.cpp
  ObjFileImporter.h
  ObjFileMtlImporter.cpp
  ObjFileMtlImporter.h
  ObjFileParser.cpp
  ObjFileParser.h
  ObjTools.h

  ObjExporter.h
  ObjExporter.cpp
)

ADD_ASSIMP_IMPORTER(OGRE
  OgreImporter.h
  OgreStructs.h
  OgreParsingUtils.h
  OgreBinarySerializer.h
  OgreXmlSerializer.h
  OgreImporter.cpp
  OgreStructs.cpp
  OgreBinarySerializer.cpp
  OgreXmlSerializer.cpp
  OgreMaterial.cpp
)

ADD_ASSIMP_IMPORTER(OPENGEX
  OpenGEXExporter.cpp
  OpenGEXExporter.h
  OpenGEXImporter.cpp
  OpenGEXImporter.h
  OpenGEXStructs.h
)

ADD_ASSIMP_IMPORTER(PLY
  PlyLoader.cpp
  PlyLoader.h
  PlyParser.cpp
  PlyParser.h
  PlyExporter.cpp
  PlyExporter.h
)

ADD_ASSIMP_IMPORTER(MS3D
  MS3DLoader.cpp
  MS3DLoader.h
)

ADD_ASSIMP_IMPORTER(COB
  COBLoader.cpp
  COBLoader.h
  COBScene.h
)

ADD_ASSIMP_IMPORTER(BLEND
  BlenderLoader.cpp
  BlenderLoader.h
  BlenderDNA.cpp
  BlenderDNA.h
  BlenderDNA.inl
  BlenderScene.cpp
  BlenderScene.h
  BlenderSceneGen.h
  BlenderIntermediate.h
  BlenderModifier.h
  BlenderModifier.cpp
  BlenderBMesh.h
  BlenderBMesh.cpp
  BlenderTessellator.h
  BlenderTessellator.cpp
)

ADD_ASSIMP_IMPORTER(IFC
  IFCLoader.cpp
  IFCLoader.h
  IFCReaderGen.cpp
  IFCReaderGen.h
  IFCUtil.h
  IFCUtil.cpp
  IFCGeometry.cpp
  IFCMaterial.cpp
  IFCProfile.cpp
  IFCCurve.cpp
  IFCBoolean.cpp
  IFCOpenings.cpp
  STEPFile.h
  STEPFileReader.h
  STEPFileReader.cpp
  STEPFileEncoding.cpp
  STEPFileEncoding.h
)

ADD_ASSIMP_IMPORTER(XGL
  XGLLoader.cpp
  XGLLoader.h
)


ADD_ASSIMP_IMPORTER(FBX
  FBXImporter.cpp
  FBXCompileConfig.h
  FBXImporter.h
  FBXParser.cpp
  FBXParser.h
  FBXTokenizer.cpp
  FBXTokenizer.h
  FBXImportSettings.h
  FBXConverter.h
  FBXConverter.cpp
  FBXUtil.h
  FBXUtil.cpp
  FBXDocument.h
  FBXDocument.cpp
  FBXProperties.h
  FBXProperties.cpp
  FBXMeshGeometry.cpp
  FBXMaterial.cpp
  FBXModel.cpp
  FBXAnimation.cpp
  FBXNodeAttribute.cpp
  FBXDeformer.cpp
  FBXBinaryTokenizer.cpp
  FBXDocumentUtil.cpp
)

SET( PostProcessing_SRCS
  CalcTangentsProcess.cpp
  CalcTangentsProcess.h
  ComputeUVMappingProcess.cpp
  ComputeUVMappingProcess.h
  ConvertToLHProcess.cpp
  ConvertToLHProcess.h
  FindDegenerates.cpp
  FindDegenerates.h
  FindInstancesProcess.cpp
  FindInstancesProcess.h
  FindInvalidDataProcess.cpp
  FindInvalidDataProcess.h
  FixNormalsStep.cpp
  FixNormalsStep.h
  GenFaceNormalsProcess.cpp
  GenFaceNormalsProcess.h
  GenVertexNormalsProcess.cpp
  GenVertexNormalsProcess.h
  PretransformVertices.cpp
  PretransformVertices.h
  ImproveCacheLocality.cpp
  ImproveCacheLocality.h
  JoinVerticesProcess.cpp
  JoinVerticesProcess.h
  LimitBoneWeightsProcess.cpp
  LimitBoneWeightsProcess.h
  RemoveRedundantMaterials.cpp
  RemoveRedundantMaterials.h
  RemoveVCProcess.cpp
  RemoveVCProcess.h
  SortByPTypeProcess.cpp
  SortByPTypeProcess.h
  SplitLargeMeshes.cpp
  SplitLargeMeshes.h
  TextureTransform.cpp
  TextureTransform.h
  TriangulateProcess.cpp
  TriangulateProcess.h
  ValidateDataStructure.cpp
  ValidateDataStructure.h
  OptimizeGraph.cpp
  OptimizeGraph.h
  OptimizeMeshes.cpp
  OptimizeMeshes.h
  DeboneProcess.cpp
  DeboneProcess.h
  ProcessHelper.h
  ProcessHelper.cpp
  PolyTools.h
  MakeVerboseFormat.cpp
  MakeVerboseFormat.h
)
SOURCE_GROUP( PostProcessing FILES ${PostProcessing_SRCS})

ADD_ASSIMP_IMPORTER(Q3D
  Q3DLoader.cpp
  Q3DLoader.h
)

ADD_ASSIMP_IMPORTER(Q3BSP
  Q3BSPFileData.h
  Q3BSPFileParser.h
  Q3BSPFileParser.cpp
  Q3BSPFileImporter.h
  Q3BSPFileImporter.cpp
  Q3BSPZipArchive.h
  Q3BSPZipArchive.cpp
)

ADD_ASSIMP_IMPORTER(RAW
  RawLoader.cpp
  RawLoader.h
)

ADD_ASSIMP_IMPORTER(SMD
  SMDLoader.cpp
  SMDLoader.h
)

ADD_ASSIMP_IMPORTER(STL
  STLLoader.cpp
  STLLoader.h
  STLExporter.h
  STLExporter.cpp
)

ADD_ASSIMP_IMPORTER(TERRAGEN
  TerragenLoader.cpp
  TerragenLoader.h
)

ADD_ASSIMP_IMPORTER(3D
  UnrealLoader.cpp
  UnrealLoader.h
)

ADD_ASSIMP_IMPORTER(X
  XFileHelper.h
  XFileImporter.cpp
  XFileImporter.h
  XFileParser.cpp
  XFileParser.h
  XFileExporter.h
  XFileExporter.cpp
)

SET( Step_SRCS
  StepExporter.h
  StepExporter.cpp
)
SOURCE_GROUP( Step FILES ${Step_SRCS})

SET( Exporter_SRCS
  Exporter.cpp
  AssimpCExport.cpp
  BlobIOSystem.h
)
SOURCE_GROUP( Exporter FILES ${Exporter_SRCS})

SET( Extra_SRCS
  MD4FileData.h
)
SOURCE_GROUP( Extra FILES ${Extra_SRCS})

SET( IrrXML_SRCS
  irrXMLWrapper.h
  ../contrib/irrXML/CXMLReaderImpl.h
  ../contrib/irrXML/heapsort.h
  ../contrib/irrXML/irrArray.h
  ../contrib/irrXML/irrString.h
  ../contrib/irrXML/irrTypes.h
  ../contrib/irrXML/irrXML.cpp
  ../contrib/irrXML/irrXML.h
)
SOURCE_GROUP( IrrXML FILES ${IrrXML_SRCS})

SET( ConvertUTF_SRCS
  ../contrib/ConvertUTF/ConvertUTF.h
  ../contrib/ConvertUTF/ConvertUTF.c
)
SOURCE_GROUP( ConvertUTF FILES ${ConvertUTF_SRCS})

SET( Clipper_SRCS
  ../contrib/clipper/clipper.hpp
  ../contrib/clipper/clipper.cpp
)
SOURCE_GROUP( Clipper FILES ${Clipper_SRCS})


SET( Poly2Tri_SRCS
  ../contrib/poly2tri/poly2tri/common/shapes.cc
  ../contrib/poly2tri/poly2tri/common/shapes.h
  ../contrib/poly2tri/poly2tri/common/utils.h
  ../contrib/poly2tri/poly2tri/sweep/advancing_front.h
  ../contrib/poly2tri/poly2tri/sweep/advancing_front.cc
  ../contrib/poly2tri/poly2tri/sweep/cdt.cc
  ../contrib/poly2tri/poly2tri/sweep/cdt.h
  ../contrib/poly2tri/poly2tri/sweep/sweep.cc
  ../contrib/poly2tri/poly2tri/sweep/sweep.h
  ../contrib/poly2tri/poly2tri/sweep/sweep_context.cc
  ../contrib/poly2tri/poly2tri/sweep/sweep_context.h
)
SOURCE_GROUP( Poly2Tri FILES ${Poly2Tri_SRCS})

SET( unzip_SRCS
  ../contrib/unzip/crypt.h
  ../contrib/unzip/ioapi.c
  ../contrib/unzip/ioapi.h
  ../contrib/unzip/unzip.c
  ../contrib/unzip/unzip.h
)
SOURCE_GROUP( unzip FILES ${unzip_SRCS})

SET ( openddl_parser_SRCS
  ../contrib/openddlparser/code/OpenDDLParser.cpp
  ../contrib/openddlparser/code/DDLNode.cpp
  ../contrib/openddlparser/code/OpenDDLCommon.cpp
  ../contrib/openddlparser/code/OpenDDLExport.cpp
  ../contrib/openddlparser/code/Value.cpp
  ../contrib/openddlparser/include/openddlparser/OpenDDLParser.h
  ../contrib/openddlparser/include/openddlparser/OpenDDLParserUtils.h
  ../contrib/openddlparser/include/openddlparser/OpenDDLCommon.h
  ../contrib/openddlparser/include/openddlparser/OpenDDLExport.h
  ../contrib/openddlparser/include/openddlparser/DDLNode.h
  ../contrib/openddlparser/include/openddlparser/Value.h
)
SOURCE_GROUP( openddl_parser FILES ${openddl_parser_SRCS})

# VC2010 fixes
if(MSVC10)
  option( VC10_STDINT_FIX "Fix for VC10 Compiler regarding pstdint.h redefinition errors" OFF )
  if( VC10_STDINT_FIX )
    ADD_DEFINITIONS( -D_STDINT )
  endif( VC10_STDINT_FIX )
endif(MSVC10)

ADD_DEFINITIONS( -DASSIMP_BUILD_DLL_EXPORT )

if ( MSVC )
  ADD_DEFINITIONS( -D_SCL_SECURE_NO_WARNINGS )
  ADD_DEFINITIONS( -D_CRT_SECURE_NO_WARNINGS )
endif ( MSVC )

if (UNZIP_FOUND)
  SET (unzip_compile_SRCS "")
else (UNZIP_FOUND)
  SET (unzip_compile_SRCS ${unzip_SRCS})
endif (UNZIP_FOUND)

MESSAGE(STATUS "Enabled formats:${ASSIMP_IMPORTERS_ENABLED}")
MESSAGE(STATUS "Disabled formats:${ASSIMP_IMPORTERS_DISABLED}")

SET( assimp_src
  # Assimp Files
  ${Core_SRCS}
  ${Common_SRCS}
  ${Logging_SRCS}
  ${Exporter_SRCS}
  ${PostProcessing_SRCS}
  ${MaterialSystem_SRCS}
  ${Step_SRCS}

  # Model Support
  ${ASSIMP_LOADER_SRCS}

  # Third-party libraries
  ${IrrXML_SRCS}
  ${ConvertUTF_SRCS}
  ${unzip_compile_SRCS}
  ${Poly2Tri_SRCS}
  ${Clipper_SRCS}
  ${openddl_parser_SRCS}
  # Necessary to show the headers in the project when using the VC++ generator:
  ${Boost_SRCS}

  ${PUBLIC_HEADERS}
  ${COMPILER_HEADERS}

)
add_definitions( -DOPENDDLPARSER_BUILD )

INCLUDE_DIRECTORIES(
  ../contrib/openddlparser/include
)

IF (ASSIMP_BUILD_NONFREE_C4D_IMPORTER)
  SET( assimp_src ${assimp_src} ${C4D_SRCS})
  INCLUDE_DIRECTORIES(${C4D_INCLUDES})
ENDIF (ASSIMP_BUILD_NONFREE_C4D_IMPORTER)

ADD_LIBRARY( assimp ${assimp_src} )

TARGET_LINK_LIBRARIES(assimp ${ZLIB_LIBRARIES} ${OPENDDL_PARSER_LIBRARIES} )
target_include_directories(assimp PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")

if(ANDROID AND ASSIMP_ANDROID_JNIIOSYSTEM)
  set(ASSIMP_ANDROID_JNIIOSYSTEM_PATH port/AndroidJNI)
  add_subdirectory(../${ASSIMP_ANDROID_JNIIOSYSTEM_PATH}/ ../${ASSIMP_ANDROID_JNIIOSYSTEM_PATH}/)
  target_link_libraries(assimp android_jniiosystem)
endif(ANDROID AND ASSIMP_ANDROID_JNIIOSYSTEM)

IF (ASSIMP_BUILD_NONFREE_C4D_IMPORTER)
  TARGET_LINK_LIBRARIES(assimp optimized ${C4D_RELEASE_LIBRARY})
  TARGET_LINK_LIBRARIES(assimp debug ${C4D_DEBUG_LIBRARY})
  TARGET_LINK_LIBRARIES(assimp ${C4D_EXTRA_LIBRARIES})
ENDIF (ASSIMP_BUILD_NONFREE_C4D_IMPORTER)

if( MSVC )
  # in order to prevent DLL hell, each of the DLLs have to be suffixed with the major version and msvc prefix
  if( MSVC70 OR MSVC71 )
    set(MSVC_PREFIX "vc70")
  elseif( MSVC80 )
    set(MSVC_PREFIX "vc80")
  elseif( MSVC90 )
    set(MSVC_PREFIX "vc90")
  elseif( MSVC10 )
    set(MSVC_PREFIX "vc100")
  elseif( MSVC11 )
    set(MSVC_PREFIX "vc110")
  elseif( MSVC12 )
    set(MSVC_PREFIX "vc120")
  else()
    set(MSVC_PREFIX "vc130")
  endif()
  set(LIBRARY_SUFFIX "${ASSIMP_LIBRARY_SUFFIX}-${MSVC_PREFIX}-mt" CACHE STRING "the suffix for the assimp windows library")
endif()

SET_TARGET_PROPERTIES( assimp PROPERTIES
  VERSION ${ASSIMP_VERSION}
  SOVERSION ${ASSIMP_SOVERSION} # use full version
  OUTPUT_NAME assimp${LIBRARY_SUFFIX}
)

if (APPLE)
  SET_TARGET_PROPERTIES( assimp PROPERTIES INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/${LIB_INSTALL_DIR}")
endif()

# Build against external unzip, or add ../contrib/unzip so
# assimp can #include "unzip.h"
if (UNZIP_FOUND)
  INCLUDE_DIRECTORIES(${UNZIP_INCLUDE_DIRS})
  TARGET_LINK_LIBRARIES(assimp ${UNZIP_LIBRARIES})
else (UNZIP_FOUND)
  INCLUDE_DIRECTORIES("../contrib/unzip")
endif (UNZIP_FOUND)

INSTALL( TARGETS assimp
  LIBRARY DESTINATION ${ASSIMP_LIB_INSTALL_DIR}
  ARCHIVE DESTINATION ${ASSIMP_LIB_INSTALL_DIR}
  RUNTIME DESTINATION ${ASSIMP_BIN_INSTALL_DIR}
  COMPONENT ${LIBASSIMP_COMPONENT})
INSTALL( FILES ${PUBLIC_HEADERS} DESTINATION ${ASSIMP_INCLUDE_INSTALL_DIR}/assimp COMPONENT assimp-dev)
INSTALL( FILES ${COMPILER_HEADERS} DESTINATION ${ASSIMP_INCLUDE_INSTALL_DIR}/assimp/Compiler COMPONENT assimp-dev)
if (ASSIMP_ANDROID_JNIIOSYSTEM)
  INSTALL(FILES ${HEADER_PATH}/../${ASSIMP_ANDROID_JNIIOSYSTEM_PATH}/AndroidJNIIOSystem.h
    DESTINATION ${ASSIMP_INCLUDE_INSTALL_DIR}
    COMPONENT assimp-dev)
endif(ASSIMP_ANDROID_JNIIOSYSTEM)

if(MSVC AND ASSIMP_INSTALL_PDB)
  install(FILES ${Assimp_BINARY_DIR}/code/Debug/assimp${CMAKE_DEBUG_POSTFIX}.pdb
    DESTINATION ${ASSIMP_LIB_INSTALL_DIR}
    CONFIGURATIONS Debug
  )
  install(FILES ${Assimp_BINARY_DIR}/code/RelWithDebInfo/assimp.pdb
    DESTINATION ${ASSIMP_LIB_INSTALL_DIR}
    CONFIGURATIONS RelWithDebInfo
  )
endif ()
