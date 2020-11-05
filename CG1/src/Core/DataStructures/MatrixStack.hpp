#pragma once

#include <stack>
#include <glm/gtc/matrix_transform.hpp>

class MatrixStack
{
private:
	std::stack<glm::mat4> _stack;

	glm::mat4 _translation;
	glm::mat4 _rotation;
	glm::mat4 _scale;
public:

	MatrixStack();
	~MatrixStack() = default;

	void translate(float x, float y, float z);
	void rotate(float degree, float x, float y, float z);
	void scale(float x, float y, float z);

	void setPosition(float x, float y, float z);
	void setRotation(float anglex, float angley, float anglez, const glm::mat4& pivot);
	void setScale(float x, float y, float z);

	void push();
	void pop();
	void reset();
	const glm::mat4 &get() const;
};