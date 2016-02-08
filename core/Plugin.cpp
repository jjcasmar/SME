#include "Plugin.h"

#include <iostream>



SME::core::Plugin *SME::core::Plugin::load(const std::string &path, std::string &error)
{
  void *handle = dlopen(path.c_str(), RTLD_LAZY);
  if (handle == nullptr)
    {
      error = std::string(dlerror());
      return nullptr;
    }
  Plugin *plugin = new Plugin(handle);
  dlerror();
  return plugin;
}

SME::core::Plugin::~Plugin()
{
    //Clean plugin
    std::string error;
    closePluginFunctor functor = (closePluginFunctor)getSymbol("closePlugin", error);
    if (functor == nullptr)
    {
        std::cerr << error << std::endl;
        std::cerr << "Every plugin must have a close function \"void closePlugin()\"" << std::endl;
    }
    else
    {
        functor();
    }

  dlclose(_handle);
  _handle = nullptr;
}

void *SME::core::Plugin::getSymbol(const std::string &symbol, std::string &error)
{
  void *functor = dlsym(_handle, symbol.c_str());
  if (functor == nullptr)
    error = dlerror();
  dlerror();
  return functor;
}

SME::core::Plugin::Plugin()
{
  _handle = nullptr;
}

SME::core::Plugin::Plugin(void *handle)
{
  _handle = handle;
}
