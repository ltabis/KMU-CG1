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
		CG::Camera _camera;

		float _sensitivity = 0.1f;
		float _lastMouseXPosition = 0;
		float _lastMouseYPosition = 0;

		bool _firstMousePosition = true;

		float _pitch = 0.f;
		float _yaw = 0.f;
		// Not really needed, but would be cool to implement.
		float _roll = 0.f;

		void _computeCameraTranslation(float deltaTime);
		void _computeCameraRotation(float deltaTime);
	};
}