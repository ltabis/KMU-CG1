#include "MatrixStack.hpp"

MatrixStack::MatrixStack()
{
	_stack.push(glm::mat4(1.f));
}

void MatrixStack::translate(float x, float y, float z)
{
	_stack.top() = glm::translate(_stack.top(), glm::vec3(x, y, z));
}

void MatrixStack::rotate(float degree, float x, float y, float z)
{
	_stack.top() = glm::rotate(_stack.top(), glm::radians(degree), glm::vec3(x, y, z));
}

void MatrixStack::scale(float x, float y, float z)
{
	_stack.top() = glm::scale(_stack.top(), glm::vec3(x, y, z));
}

void MatrixStack::push()
{
	_stack.push(_stack.top());
}

void MatrixStack::pop()
{
	if (_stack.size() != 1)
		_stack.push(_stack.top());
}

const glm::mat4& MatrixStack::get() const
{
	return _stack.top();
}