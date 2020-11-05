#include "MatrixStack.hpp"

MatrixStack::MatrixStack()
	: _translation { glm::mat4(1.f)                             }
	, _rotation    { glm::mat4(1.f)                             }
	, _scale       { glm::scale(glm::mat4(1.f), glm::vec3(1.f)) }
{
	_stack.push(glm::mat4(1.f));
}

void MatrixStack::translate(float x, float y, float z)
{
	_stack.top() *= glm::translate(glm::mat4(1.f), glm::vec3(x, y, z));
	_translation *= glm::translate(glm::mat4(1.f), glm::vec3(x, y, z));
}

void MatrixStack::rotate(float degree, float x, float y, float z)
{
	_stack.top() *= glm::rotate(glm::mat4(1.f), glm::radians(degree), glm::vec3(x, y, z));
	_rotation *= glm::rotate(glm::mat4(1.f), glm::radians(degree), glm::vec3(x, y, z));
}

void MatrixStack::scale(float x, float y, float z)
{
	_stack.top() *= glm::scale(glm::mat4(1.f), glm::vec3(x, y, z));
	_scale *= glm::scale(glm::mat4(1.f), glm::vec3(x, y, z));
}

void MatrixStack::setPosition(float x, float y, float z)
{
	_translation = glm::translate(glm::mat4(1.f), glm::vec3(x, y, z));
	_stack.top() = _translation * _scale * _rotation;
}

void MatrixStack::setRotation(float anglex, float angley, float anglez, const glm::mat4& pivot)
{
	_rotation =
		  glm::rotate(glm::mat4(1.f), glm::radians(anglex), glm::vec3(pivot[0][0], pivot[0][1], pivot[0][2]))
		* glm::rotate(glm::mat4(1.f), glm::radians(angley), glm::vec3(pivot[1][0], pivot[1][1], pivot[1][2]))
		* glm::rotate(glm::mat4(1.f), glm::radians(anglez), glm::vec3(pivot[2][0], pivot[2][1], pivot[2][2]));
	_stack.top() = _translation * _scale * _rotation;
}

void MatrixStack::setScale(float x, float y, float z)
{
	_scale = glm::scale(glm::mat4(1.f), glm::vec3(x, y, z));
	_stack.top() = _translation * _scale * _rotation;
}

void MatrixStack::push()
{
	_stack.push(get());
}

void MatrixStack::pop()
{
	if (_stack.size() != 1)
		_stack.pop();
}

void MatrixStack::reset()
{
	while (_stack.size() != 1)
		pop();
}

const glm::mat4& MatrixStack::get() const
{
	return _stack.top();
}