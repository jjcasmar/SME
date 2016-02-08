#include "Mesh.h"

#include <tinyxml2.h>

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

using namespace SME::asset;

SME::asset::Mesh::Mesh(const std::string &type) :
    SME::core::IAsset(type)
{
    _type = "Mesh";
    initData(&_points   , "points"   , "");
    initData(&_normals  , "normals"  , "");
    initData(&_uvs      , "uvs"      , "");
    initData(&_triangles, "triangles", "");
}

SME::asset::Mesh::~Mesh()
{

}

void Mesh::configure(tinyxml2::XMLElement *element)
{
    const char * src   = element->Attribute("src");
    if (src != nullptr)
    {
        std::string file(src);
        auto i = file.find_last_of('.');
        std::string type = file.substr(i, file.size());
        if (type != ".obj")
            return;

        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(file, aiProcessPreset_TargetRealtime_Fast);
        if (scene == nullptr){
            std::cerr << importer.GetErrorString() << std::endl;
            return;
        }
        if (scene->HasMeshes())
        {
            auto numMeshes = scene->mNumMeshes;
            aiMesh *aimesh;
            for (auto i = 0; i < numMeshes; ++i)
            {
                aimesh = scene->mMeshes[i];

                auto numverts = aimesh->mNumVertices;
                std::vector<Point> points;
                std::vector<Normal> normals;
                points.resize(numverts);
                normals.resize(numverts);
                for (auto nv = 0; nv < numverts; ++nv)
                {
                    points[nv] = Point(aimesh->mVertices[nv].x,
                                       aimesh->mVertices[nv].y,
                                       aimesh->mVertices[nv].z);

                    normals[nv] = Normal(aimesh->mNormals[nv].x,
                                         aimesh->mNormals[nv].y,
                                         aimesh->mNormals[nv].z);

                }

                _points.setValue(points);
                _normals.setValue(normals);

                auto numfaces = aimesh->mNumFaces;
                std::vector<unsigned int> faces;
                faces.resize(3*numfaces);
                for (auto nf = 0; nf < numfaces; ++nf)
                {
                    if (aimesh->mFaces[nf].mNumIndices != 3)
                    {
                        std::cerr << "A face of the mesh " << file << " is not a triangle" << std::endl;
                        return;
                    }

                    for (auto j = 0; j < 3; ++j)
                        faces[3*nf + j] = aimesh->mFaces[nf].mIndices[j];
                }
                _triangles.setValue(faces);
            }
        }
    }

    const char *name = element->Attribute("name");
    if (name != nullptr)
    {
        _name = name;
    }
}
