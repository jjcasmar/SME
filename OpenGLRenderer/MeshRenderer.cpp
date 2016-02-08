#include "MeshRenderer.h"

#include <tinyxml2.h>
#include <core/World.h>

#include <core/corePlugin/assets/Mesh.h>

#define VERTEX_LOC 0
#define NORMALS_LOC 1
#define UV_LOC 2


using namespace SME::ogl;

MeshRenderer::MeshRenderer(const std::string &type) : SME::core::Component(type)
{
    _mesh = nullptr;
}

MeshRenderer::~MeshRenderer(){}

SME::core::IAsset *MeshRenderer::mesh() const
{
    return _mesh;
}

SME::core::IAsset *MeshRenderer::shader() const
{
    return _shader;
}

void MeshRenderer::configure(tinyxml2::XMLElement *element)
{
    const char *mesh = element->Attribute("mesh");

    _mesh = SME::core::World::get()->getAssetLibrary()->getAsset(mesh);
    if (_mesh == nullptr)
    {
        std::cerr << "No mesh with name " << mesh << std::endl;
        return;
    }

    //Check if the mesh is already loaded in GPU
    SME::core::Data<GPUMesh*> *gpumesh_data = dynamic_cast<SME::core::Data<GPUMesh*> *>(_mesh->data("GPUMesh"));
    if (gpumesh_data == nullptr)
    {
        //TODO generate buffers for OpenGL
        GPUMesh *gpumesh = new GPUMesh;
        gpumesh->indexBuffer = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);

        gpumesh->vertexBuffer.create();
        gpumesh->normalBuffer.setUsagePattern(QOpenGLBuffer::StreamDraw);

        gpumesh->normalBuffer.create();
        gpumesh->normalBuffer.setUsagePattern(QOpenGLBuffer::StreamDraw);

        gpumesh->uvBuffer.create();
        gpumesh->uvBuffer.setUsagePattern(QOpenGLBuffer::StreamDraw);

        gpumesh->indexBuffer.create();
        gpumesh->indexBuffer.setUsagePattern(QOpenGLBuffer::StreamDraw);

        gpumesh->vertexBuffer.bind();
        std::vector<SME::asset::Point> points = dynamic_cast<SME::core::Data<SME::asset::Points> *>(_mesh->data("points"))->value();
        gpumesh->vertexBuffer.allocate(points.data(), points.size()*sizeof(points[0]));

        gpumesh->normalBuffer.bind();
        SME::asset::Normals normals = dynamic_cast<SME::core::Data<SME::asset::Normals> *>(_mesh->data("normals"))->value();
        gpumesh->normalBuffer.allocate(normals.data(), normals.size()*sizeof(normals[0]));

        gpumesh->uvBuffer.bind();
        SME::asset::UVS uvs = dynamic_cast<SME::core::Data<SME::asset::UVS> *>(_mesh->data("uvs"))->value();
        gpumesh->uvBuffer.allocate(uvs.data(), uvs.size()*sizeof(uvs[0]));

        gpumesh->indexBuffer.bind();
        std::vector<unsigned int> index = dynamic_cast<SME::core::Data<std::vector<unsigned int> > *>(_mesh->data("triangles"))->value();
        gpumesh->indexBuffer.allocate(index.data(), index.size()*sizeof(index[0]));

        //VAOs
        gpumesh->vao.create();
        gpumesh->vao.bind();

        glBindBuffer(GL_ARRAY_BUFFER, gpumesh->vertexBuffer.bufferId());
        glVertexAttribPointer(VERTEX_LOC ,3, GL_FLOAT,GL_FALSE, 0, 0);
        glEnableVertexAttribArray(VERTEX_LOC);

        glBindBuffer(GL_ARRAY_BUFFER, gpumesh->normalBuffer.bufferId());
        glVertexAttribPointer(NORMALS_LOC, 3, GL_FLOAT,GL_FALSE, 0, 0);
        glEnableVertexAttribArray(NORMALS_LOC);

        glBindBuffer(GL_ARRAY_BUFFER, gpumesh->uvBuffer.bufferId());
        glVertexAttribPointer(UV_LOC,2, GL_FLOAT,GL_FALSE, 0, 0);
        glEnableVertexAttribArray(UV_LOC);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gpumesh->indexBuffer.bufferId());

        gpumesh->vao.release();
        gpumesh_data = dynamic_cast<SME::core::Data<GPUMesh*> *>(_mesh->addData<GPUMesh*>("GPUMesh"));
        gpumesh_data->setValue(gpumesh);
    }

    //Shader program
    const char *shader = element->Attribute("shader");
    _shader = SME::core::World::get()->getAssetLibrary()->getAsset(shader);
    if (_shader == nullptr)
    {
        std::cerr << "No shader with name " << shader << std::endl;
        return;
    }
}
