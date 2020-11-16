#include "TestCameraController.hpp"

CG::Test::TestCameraController::TestCameraController()
	: _fov		  { 90	  }
	, _helpOpened { false }
{
	_cube = std::make_unique<Cube>(
		glm::vec3(0.f, 0.f, -3.f),
		glm::vec3(0.f),
		glm::vec3(1.f)
	);

	_sloader = std::make_unique<ShaderLoader>();

	_sloader->load("./res/shaders/square.shader");
	_sloader->attach("triangle");
	_sloader->attach("color");
	_sloader->createExecutable();
}

CG::Test::TestCameraController::~TestCameraController()
{
}

void CG::Test::TestCameraController::onStart()
{
	if (!_controller.get())
		_controller = std::make_unique<CameraController>(
			_renderer->window(),
			glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.f),
			1.f,
			1.f
		);

	_sloader->setUniform("u_mvp", glm::mat4(1.f));
}

void CG::Test::TestCameraController::onUpdate(float deltaTime)
{
	_controller->update(deltaTime);
}

void CG::Test::TestCameraController::onRender()
{
	ImGui::Begin("Camera Controller");
	// control over the projection matrix.
	if (ImGui::InputFloat("FOV", &_fov, 1)) {
		_controller->setFieldOfView(_fov);
		CG_CONSOLE_INFO("fov set to {}", _fov);
	}
	if (ImGui::InputFloat2("Aspect Ratio", &_aspectRatio[0], 1))
		_controller->setAspectRatio(_aspectRatio.x, _aspectRatio.y);
	if (ImGui::Button("Help"))
		_helpOpened = !_helpOpened;

	if (_helpOpened) {
		ImGui::BeginChild("Tips");
		ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), "How to use the controller.");
		ImGui::Text("Use the mouse to look around.");
		ImGui::Text("Use 'W' 'A' 'S' 'D' to move the camera.");
		ImGui::Text("Use 'Space' and 'Left Shift' to move the camera up or down.");
		ImGui::EndChild();
	}
	ImGui::End();

	glm::mat4 mvp = _controller->view() * _cube->transform.model();
	_sloader->setUniform("u_mvp", mvp);
	_renderer->drawWireFrame(*_cube, *_sloader);
}

void CG::Test::TestCameraController::onStop()
{
}

void CG::Test::TestCameraController::onReset()
{
	// reseting the translation uniform.
	_sloader->setUniform("u_mvp", glm::translate(glm::mat4(1.f), glm::vec3(0.f)));

	// TODO: reset cam position and rotation.
}
