SET(SOURCES
        World.cpp
        AssetLibrary.cpp 
        ComponentFactory.cpp
        SystemFactory.cpp
        AssetFactory.cpp
        Plugin.cpp
        PluginManager.cpp
        SceneLoader.cpp
        Data.cpp
        helpers/functions.cpp
        )

SET(HEADERS
	World.h
        AssetLibrary.h    
        ComponentFactory.h
        SystemFactory.h
        AssetFactory.h
        Plugin.h
        PluginManager.h
        SceneLoader.h
        Data.h
        )

add_library(SME SHARED ${SOURCES} ${HEADERS})
target_link_libraries(SME tinyxml2)

