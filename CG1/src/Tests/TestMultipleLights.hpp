#pragma once

#include "Framework/ATest.hpp"
#include "WorldObjects/Primitives/Triangle.hpp"
#include "WorldObjects/Complex/Model.hpp"
#include "WorldObjects/Complex/Cube.hpp"
#include "NoClipCameraController.hpp"

#include "../Dependencies/models/vbotorus.hpp"

namespace CG {
	namespace Test {
		class TestMultipleLights : public ATest
		{
		public:
			TestMultipleLights();
			~TestMultipleLights() = default;

			void onStart() override;
			void onUpdate(float deltaTime) override;
			void onRender() override;
			void onStop() override;
			void onReset() override;

			void hotReloadShader(std::unique_ptr<ShaderLoader>& shader, const std::string &shaderPath);

		private:
			void updateLightPosInShader();

			std::vector<std::unique_ptr<AShape>> m_Shapes;
			std::vector<std::pair<glm::vec3, std::unique_ptr<AShape>>> m_Lights;

			std::unique_ptr<ShaderLoader> m_PhongShader;
			std::unique_ptr<ShaderLoader> m_LightCubeShader;

			std::unique_ptr<NoClipCameraController> m_Controller;

			float m_Fov;
			float m_AngleOffset;
			bool m_HelpOpened;
			bool m_ControllerFreeze;
			bool m_FpsMode;

			glm::vec3 m_ObjectColor;

			glm::vec2 m_AspectRatio;
		};
	}
}