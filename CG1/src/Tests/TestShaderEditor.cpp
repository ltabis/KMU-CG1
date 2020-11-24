#include "TestShaderEditor.hpp"

CG::Test::TestShaderEditor::TestShaderEditor()
	: m_Fov				   { 90						   }
	, m_HelpOpened		   { false					   }
	, m_ControllerFreeze   { false					   }
	, m_FpsMode			   { false					   }
	, m_AmbiantLightColor  { glm::vec3(.2f, .2f, .2f)  }
	, m_ObjectColor        { glm::vec3(1.f, .0f, .0f)  }
	, m_lightPos		   { glm::vec3(5.f, 10.f, 0.f) }
{
	// creating triangles
	// front
	m_Triangles.push_back(
		std::make_unique<Triangle>(
			glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.f),
			glm::vec3(1.f)
	));
	m_Triangles.push_back(
		std::make_unique<Triangle>(
			glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.f, 0.f, 180.f),
			glm::vec3(1.f)
	));

	// back
	m_Triangles.push_back(
		std::make_unique<Triangle>(
			glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(0.f, 180.f, 0.f),
			glm::vec3(1.f)
	));
	m_Triangles.push_back(
		std::make_unique<Triangle>(
			glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(0.f, 180.f, 180.f),
			glm::vec3(1.f)
	));

	// top
	m_Triangles.push_back(
		std::make_unique<Triangle>(
			glm::vec3(0.f, 1.f, 0.f),
			glm::vec3(90.f, 0.f, 0.f),
			glm::vec3(1.f)
	));
	m_Triangles.push_back(
		std::make_unique<Triangle>(
			glm::vec3(0.f, 1.f, 0.f),
			glm::vec3(90.f, 0.f, 180.f),
			glm::vec3(1.f)
	));

	// bottom
	m_Triangles.push_back(
		std::make_unique<Triangle>(
			glm::vec3(0.f, -1.f, 0.f),
			glm::vec3(-90.f, 0.f, 0.f),
			glm::vec3(1.f)
	));
	m_Triangles.push_back(
		std::make_unique<Triangle>(
			glm::vec3(0.f, -1.f, 0.f),
			glm::vec3(-90.f, 0.f, 180.f),
			glm::vec3(1.f)
	));

	// left
	m_Triangles.push_back(
		std::make_unique<Triangle>(
			glm::vec3(-1.f, 0.f, 0.f),
			glm::vec3(0.f, 90.f, 0.f),
			glm::vec3(1.f)
	));
	m_Triangles.push_back(
		std::make_unique<Triangle>(
			glm::vec3(-1.f, 0.f, 0.f),
			glm::vec3(0.f, 90, 180.f),
			glm::vec3(1.f)
	));

	// right
	m_Triangles.push_back(
		std::make_unique<Triangle>(
			glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(0.f, -90.f, 0.f),
			glm::vec3(1.f)
	));
	m_Triangles.push_back(
		std::make_unique<Triangle>(
			glm::vec3(1.f, 0.f, 0.f),
			glm::vec3(0.f, -90, 180.f),
			glm::vec3(1.f)
	));

	// creating a simple sphere from the dep list.
	m_LightCube = std::make_unique<Cube>(glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f));
	m_Sphere = std::make_unique<Sphere>(1.f, 100, 100);
	m_TeaPot = std::make_unique<VBOTeapot>(64, glm::mat4(1.f));
	m_TeaPot->transform.translate(5.f, 0.f, 0.f);
	m_TeaPot->transform.rotate(-90, 1, 0, 0);
	m_ShaderSphere = std::make_unique<ShaderLoader>();

	m_ShaderSphere->load("./res/shaders/phong-sphere.shader");
	m_ShaderSphere->attach("triangle");
	m_ShaderSphere->attach("color");
	m_ShaderSphere->createExecutable();

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
			glm::vec3(0.f, 3.f, 3.f),
			glm::vec3(0.f)
		);

	m_Sloader->setUniform("u_ambiantLightColor", m_AmbiantLightColor);
	m_Sloader->setUniform("u_objectColor", m_ObjectColor);
	m_Sloader->setUniform("u_mvp", glm::mat4(1.f));
	m_Sloader->setUniform("u_modelView", glm::mat4(1.f));
	m_Sloader->setUniform("u_view", glm::mat4(1.f));
	m_Sloader->setUniform("u_lightPos", glm::vec4(-2.0, 10.0, 0.0, 1.0));
}

