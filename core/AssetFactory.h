#ifndef ASSETFACTORY_H
#define ASSETFACTORY_H

#include <string>
#include <map>
#include <list>

namespace SME
{
  namespace core
  {
    class IAsset;
    typedef IAsset *(*AssetCreatorFunctor)();

    class AssetFactory
    {
      public:
        static AssetFactory *get();
        virtual ~AssetFactory();
        
        bool registerType(const std::string &type, AssetCreatorFunctor creator, std::string &report);
        IAsset *create(std::string type) const;
        std::list<std::string> types() const;

      private:
        AssetFactory();

        static AssetFactory *_instance;
        std::map<std::string, AssetCreatorFunctor> _creators;
    };
  }
}

#define REGISTER_ASSET( _name ) \
  SME::core::IAsset *create_ ## _name(){return new _name( #_name  ); }

#endif //ASSETFACTORY_H
