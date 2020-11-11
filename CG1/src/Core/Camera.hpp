#pragma once

#include <glm/gtc/matrix_transform.hpp>

namespace CG {
	class Camera
	{
	private:
		glm::mat4 _view;
		glm::mat4 _projection;
		glm::mat4 _mvp;

		glm::vec3 _position;
		glm::vec3 _point;
		glm::vec3 _up;

		float _fov;
		float _aspectRatio;

		void _createViewMatrix();

	public:
		Camera(const glm::vec3& position, const glm::vec3& point, const glm::vec3& up, float fov, float width, float height);
		~Camera();

		void translate(const glm::vec3& translation);
		void rotate(const glm::vec3& position);

		void setPosition();
		void setRotation();

		void setFieldOfView(float fov);
		void setAspectRatio(float width, float height);

		glm::mat4 view() const;
	};
}