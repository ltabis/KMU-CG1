#pragma once

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
	};
}
