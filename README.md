# KMU-CG1
Doing some rendering with C++ and OpenGL.

## Goal

Create a simple renderer that could be integrated into a game engine.
It will first support 2D, then eventually 3D.
It won't we necesserly optimised all the way, this project is used mainly to learn opengl and mathematics.

*Current version*: 0.23.0

## Build

The project only compiles with a VS solution for the time being.
Dependencies must be listed at ``C:\Graphics\Tools\`` by default, but you could override the path in the VS solution.

## Tests

The renderer is tested using a custom test framework located in the CG1/src/Tests folder.
You can add your own tests by creating an object inheriting the ATest abstract class.
Then, register your test using the TestMenu's ``registerTest<classType>("test name")`` in the main.cpp file.
You will be able to load the test using an ImGui interface when launching the solution.

## Dependencies

[GLEW](http://glew.sourceforge.net/)
[GLFW](https://www.glfw.org/)
[GLM](https://glm.g-truc.net/0.9.4/api/index.html)
[Imgui](https://github.com/ocornut/imgui)
[Spdlog](https://github.com/gabime/spdlog)

![Test framework](placeholder.png)