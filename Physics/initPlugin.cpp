#include <core/ComponentFactory.h>
#include <core/SystemFactory.h>
#include <core/PluginManager.h>

#include "CorotationalElasticFEM.h"
#include "PhysicsSystem.h"

using namespace SME::physics;

//Components registration
REGISTER_COMPONENT(CorotationalElasticFEM)

//Systems registration
REGISTER_SYSTEM(PhysicsSystem)

extern "C" bool initPlugin(const SME::core::PM_PluginManagerInfo &pmInfo, SME::core::PM_PluginInfo &pluginInfo);

bool initPlugin(const SME::core::PM_PluginManagerInfo &pmInfo, SME::core::PM_PluginInfo &pluginInfo)
{
    //TODO check initialization
    std::string report;
  SME::core::ComponentFactory::get()->registerType("CorotationalElasticFEM", &create_CorotationalElasticFEM, report);

  //Sistemas
  SME::core::SystemFactory::get()->registerType("PhysicsSystem", &create_PhysicsSystem, report);

  pluginInfo.name = "SMEPhysics";


    return true;
}


