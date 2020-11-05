#pragma once

#include <stack>
#include <glm/gtc/matrix_transform.hpp>

class MatrixStack
{
private:
	std::stack<glm::mat4> _stack;
public:

	MatrixStack();
	~MatrixStack() = default;

	void translate(float x, float y, float z);
	void rotate(float degree, float x, float y, float z);
	void scale(float x, float y, float z);

	void push();
	void pop();
	const glm::mat4 &get() const;
};