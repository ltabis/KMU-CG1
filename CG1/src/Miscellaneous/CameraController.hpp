#pragma once

#include "Camera.hpp"
#include "Renderer.hpp"

namespace CG {
	class CameraController
	{
	public:

		CameraController(
			GLFWwindow* _window,
			const glm::vec3& position,
			const glm::vec3& point,
			float speed,
			float sensibility
		);
		~CameraController();

		void update(float deltaTime);
		glm::mat4 view() const;

		float speed;
		float sensibility;

	private:

		Camera _camera;
		GLFWwindow* _window;

		float _pitch;
		float _yaw;
		float _roll;
	};
}