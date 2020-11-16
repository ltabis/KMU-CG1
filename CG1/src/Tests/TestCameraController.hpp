#pragma once

#include "Framework/ATest.hpp"
#include "WorldObjects/Complex/Cube.hpp"
#include "CameraController.hpp"

namespace CG {
	namespace Test {
		class TestCameraController : public ATest
		{
		public:
			TestCameraController();
			~TestCameraController();

			void onStart() override;
			void onUpdate(float deltaTime) override;
			void onRender() override;
			void onStop() override;
			void onReset() override;

		private:
			std::unique_ptr<ShaderLoader> _sloader;
			std::unique_ptr<AShape> _cube;

			std::unique_ptr<CameraController> _controller;

			float _fov;
			bool _helpOpened;
			glm::vec2 _aspectRatio;
		};
	}
}