void CG::Test::TestShaderEditor::onUpdate(float deltaTime)
{
	if (!m_ControllerFreeze)
		m_Controller->update(deltaTime);

	if (glfwGetKey(_renderer->window(), GLFW_KEY_F))
		m_ControllerFreeze = !m_ControllerFreeze;

	if (glfwGetKey(_renderer->window(), GLFW_KEY_R)) {
		hotReloadShader(m_Sloader, "./res/shaders/phong.shader");
		hotReloadShader(m_ShaderSphere, "./res/shaders/phong-sphere.shader");
	}
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
	if (m_ControllerFreeze)
		if (ImGui::Button("Unfreeze controller")) m_ControllerFreeze = false;
	else
		if (ImGui::Button("Freeze controller")) m_ControllerFreeze = true;
	if (ImGui::Button("Help"))
		m_HelpOpened = !m_HelpOpened;

	if (m_HelpOpened) {
		ImGui::BeginChild("Tips");
		ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), "How to use the controller.");
		ImGui::Text("Use the mouse to look around.");
		ImGui::Text("Use 'W' 'A' 'S' 'D' to move the camera.");
		ImGui::Text("Use 'Space' and 'Left Shift' to move the camera up or down.");
		ImGui::Text("Press mouse right click to enter fps mode and reclick to get out");
		ImGui::Text("Press 'F' to freeze the camera or unfreeze it.");
		ImGui::EndChild();
	}

	ImGui::End();
	ImGui::Begin("Shader control");
	if (ImGui::ColorEdit3("Ambiant light color", &m_AmbiantLightColor[0], 1) ||
		ImGui::InputFloat3("Light position", &m_lightPos[0], 1) ||
		ImGui::ColorEdit3("object color", &m_ObjectColor[0], 1)) {
		hotReloadShader(m_Sloader, "./res/shaders/phong.shader");
		hotReloadShader(m_ShaderSphere, "./res/shaders/phong-sphere.shader");
	}

	ImGui::End();

	if (glfwGetMouseButton(_renderer->window(), GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) {
		m_FpsMode = !m_FpsMode;
		if (m_FpsMode)
			glfwSetInputMode(_renderer->window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else
			glfwSetInputMode(_renderer->window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	// drawing each triangles for the cube.
	//for (auto& triangle : m_Triangles) {
	//	glm::mat4 mvp = m_Controller->projectionView() * triangle->transform.model();
	//	glm::mat3 normalMat = glm::mat3(glm::transpose(glm::inverse(m_Controller->view() * triangle->transform.model())));

	//	m_Sloader->setUniform("u_mvp", mvp);
	//	m_Sloader->setUniform("u_view", m_Controller->view());
	//	m_Sloader->setUniform("u_modelView", m_Controller->view() * triangle->transform.model());
	//	m_Sloader->setUniform("u_normalMat", normalMat);
	//	_renderer->draw(*triangle, *m_Sloader);
	//}

	// drawing the sphere.
	glm::mat3 normalMat = glm::mat3(glm::transpose(glm::inverse(m_Controller->view() * m_Sphere->transform.model())));

	m_ShaderSphere->setUniform("u_mvp", m_Controller->projectionView() * m_Sphere->transform.model());
	m_ShaderSphere->setUniform("u_view", m_Controller->view());
	m_ShaderSphere->setUniform("u_modelView", m_Controller->view() * m_Sphere->transform.model());
	m_ShaderSphere->setUniform("u_normalMat", normalMat);
	_renderer->draw(*m_Sphere, *m_ShaderSphere);

	normalMat = glm::mat3(glm::transpose(glm::inverse(m_Controller->view() * m_TeaPot->transform.model())));

	m_ShaderSphere->setUniform("u_mvp", m_Controller->projectionView() * m_TeaPot->transform.model());
	m_ShaderSphere->setUniform("u_view", m_Controller->view());
	m_ShaderSphere->setUniform("u_modelView", m_Controller->view() * m_TeaPot->transform.model());
	m_ShaderSphere->setUniform("u_normalMat", normalMat);
	_renderer->draw(*m_TeaPot, *m_ShaderSphere);
}

void CG::Test::TestShaderEditor::onStop()
{
}

void CG::Test::TestShaderEditor::onReset()
{
	// reseting the translation uniform.
	m_Sloader->setUniform("u_mvp", glm::mat4(1.f));
	m_Sloader->setUniform("u_view", glm::mat4(1.f));
	m_Sloader->setUniform("u_modelView", glm::mat4(1.f));
	m_Sloader->setUniform("u_normalMat", glm::mat3(1.f));

	// TODO: reset cam position and rotation.
}

void CG::Test::TestShaderEditor::hotReloadShader(std::unique_ptr<ShaderLoader>& shader, const std::string &shaderPath)
{
	CG_CONSOLE_INFO("Reloading shaders ...");
	// deleting the current shaders.
	shader.reset();

	// reloading them.
	shader = std::make_unique<ShaderLoader>();
	shader->load(shaderPath);
	shader->attach("triangle");
	shader->attach("color");
	shader->createExecutable();

	shader->setUniform("u_ambiantLightColor", m_AmbiantLightColor);
	shader->setUniform("u_objectColor", m_ObjectColor);
	shader->setUniform("u_lightPos", m_lightPos);
}
