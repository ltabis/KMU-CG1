// Renderer.hpp
// Renderer class declaration.

#pragma once

// using the crt library in debug mode
// to find memory leaks.
#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
	#define DEBUG_CLIENTBLOCK new( _CLIENT_BLOCK, __FILE__, __LINE__)
	#define new DEBUG_CLIENTBLOCK
#endif /* ! _DEBUG */

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "GUI.hpp"
#include "Logger.hpp"
#include "VertexArray.hpp"
#include "ShaderLoader.hpp"
#include "IndexBuffer.hpp"

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
	class Renderer;
	class EventHandler;
	typedef void (*CGCallback)(Renderer* renderer, int key, int scancode, int action, int mods);

	class Renderer
	{
	private:
		GLFWwindow* _window;
		std::unique_ptr<EventHandler> _eventHandler;

	public:
		friend void input_handler(GLFWwindow* window, int key, int scancode, int action, int mods);

		Renderer();
		~Renderer();

		void clear() const;
		void clearColor(float r, float g, float b, float a) const;
		void draw(const VertexArray& vao, const IndexBuffer& ibo, const ShaderLoader& shader) const;
		void pollEvents() const;
		void swapBuffers() const;
		bool windowShouldClose();

		void registerKeyBindingCallback(unsigned int key, CGCallback callback);
		GLFWwindow* window() { return _window; };
	};

	// forward declarations.
	void input_handler(GLFWwindow* window, int key, int scancode, int action, int mods);

	class EventHandler
	{
	private:
		std::string _configPath;
		std::unordered_map<unsigned int, CGCallback> _keyCallbacks;
	public:

		EventHandler(Renderer* renderer, const std::string& configPath = "")
			: _configPath{ configPath }
		{
			if (!renderer || !renderer->window())
				throw "Couldn't initialize the event handler, window null";

			glfwSetKeyCallback(renderer->window(), input_handler);
			glfwSetWindowUserPointer(renderer->window(), renderer);
		}

		void saveBindings() const;
		void loadBindings() const;
		void registerCallback(unsigned int, CGCallback callback);
		void executeCallback(Renderer* renderer, int key, int scancode, int action, int mods);
	};

	/*
		Initiate callbacks used by the event handler. TODO: rething about the whole thing.
		the method to register the callback and set the user data pointer are not declared
		inside the event handler, which is confusing.
	*/
	static void input_handler(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		void* data = glfwGetWindowUserPointer(window);

		if (!data)
			return;

		Renderer *handler = static_cast<CG::Renderer*>(data);
		handler->_eventHandler->executeCallback(handler, key, scancode, action, mods);
	}
}
