// GUI.hpp
// GUI class definition

#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>

namespace CG {

	class GUI
	{
	public:
		enum class Style { CLASSIC, DARK };

		GUI(GLFWwindow* window, Style style);
		~GUI();

		void newFrame();
		void drawUI();
		void renderGUI();
	private:
	};
}

