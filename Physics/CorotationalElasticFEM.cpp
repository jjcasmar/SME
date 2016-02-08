#include "CorotationalElasticFEM.h"

using namespace SME::physics;

CorotationalElasticFEM::CorotationalElasticFEM(std::string type) :
    SME::core::Component(type)
{

}

CorotationalElasticFEM::~CorotationalElasticFEM()
{

}

void CorotationalElasticFEM::configure(tinyxml2::XMLElement *element)
{

}

std::vector<float> CorotationalElasticFEM::youngModulus() const
{
    return _youngModulus;
}

std::vector<float> CorotationalElasticFEM::poissonRatio() const
{
    return _poissonRatio;
}
