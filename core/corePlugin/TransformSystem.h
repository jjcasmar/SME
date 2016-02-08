#ifndef TRANSFORM_SYSTEM_H
#define TRANSFORM_SYSTEM_H

#include <core/World.h>
#include <Eigen/Geometry>
#include "Transform.h"

namespace SME
{
  namespace system
  {
    class TransformSystem : public SME::core::System
    {
      public:
        TransformSystem(SME::core::World *world, const std::string &type);
        virtual ~TransformSystem();
        virtual void Update();
        virtual void Start();

      private:
        Eigen::Affine3f local(SME::components::Transform *t);
        Eigen::Affine3f world(SME::components::Transform *t);
      
    };
  }
}

#endif //TRANFORM_SYSTEM_H
