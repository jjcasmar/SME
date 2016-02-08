#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <map>
#include <string>
#include <iostream>

#include <core/AssetLibrary.h>
#include <core/ComponentFactory.h>
#include <core/SystemFactory.h>
#include <core/Data.h>



//TODO Esto habria que quitarlo cuando pongamos el configurado de componentes en condiciones
namespace tinyxml2
{
  class XMLElement;
}

namespace SME
{
  namespace core
  {
  typedef unsigned int EntityId;
  typedef unsigned int ComponentId;
  typedef std::vector<bool> ComponentMask;
  typedef std::map<ComponentId, Component*> ComponentList;
  typedef std::map<std::string, ComponentId> ComponentNameMap;


    class Component
    {
    public:
      Component(const std::string &type);
      virtual ~Component() = 0;
      virtual void configure(tinyxml2::XMLElement *element) = 0;
      const std::string &type() const;
      inline void initData(BaseData *data, const std::string variableName, const std::string variableDescriptor = "")
      {
          auto it = _data.find(variableName);
          if (it != _data.end())
          {
              std::cerr << "Variable already exist" << std::endl;
              return;
          }
          data->setName(variableName);
          data->setDescription(variableDescriptor);
          _data[variableName] = data;
      }

      inline BaseData *data(const std::string &variable) const
      {
          auto it = _data.find(variable);
          if (it != _data.end())
              return it->second;

         std::cerr << "Variable " << variable << " is not registered as visible from outside the plugin. Access forbidden" << std::endl;
         return nullptr;
      }

    protected:
      static std::string _type;
      std::map<std::string, BaseData*> _data;
    };

    class World;
    class System {
    public:
      System(World *world, const std::string &type);
      inline const std::string &type() const {return _type;}
      virtual ~System();

    protected:
      std::string _type;
      World *_world;
      std::vector<std::string> _componentList;

      //Method to retrieve the entities that the system is interested in
      std::vector<EntityId> entities();
    public:
      //Perform actions over the components
      virtual void Update() = 0;
      virtual void Start()  = 0;
      virtual void postStart();
    };



    class World
    {

      private:
      World(); 
      static World *_instance;

      public:
      ~World();
      static World *get();

      //Initiates the world
      //TODO Check if this is really necessary
      void initWorld();
      void updateWorldComponents();

      //Update function
      void loop();

      //Get entities
      inline const std::vector<EntityId> entities();

      //Gives back the component index used by the component
      bool componentId(const std::string &component, ComponentId &_componentId);

      //Creates a new entity in the World and returns the EntityId
      EntityId createNewEntity();

      //Get and set entity name
      std::string name(EntityId id);
      void name(std::string name, EntityId id);
      EntityId getEntityByName(const std::string &name);

      //Adds a component "ComponentType" to the entity "e"
      void addComponent(std::string componentType, EntityId e);

      Component *getComponent(const std::string &componentType, const EntityId &e);
      //static Component *getComponent(const ComponentId &componentIdx,  const EntityId &e) const;

      //Remove functions
      void removeEntity(const EntityId &e);
      void removeComponent(const std::string &componentType, const EntityId &e);

      bool hasComponent(const std::string componentType, const EntityId &e);

      //Install system in this world
      bool installSystem(System *system);
      System *getSystemByName(const std::string &system) const;
      void systemsPostStart();

      //Clean up functions
      void cleanUp();

      AssetLibrary *getAssetLibrary();

    private:
      //Vector to hold entities id
      std::vector<EntityId> _entities;
      std::map<EntityId, std::string> _entitiesNames;

      //Number of components discovered in the engine
      unsigned int _componentSize;

      //For each entity, I have a vector of bool as long as the component list.
      //Each bool specifies if the entity has that kind of component
      std::map<EntityId, ComponentMask> _entityComponentMap;

      //For each entity, I have a list of components
      std::map<EntityId, ComponentList> _entityComponentList;

      //This map translates the component human-readable name to the integer that
      //represents it in the engine
      ComponentNameMap _componentNameMap;

      //To check if an entity has a certain kind of component and retrieve it
      //unsigned int transformComponentIndex = _componentNameMap['Transform'];
      //for (EntityId e = 0; i < _entities.size(); ++i){
      //	//Check if it has the component
      //	if (_entityComponentMap[e][transformComponentIndex]){
      //		//Retrieve the component
      //		Component &transform = _entityComponentList[e][transformComponentIndex];
      
      AssetLibrary _assetLibrary;

      std::map<std::string, System*> _systems;
    };
  }
}

#endif //WORLD_H
