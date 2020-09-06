#include "Core.h"

CG::Core::Core()
{
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

        glBegin(GL_TRIANGLES);

        glVertex2d(.5f, .5f);
        glVertex2d(-.5f, .5f);
        glVertex2d(-.5f, -.5f);

        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(_window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}