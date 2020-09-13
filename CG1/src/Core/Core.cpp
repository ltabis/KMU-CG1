#include "Core.hpp"

CG::Core::Core()
{
    /* setting error callback */
    glfwSetErrorCallback(error_callback);

    /* Initialize glfw */
    if (!glfwInit())
        throw "Couldn't initialize glfw.";

    /* Create a windowed mode window and its OpenGL context */
    _window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

    if (!_window)
    {
        glfwTerminate();
        throw "Couldn't initialize glfw's window.";
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(_window);

    /* Vsync, to be investigated  */
    glfwSwapInterval(1);

    /* Initialize glew */
    if (glewInit() != GLEW_OK)
        throw "Couldn't initialize glew.";
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

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(_window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}

void CG::Core::error_callback(int error, const char* description)
{
    std::cerr << "[" << error << "] Error: " << description << std::endl;
}