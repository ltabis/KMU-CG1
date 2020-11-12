#include "CameraController.hpp"

CG::CameraController::CameraController(
    GLFWwindow *window,
    const glm::vec3& position,
    const glm::vec3& point,
    float speed,
    float sensibility
)
    : speed       { speed       }
    , sensibility { sensibility }
    , _camera {
        glm::vec3(0.f, 0.f, 1.f),
        glm::vec3(0.f, 0.f, -1.f),
        glm::vec3(0.f, 1.f, 0.f),
        1920,
        1080
    }
    , _window { window }
    , _pitch  { 0      }
    , _yaw    { 0      }
    , _roll   { 0      }
{
}

CG::CameraController::~CameraController()
{
}

void CG::CameraController::update()
{
    if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
        _camera.translate(_camera.front() * speed);
    if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
        _camera.translate(-_camera.front() * speed);
    if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
        _camera.translate(glm::normalize(glm::cross(_camera.front(), _camera.up())) * speed);
    if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
        _camera.translate(-glm::normalize(glm::cross(_camera.front(), _camera.up())) * speed);

    if (glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        _camera.translate(_camera.up() * speed);
    if (glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS)
        _camera.translate(-_camera.up() * speed);
}

glm::mat4 CG::CameraController::view() const
{
    return _camera.view();
}

//void CG::CameraController::translate(const glm::vec3& translation)
//{
//    _position += translation;
//	_view = glm::translate(_view, translation);
//}
//
//void CG::CameraController::rotate(const glm::vec3& rotation)
//{
//    _point += rotation;
//    _view *= glm::rotate(glm::mat4(1.f), rotation.x, glm::vec3(1, 0, 0)) *
//             glm::rotate(glm::mat4(1.f), rotation.y, glm::vec3(0, 1, 0)) *
//             glm::rotate(glm::mat4(1.f), rotation.z, glm::vec3(0, 0, 1));
//}

//void CG::CameraController::setFieldOfView(float fov)
//{
//    _fov = fov;
//    _createProjectionMatrix();
//}

//void CG::CameraController::setAspectRatio(float width, float height)
//{
//    _aspectRatio = width / height;
//    _createProjectionMatrix();
//}