#ifndef SCENELOADER_H
#define SCENELOADER_H

#include <core/World.h>
#include <core/SystemFactory.h>
#include <core/ComponentFactory.h>
#include <core/AssetFactory.h>

namespace SME
{
  namespace core
  {
    class World;
    class SceneLoader
    {
      public:
        SceneLoader();

        static bool load(const std::string &src); 

        const static std::string getErrorString();
        

      protected:
        static SME::core::EntityId retrieveEntity(tinyxml2::XMLElement *entityElement);

        static std::string pluginDefaultDir;
        static std::string errorString;
    };
  }
}


#endif // SCENELOADER_H
