#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H

#include <string>
#include <map>
#include <list>

namespace SME
{
  namespace core
  {
    class Component;

    typedef Component *(*ComponentCreatorFunctor)();
    class ComponentFactory
    {
    public:
      static ComponentFactory *get();
      virtual ~ComponentFactory();

      bool registerType(const std::string &type, ComponentCreatorFunctor creator, std::string &report);
      void deleteType(const std::string &type, std::string &report);
      Component *create(std::string type) const;
      std::list<std::string> types() const;


    private:
      ComponentFactory();

      static ComponentFactory *_instance;
      std::map<std::string, ComponentCreatorFunctor> _creators;
    };

  }
}

#define REGISTER_COMPONENT( _name ) \
  SME::core::Component *create_ ## _name() {  \
    return new _name( #_name ); \
    }

#endif // COMPONENTFACTORY_H
