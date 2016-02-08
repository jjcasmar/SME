#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include <core/World.h>

#include <GL/glew.h>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

namespace SME
{
namespace ogl
{

//Instead of extending Mesh asset to support gpu data,
//I add some data to the asset through the Data class
typedef struct
{

    QOpenGLBuffer vertexBuffer;
    QOpenGLBuffer normalBuffer;
    QOpenGLBuffer uvBuffer;
    QOpenGLBuffer indexBuffer;
    QOpenGLVertexArrayObject vao;
} GPUMesh;

class MeshRenderer : public SME::core::Component
{
public:
    MeshRenderer(const std::string &type);
    virtual ~MeshRenderer();

    SME::core::IAsset *mesh() const;
    SME::core::IAsset *shader() const;

private:
    SME::core::IAsset *_mesh;
    SME::core::IAsset *_shader;


    // Component interface
public:
    void configure(tinyxml2::XMLElement *element);

};
}
}

#endif // MESHRENDERER_H
