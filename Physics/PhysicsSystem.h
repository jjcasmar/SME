#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include <core/World.h>

namespace SME
{
namespace physics
{

class PhysicsSystem : public SME::core::System
{
public:
    PhysicsSystem(SME::core::World *world, const std::string &type);
    virtual ~PhysicsSystem();

    // System interface
public:
    void Update();
    void Start();
    void postStart();
};

}
}


#endif // PHYSICSSYSTEM_H
