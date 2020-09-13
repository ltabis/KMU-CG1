// Core.hpp
// core class declaration.

#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace glm
{
	// recreate your propre classes
	// it will be better in memory.
	// (vector class is bloated)
	typedef vec2 point2;
	typedef vec3 point3;
}

namespace CG
{
	class Core
	{
	private:
		GLFWwindow *_window;

	public:
		Core();
		~Core();

		void run();
		static void error_callback(int error, const char *description);
	};
}
