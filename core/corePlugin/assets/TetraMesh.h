#ifndef TETRAMESH_H
#define TETRAMESH_H

#include <core/AssetLibrary.h>
#include <Eigen/Core>
#include <vector>
#include <core/Data.h>

namespace SME
{
namespace asset
{

class TetraMesh : public SME::core::IAsset
{
    typedef Eigen::Vector3f Point;

public:
    TetraMesh(const std::string &type);
    virtual ~TetraMesh();

private:
    SME::core::Data<std::vector<Point>        > _points;
    SME::core::Data<std::vector<unsigned int> > _tetras;

    // IAsset interface
    void configure(tinyxml2::XMLElement *element);
};

}
}


#endif // TETRAMESH_H
