// main.cpp
// Application entry point.

#include <glm/gtx/string_cast.hpp>

#include "Callbacks.hpp"
#include "Profiling/Breakpoint.hpp"
#include "Tests/TestBackgroundColorChange.hpp"
#include "Tests/TestShapeSpawner.hpp"
#include "Tests/TestDrawTriangle.hpp"
#include "Tests/TestCamera.hpp"
#include "Tests/TestNoClipCameraController.hpp"
#include "Tests/Framework/TestMenu.hpp"
#include "Tests/TestShaderEditor.hpp"
#include "Tests/TestDrawMesh.hpp"

int main(void)
{
	CG::Logger::Init();

	std::shared_ptr<CG::Renderer> renderer = std::make_shared<CG::Renderer>("Test framework", 1920, 1080);
	std::shared_ptr<CG::GUI> gui = std::make_shared<CG::GUI>(renderer->window(), CG::GUI::Style::DARK);
	CG::Test::TestMenu menu(renderer, gui);

	renderer->registerKeyBindingCallback(GLFW_KEY_ESCAPE, escape_callback);
	renderer->registerKeyBindingCallback(GLFW_KEY_SPACE, spacebar_callback);

	menu.registerTest<CG::Test::TestBackgroundColorChange>("Change color of background");
	menu.registerTest<CG::Test::TestDrawTriangle>("Display a single colored triangle");
	menu.registerTest<CG::Test::TestShapeSpawner>("Spawn multiple shapes");
	menu.registerTest<CG::Test::TestCamera>("Test a camera transformation");
	menu.registerTest<CG::Test::TestNoClipCameraController>("Camera controller");
	menu.registerTest<CG::Test::TestShaderEditor>("Shader Editor");
	menu.registerTest<CG::Test::TestDrawMesh>("Draw mesh");

	while (!renderer->windowShouldClose())
		menu.onRender();

	return 0;
}