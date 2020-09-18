// GUI.cpp
// GUI class implementation

#include "GUI.hpp"

GUI::GUI(GLFWwindow* window)
{
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
}

GUI::~GUI()
{
}
