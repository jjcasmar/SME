#include "World.h"
#include <core/PluginManager.h>
#include <iostream>


using namespace SME::core;

/*
std::vector<EntityId> World::_entities = std::vector<EntityId>();
std::map<EntityId,ComponentMask> World::_entityComponentMap = std::map<EntityId, ComponentMask>();
std::map<EntityId, ComponentList> World::_entityComponentList = std::map<EntityId,ComponentList>();
ComponentNameMap World::_componentNameMap = ComponentNameMap();
unsigned int World::_componentSize = 0;
*/

std::string Component::_type = "NULL";
World * World::_instance = nullptr;

World *World::get()
{
  if (_instance == nullptr)
    _instance = new World();
  return _instance;
}

World::World()
{

}

World::~World()
{

}

void World::initWorld()
{
  //This must be done in a call to the factory discovery
  std::list<std::string> components = ComponentFactory::get()->types();
  auto it = components.begin();
  auto i = 0;
  for ( ; it != components.end(); ++it, ++i)
    _componentNameMap[(*it)] = i;
  this->_componentSize = this->_componentNameMap.size();

  //Create the initial node
  _entities.push_back(0);
  _entitiesNames[0] = "Root";

  //No components for this object
  _entityComponentMap[0] = ComponentMask(_componentSize, false);
}

void World::updateWorldComponents()
{
    std::list<std::string> components = ComponentFactory::get()->types();
    auto it = components.begin();
    auto i = 0;
    for ( ; it != components.end(); ++it, ++i)
      _componentNameMap[(*it)] = i;
    this->_componentSize = this->_componentNameMap.size();
}

const std::vector<EntityId> World::entities()
{
    return _entities;
}

bool World::componentId(const std::string &component, ComponentId &_componentId)
{
  auto it = this->_componentNameMap.find(component);
  if (it != this->_componentNameMap.end())
    {
      _componentId = it->second;
      return true;
    }

  //If there is no component with this name, return an error
  std::cerr << "Component " << component << " is not registered." << std::endl;
  return false;
}

EntityId World::getEntityByName(const std::string &name)
{
  if (_entities.size() != _entitiesNames.size())
  {
    std::cerr << "Entities size does not match with entities names size... WTF!?" << std::endl;
    return -1;
  }

  for (auto it = _entitiesNames.begin(); it != _entitiesNames.end(); ++it)
  {
      if (it->second == name)
        return it->first;
  }
  std::cerr << "No entity found with that name" << std::endl;
  return -1;
}


EntityId World::createNewEntity()
{
  const EntityId lastEntityId = World::_entities.back();
  _entities.push_back(lastEntityId+1);

  _entityComponentMap[lastEntityId+1] = std::vector<bool>(_componentSize, false);
  _entitiesNames[lastEntityId+1] = "Default name";

  return lastEntityId+1;
}

std::string World::name(EntityId id)
{
    return _entitiesNames[id];
}

void World::name(std::string name, EntityId id)
{
    auto it = _entitiesNames.find(id);
    if (it == _entitiesNames.end())
    {
        std::cerr << "There is no entity with identifier number " << id << std::endl;
        return;
    }

    _entitiesNames[id] = name;
}

void World::addComponent(std::string componentType, EntityId e)
{
  auto it = _entityComponentMap.find(e);
  if (it != this->_entityComponentMap.end())
    {
      unsigned int componentIdx;
      if (this->componentId(componentType, componentIdx))
        {
          it->second[componentIdx] = true;
          this->_entityComponentList[e][componentIdx] = ComponentFactory::get()->create(componentType);
        }
    }
  else
    std::cerr << "There is no entity with identifier number " << e << std::endl;
}

Component *World::getComponent(const std::string &componentType, const EntityId &e)
{
  if (hasComponent(componentType, e))
    {
      ComponentId componentId;
      this->componentId(componentType, componentId);
      return _entityComponentList[e][componentId];
    }
  return nullptr; 
}

void World::removeEntity(const EntityId &e)
{
  auto it = _entityComponentList.find(e);
  if (it != _entityComponentList.end())
    {
      for (auto mapIt = it->second.begin(); mapIt != it->second.end(); ++mapIt)
        delete mapIt->second;
      it->second.clear();
      _entityComponentList.erase(it);
    }

  auto it2 = _entityComponentMap.find(e);
  if (it2 != _entityComponentMap.end())
    {
      it2->second.clear();
      _entityComponentMap.erase(it2);
    }

  for (auto it3 = _entities.begin(); it3 != _entities.end(); ++it3)
    {
      if (*it3 == e)
        _entities.erase(it3);
    }
}

void World::removeComponent(const std::string &componentType, const EntityId &e)
{
  if (hasComponent(componentType, e))
    {
      ComponentId componentId;
      if (this->componentId(componentType, componentId))
        {
          //Set to false
          _entityComponentMap[e][componentId] = false;

          //Remove the component
          auto it = _entityComponentList[e].find(componentId);
          delete it->second;
          _entityComponentList[e].erase(it);
        }
    }
}

bool World::hasComponent(const std::string componentType, const EntityId &e)
{
  ComponentId componentId;
  if (this->componentId(componentType, componentId))
    {
      return this->_entityComponentMap[e][componentId];
    }
  return false;
}

bool World::installSystem(System *system)
{
    auto it = _systems.find(system->type());
    if (it != _systems.end())
    {
        std::cerr << "There is already one system of type " << system->type() << std::endl;
        return false;
    }
    _systems[system->type()] = system;
    system->Start();
    return true;
}

System *World::getSystemByName(const std::string &system) const
{
    auto it = _systems.find(system);
    if (it != _systems.end())
        return it->second;
    return nullptr;
}

void World::systemsPostStart()
{
  for (auto it = _systems.begin() ; it != _systems.end(); ++it)
    it->second->postStart();
}

void World::cleanUp()
{
    //TODO coño, Limpiar!!!!
  //for (auto i = 0; i < _entities.size(); ++i)
  //  removeEntity()
}

AssetLibrary *World::getAssetLibrary()
{
    return &_assetLibrary;
}

void World::loop()
{
    for (auto it = _systems.begin(); it != _systems.end(); ++it)
        it->second->Update();
}

System::System(World *world, const std::string &type)
{
  _world = world;
  _type = type;
}

System::~System()
{
  //TODO Remove system from the world list
}

std::vector<EntityId> System::entities()
{
  std::vector<ComponentId> componentsId;
  for (int i = 0; i < _componentList.size(); ++i)
    {
      ComponentId componentId;
      if (_world->componentId(_componentList[i], componentId))
        componentsId.push_back(componentId);
    }

  std::vector<EntityId> result;
  for (EntityId i = 0; i < _world->entities().size(); ++i)
    {
      EntityId e = _world->entities()[i];
      bool hasComponents = true;
      for (unsigned int j = 0; j < componentsId.size() && hasComponents==true; ++j)
        hasComponents = hasComponents && _world->hasComponent(_componentList[j], e);
      if (hasComponents)
        result.push_back(e);
    }

  return result;
}

void System::postStart()
{

}

Component::~Component()
{
}

Component::Component(const std::string &type)
{
    _type = type;
}

const std::string &Component::type() const
{
    return _type;
}
