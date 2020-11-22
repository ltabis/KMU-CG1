#pragma once

#include "Framework/ATest.hpp"
#include "WorldObjects/Primitives/Triangle.hpp"
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
			std::vector<std::unique_ptr<AShape>> m_Triangles;

			std::unique_ptr<NoClipCameraController> m_Controller;

			float m_Fov;
			bool m_HelpOpened;
			bool m_ControllerFreeze;
			bool m_FpsMode;

			glm::vec3 m_AmbiantLightColor;
			glm::vec3 m_AmbiantObjectColor;
			glm::vec3 m_lightPos;

			glm::vec2 m_AspectRatio;
		};
	}
}