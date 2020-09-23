#pragma once

#include <GL/glew.h>

namespace CG
{
class VertexBuffer
{
public:
	VertexBuffer(const void *data, unsigned int size);
	~VertexBuffer();

	void bind();
	void unbind();
private:
	unsigned int _id;
};
}