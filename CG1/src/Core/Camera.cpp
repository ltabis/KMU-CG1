#include "Camera.hpp"

CG::Camera::Camera(const glm::vec3& position, const glm::vec3& point, const glm::vec3& up, float width, float height, float nearPlane, float farPlane, float fov, CameraType type)
	: _position		{ position       }
	, _point		{ point          }
	, _up			{ up             }
    , _fov          { fov            }
    , _nearPlane    { nearPlane      }
    , _farPlane     { farPlane       }
    , _aspectRatio  { width / height }
    , _type         { type           }
{
    _createProjectionMatrix();
    _createViewMatrix();
}

void CG::Camera::_createProjectionMatrix()
{
    _projection = glm::mat4{
        { 1 / (_aspectRatio * glm::tan(_fov / 2)), 0, 0, 0 },
        { 0, 1 / glm::tan(_fov / 2), 0, 0 },
        { 0, 0, -((_farPlane + _nearPlane) / (_farPlane- _nearPlane)), -1},
        { 0, 0, -((2 * _farPlane * _nearPlane) / (_farPlane - _nearPlane)), 0 }
    };
}

void CG::Camera::_createViewMatrix()
{
    glm::vec3 z = glm::normalize(_position - _point);
    glm::vec3 x = glm::normalize(glm::cross(_up, z));
    glm::vec3 y = glm::normalize(glm::cross(z, x));

    glm::mat4 translation{ glm::translate(glm::mat4(1.0f), -_position) };
    glm::mat4 rotation{
        { x.x, y.x, z.x, 0 },
        { x.y, y.y, z.y, 0 },
        { x.z, y.z, z.z, 0 },
        { 0,   0,   0,   1 }
    };

    _view = rotation * translation;
}

CG::Camera::~Camera()
{
}

void CG::Camera::translate(const glm::vec3& translation)
{
    _position += translation;
	_view = glm::translate(_view, translation);
}

void CG::Camera::rotate(const glm::vec3& rotation)
{
    _point += rotation;
    _view *= glm::rotate(glm::mat4(1.f), rotation.x, glm::vec3(1, 0, 0)) *
             glm::rotate(glm::mat4(1.f), rotation.y, glm::vec3(0, 1, 0)) *
             glm::rotate(glm::mat4(1.f), rotation.z, glm::vec3(0, 0, 1));
}

void CG::Camera::setFieldOfView(float fov)
{
    _fov = fov;
    // TODO: implemente
}

void CG::Camera::setAspectRatio(float width, float height)
{
    _aspectRatio = width / height;
    // TODO: implemente
}

glm::mat4 CG::Camera::view() const
{
	return _projection * _view;
}
