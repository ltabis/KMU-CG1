#include "TestDrawCube.hpp"

CG::Test::TestDrawCube::TestDrawCube()
{
	_vbo = std::make_unique<VertexBuffer>(_cubeVertices, sizeof(_cubeVertices));
	_dataLayout = std::make_unique<VertexArrayLayout>();

	_dataLayout->push<float>(4);
	_dataLayout->push<float>(3);

	_vao = std::make_unique<VertexArray>();
	_vao->addBuffer(*_vbo, *_dataLayout);

	_ibo = std::make_unique<IndexBuffer>(_cubeIndices, sizeof(_cubeIndices));
	_sloader = std::make_unique<ShaderLoader>();

	_sloader->load("./res/shaders/basic.shader");
	_sloader->attach("colored_triangle_vertex");
	_sloader->attach("vertices_colors");
	_sloader->createExecutable();
	_sloader->setUniform("u_projection", glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f));
}

CG::Test::TestDrawCube::~TestDrawCube()
{
}

void CG::Test::TestDrawCube::onStart()
{
}

void CG::Test::TestDrawCube::onUpdate(float deltaTime)
{
}

void CG::Test::TestDrawCube::onRender()
{
	_renderer->draw(*_vao, *_ibo, *_sloader);
}

void CG::Test::TestDrawCube::onStop()
{
}

void CG::Test::TestDrawCube::onReset()
{
}
