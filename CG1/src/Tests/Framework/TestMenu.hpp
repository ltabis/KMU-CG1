#pragma once

#include "ATest.hpp"

namespace CG {
	namespace Test {
		class TestMenu
		{
		public:
			TestMenu(std::shared_ptr<Renderer> &renderer, std::shared_ptr <GUI> gui);
			~TestMenu();
			void onRender();

			template<typename T>
			void registerTest(const std::string& testName)
			{
				if (testName == "")
					return;

				if (_tests.find(testName) == _tests.end()) {
					_tests.emplace(testName, std::make_pair(std::make_unique<T>(), false));
					_tests[testName].first->onInit(_renderer);
				}
			}
		private:

			float _deltaTime;
			float _lastFrame;

			std::unordered_map<std::string, std::pair<std::unique_ptr<ATest>, bool>> _tests;
			std::string _currentTest;
			std::shared_ptr<Renderer> _renderer;
			std::shared_ptr<GUI> _gui;
		};
	}
}