#include "Shader.h"
#include <tinyxml2.h>

#include <QOpenGLShader>

SME::ogl::Shader::Shader(const std::string &type) :
  SME::core::IAsset(type)
{

}

void SME::ogl::Shader::configure(tinyxml2::XMLElement *element)
{
  const char *vertex_src = element->Attribute("vertex");
  const char *fragment_src = element->Attribute("fragment");

  if (vertex_src == nullptr || fragment_src == nullptr)
  {
    std::cerr << "Shaders must have at least a vertex and fragment source code" << std::endl;
    return;
  }

  vertexShader   = new QOpenGLShader(QOpenGLShader::Vertex);
  fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment);

  vertexShader->compileSourceFile(vertex_src);
  fragmentShader->compileSourceFile(fragment_src);

  _program = new QOpenGLShaderProgram;
  _program->addShader(vertexShader);
  _program->addShader(fragmentShader);

  const char *name = element->Attribute("name");
  if (name != nullptr)
  {
      _name = name;
  }

}
