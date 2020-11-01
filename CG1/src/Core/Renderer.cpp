#include "Renderer.hpp"

/* register a new callback in memory that will be called when a key is pressed. */
void CG::EventHandler::registerCallback(unsigned int key,
    CG::CGCallback callback
)
{
    auto key_index = _keyCallbacks.find(key);

    if (key_index == _keyCallbacks.end())
        _keyCallbacks.emplace(key, callback);
    else {
        CG_CONSOLE_WARN("callback '{}' already bound. overriding it.", key);
        _keyCallbacks[key] = callback;
    }
}

/* execute the callback assigned to a specific key. */
void CG::EventHandler::executeCallback(Renderer* renderer, int key, int scancode, int action, int mods)
{
    for (auto& [callbackKey, callback] : _keyCallbacks)
        if (key == callbackKey)
            callback(renderer, key, scancode, action, mods);
}

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

/* initializing the Renderer object. glfw / glew */
CG::Renderer::Renderer()
{
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

    /* setting window resize callback */
    glfwSetWindowSizeCallback(_window, resize_callback);

    /* Initialize glew */
    if (glewInit() != GLEW_OK)
        throw "Couldn't initialize glew.";

    CG_LOG_INFO("Glew initialized.");

    /* Create an event handler instance to register key callbacks */
    _eventHandler = std::make_unique<EventHandler>(this);

    /* Initializing error debug callback */
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(glewErrorCallback, 0);

    CG_LOG_INFO("Renderer ready.");
}

CG::Renderer::~Renderer()
{
    glfwTerminate();
}

void CG::Renderer::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void CG::Renderer::clearColor(float r, float g, float b, float a) const
{
    glClearColor(r, g, b, a);
}

void CG::Renderer::draw(const VertexArray& vao, const IndexBuffer& ibo, const ShaderLoader& shader) const
{
    shader.use();
    vao.bind();
    ibo.bind();

    glDrawElements(GL_TRIANGLES, ibo.indices(), GL_UNSIGNED_INT, nullptr);
}

void CG::Renderer::pollEvents() const
{
    glfwPollEvents();
}

void CG::Renderer::swapBuffers() const
{
    glfwSwapBuffers(_window);
}

bool CG::Renderer::windowShouldClose()
{
    return glfwWindowShouldClose(_window);
}

void CG::Renderer::registerKeyBindingCallback(
    unsigned int key,
    CGCallback callback
)
{
    _eventHandler->registerCallback(key, callback);
}