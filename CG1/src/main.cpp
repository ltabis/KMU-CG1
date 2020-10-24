// main.cpp
// Application entry point.

#include "Renderer.hpp"
#include "Profiling/Breakpoint.hpp"
#include <glm/gtx/string_cast.hpp>

glm::mat4 lookAt(const glm::vec3& campos, const glm::vec3 &look, const glm::vec3 &up)
{
    glm::vec3 z = glm::normalize(campos - look);
    glm::vec3 x = glm::normalize(glm::cross(up, z));
    glm::vec3 y = glm::normalize(glm::cross(z, x));

    glm::mat4 translation { glm::translate(glm::mat4(1.0f), -campos) };
    glm::mat4 rotation {
        { x.x, y.x, z.x, 0 },
        { x.y, y.y, z.y, 0 },
        { x.z, y.z, z.z, 0 },
        { 0,   0,   0,   1 }
    };

    return rotation * translation;
}

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
    
    CG::ShaderLoader sloader1;
    CG::ShaderLoader sloader2;

    // profiling shader loading.
    {
#if _DEBUG
        CG::BreakpointUs b("Shader loading");
#endif
        sloader1.load("./res/shaders/basic.shader");
        sloader2.load("./res/shaders/basic.shader");
    }

    float verticesDataT1[] = {
        -0.5f, -0.5f, 0.0f, 1.0f,    1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f,    0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 1.0f,    0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f,    1.0f,  1.0f, 1.0f
    };

    float verticesDataT2[] = {
        -0.2f, -0.2f, 0.0f, 1.0f,
         0.2f, -0.2f, 0.0f, 1.0f,
         0.2f,  0.2f, 0.0f, 1.0f,
        -0.2f,  0.2f, 0.0f, 1.0f,
        -0.2f,  0.5f, 0.0f, 1.0f
    };

    // order of vertex rendering.
    unsigned int indices1[] = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int indices2[] = {
        0, 1, 2,
        2, 3, 0,
        2, 3, 4
    };

    // creating a new vertex buffer.
    CG::VertexBuffer vboV1(verticesDataT1, sizeof(verticesDataT1));
    CG::VertexBuffer vboV2(verticesDataT2, sizeof(verticesDataT2));
    CG::VertexArrayLayout layout1;
    CG::VertexArrayLayout layout2;

    layout1.push<float>(4);
    layout1.push<float>(3);
    layout2.push<float>(4);

    CG::VertexArray vao1;
    vao1.addBuffer(vboV1, layout1);

    CG::VertexArray vao2;
    vao2.addBuffer(vboV2, layout2);

    // creating a new index buffer.
    CG::IndexBuffer ibo1(indices1, 6);
    CG::IndexBuffer ibo2(indices2, 9);

    // attaching a vertex and fragment shader to the program.
    sloader1.attach("colored_triangle_vertex");
    sloader1.attach("vertices_colors");

    sloader2.attach("regular_triangle_vertex");
    sloader2.attach("green");

    // creating an executable with both shaders and using the program on the GPU.
    sloader1.createExecutable();
    sloader2.createExecutable();

    CG_CONSOLE_INFO("Loggin to the main console.");

    /* Loop until the user closes the window */
    while (!renderer->windowShouldClose()) {
        renderer->clear();
        renderer->draw(vao1, ibo1, sloader1);
        renderer->draw(vao2, ibo2, sloader2);
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