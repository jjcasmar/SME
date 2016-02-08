#ifndef SYSTEMFACTORY_H
#define SYSTEMFACTORY_H

#include <string>
#include <map>
#include <list>

namespace SME
{
  namespace core
  {
    class System;

    typedef System *(*SystemCreatorFunctor)();
    class SystemFactory
    {
      public:
        static SystemFactory *get();
        virtual ~SystemFactory();

        bool registerType(const std::string &type, SystemCreatorFunctor creator, std::string &report);
        void deleteType(const std::string &type, std::string &report);
        System *create(std::string type) const;
        std::list<std::string> types() const;

      private:
        SystemFactory();
        
        static SystemFactory *_instance;
        std::map<std::string, SystemCreatorFunctor> _creators;
    };
  }
}

#define REGISTER_SYSTEM( _name ) \
  SME::core::System *create_ ## _name(){return new _name(SME::core::World::get(), #_name);}

#endif //SYSTEMFACTORY_H
