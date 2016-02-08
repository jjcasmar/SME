#include "Transform.h"

#include <iostream>
#include <tinyxml2.h>
#include "core/helpers/functions.cpp"

#include <core/World.h>

using namespace SME::components;

Transform::Transform(const std::string &type) : SME::core::Component(type)
{
  initData(&_position, "position", "");
  initData(&_rotation, "rotation", "");
  initData(&_scale   , "scale"   , "");
  initData(&_world   , "world"   , "");
  initData(&_local   , "local"   , "");
  _position.setValue(Eigen::Vector3f(0,5,0));
  _rotation.setValue(Eigen::Quaternionf(1,0,0,0));
  _scale.setValue(Eigen::Vector3f(1,1,1));
  _parent = nullptr;
  _needUpdate = true;
}

void Transform::configure(tinyxml2::XMLElement *element)
{
  const char * matrix   = element->Attribute("matrix");
  if (matrix != nullptr)
  {
    std::vector<std::string> matrix_elements_str;
    split_str(matrix_elements_str, matrix, ' ');

    if (matrix_elements_str.size() != 16)
      std::cerr << "Matrix attribute must have 12 numeric elements" << std::endl;
    else
    { 
      std::vector<float> m;
      m.resize(16);
      for (auto i = 0; i < 16; i++)
        m[i] = std::stof(matrix_elements_str[i]);

      Eigen::Affine3f matrix;
      matrix.matrix() <<m[0], m[1], m[2], m[3],
              m[4], m[5], m[6], m[7],
              m[8], m[9], m[10],m[11],
              m[12],m[13],m[14],m[15];

      _local.setValue(matrix);
      _position.setValue(_local.value().translation());
      _rotation.setValue(Eigen::Quaternionf(_local.value().rotation()));
      _needUpdate = true;
    }
  } 
  else
  {
    const char * position = element->Attribute("position");
    const char * rotation = element->Attribute("rotation"); 
    const char * scale    = element->Attribute("scale"   );
    if (position || rotation || scale)
      std::cerr << "Position, rotation and scale attributes are not yet supported. use matrix instead" << std::endl;
  }

  const char *parent = element->Attribute("parent");
  if (parent)
  {
    SME::core::EntityId eid = SME::core::World::get()->getEntityByName(parent);
    if (eid == -1)
      std::cerr << "Parent for this transform is not valid" << std::endl;
    else
    {
      Transform *t = dynamic_cast<Transform*>(
          SME::core::World::get()->getComponent("Transform", eid)
          );

      if (t == nullptr)
        std::cerr << "Parent entity does not have a transform component" << std::endl;
      else
        this->setParent(t);
    }
  }
}

Transform::~Transform()
{
}

Transform *Transform::addChild()
{
  Transform *child = new Transform(_type);
  child->_parent = this;
  _children.push_back(child);

  return child;
}

void Transform::addChild(Transform *child)
{
  this->_children.push_back(child);
}

void Transform::setParent(Transform *parent)
{
  if (parent == _parent)
    return;
  this->_parent = parent;
  parent->addChild(this);
  _needUpdate = true;
}

const Eigen::Affine3f Transform::local()
{
  return _local.value();
}

const Eigen::Affine3f Transform::world()
{
  return _world.value();
}

