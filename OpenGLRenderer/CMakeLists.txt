SET(SOURCES
    MeshRenderer.cpp
    Camera.cpp
    OpenGLRendererSystem.cpp
    SMEOpenGLWidget.cpp
    initPlugin.cpp
    Shader.cpp
    )

SET(HEADERS
    MeshRenderer.h
    Camera.h
    OpenGLRendererSystem.h
    SMEOpenGLWidget.h
    Shader.h
    )

FIND_PACKAGE(GLEW REQUIRED)
FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)

FIND_PACKAGE(Eigen3 REQUIRED)
INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS})

add_library(SMEOpenGL SHARED ${SOURCES} ${HEADERS})
target_link_libraries(SMEOpenGL SME ${GLEW_LIBRARIES} Qt5::Gui Qt5::Widgets)

