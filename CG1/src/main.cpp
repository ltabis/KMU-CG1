// main.cpp
// Application entry point.

#include "Renderer.hpp"
#include "Profiling/Breakpoint.hpp"

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
    std::unique_ptr<CG::Renderer> renderer = nullptr;

    try {
        renderer = std::make_unique<CG::Renderer>(CG::GUI::Style::CLASSIC);
    } catch (std::string& e) {
        CG_LOG_CRITICAL(e);
        return 1;
    }

    // registering callbacks.
    renderer->registerKeyBindingCallback(GLFW_KEY_ESCAPE, escape_callback);
    renderer->registerKeyBindingCallback(GLFW_KEY_SPACE, spacebar_callback);
    
    CG::ShaderLoader sloader;

    // profiling shader loading.
    {
#if _DEBUG
        CG::BreakpointUs b("Shader loading");
#endif
        sloader.load("./res/shaders/basic.shader");
    }

    float verticesDataT1[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f,
    };

    float verticesDataT2[] = {
        -0.2f, -0.7f,
         0.2f, -0.2f,
         0.2f,  0.2f,
        -0.2f,  0.2f,
    };

    float colorData[] = {
        1.0f,  0.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
        0.0f,  0.0f, 1.0f,
        1.0f,  1.0f, 1.0f
    };

    // order of vertex rendering.
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    // creating a new vertex buffer.
    CG::VertexBuffer vboV1(verticesDataT1, sizeof(verticesDataT1));
    CG::VertexBuffer vboV2(verticesDataT2, sizeof(verticesDataT2));
    CG::VertexBuffer vboC(colorData, sizeof(colorData));
    CG::VertexArrayLayout layout1;
    CG::VertexArrayLayout layout2;

    layout1.push<float>(vboV1, 2);
    layout1.push<float>(vboC, 3);
    layout2.push<float>(vboV2, 2);
    layout2.push<float>(vboC, 3);

    CG::VertexArray vao1;
    vao1.addBuffer(vboV1, layout1);
    vao1.addBuffer(vboC, layout1);

    CG::VertexArray vao2;
    vao2.addBuffer(vboV2, layout2);
    vao2.addBuffer(vboC, layout2);

    // creating a new index buffer.
    CG::IndexBuffer ibo(indices, 6);

    // enabling the attribute.
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    //CG::VertexBuffer vbColors(colors, sizeof(colors));
    //glEnableVertexAttribArray(1);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    // attaching a vertex and fragment shader to the program.
    sloader.attach("colored_triangle_vertex");
    sloader.attach("vertices_colors");

    // creating an executable with both shaders and using the program on the GPU.
    sloader.createExecutable();
    sloader.use();

    CG_CONSOLE_INFO("Loggin to the main console.");

    /* Loop until the user closes the window */
    while (!renderer->windowShouldClose()) {
        renderer->clear();
        renderer->draw(vao1, ibo, sloader);
        renderer->draw(vao2, ibo, sloader);
        renderer->drawUI();
        renderer->pollEvents();
        renderer->swapBuffers();
    }

    CG_LOG_WARN("Ending session...");

#ifdef _DEBUG
    _CrtDumpMemoryLeaks();
#endif /* ! _DEBUG */

    return 0;
}