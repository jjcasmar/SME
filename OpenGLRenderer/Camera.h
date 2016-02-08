#ifndef CAMERA_H
#define CAMERA_H

#include "core/World.h"
#include "core/Data.h"

#include <Eigen/Core>


namespace SME
{
namespace ogl
{

class Camera : public SME::core::Component
{
public:
    Camera(const std::string &type);
    virtual ~Camera();

    float fov() const;
    void setFov(float fov);
    float ar() const;
    void setAr(float ar);
    float near() const;
    void setNear(float near);
    float far() const;
    void setFar(float far);
    float width() const;
    void setWidth(float width);
    float height() const;
    void setHeight(float height);
    bool active() const;
    void setActive(bool active);

private:
   float _fov;
   float _ar;
   float _near;
   float _far;
   float _width;
   float _height;

   bool _active;
   bool _updateNeeded;

    Eigen::Matrix4f _projection;


    // Component interface
public:
    void configure(tinyxml2::XMLElement *element);
    Eigen::Matrix4f projection();

};

}
}



#endif // CAMERA_H
