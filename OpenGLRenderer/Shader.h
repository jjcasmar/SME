#ifndef SHADER_H
#define SHADER_H

#include <core/World.h>

#include <QOpenGLShaderProgram>

namespace SME
{
  namespace ogl
  {

    class Shader : public SME::core::IAsset
    {
      public:
        Shader(const std::string &type);

        // IAsset interface
      public:
        void configure(tinyxml2::XMLElement *element);

        QOpenGLShaderProgram *program() const {return _program;}

    private:
        QOpenGLShader *vertexShader;
        QOpenGLShader *fragmentShader;
        QOpenGLShaderProgram *_program;

    };

  }
}



#endif // SHADER_H
