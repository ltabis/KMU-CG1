// main.cpp
// Application entry point.

#include <glm/gtx/string_cast.hpp>

#include "Callbacks.hpp"
#include "Profiling/Breakpoint.hpp"
#include "Tests/Framework/TestMenu.hpp"
#include "Tests/TestMultipleLights.hpp"
#include "Tests/TestShaderEditor.hpp"
#include "Tests/TestDrawMesh.hpp"
#include "Tests/TestDrawTexture.hpp"
#include "Tests/TestDrawSimpleTexture.hpp"

int main(void)
{
	CG::Logger::Init();

	std::shared_ptr<CG::Renderer> renderer = std::make_shared<CG::Renderer>("Test framework", 1920, 1080);
	std::shared_ptr<CG::GUI> gui = std::make_shared<CG::GUI>(renderer->window(), CG::GUI::Style::DARK);
	CG::Test::TestMenu menu(renderer, gui);

	renderer->registerKeyBindingCallback(GLFW_KEY_ESCAPE, escape_callback);
	renderer->registerKeyBindingCallback(GLFW_KEY_SPACE, spacebar_callback);

	menu.registerTest<CG::Test::TestShaderEditor>("Shader Editor");
	menu.registerTest<CG::Test::TestDrawMesh>("Draw meshes");
	menu.registerTest<CG::Test::TestMultipleLights>("Display multiple lights");
	menu.registerTest<CG::Test::TestDrawTexture>("Draw textures on models");
	menu.registerTest<CG::Test::TestDrawSimpleTexture>("Draw textures");

	while (!renderer->windowShouldClose())
		menu.onRender();

	return 0;
}