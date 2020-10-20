// main.cpp
// Application entry point.

#include "Core.hpp"
#include "ShaderLoader.hpp"
#include "Profiling/Breakpoint.hpp"
#include "VertexArrayLayout.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

// -- Callbacks -- //
static void escape_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void spacebar_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
        CG_CONSOLE_INFO("spacebar pressed");
}

int main(void)
{
    std::unique_ptr<CG::Core> core = nullptr;

    try {
        core = std::make_unique<CG::Core>(CG::GUI::Style::CLASSIC);
    } catch (std::string& e) {
        CG_LOG_CRITICAL(e);
        return 1;
    }

    // registering callbacks.
    core->registerKeyBindingCallback(GLFW_KEY_ESCAPE, escape_callback);
    core->registerKeyBindingCallback(GLFW_KEY_SPACE, spacebar_callback);
    
    CG::ShaderLoader sloader;

    // profiling shader loading.
    {
#if _DEBUG
        CG::BreakpointUs b("Shader loading");
#endif
        sloader.load("./res/shaders/basic.shader");
    }

    /* trying to render a triangle. */

    // data to render a triangle.
    float vertices[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    float colors[] = {
         1.0f,  0.0f, 0.0f,
         0.0f,  1.0f, 0.0f,
         0.0f,  0.0f, 1.0f,

         0.0f,  0.0f, 1.0f,
         0.0f,  1.0f, 0.0f,
         1.0f,  0.0f, 0.0f,
    };

    // order of vertex rendering.
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    // creating a new vertex buffer.
    CG::VertexBuffer vbVerticies(vertices, sizeof(vertices));
    CG::VertexArrayLayout layout;

    layout.push<float>(2);

    CG::VertexArray vbo;
    vbo.addBuffer(vbVerticies, layout);

    // enabling the attribute.
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    //CG::VertexBuffer vbColors(colors, sizeof(colors));
    //glEnableVertexAttribArray(1);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    // creating a new index buffer.
    CG::IndexBuffer ib(indices, 6);

    // attaching a vertex and fragment shader to the program.
    sloader.attach("regular_triangle_vertex");
    sloader.attach("red");

    // creating an executable with both shaders and using the program on the GPU.
    sloader.createExecutable();
    sloader.use();

    CG_CONSOLE_INFO("Loggin to the main console.");

    // running window loop.
    core->run(vbo);

    CG_LOG_WARN("Ending session...");

#ifdef _DEBUG
    _CrtDumpMemoryLeaks();
#endif /* ! _DEBUG */
    return 0;
}