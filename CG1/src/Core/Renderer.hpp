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
#include "EventHandler.hpp"
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
	class Renderer
	{
	private:
		GLFWwindow *_window;
		std::unique_ptr<EventHandler> _eventHandler;
		std::unique_ptr<GUI> _gui;

	public:
		Renderer(GUI::Style style);
		~Renderer();

		void clear();
		void clearColor(float r, float g, float b, float a);
		void draw(const VertexArray& vao, const IndexBuffer& ibo, const ShaderLoader& shader);
		void drawUI();
		void pollEvents();
		void swapBuffers();
		bool windowShouldClose();

		void registerKeyBindingCallback(unsigned int key, void (*callback)(GLFWwindow* window, int key, int scancode, int action, int mods));
	};
}
