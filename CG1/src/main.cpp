// main.cpp
// Application entry point.

#include "Core.hpp"
#include "ShaderLoader.hpp"
#include "Profiling/Breakpoint.hpp"

// Error handling could be made.
static unsigned int compileShader(const std::string& sourceCode, unsigned int type)
{
    unsigned int id = glCreateShader(type);
    const char *rawSource = sourceCode.c_str();

    glShaderSource(id, 1, &rawSource, nullptr);
    glCompileShader(id);

    // error handling.
    // wrapp this code into an error object with a logger.
    int status = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);

    if (!status) {

        int messageLength = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &messageLength);

        // stack allocated string.
        char *message = (char *)_malloca(sizeof(char) * messageLength);

        glGetShaderInfoLog(id, messageLength, &messageLength, message);

        CG_LOG_ERROR("Shader compilation failed. Error: {}", message);

        glDeleteShader(id);
        return 0;
    }
    return id;
}

// For the example sake.
static unsigned int createShaders(const std::string& vertexShader, const std::string& fragmentShader)
{
    // try to use base types as much as possible when using opengl
    // in case you use other graphical apis.
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fs = compileShader(fragmentShader,  GL_FRAGMENT_SHADER);

    if (!vs || !fs)
        return 0;

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    // deleting the intermidiate shaders since
    // they've been correctly loaded into the program.
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
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

    CG::ShaderLoader sloader;

    // profiling shader loading.
    {
#if _DEBUG
        CG::Breakpoint<std::chrono::microseconds> b("Shader loading", "μs");
#endif
        sloader.load("./res/shaders/basic.shader");
    }

    // Core code, will be used when opengl
    // will be encapsulated.
    //try {
    //    CG::Core core;
    //    core.run();
    //} catch (std::string err) {
    //    std::cerr << "Exception: " << err << std::endl;
    //}

    /* trying to render a triangle. */

    // data to render a triangle.
    unsigned int id;
    float vertices[6] = {
       -0.5f, -0.5f,
        0.0f,  0.5f,
        0.5f, -0.5f
    };
 
    // creating a new vertex buffer.
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, vertices, GL_STATIC_READ);
    
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

    // enabling the attribute.
    glEnableVertexAttribArray(0);

    const std::string vertexShader = sloader.get("triangle_vertex").source;
    const std::string fragmentShader = sloader.get("blue").source;

    unsigned int program = createShaders(vertexShader, fragmentShader);
    glUseProgram(program);

    // running window loop.
    core->run();

    glDeleteProgram(program);

    CG_LOG_WARN("Ending session...");

    return 0;
}