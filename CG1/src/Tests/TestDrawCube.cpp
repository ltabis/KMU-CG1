#include "TestDrawCube.hpp"

CG::Test::TestDrawCube::TestDrawCube()
	: _rotation    { glm::vec3(0.f) }
	, _translation { glm::vec3(0.f) }
	, _scale       { glm::vec3(1.f) }
	, _fov         { 45             }
{
	_vbo = std::make_unique<VertexBuffer>(_cubeVertices, sizeof(_cubeVertices));
	_dataLayout = std::make_unique<VertexArrayLayout>();

	_dataLayout->push<float>(4);
	_dataLayout->push<float>(3);

	_vao = std::make_unique<VertexArray>();
	_vao->addBuffer(*_vbo, *_dataLayout);

	_ibo = std::make_unique<IndexBuffer>(_cubeIndices, sizeof(_cubeIndices));
	_sloader = std::make_unique<ShaderLoader>();

	_sloader->load("./res/shaders/square.shader");
	_sloader->attach("triangle");
	_sloader->attach("color");
	_sloader->createExecutable();
}

CG::Test::TestDrawCube::~TestDrawCube()
{
}

void CG::Test::TestDrawCube::onStart()
{
	_sloader->setUniform("u_model", glm::mat4(1.f));
	_sloader->setUniform("u_view", _renderer->viewMatrix());
	_sloader->setUniform("u_projection", _renderer->projectionMatrix());
}

void CG::Test::TestDrawCube::onUpdate(float deltaTime)
{
	_renderer->pollEvents();
}

void CG::Test::TestDrawCube::onRender()
{
	ImGui::Begin("Cube Rotation");
	glm::mat4 model = glm::mat4(1.f);

	if (ImGui::SliderFloat("FOV", &_fov, 45, 120, "%.1f")) {
		CG_CONSOLE_INFO("fov: {}", _fov);
		_renderer->setFov(_fov);
		_sloader->setUniform("u_projection", _renderer->projectionMatrix());
	}
	ImGui::SliderFloat3("translation", &_translation[0], -10, 10, "%.1f");
	ImGui::SliderFloat3("rotation", &_rotation[0], 0, 360, "%.1f");
	ImGui::SliderFloat3("scale", &_scale[0], 1, 100, "%.1f");

	_scale = glm::clamp(_scale, glm::vec3(1, 1, 1), glm::vec3(100, 100, 100));

	ImGui::End();

	model *= glm::translate(model, glm::vec3(_translation[0], _translation[1], _translation[2]));
	model *= glm::scale(glm::mat4(1.f), glm::vec3(_scale[0], _scale[1], _scale[2]));

	model *= glm::rotate(glm::mat4(1.f), glm::radians(_rotation[0]), glm::vec3(1, 0, 0))
		   * glm::rotate(glm::mat4(1.f), glm::radians(_rotation[1]), glm::vec3(0, 1, 0))
		   * glm::rotate(glm::mat4(1.f), glm::radians(_rotation[2]), glm::vec3(0, 0, 1));

	if (model != glm::mat4(1.f))
		_sloader->setUniform("u_model", model);

	_renderer->draw(*_vao, *_ibo, *_sloader);
}

void CG::Test::TestDrawCube::onStop()
{
}

void CG::Test::TestDrawCube::onReset()
{
	// reseting the translation uniform.
	_sloader->setUniform("u_model", glm::translate(glm::mat4(1.f), glm::vec3(0.f)));
	
	// reseting transform.
	_translation = glm::vec3(0.f);
	_rotation = glm::vec3(0.f);
	_scale = glm::vec3(1.f);
}
