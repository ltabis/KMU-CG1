// main.cpp
// Application entry point.

#include "Core.hpp"
#include "ShaderLoader.hpp"
#include "Profiling/Breakpoint.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

int main(void)
{
    std::unique_ptr<CG::Core> core = nullptr;

    try {
        core = std::make_unique<CG::Core>(CG::GUI::Style::CLASSIC);
    } catch (std::string& e) {
        CG_LOG_CRITICAL(e);
        return 1;
    }

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

    // enabling the attribute.
    glEnableVertexAttribArray(0);
    // Parameters:
    // 1. index of the start of the attribute in memory.
    //    Here, it is our first attribute, so the index is 0.
    // 2. Component count of the attribute.
    //    Here, each vertex has 2 floats for the position. so 2.
    // 3. The type of each element.
    // 4. Werever your data needs to be normalized.
    // 5. Amount of bytes between each component.
    // 6. Starting point of the attribute.
    //    ex:         [ 1.f, 1.f ]           -> vertex component, so zero.
    //                [ 1.f, 1.f, 1.f, 1.f ] -> vertex component + texture coord
    //                                          to define textcoord: sizeof(float) * 2
    //                                          so (const void *)8.
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    CG::VertexBuffer vbColors(colors, sizeof(colors));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    // creating a new index buffer.
    CG::IndexBuffer ib(indices, 6);

    // attaching a vertex and fragment shader to the program.
    sloader.attach("triangle_vertex");
    sloader.attach("vertices_colors");

    // creating an executable with both shaders and using the program on the GPU.
    sloader.createExecutable();
    sloader.use();

    CG_CONSOLE_INFO("Loggin to the main console.");

    // running window loop.
    core->run();

    CG_LOG_WARN("Ending session...");

    return 0;
}