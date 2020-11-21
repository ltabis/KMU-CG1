#pragma once

#include "Framework/ATest.hpp"
#include "WorldObjects/Complex/Cube.hpp"
#include "NoClipCameraController.hpp"

namespace CG {
	namespace Test {
		class TestShaderEditor : public ATest
		{
		public:
			TestShaderEditor();
			~TestShaderEditor();

			void onStart() override;
			void onUpdate(float deltaTime) override;
			void onRender() override;
			void onStop() override;
			void onReset() override;

			void hotReloadShader(ShaderLoader &shader);

		private:
			std::unique_ptr<ShaderLoader> m_Sloader;
			std::unique_ptr<AShape> m_Cube;

			std::unique_ptr<NoClipCameraController> m_Controller;

			float m_Fov;
			bool m_HelpOpened;
			bool m_FpsMode;
			glm::vec2 m_AspectRatio;
		};
	}
}