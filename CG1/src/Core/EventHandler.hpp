#pragma once

#include <unordered_map>
#include "GLFW/glfw3.h"
#include "Logger.hpp"

namespace CG
{
	static void input_handler(GLFWwindow* window, int key, int scancode, int action, int mods);

	class EventHandler
	{
	private:
		std::string _configPath;
		std::unordered_map<unsigned int, GLFWkeyfun> _keyCallbacks;
	public:

		EventHandler(GLFWwindow *window, const std::string& configPath = "")
			: _configPath(configPath)
		{
			if (!window)
				throw "Couldn't create the event handler, window object uninitialized.";
			// adding the object to the userData of the window
			// so we can access its data in key events callbacks.
			glfwSetWindowUserPointer(window, this);

			// setting the callback to any input.
			glfwSetKeyCallback(window, input_handler);
		};

		void saveBindings() const;
		void loadBindings() const;
		void registerCallback(unsigned int, void (*callback)(GLFWwindow* window, int key, int scancode, int action, int mods));
		void executeCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		std::unordered_map<unsigned int, GLFWkeyfun> &keyCallbacks();
	};

	static void input_handler(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		EventHandler* handler = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));

		if (!handler)
			return;

		handler->executeCallback(window, key, scancode, action, mods);
	}
}