SET(SOURCES
	Transform.cpp
        transformsystem.cpp
        initPlugin.cpp
        assets/Mesh.cpp
        assets/TetraMesh.h
        )

SET(HEADERS
	Transform.h
        TransformSystem.h
        assets/Mesh.cpp
        assets/TetraMesh.cpp
   )

FIND_PACKAGE(Eigen3 REQUIRED)
MESSAGE(STATUS "Eigen3 directory: ${EIGEN3_INCLUDE_DIR}" )
INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})

add_library(SMECore SHARED ${SOURCES} ${HEADERS})
target_link_libraries(SMECore SME tinyxml2 assimp)
