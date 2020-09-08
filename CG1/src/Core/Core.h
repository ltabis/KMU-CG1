#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
		// TODO: delete.
		void test();
		static void error_callback(int error, const char *description);
	};
}
