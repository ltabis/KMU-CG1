#include "CameraController.hpp"

CG::CameraController::CameraController(
    GLFWwindow *window,
    const glm::vec3& position,
    const glm::vec3& point,
    float speed,
    float sensitivity
)
    : speed   { speed  }
    , _window { window }
    , _camera {
        position,
        point,
        glm::vec3(0.f, 1.f, 0.f),
        1920.f,
        1080.f,
        .1f,
        500.f,
        90.f,
        true
    }
{
    _sensitivity = sensitivity;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

CG::CameraController::~CameraController()
{
}

void CG::CameraController::setFieldOfView(float fov)
{
    _camera.setFieldOfView(fov);
}

void CG::CameraController::setAspectRatio(float width, float height)
{
    _camera.setAspectRatio(width, height);
}

void CG::CameraController::update(float deltaTime)
{
    _computeCameraTranslation(deltaTime);
    _computeCameraRotation(deltaTime);
}

glm::mat4 CG::CameraController::view() const
{
    return _camera.view();
}

void CG::CameraController::_computeCameraTranslation(float deltaTime)
{
    if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
        
        _camera.translate(glm::normalize(_camera.front()) * speed * deltaTime);
    if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
        _camera.translate(glm::normalize(-_camera.front()) * speed * deltaTime);
    if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
        _camera.translate(glm::normalize(glm::cross(_camera.front(), _camera.up())) * speed * deltaTime);
    if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
        _camera.translate(-glm::normalize(glm::cross(_camera.front(), _camera.up())) * speed * deltaTime);

    if (glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS)
        _camera.translate(glm::normalize(_camera.up()) * speed * deltaTime);
    if (glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        _camera.translate(glm::normalize(-_camera.up()) * speed * deltaTime);
}

void CG::CameraController::_computeCameraRotation(float deltaTime)
{
    double xpos;
    double ypos;

    glfwGetCursorPos(_window, &xpos, &ypos);

    if (_firstMousePosition) {
        _lastMouseXPosition = (float)xpos;
        _lastMouseYPosition = (float)ypos;
        _firstMousePosition = false;
    }

    float mouse_x_offset = ((float)xpos - _lastMouseXPosition) * _sensitivity;
    float mouse_y_offset = (_lastMouseYPosition - (float)ypos) * _sensitivity;

    _lastMouseXPosition = (float)xpos;
    _lastMouseYPosition = (float)ypos;

    _yaw += mouse_x_offset;
    _pitch += mouse_y_offset;

    // applying constraints on the y axis.
    if (_pitch > 89.0f)
        _pitch = 89.0f;
    if (_pitch < -89.0f)
        _pitch = -89.0f;

    glm::vec3 direction;
    direction.x = std::cos(glm::radians(_yaw)) * std::cos(glm::radians(_pitch));
    direction.y = std::sin(glm::radians(_pitch));
    direction.z = std::sin(glm::radians(_yaw)) * std::cos(glm::radians(_pitch));

    _camera.setFront(glm::normalize(direction));
}
