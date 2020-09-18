// GUI.cpp
// GUI class implementation

#include "GUI.hpp"

CG::GUI::GUI(GLFWwindow* window, CG::GUI::Style style)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	if (style == Style::CLASSIC)
		ImGui::StyleColorsClassic();
	else
		ImGui::StyleColorsDark();
}

CG::GUI::~GUI()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
}

void CG::GUI::newFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void CG::GUI::drawUI()
{
	ImGui::Begin("Tools");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	ImGui::End();
}

void CG::GUI::renderGUI()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
