#include "TestShaderEditor.hpp"

CG::Test::TestShaderEditor::TestShaderEditor()
	: m_Fov		   { 90	  }
	, m_HelpOpened { false }
	, m_FpsMode    { false }
{
	m_Cube = std::make_unique<Cube>(
		glm::vec3(0.f, 0.f, -3.f),
		glm::vec3(0.f),
		glm::vec3(1.f)
	);

	m_Sloader = std::make_unique<ShaderLoader>();

	m_Sloader->load("./res/shaders/phong.shader");
	m_Sloader->attach("triangle");
	m_Sloader->attach("color");
	m_Sloader->createExecutable();
}

CG::Test::TestShaderEditor::~TestShaderEditor()
{
}

void CG::Test::TestShaderEditor::onStart()
{
	if (!m_Controller.get())
		m_Controller = std::make_unique<NoClipCameraController>(
			_renderer->window(),
			glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.f)
		);

	m_Sloader->setUniform("u_mvp", glm::mat4(1.f));
}

void CG::Test::TestShaderEditor::onUpdate(float deltaTime)
{
	m_Controller->update(deltaTime);

	if (glfwGetKey(_renderer->window(), GLFW_KEY_R))
		hotReloadShader(*m_Sloader);
}

void CG::Test::TestShaderEditor::onRender()
{
	ImGui::Begin("Camera Controller");
	// control over the projection matrix.
	if (ImGui::InputFloat("FOV", &m_Fov, 1)) {
		m_Controller->setFieldOfView(m_Fov);
		CG_CONSOLE_INFO("fov set to {}", m_Fov);
	}
	if (ImGui::InputFloat2("Aspect Ratio", &m_AspectRatio[0], 1))
		m_Controller->setAspectRatio(m_AspectRatio.x, m_AspectRatio.y);
	if (ImGui::Button("Help"))
		m_HelpOpened = !m_HelpOpened;

	if (m_HelpOpened) {
		ImGui::BeginChild("Tips");
		ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), "How to use the controller.");
		ImGui::Text("Use the mouse to look around.");
		ImGui::Text("Use 'W' 'A' 'S' 'D' to move the camera.");
		ImGui::Text("Use 'Space' and 'Left Shift' to move the camera up or down.");
		ImGui::Text("Press mouse right click to enter fps mode and reclick to get out");
		ImGui::EndChild();
	}
	ImGui::End();

	if (glfwGetMouseButton(_renderer->window(), GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) {
		m_FpsMode = !m_FpsMode;
		if (m_FpsMode)
			glfwSetInputMode(_renderer->window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else
			glfwSetInputMode(_renderer->window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}


	glm::mat4 mvp = m_Controller->view() * m_Cube->transform.model();
	m_Sloader->setUniform("u_mvp", mvp);
	_renderer->drawWireFrame(*m_Cube, *m_Sloader);
}

void CG::Test::TestShaderEditor::onStop()
{
}

void CG::Test::TestShaderEditor::onReset()
{
	// reseting the translation uniform.
	m_Sloader->setUniform("u_mvp", glm::translate(glm::mat4(1.f), glm::vec3(0.f)));

	// TODO: reset cam position and rotation.
}

void CG::Test::TestShaderEditor::hotReloadShader(ShaderLoader& shader)
{
	CG_CONSOLE_INFO("Reloading shaders ...");
	// deleting the current shaders.
	m_Sloader.reset();

	// reloading them.
	m_Sloader = std::make_unique<ShaderLoader>();
	m_Sloader->load("./res/shaders/phong.shader");
	m_Sloader->attach("triangle");
	m_Sloader->attach("color");
	m_Sloader->createExecutable();
	m_Sloader->setUniform("u_mvp", glm::mat4(1.f));
}
