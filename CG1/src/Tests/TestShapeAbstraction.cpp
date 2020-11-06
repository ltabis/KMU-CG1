#include "TestShapeAbstraction.hpp"

CG::Test::TestShapeAbstraction::TestShapeAbstraction()
	: _fov { 45 }
{
	_sloader = std::make_unique<ShaderLoader>();

	_sloader->load("./res/shaders/square.shader");
	_sloader->attach("triangle");
	_sloader->attach("color");
	_sloader->createExecutable();

	_plane = std::make_unique<Plane>(
		glm::vec3(0.f),
		glm::vec3(0.f),
		glm::vec3(1.f)
	);
}

CG::Test::TestShapeAbstraction::~TestShapeAbstraction()
{
}

void CG::Test::TestShapeAbstraction::onStart()
{
}

void CG::Test::TestShapeAbstraction::onUpdate(float deltaTime)
{
	_renderer->pollEvents();
}

void CG::Test::TestShapeAbstraction::onRender()
{
	ImGui::Begin("Projection transformation");
	// control over the projection matrix.
	if (ImGui::SliderFloat("FOV", &_fov, 45, 120, "%.1f"))
		_renderer->setFov(_fov);
	ImGui::End();

	glm::mat4 mvp = _renderer->projectionMatrix() * _renderer->viewMatrix() * glm::mat4(1.f);
	_sloader->setUniform("u_mvp", mvp);
	_renderer->draw(*_plane, *_sloader);
}

void CG::Test::TestShapeAbstraction::onStop()
{
}

void CG::Test::TestShapeAbstraction::onReset()
{
	// reseting the translation uniform.
	_sloader->setUniform("u_mvp", glm::mat4(1.f));
}
