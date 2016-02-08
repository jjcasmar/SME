#ifndef MESH_H
#define MESH_H

#include <core/AssetLibrary.h>
#include <Eigen/Core>
#include <vector>


namespace SME
{
  namespace asset
  {
    typedef Eigen::Vector3f Point;
    typedef Eigen::Vector3f Normal;
    typedef Eigen::Vector2f uv;

    typedef std::vector<Point> Points;
    typedef std::vector<Normal> Normals;
    typedef std::vector<uv> UVS;

    class Mesh : public SME::core::IAsset
    {
      public:
        Mesh(const std::string &type);
        virtual ~Mesh();

      protected:
        SME::core::Data<Points>  _points;
        SME::core::Data<Normals> _normals;
        SME::core::Data<UVS>     _uvs;
        SME::core::Data<std::vector<unsigned int> > _triangles;

        // IAsset interface
    public:
        void configure(tinyxml2::XMLElement *element);
    };
  }
}


#endif // MESH_H
