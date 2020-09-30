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

    // order of vertex rendering.
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    // creating a new vertex buffer.
    CG::VertexBuffer vb(vertices, 8 * sizeof(float));

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

    // creating a new index buffer.
    CG::IndexBuffer ib(indices, 6);

    // attaching a vertex and fragment shader to the program.
    sloader.attach("triangle_vertex");
    sloader.attach("red");

    // creating an executable with both shaders and using the program.
    sloader.createExecutable();
    sloader.use();

    // running window loop.
    core->run();

    CG_LOG_WARN("Ending session...");

    return 0;
}