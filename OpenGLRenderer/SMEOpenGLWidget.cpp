#include "SMEOpenGLWidget.h"

#include <QOpenGLContext>

#include "core/World.h"
#include "OpenGLRendererSystem.h"

using namespace SME::ogl;

SMEOpenGLWidget::SMEOpenGLWidget(OpenGLRendererSystem *system, QWidget *parent) : QOpenGLWidget(parent)
{
    _system = system;
}

SMEOpenGLWidget::~SMEOpenGLWidget()
{

}

void SMEOpenGLWidget::initializeGL()
{
    glewInit();

    //Activate culling
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    //glEnable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glClearColor(0,0,0,1);
}

void SMEOpenGLWidget::resizeGL(int w, int h)
{
  glViewport(0,0,w,h);
  _system->resize(w,h);
}

void SMEOpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    _system->Render();
}
