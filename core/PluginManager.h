#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <string>
#include <list>

namespace SME
{
  namespace core
  {

    class Plugin;

    typedef struct {
      std::string name; 
      std::list<std::string> components;
      std::list<std::string> systems;
      std::list<std::string> assets;
      Plugin *plugin;

      std::string report; //To report errors if the plugin can not be initialized
    } PM_PluginInfo;


    typedef struct {
      unsigned int major;
      unsigned int minor;
      unsigned int revision;

      std::list<PM_PluginInfo> activePlugins;
    } PM_PluginManagerInfo;

    typedef bool (*initPluginFunctor)(const PM_PluginManagerInfo&, PM_PluginInfo&);

    class PluginManager
    {
      public:
        static PluginManager *get();
        void loadAll();
        bool loadPlugin(const std::string path);
        void shutdown();

      private:
        PluginManager();

        PM_PluginManagerInfo _info;
        static PluginManager *_instance;
    };
  }
}



#endif // PLUGINMANAGER_H
