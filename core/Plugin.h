#ifndef PLUGIN_H
#define PLUGIN_H

#include <dlfcn.h>
#include <string>

namespace SME
{
  namespace core
  {

    typedef void (*closePluginFunctor)();

    class Plugin
    {
    public:
      static Plugin *load(const std::string &path,
                          std::string &error);
      ~Plugin();
      void *getSymbol(const std::string &symbol, std::string &error);

    private:
      Plugin();
      Plugin(void *handle);

      void *_handle;
    };
  }
}



#endif // PLUGIN_H
