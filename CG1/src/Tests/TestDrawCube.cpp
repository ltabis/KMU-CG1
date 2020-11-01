#include "TestDrawCube.hpp"

CG::Test::TestDrawCube::TestDrawCube()
	: _rotation { 0 }
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
	_sloader->setUniform("u_mvp", glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f));
	_sloader->setUniform("u_translation", glm::translate(glm::mat4(1.f), glm::vec3(0.f)));
}

CG::Test::TestDrawCube::~TestDrawCube()
{
}

void CG::Test::TestDrawCube::onStart()
{
}

void CG::Test::TestDrawCube::onUpdate(float deltaTime)
{
	_renderer->pollEvents();
}

void CG::Test::TestDrawCube::onRender()
{
	ImGui::Begin("Cube Rotation");

	// translating if the UI if updated.
	if (ImGui::SliderFloat3("translation", _translation, -1, 1)) {
		auto translation = glm::translate(glm::mat4(1.f), glm::vec3(_translation[0], _translation[1], 1));
		_sloader->setUniform("u_translation", translation);
	}

	ImGui::SliderFloat3("rotation", _rotation, 0, 360);
	ImGui::SliderFloat3("scale", _scale, 0, 360);
	ImGui::End();

	_renderer->draw(*_vao, *_ibo, *_sloader);
}

void CG::Test::TestDrawCube::onStop()
{
}

void CG::Test::TestDrawCube::onReset()
{
	// reseting the translation uniform.
	_sloader->setUniform("u_translation", glm::translate(glm::mat4(1.f), glm::vec3(0.f)));
	
	// reseting transform.
	std::memset(_rotation, 0, sizeof(_rotation));
	std::memset(_scale, 0, sizeof(_scale));
	std::memset(_translation, 0, sizeof(_translation));
}
