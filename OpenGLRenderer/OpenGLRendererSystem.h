#ifndef OPENGLRENDERERSYSTEM_H
#define OPENGLRENDERERSYSTEM_H

#include <core/World.h>

namespace SME
{
  namespace ogl
  {
    class SMEOpenGLWidget;
    class OpenGLRendererSystem : public SME::core::System
    {
      public:
        OpenGLRendererSystem(SME::core::World *world, const std::string &type);
        virtual ~OpenGLRendererSystem();

        void resize(int w, int h);
        void Render();


    private:
        void init();
        bool _isInit;

        SMEOpenGLWidget *glwidget;

        // System interface
    public:
        virtual void Start();
        virtual void Update();
        void postStart();

    };
  }
}

#endif // OPENGLRENDERERSYSTEM_H
