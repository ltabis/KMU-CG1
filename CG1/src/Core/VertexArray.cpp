#include "VertexArray.hpp"

CG::VertexArray::VertexArray()
{
	glCreateVertexArrays(1, &_id);
	glBindBuffer(GL_ARRAY_BUFFER, _id);
}

CG::VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &_id);
}

void CG::VertexArray::addBuffer(const VertexBuffer& vb, const VertexArrayLayout& layout)
{
	bind();
	vb.bind();

	const auto& elements = layout.layout();
	for (size_t i = 0; i < elements.size(); ++i) {
		unsigned int offset = elements[i].count * elements[i].type;
		// specifying that we're adding a new layout element to the array.
		glEnableVertexAttribArray(i);

		glVertexAttribPointer(i,
			elements[i].count,
			elements[i].type,
			elements[i].normalized,
			layout.stride(),
			(const void*)offset);
	}
}
