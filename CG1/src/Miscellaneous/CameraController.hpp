#pragma once

#include "Camera.hpp"
#include "Renderer.hpp"

namespace CG {
	class CameraController
	{
	public:

		CameraController(
			GLFWwindow* _window,
			const glm::vec3& position = glm::vec3(0.f),
			const glm::vec3& point = glm::vec3(0.f),
			float speed = 1.f,
			float sensitivity = .1f
		);
		~CameraController();

		void setFieldOfView(float fov);
		void setAspectRatio(float width, float height);
		void update(float deltaTime);
		glm::mat4 view() const;

		float speed;

	private:

		GLFWwindow* _window;

		void _computeCameraTranslation(float deltaTime);
	};
}