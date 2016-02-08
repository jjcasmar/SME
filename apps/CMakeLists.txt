SET(SOURCES
	main.cpp
        SMEApplication.cpp
        )

SET(HEADERS
        SMEApplication.h


        )

FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(DL REQUIRED)
FIND_PACKAGE(Eigen3 REQUIRED)
INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})

add_executable(SMETrial ${SOURCES} ${HEADERS})
target_link_libraries(SMETrial SME ${DL_LIBRARIES} Qt5::Widgets)

