#pragma once

#include "Framework/ATest.hpp"
#include "WorldObjects/Primitives/Triangle.hpp"
#include "WorldObjects/Complex/Model.hpp"
#include "WorldObjects/Complex/Cube.hpp"
#include "NoClipCameraController.hpp"

#include "../Dependencies/models/vbotorus.hpp"

namespace CG {
	namespace Test {
		class TestDrawTexture : public ATest
		{
		public:
			TestDrawTexture();
			~TestDrawTexture() = default;

			void onStart() override;
			void onUpdate(float deltaTime) override;
			void onRender() override;
			void onStop() override;
			void onReset() override;

			void hotReloadShader(std::unique_ptr<ShaderLoader>& shader, const std::string &shaderPath);

		private:
			std::vector<std::unique_ptr<Model>> m_Models;

			std::unique_ptr<AShape> m_LightCube;
			std::unique_ptr<ShaderLoader> m_PhongShader;
			std::unique_ptr<ShaderLoader> m_LightCubeShader;

			std::unique_ptr<NoClipCameraController> m_Controller;

			float m_Fov;
			bool m_HelpOpened;
			bool m_ControllerFreeze;
			bool m_FpsMode;

			glm::vec3 m_ObjectColor;
			glm::vec3 m_LightPos;
			glm::vec3 m_AmbiantLightColor;

			glm::vec2 m_AspectRatio;
		};
	}
}