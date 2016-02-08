#include "OpenGLRendererSystem.h"

#include "SMEOpenGLWidget.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Shader.h"
#include <iostream>
#include <Eigen/Geometry>

using namespace SME::ogl;



OpenGLRendererSystem::OpenGLRendererSystem(SME::core::World *world, const std::string &type) :
  SME::core::System(world, type)
{
  _isInit = false;
}

OpenGLRendererSystem::~OpenGLRendererSystem()
{

}

void OpenGLRendererSystem::Start()
{
  if (!_isInit)
    init();
}

void OpenGLRendererSystem::Update()
{
  glwidget->update();
}

void OpenGLRendererSystem::postStart()
{
  this->_componentList.clear();
  this->_componentList.push_back("Camera");
  std::vector<SME::core::EntityId> es;
  es = entities();
  for(auto it = es.begin(); it != es.end(); ++it)
    {

      //Get camera component
      int w = glwidget->width();
      int h = glwidget->height();
      Camera *camera = dynamic_cast<Camera*>(SME::core::World::get()->getComponent("Camera", *it));
      camera->setAr((float)w/(float)h);
    }
}

void OpenGLRendererSystem::resize(int w, int h)
{
  this->_componentList.clear();
  this->_componentList.push_back("Camera");
  std::vector<SME::core::EntityId> es;
  es = entities();
  for(auto it = es.begin(); it != es.end(); ++it)
    {

      //Get camera component
      Camera *camera = dynamic_cast<Camera*>(SME::core::World::get()->getComponent("Camera", *it));
      camera->setAr((float)w/(float)h);
    }
}

void OpenGLRendererSystem::Render()
{
  //This is the final painting method!

  //First of all, check for cameras
  this->_componentList.clear();
  this->_componentList.push_back("Transform");
  this->_componentList.push_back("Camera");

  std::vector<SME::core::EntityId> es;
  es = entities();
  //View matrix takes the vertex from world space and takes them to camera space
  Eigen::Matrix4f view;

  //Projection matrix takes the vertex from camera space and applies a projection
  Eigen::Matrix4f projection;
  bool active_camera = false;
  for(auto it = es.begin(); it != es.end(); ++it)
    {

      //Get camera component
      Camera *camera = dynamic_cast<Camera*>(SME::core::World::get()->getComponent("Camera", *it));
      if (camera->active())
        {
          active_camera = true;
          SME::core::Component *transformComponent = SME::core::World::get()->getComponent("Transform", *it);
          view = dynamic_cast<SME::core::Data<Eigen::Affine3f> *>(transformComponent->data("world"))->value().matrix().inverse();
          projection = camera->projection();
        }
    }
  if (!active_camera)
    return;

  //Get rendereable objects
  this->_componentList.clear();
  this->_componentList.push_back("Transform");
  this->_componentList.push_back("MeshRenderer");

  es = entities();

  for(auto it = es.begin(); it != es.end(); ++it)
    {
      MeshRenderer *mr = dynamic_cast<MeshRenderer*>(SME::core::World::get()->getComponent("MeshRenderer", *it));
      SME::core::IAsset *mesh = mr->mesh();
      SME::core::Data<GPUMesh*> *gpumesh_data = dynamic_cast<SME::core::Data<GPUMesh*> *> (mesh->data("GPUMesh"));
      GPUMesh *gpumesh = gpumesh_data->value();

      SME::ogl::Shader *sh = dynamic_cast<SME::ogl::Shader*>(mr->shader());
      sh->program()->bind();

      //Transforms
      SME::core::Component *transformComponent = SME::core::World::get()->getComponent("Transform", *it);
      SME::core::Data<Eigen::Affine3f> *world = dynamic_cast<SME::core::Data<Eigen::Affine3f> *>(transformComponent->data("world"));


      //Model matrix takes the vertex in object space and takes them to world space
      Eigen::Matrix4f model;

      Eigen::Matrix4f mvpMatrix;
      Eigen::Matrix4f normalMatrix;


      model = world->value().matrix();

      mvpMatrix    = projection*view*model;
      normalMatrix = (view*model).inverse().transpose();

      GLint mvpLocation = sh->program()->uniformLocation("mvpMatrix");
      glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, mvpMatrix.data());

      GLint normalLocation = sh->program()->uniformLocation("normalMatrix");
      glUniformMatrix4fv(normalLocation, 1, GL_FALSE, normalMatrix.data());

      gpumesh->vao.bind();
      SME::core::Data<std::vector<unsigned int> > *tris = dynamic_cast<SME::core::Data<std::vector<unsigned int> > *>(mesh->data("triangles"));
      glDrawElements(GL_TRIANGLES, tris->value().size(), GL_UNSIGNED_INT, 0);
      gpumesh->vao.release();

      sh->program()->release();
    }
}

void OpenGLRendererSystem::init()
{
  glwidget = new SME::ogl::SMEOpenGLWidget(this);

  QSurfaceFormat format;
  format.setDepthBufferSize(24);
  format.setStencilBufferSize(8);
  format.setVersion(4, 5);
  format.setProfile(QSurfaceFormat::CoreProfile);

  glwidget->setFormat(format);
  glwidget->show();

  _isInit = true;
}
