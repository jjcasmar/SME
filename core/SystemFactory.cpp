#include "SystemFactory.h"
#include <core/World.h>
#include <iostream>

SME::core::SystemFactory *SME::core::SystemFactory::_instance = nullptr;

SME::core::SystemFactory::SystemFactory()
{

}

SME::core::SystemFactory::~SystemFactory()
{

}

bool SME::core::SystemFactory::registerType(const std::string &type, SystemCreatorFunctor creator, std::string &report)
{
    if (_creators.find(type) != _creators.end())
    {
        report = "There is already a component with this name";
        return false;
    }
  _creators[type] = creator;
  return true;
}

void SME::core::SystemFactory::deleteType(const std::string &type, std::string &report)
{
    auto it = _creators.find(type);
    if (it != _creators.end())
        _creators.erase(it);
    else
        report = "System type " + type + " does not exist";
}

SME::core::System *SME::core::SystemFactory::create(std::string type) const
{
  auto it = _creators.find(type);
  if (it != _creators.end())
    return it->second();
  std::cerr << "System: " << type << " is not registered" << std::endl;
  return nullptr;
}

std::list<std::string> SME::core::SystemFactory::types() const
{
  std::list<std::string> systems;
  for (auto it = _creators.begin(); it != _creators.end(); ++it)
    systems.push_back(it->first);
 return systems; 
}

SME::core::SystemFactory *SME::core::SystemFactory::get()
{
  if (_instance == nullptr)
    _instance = new SME::core::SystemFactory;
  return _instance;
}
