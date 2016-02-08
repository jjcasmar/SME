#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <core/World.h>
#include <Eigen/Geometry>
#include <vector>

#include <core/Data.h>

namespace SME
{
  namespace components
  {
    class Transform : public SME::core::Component
    {
    public:
      Transform(const std::string &type);
      virtual ~Transform();
      virtual void configure(tinyxml2::XMLElement *element);

      inline const Eigen::Vector3f    position() const {return _position.value();}
      inline const Eigen::Vector3f    scale()    const {return _scale.value();}
      inline const Eigen::Quaternionf rotation() const {return _rotation.value();}

      inline void setPosition(const Eigen::Vector3f &position) {_position.setValue(position); _needUpdate = true;}
      inline void setScale   (const Eigen::Vector3f &scale   ) {_scale.setValue(scale);       _needUpdate = true;}
      inline void setRotation(const Eigen::Quaternionf &rot  ) {_rotation.setValue(rot);      _needUpdate = true;}

      Transform *addChild();
      void addChild(Transform *child);
      void setParent(Transform *child);
      inline Transform *parent() const {return _parent;}

      inline const bool &needUpdate() const {return _needUpdate;}

      inline void setLocal(const Eigen::Affine3f &local){_local.setValue(local); _needUpdate = true ;}
      inline void setWorld(const Eigen::Affine3f &world){_world.setValue(world); _needUpdate = false;}

      const Eigen::Affine3f local();
      const Eigen::Affine3f world();

    private:
      SME::core::Data<Eigen::Vector3f>    _position;
      SME::core::Data<Eigen::Quaternionf> _rotation;
      SME::core::Data<Eigen::Vector3f>    _scale;

      SME::core::Data<Eigen::Affine3f> _local;
      SME::core::Data<Eigen::Affine3f> _world;

      bool _needUpdate;

      Transform *_parent;
      std::vector<Transform*> _children;
    };
  }
}

#endif //TRANSFORM_H
