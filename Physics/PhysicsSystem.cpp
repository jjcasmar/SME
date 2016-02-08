#include "PhysicsSystem.h"

using namespace SME::physics;

PhysicsSystem::PhysicsSystem(SME::core::World *world, const std::string &type) :
    SME::core::System(world, type)
{

}

PhysicsSystem::~PhysicsSystem()
{

}

void PhysicsSystem::Update()
{
    std::cout << "Physics" << std::endl;

    //Generate the system
    _componentList.push_back("CorotationalElasticFEM");
}

void PhysicsSystem::Start()
{

}

void PhysicsSystem::postStart()
{

}
