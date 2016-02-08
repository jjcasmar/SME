#include "Camera.h"

#include <math.h>

using namespace SME::ogl;

SME::ogl::Camera::Camera(const std::string &type) :
    SME::core::Component(type)
{
    _near = 0.1;
    _far = 100;
    _active = true;
    _fov = 60;
    _updateNeeded = true;
}

Camera::~Camera()
{

}

bool Camera::active() const
{
    return _active;
}

void Camera::setActive(bool active)
{
    _active = active;
    _updateNeeded = true;
}

float Camera::height() const
{
    return _height;
}

void Camera::setHeight(float height)
{
    _height = height;
    _updateNeeded = true;
}

float Camera::width() const
{
    return _width;
}

void Camera::setWidth(float width)
{
    _width = width;
    _updateNeeded = true;
}

float Camera::far() const
{
    return _far;
}

void Camera::setFar(float far)
{
    _far = far;
    _updateNeeded = true;
}

float Camera::near() const
{
    return _near;
}

void Camera::setNear(float near)
{
    _near = near;
    _updateNeeded = true;
}

float Camera::ar() const
{
    return _ar;
}

void Camera::setAr(float ar)
{
    _ar = ar;
    _updateNeeded = true;
}

float Camera::fov() const
{
    return _fov;
}

void Camera::setFov(float fov)
{
    _fov = fov;
    _updateNeeded = true;
}

Eigen::Matrix4f Camera::projection()
{
    if (!_updateNeeded)
        return _projection;

    float theta = _fov*0.5;
    float range = _far - _near;
    float invtan = 1./tan(theta);

    _projection.setZero();

    _projection(0,0) = invtan / _ar;
    _projection(1,1) = invtan;
    _projection(2,2) = -(_near + _far) / range;
    _projection(3,2) = -1;
    _projection(2,3) = -2 * _near * _far / range;
    _projection(3,3) = 0;

    _updateNeeded = false;
    return _projection;
}

void Camera::configure(tinyxml2::XMLElement *element)
{
    
}
