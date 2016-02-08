#include "SceneLoader.h"
#include <core/World.h>

#include <core/PluginManager.h>
#include <core/SystemFactory.h>
#include <core/ComponentFactory.h>
#include <core/AssetFactory.h>

#include <iostream>

#include <tinyxml2.h>

std::string SME::core::SceneLoader::pluginDefaultDir = "";
std::string SME::core::SceneLoader::errorString = "";

SME::core::SceneLoader::SceneLoader()
{

}

bool SME::core::SceneLoader::load(const std::string &src)
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError result = doc.LoadFile(src.c_str());
    if (result != tinyxml2::XML_NO_ERROR)
    {
        std::cout << doc.GetErrorStr1() << std::endl;
        return false;
    }

    SME::core::World::get()->cleanUp();

    const char *attr;
    tinyxml2::XMLElement *sceneElement = doc.FirstChildElement("Scene");
    if (sceneElement != nullptr)
    {
        tinyxml2::XMLElement *worldConfigurationElement = sceneElement->FirstChildElement("WorldConfiguration");
        if (worldConfigurationElement != nullptr)
        {
            tinyxml2::XMLElement *pluginElement = worldConfigurationElement->FirstChildElement("Plugin");
            while (pluginElement != nullptr)
            {
                attr = pluginElement->Attribute("default_path");
                if (attr != nullptr)
                    pluginDefaultDir = attr;
                attr = pluginElement->Attribute("name");
                if (attr != nullptr)
                {
                    //Permitir la carga de simbolos de debug!
                    if (!SME::core::PluginManager::get()->loadPlugin(pluginDefaultDir +"/"+ std::string(attr)))
                    {
                        errorString = "Error loading plugin: " + pluginDefaultDir+"/"+std::string(attr);
                        return false;
                    }

                }

                attr = pluginElement->Attribute("src");
                if (attr != nullptr)
                {
                    if (!SME::core::PluginManager::get()->loadPlugin(attr))
                    {
                        errorString = "Error loading plugin: " + std::string(attr);
                        return false;
                    }
                }
                pluginElement = pluginElement->NextSiblingElement("Plugin");
            }
        }

        tinyxml2::XMLElement *systemsElement = sceneElement->FirstChildElement("Systems");
        tinyxml2::XMLElement *systemElement;
        if (systemsElement != nullptr)
        {
            systemElement = static_cast<tinyxml2::XMLElement*>(systemsElement->FirstChild());
            while (systemElement != nullptr)
            {
                SME::core::System *system = SME::core::SystemFactory::get()->create(systemElement->Value());
                if (!World::get()->installSystem(system))
                    delete system;
                systemElement = (tinyxml2::XMLElement*)systemElement->NextSiblingElement();
            }
        }

        tinyxml2::XMLElement *assetsElement = sceneElement->FirstChildElement("Assets");
        tinyxml2::XMLElement *assetElement;
        if (assetsElement != nullptr)
        {
            assetElement = static_cast<tinyxml2::XMLElement*>(assetsElement->FirstChild());
            while (assetElement != nullptr)
            {
                SME::core::IAsset *asset =  AssetFactory::get()->create(assetElement->Value());
                if (asset != nullptr)
                {
                    asset->configure(assetElement);
                    World::get()->getAssetLibrary()->addAsset(asset);
                }
                assetElement = (tinyxml2::XMLElement*)assetElement->NextSiblingElement();
            }
        }

        tinyxml2::XMLElement *worldElement = sceneElement->FirstChildElement("World");
        if (worldElement != nullptr)
        {
            tinyxml2::XMLElement *entityElement = worldElement->FirstChildElement("Entity");
            while (entityElement != nullptr)
            {
                retrieveEntity(entityElement);
                entityElement = entityElement->NextSiblingElement("Entity");
            }
        }

        World::get()->systemsPostStart();
    }
}

SME::core::EntityId SME::core::SceneLoader::retrieveEntity(tinyxml2::XMLElement *entityElement)
{
    SME::core::EntityId eid = World::get()->createNewEntity();
    const char *attr;
    attr = entityElement->Attribute("name");
    if (attr != nullptr)
        World::get()->name(attr, eid);

    tinyxml2::XMLElement *componentElement = (tinyxml2::XMLElement*)entityElement->FirstChild();
    while (componentElement != nullptr)
    {
        World::get()->addComponent(componentElement->Value(), eid);
        SME::core::Component *component =  World::get()->getComponent(componentElement->Value(), eid);
        if (component != nullptr)
            component->configure(componentElement);

        componentElement = (tinyxml2::XMLElement*)componentElement->NextSibling();
    }
}

const std::string SME::core::SceneLoader::getErrorString()
{
    std::string answer = errorString;
    errorString = "";
    return answer;
}
