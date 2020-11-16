// main.cpp
// Application entry point.

#include <glm/gtx/string_cast.hpp>

#include "Callbacks.hpp"
#include "Profiling/Breakpoint.hpp"
#include "Tests/TestBackgroundColorChange.hpp"
#include "Tests/TestShapeAbstraction.hpp"
#include "Tests/TestShapeSpawner.hpp"
#include "Tests/TestDrawTriangle.hpp"
#include "Tests/TestDrawCube.hpp"
#include "Tests/TestCamera.hpp"
#include "Tests/TestNoClipCameraController.hpp"
#include "Tests/Framework/TestMenu.hpp"

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
	menu.registerTest<CG::Test::TestDrawCube>("Draw a colored cube");
	menu.registerTest<CG::Test::TestShapeAbstraction>("Draw a colored plane from shape abstraction");
	menu.registerTest<CG::Test::TestShapeSpawner>("Spawn multiple shapes");
	menu.registerTest<CG::Test::TestCamera>("Test a camera transformation");
	menu.registerTest<CG::Test::TestNoClipCameraController>("Camera controller");

	while (!renderer->windowShouldClose())
		menu.onRender();

	return 0;
}