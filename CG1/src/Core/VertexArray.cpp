#include "VertexArray.hpp"

CG::VertexArray::VertexArray()
{
	glCreateVertexArrays(1, &_id);
	glBindVertexArray(_id);
}

CG::VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &_id);
}

void CG::VertexArray::addBuffer(const VertexBuffer& vb, const VertexArrayLayout& layout)
{
	const auto& elements = layout.layout();

	// binding the current vertex array.
	bind();

	for (unsigned int i = 0; i < elements.size(); ++i) {

		// binding the current vertex buffer.
		elements[i].reference.bind();

		// specifying that we're adding a new layout element to the array.
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i,
			elements[i].count,
			elements[i].type,
			elements[i].normalized,
			0,
			NULL);
	}
}
