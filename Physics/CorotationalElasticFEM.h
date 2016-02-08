#ifndef COROTATIONALELASTICFEM_H
#define COROTATIONALELASTICFEM_H

#include <core/World.h>
#include <Eigen/Sparse>

namespace SME
{
namespace physics
{

class CorotationalElasticFEM : public SME::core::Component
{

public:
    CorotationalElasticFEM(std::string type);
    virtual ~CorotationalElasticFEM();
    virtual void configure(tinyxml2::XMLElement *element);

    std::vector<float> youngModulus() const;
    std::vector<float> poissonRatio() const;

private:
    std::vector<float> _youngModulus;
    std::vector<float> _poissonRatio;

    std::vector<Eigen::Vector3f> _positions;
    std::vector<Eigen::Vector3f> _velocities;
};

}
}

#endif // COROTATIONALELASTICFEM_H
