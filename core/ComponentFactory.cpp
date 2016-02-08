#include "ComponentFactory.h"

#include <core/World.h>

SME::core::ComponentFactory *SME::core::ComponentFactory::_instance = nullptr;

SME::core::ComponentFactory::ComponentFactory()
{

}

SME::core::ComponentFactory::~ComponentFactory()
{

}

bool SME::core::ComponentFactory::registerType(const std::string &type, ComponentCreatorFunctor creator, std::string &report)
{
    if (_creators.find(type) != _creators.end())
    {
        report = "There is already a component with name " + type;
        return false;
    }
  _creators[type] = creator;
  return true;
}

void SME::core::ComponentFactory::deleteType(const std::string &type, std::string &report)
{
    auto it = _creators.find(type);
    if (it != _creators.end())
        _creators.erase(it);
    else
        report = "Component type " + type + " does not exist";
}

SME::core::Component *SME::core::ComponentFactory::create(std::string type) const
{
  auto it = _creators.find(type);
  if (it != _creators.end())
    return it->second();
  return nullptr;
}

std::list<std::string> SME::core::ComponentFactory::types() const
{
  std::list<std::string> components;
  for (auto it = _creators.begin(); it != _creators.end(); ++it)
    {
      components.push_back(it->first);
    }
  return components;
}

SME::core::ComponentFactory *SME::core::ComponentFactory::get()
{

  if (_instance == nullptr)
    _instance = new SME::core::ComponentFactory;
  return _instance;

}
