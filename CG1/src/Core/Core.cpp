#include "Core.hpp"

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

static void glfwErrorCallback(int error, const char* description)
{
    CG_LOG_ERROR("Error '{}': {}", error, description);
}

CG::Core::Core(CG::GUI::Style style)
{
    CG::Logger::Init();
    CG_LOG_INFO("Initializing OpenGL Core.");

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

    /* Vsync, to be investigated */
    glfwSwapInterval(1);

    /* Initialize glew */
    if (glewInit() != GLEW_OK)
        throw "Couldn't initialize glew.";

    CG_LOG_INFO("Glew initialized.");

    /* Create a GUI instance to display debug */
    _gui = std::make_unique<GUI>(_window, style);


    /* Initializing error debug callback */
     glEnable(GL_DEBUG_OUTPUT);
     glDebugMessageCallback(glewErrorCallback, 0);

    CG_LOG_INFO("Core ready.");
}

CG::Core::~Core()
{
    glfwTerminate();
}

void CG::Core::run()
{
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(_window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        /* Poll for and process events */
        glfwPollEvents();

        _gui->newFrame();
        _gui->drawUI();
        _gui->renderGUI();

        /* Swap front and back buffers */
        glfwSwapBuffers(_window);
    }
}