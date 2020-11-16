#include "CameraController.hpp"

// Limitations: impossible to create multiple cameras.
// TODO: find a way to put the following variable into the class.
static float last_mouse_x_position = 0;
static float last_mouse_y_position = 0;

static bool first_mouse_position = true;

static float pitch = 0.f;
static float yaw = 0.f;
// Not really needed, but would be cool to implement.
static float roll = 0.f;

static float sensitivity = 0.1f;

static std::unique_ptr<CG::Camera> camera;

void mouse_camera_controller_callback(GLFWwindow* window, double xpos, double ypos)
{
    (void)window;

    if (first_mouse_position) {
        last_mouse_x_position = (float)xpos;
        last_mouse_y_position = (float)ypos;
        first_mouse_position = false;
    }

    float mouse_x_offset = ((float)xpos - last_mouse_x_position) * sensitivity;
    float mouse_y_offset = (last_mouse_y_position - (float)ypos) * sensitivity;

    last_mouse_x_position = (float)xpos;
    last_mouse_y_position = (float)ypos;

    yaw += mouse_x_offset;
    pitch += mouse_y_offset;

    // applying constraints on the y axis.
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = std::cos(glm::radians(yaw)) * std::cos(glm::radians(pitch));
    direction.y = std::sin(glm::radians(pitch));
    direction.z = std::sin(glm::radians(yaw)) * std::cos(glm::radians(pitch));

    camera->setFront(glm::normalize(direction));
}

CG::CameraController::CameraController(
    GLFWwindow *window,
    const glm::vec3& position,
    const glm::vec3& point,
    float speed,
    float sensitivity
)
    : speed   { speed  }
    , _window { window }
{
    camera = std::make_unique<CG::Camera>(
            position,
            point,
            glm::vec3(0.f, 1.f, 0.f),
            1920.f,
            1080.f,
            .1f,
            500.f,
            90.f,
            true
        );

    sensitivity = sensitivity;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetCursorPosCallback(window, mouse_camera_controller_callback);
}

CG::CameraController::~CameraController()
{
}

void CG::CameraController::update(float deltaTime)
{
    _computeCameraTranslation(deltaTime);
}

glm::mat4 CG::CameraController::view() const
{
    return camera->view();
}

void CG::CameraController::_computeCameraTranslation(float deltaTime)
{
    if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
        camera->translate(glm::normalize(camera->front()) * speed * deltaTime);
    if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
        camera->translate(glm::normalize(-camera->front()) * speed * deltaTime);
    if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
        camera->translate(glm::normalize(glm::cross(camera->front(), camera->up())) * speed * deltaTime);
    if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
        camera->translate(-glm::normalize(glm::cross(camera->front(), camera->up())) * speed * deltaTime);

    if (glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera->translate(glm::normalize(camera->up()) * speed * deltaTime);
    if (glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera->translate(glm::normalize(-camera->up()) * speed * deltaTime);
}