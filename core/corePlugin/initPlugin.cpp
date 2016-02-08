#include <core/ComponentFactory.h>
#include <core/SystemFactory.h>
#include <core/AssetFactory.h>

#include <core/PluginManager.h>

#include <core/corePlugin/Transform.h>
#include <core/corePlugin/TransformSystem.h>
#include <core/corePlugin/assets/Mesh.h>
#include <core/corePlugin/assets/TetraMesh.h>

#include <iostream>

using namespace SME::components;
using namespace SME::system;
using namespace SME::asset;

//Register the different components this Plugin implements
REGISTER_COMPONENT(Transform)

//Register the different systems this Plugin implements
REGISTER_SYSTEM(TransformSystem)

  //Register the diferent assets this plugin implements
REGISTER_ASSET(Mesh)
REGISTER_ASSET(TetraMesh)

extern "C" bool initPlugin(const SME::core::PM_PluginManagerInfo &pmInfo, SME::core::PM_PluginInfo &pluginInfo);
extern "C" void closePlugin();

bool initPlugin(const SME::core::PM_PluginManagerInfo &pmInfo, SME::core::PM_PluginInfo &pluginInfo)
{
    //TODO check initialization
    pluginInfo.name = "CorePlugin";
    std::string report;
    if (!SME::core::ComponentFactory::get()->registerType("Transform", &create_Transform, report)){
        pluginInfo.report = report;
        return false;
    }
    pluginInfo.components.push_back("Transform");

    //Sistemas
    if (!SME::core::SystemFactory::get()->registerType("TransformSystem", &create_TransformSystem, report))
    {
        pluginInfo.report = report;
        return false;
    }
    pluginInfo.systems.push_back("TransformSystem");

    //Assets
    if (!SME::core::AssetFactory::get()->registerType("Mesh", &create_Mesh, report))
    {
        pluginInfo.report = report;
        return false;
    }
    pluginInfo.assets.push_back("Mesh");

    pluginInfo.report = "Core plugin succesfully loaded. Core plugin must always be loaded";

    return true;
}

void closePlugin()
{
    //TODO clean plugin registers
    std::cout << "Clean plugin registers" << std::endl;
    std::string report;

    //Clean up components
    SME::core::ComponentFactory::get()->deleteType("Transform", report);

    //Clean up system
    SME::core::SystemFactory::get()->deleteType("TransformSystem", report);

    //Clean up assets
}


