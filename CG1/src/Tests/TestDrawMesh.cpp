#include "TestDrawMesh.hpp"

CG::Test::TestDrawMesh::TestDrawMesh()
	: m_Fov				   { 90						   }
	, m_HelpOpened		   { false					   }
	, m_ControllerFreeze   { false					   }
	, m_FpsMode			   { false					   }
	, m_ObjectColor        { glm::vec3(1.f, .0f, .0f)  }
{
}

void CG::Test::TestDrawMesh::onStart()
{
	if (!m_Controller.get())
		m_Controller = std::make_unique<NoClipCameraController>(
			_renderer->window(),
			glm::vec3(0.f, 3.f, 3.f),
			glm::vec3(0.f)
		);

	// creating models.
	// m_Models.push_back(std::make_unique<Model>("../meshes/bunny.obj", glm::vec3(0.f), glm::vec3(0.f), glm::vec3(2.f)));

	// creating shapes.
	m_Shapes.push_back(std::make_unique<VBOTorus>(2, 1, 100, 100));
	m_Shapes[0]->transform.rotate(90.f, 1.f, 0.f, 0.f);

	// TODO: create each light cubes for every lights created.
	// m_LightCube = std::make_unique<Cube>(m_LightPos, glm::vec3(0.f), glm::vec3(1.f));

	m_PhongShader = std::make_unique<ShaderLoader>();
	m_LightCubeShader = std::make_unique<ShaderLoader>();

	m_PhongShader->load("./res/shaders/blinn-phong-mul-lights.shader");
	m_PhongShader->attach("triangle");
	m_PhongShader->attach("color");
	m_PhongShader->createExecutable();

	// generating lights.
	for (unsigned int i = 0, x = 0; i < 5; ++i, x += 3) {
		std::string light = "u_lights[" + std::to_string(i) + "].Position";
		m_PhongShader->setUniform(light, glm::vec4(x, 10.f, 0.f, 0.f));
	}

	m_PhongShader->setUniform("u_lights[0].Intensity", glm::vec3(0.0f, 0.8f, 0.8f));
	m_PhongShader->setUniform("u_lights[1].Intensity", glm::vec3(0.0f, 0.0f, 0.8f));
	m_PhongShader->setUniform("u_lights[2].Intensity", glm::vec3(0.8f, 0.0f, 0.0f));
	m_PhongShader->setUniform("u_lights[3].Intensity", glm::vec3(0.0f, 0.8f, 0.0f));
	m_PhongShader->setUniform("u_lights[4].Intensity", glm::vec3(0.8f, 0.8f, 0.8f));

	m_PhongShader->setUniform("u_objectColor", m_ObjectColor);
	m_PhongShader->setUniform("u_mvp", glm::mat4(1.f));
	m_PhongShader->setUniform("u_modelView", glm::mat4(1.f));
	m_PhongShader->setUniform("u_view", glm::mat4(1.f));

	m_LightCubeShader->load("./res/shaders/white.shader");
	m_LightCubeShader->attach("triangle");
	m_LightCubeShader->attach("color");
	m_LightCubeShader->createExecutable();
	m_LightCubeShader->setUniform("u_mvp", glm::mat4(1.f));
}

void CG::Test::TestDrawMesh::onUpdate(float deltaTime)
{
	if (!m_ControllerFreeze)
		m_Controller->update(deltaTime);

	if (glfwGetKey(_renderer->window(), GLFW_KEY_F))
		m_ControllerFreeze = !m_ControllerFreeze;

	if (glfwGetKey(_renderer->window(), GLFW_KEY_R))
		hotReloadShader(m_PhongShader, "./res/shaders/blinn-phong-mul-lights.shader");
}

void CG::Test::TestDrawMesh::onRender()
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
	if (ImGui::ColorEdit3("object color", &m_ObjectColor[0], 1)) {
		hotReloadShader(m_PhongShader, "./res/shaders/blinn-phong-mul-lights.shader");
	}
	//if (ImGui::InputFloat3("Light position", &m_LightPos[0], 1)) {
	//	m_LightCube->transform.setPosition(m_LightPos.x, m_LightPos.y, m_LightPos.z);
	//	hotReloadShader(m_PhongShader, "./res/shaders/blinn-phong-mul-lights.shader");
	//}

	ImGui::End();

	if (glfwGetMouseButton(_renderer->window(), GLFW_MOUSE_BUTTON_2) == GLFW_PRESS) {
		m_FpsMode = !m_FpsMode;
		if (m_FpsMode)
			glfwSetInputMode(_renderer->window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else
			glfwSetInputMode(_renderer->window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	// draw eventual models.
	for (auto& model : m_Models) {
		for (auto& mesh : model->meshes()) {
			glm::mat3 normalMat = glm::mat3(glm::transpose(glm::inverse(m_Controller->view() * mesh->transform.model())));

			m_PhongShader->setUniform("u_mvp", m_Controller->projectionView() * mesh->transform.model());
			m_PhongShader->setUniform("u_view", m_Controller->view());
			m_PhongShader->setUniform("u_modelView", m_Controller->view() * mesh->transform.model());
			m_PhongShader->setUniform("u_normalMat", normalMat);
			_renderer->draw(*mesh, *m_PhongShader);
		}
	}

	// draw eventual shapes.
	for (auto& shape : m_Shapes) {
		glm::mat3 normalMat = glm::mat3(glm::transpose(glm::inverse(m_Controller->view() * shape->transform.model())));

		m_PhongShader->setUniform("u_mvp", m_Controller->projectionView() * shape->transform.model());
		m_PhongShader->setUniform("u_view", m_Controller->view());
		m_PhongShader->setUniform("u_modelView", m_Controller->view() * shape->transform.model());
		m_PhongShader->setUniform("u_normalMat", normalMat);
		_renderer->draw(*shape, *m_PhongShader);
	}


//	m_LightCubeShader->setUniform("u_mvp", m_Controller->projectionView() * m_LightCube->transform.model());
//	_renderer->draw(*m_LightCube, *m_LightCubeShader);
}

void CG::Test::TestDrawMesh::onStop()
{
}

void CG::Test::TestDrawMesh::onReset()
{
	// TODO: reset cam position and rotation.
}

void CG::Test::TestDrawMesh::hotReloadShader(std::unique_ptr<ShaderLoader>& shader, const std::string &shaderPath)
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

	shader->setUniform("u_objectColor", m_ObjectColor);
	for (unsigned int i = 0, x = 0; i < 5; ++i, x += 3) {
		std::string light = "u_lights[" + std::to_string(i) + "].Position";
		m_PhongShader->setUniform(light, glm::vec4(x, 20.f, 0.f, 0.f));
	}

	m_PhongShader->setUniform("u_lights[0].Intensity", glm::vec3(0.0f, 0.8f, 0.8f));
	m_PhongShader->setUniform("u_lights[1].Intensity", glm::vec3(0.0f, 0.0f, 0.8f));
	m_PhongShader->setUniform("u_lights[2].Intensity", glm::vec3(0.8f, 0.0f, 0.0f));
	m_PhongShader->setUniform("u_lights[3].Intensity", glm::vec3(0.0f, 0.8f, 0.0f));
	m_PhongShader->setUniform("u_lights[4].Intensity", glm::vec3(0.8f, 0.8f, 0.8f));
}