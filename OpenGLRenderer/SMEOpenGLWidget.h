#ifndef SMEOPENGLWIDGET_H
#define SMEOPENGLWIDGET_H

#include <GL/glew.h>

#include <QOpenGLWidget>

namespace SME
{
namespace ogl
{

class OpenGLRendererSystem;

class SMEOpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    SMEOpenGLWidget(OpenGLRendererSystem *system, QWidget *parent = nullptr);
    virtual ~SMEOpenGLWidget();

    // QOpenGLWidget interface
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    OpenGLRendererSystem *_system;
};

}
}


#endif // SMEOPENGLWIDGET_H
