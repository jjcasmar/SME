#include "TransformSystem.h"
#include <iostream>

#include "Transform.h"

#include <core/World.h>

using namespace SME::system;

TransformSystem::TransformSystem(SME::core::World *world, const std::string &type) : SME::core::System(world, type)
{
  this->_componentList.push_back("Transform");
  //this->_componentList.push_back("Collider");
}

TransformSystem::~TransformSystem()
{

}

void TransformSystem::Update()
{
  std::vector<SME::core::EntityId> es = entities();

  for (auto it = es.begin(); it != es.end(); ++it)
  {
    SME::components::Transform *t =
      dynamic_cast<SME::components::Transform*>
      (SME::core::World::get()->getComponent("Transform", *it));
    world(t);
  }
}

void TransformSystem::Start()
{

}

Eigen::Affine3f TransformSystem::local(SME::components::Transform *t)
{
  //Position rotation and scale not yet supported, so return directly the local matrix
  //Even more, just compute the local when position rotation and scale is changed
  return t->local();
}

Eigen::Affine3f TransformSystem::world(SME::components::Transform *t)
{
  if (!t->needUpdate())
    return t->world();

  Eigen::Affine3f _world;
  if (t->parent() != nullptr)
  {
    _world = world(t->parent()) * local(t);
    t->setWorld(_world);
    return _world;
  }
  _world = local(t);
  t->setWorld(_world);
  return _world;

}
