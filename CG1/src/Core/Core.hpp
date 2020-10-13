// Core.hpp
// core class declaration.

#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "GUI.hpp"
#include "Logger.hpp"
#include "EventHandler.hpp"

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
		std::unique_ptr<EventHandler> _eventHandler;
		std::unique_ptr<GUI> _gui;

	public:
		Core(GUI::Style style);
		~Core();

		void run();
		void registerKeyBindingCallback(unsigned int key, void (*callback)(GLFWwindow* window, int key, int scancode, int action, int mods));
	};
}
