#pragma once

#include "Framework/ATest.hpp"
#include "NoClipCameraController.hpp"
#include "WorldObjects/Primitives/Plane.hpp"
#include "WorldObjects/Primitives/Mesh.hpp"
#include "DataStructures/Texture.hpp"

namespace CG {
	namespace Test {
		class TestDrawSimpleTexture : public ATest
		{
		public:
			TestDrawSimpleTexture();
			~TestDrawSimpleTexture() = default;

			void onStart() override;
			void onUpdate(float deltaTime) override;
			void onRender() override;
			void onStop() override;
			void onReset() override;

			void hotReloadShader(std::unique_ptr<ShaderLoader>& shader, const std::string &shaderPath);

		private:
			std::unique_ptr<Texture> m_PlaneTexture;

			float m_Vertices[36] = {
				-0.5f, -0.5f, 0.0f, 1.0f,    0.0f,  0.0f, 1.0f,    0.0f,  0.0f,
				 0.5f, -0.5f, 0.0f, 1.0f,    0.0f,  0.0f, 1.0f,    1.0f,  0.0f,
				 0.5f,  0.5f, 0.0f, 1.0f,    0.0f,  0.0f, 1.0f,    1.0f,  1.0f,
				-0.5f,  0.5f, 0.0f, 1.0f,    0.0f,  0.0f, 1.0f,    0.0f,  1.0f
			};

			unsigned int m_Indices[6] = {
				0, 1, 2,
				2, 3, 0
			};

			std::vector<Vertex> m_VerticesVector;
			std::vector<Texture> m_TextureVector;
			std::vector<unsigned int> m_IndexVector;
			std::unique_ptr<Mesh> m_Mesh;

			std::unique_ptr<VertexBuffer> _vbo;
			std::unique_ptr<VertexArray> _vao;
			std::unique_ptr<VertexArrayLayout> _valo;
			std::unique_ptr<IndexBuffer> _ibo;

			std::unique_ptr<ShaderLoader> m_PhongShader;

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