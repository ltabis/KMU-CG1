#include "Renderer.hpp"

/* openGL error callback. will be called if any error is thrown by glew. */
static void GLAPIENTRY glewErrorCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    CG_LOG_ERROR("OpenGL internal error: {}, type: 0x{}, severity: 0x{}, message: {}",
        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
        type,
        severity,
        message
    );
}

/* glfw error callback. will be called if any error is thrown by glfw */
static void glfwErrorCallback(int error, const char* description)
{
    CG_LOG_ERROR("Error '{}': {}", error, description);
}

/* initializing the Renderer object. glfw / glew / spdlog */
CG::Renderer::Renderer(CG::GUI::Style style)
{
    CG::Logger::Init();
    CG_LOG_INFO("Initializing OpenGL Renderer.");

    /* using modern opengl */
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* setting error callback */
    glfwSetErrorCallback(glfwErrorCallback);

    /* Initialize glfw */
    if (!glfwInit())
        throw "Couldn't initialize glfw.";

    CG_LOG_INFO("Glfw initialized.");

    /* Create a windowed mode window and its OpenGL context */
    _window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

    if (!_window)
    {
        glfwTerminate();
        throw "Couldn't initialize glfw's window.";
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(_window);

    /* disable Vsync, synchronises with monitor refresh rate */
    glfwSwapInterval(1);

    /* Initialize glew */
    if (glewInit() != GLEW_OK)
        throw "Couldn't initialize glew.";

    CG_LOG_INFO("Glew initialized.");

    /* Create a GUI instance to display debug */
    _gui = std::make_unique<GUI>(_window, style);
    /* Create an event handler instance to register key callbacks */
    _eventHandler = std::make_unique<EventHandler>(_window);

    /* Initializing error debug callback */
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(glewErrorCallback, 0);

    CG_LOG_INFO("Renderer ready.");
}

CG::Renderer::~Renderer()
{
    glfwTerminate();
}

void CG::Renderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void CG::Renderer::clearColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

void CG::Renderer::draw(const VertexArray& vao, const IndexBuffer& ibo, const ShaderLoader& shader)
{
    shader.use();
    vao.bind();
    ibo.bind();

    glDrawElements(GL_TRIANGLES, ibo.indices(), GL_UNSIGNED_INT, nullptr);
}

void CG::Renderer::drawUI()
{
    _gui->newFrame();
    _gui->drawUI();
    _gui->renderGUI();
}

void CG::Renderer::pollEvents()
{
    glfwPollEvents();
}

void CG::Renderer::swapBuffers()
{
    glfwSwapBuffers(_window);
}

bool CG::Renderer::windowShouldClose()
{
    return glfwWindowShouldClose(_window);
}

void CG::Renderer::registerKeyBindingCallback(
    unsigned int key,
    void(*callback)(GLFWwindow* window, int key, int scancode, int action, int mods
))
{
    _eventHandler->registerCallback(key, callback);
}