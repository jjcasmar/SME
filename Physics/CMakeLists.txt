SET(SOURCES
    initPlugin.cpp
    CorotationalElasticFEM.cpp
    PhysicsSystem.cpp
    )

SET(HEADERS
    CorotationalElasticFEM.h
    PhysicsSystem.h
    )

FIND_PACKAGE(Eigen3 REQUIRED)
INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})

add_library(SMEPhysics SHARED ${SOURCES} ${HEADERS})
target_link_libraries(SMEPhysics)

