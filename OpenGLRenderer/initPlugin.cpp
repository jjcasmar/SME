
#include <GL/glew.h>

#include <core/ComponentFactory.h>
#include <core/SystemFactory.h>
#include <core/AssetFactory.h>
#include <core/PluginManager.h>

#include <OpenGLRenderer/OpenGLRendererSystem.h>
#include <OpenGLRenderer/MeshRenderer.h>
#include <OpenGLRenderer/Camera.h>
#include <OpenGLRenderer/Shader.h>

using namespace SME::ogl;

//Register the different components this Plugin implements
REGISTER_COMPONENT(MeshRenderer)
REGISTER_COMPONENT(Camera)

//Register the different systems this Plugin implements
REGISTER_SYSTEM(OpenGLRendererSystem)

//Register the assets
REGISTER_ASSET(Shader)

extern "C" bool initPlugin(const SME::core::PM_PluginManagerInfo &pmInfo, SME::core::PM_PluginInfo &pluginInfo);

bool initPlugin(const SME::core::PM_PluginManagerInfo &pmInfo, SME::core::PM_PluginInfo &pluginInfo)
{
    //TODO check initialization
    std::string report;
  SME::core::ComponentFactory::get()->registerType("MeshRenderer", &create_MeshRenderer, report);
  SME::core::ComponentFactory::get()->registerType("Camera", &create_Camera, report);

  //Sistemas
  SME::core::SystemFactory::get()->registerType("OpenGLRendererSystem", &create_OpenGLRendererSystem, report);

  //Assets
  SME::core::AssetFactory::get()->registerType("Shader", &create_Shader, report);

  pluginInfo.name = "OpenGLRenderer";


  return true;
}


