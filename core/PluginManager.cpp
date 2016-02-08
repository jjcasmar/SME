#include "PluginManager.h"
#include <core/Plugin.h>
#include <core/World.h>

#include <iostream>
using namespace SME::core;

extern "C" bool initPlugin(const PM_PluginManagerInfo &pmInfo, PM_PluginInfo &pluginInfo);


SME::core::PluginManager *SME::core::PluginManager::_instance = nullptr;

SME::core::PluginManager::PluginManager()
{

}

SME::core::PluginManager *SME::core::PluginManager::get()
{
  if (_instance == nullptr)
    _instance = new PluginManager();
  return _instance;
}

void PluginManager::loadAll()
{
  loadPlugin("/home/jjcasmar/SME/build/lib/libSMECore.so");
  loadPlugin("/home/jjcasmar/SME/build/lib/libSMEOpenGL.so");
}

bool SME::core::PluginManager::loadPlugin(const std::string path)
{
  std::string error;
  Plugin *plugin = Plugin::load(path, error);
  if (plugin == nullptr)
  {
    std::cout << error << std::endl;
    return false;
  }

  initPluginFunctor functor = (initPluginFunctor)plugin->getSymbol("initPlugin", error);
  if (functor == nullptr)
  {
    std::cout << error << std::endl;
    return false;
  }

  PM_PluginInfo pluginInfo;
  if (functor(_info, pluginInfo)){
    pluginInfo.plugin = plugin;
    _info.activePlugins.push_back(pluginInfo);
  }
  else
  {
    std::cerr << pluginInfo.report << std::endl;
    delete plugin;
    return false;
  }
    World::get()->updateWorldComponents();
  return true;
}
