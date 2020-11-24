#pragma once

#include "Framework/ATest.hpp"
#include "WorldObjects/Primitives/Triangle.hpp"
#include "WorldObjects/Complex/Cube.hpp"
#include "NoClipCameraController.hpp"

// vendor.
#include "../Dependencies/models/Sphere.hpp"
#include "../Dependencies/models/vboteapot.hpp"

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

			void hotReloadShader(std::unique_ptr<ShaderLoader>& shader, const std::string &shaderPath);

		private:
			std::vector<std::unique_ptr<AShape>> m_Triangles;

			// TODO: implemente a debug light vizualiser.
			std::unique_ptr<AShape> m_LightCube;
			std::unique_ptr<AShape> m_Sphere;
			std::unique_ptr<AShape> m_TeaPot;
			std::unique_ptr<ShaderLoader> m_PhongShader;
			std::unique_ptr<ShaderLoader> m_LightCubeShader;

			std::unique_ptr<NoClipCameraController> m_Controller;

			float m_Fov;
			bool m_HelpOpened;
			bool m_ControllerFreeze;
			bool m_FpsMode;

			glm::vec3 m_AmbiantLightColor;
			glm::vec3 m_ObjectColor;
			glm::vec3 m_LightPos;

			glm::vec2 m_AspectRatio;
		};
	}
}