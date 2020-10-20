#pragma once

#include <vector>
#include <GL/glew.h>
#include "VertexBuffer.hpp"

namespace CG
{
	struct VertexBufferElement
	{
		unsigned int type;
		unsigned int count;
		unsigned char normalized;
		const VertexBuffer& reference;
	};

	class VertexArrayLayout
	{
	public:

		VertexArrayLayout()
			: _stride { 0 }
		{}

		template<typename T>
		void push(const VertexBuffer& vbo, unsigned int count)
		{
			(void)vbo;
			(void)count;
			throw "Cannot use this type to create a layout.";
		}

		template<>
		void push<float>(const VertexBuffer& vbo, unsigned int count)
		{
			_layout.push_back(VertexBufferElement{ GL_FLOAT, count, GL_FALSE, vbo });
			_stride += count * sizeof(float);
		}

		template<>
		void push<unsigned int>(const VertexBuffer& vbo, unsigned int count)
		{
			_layout.push_back(VertexBufferElement{ GL_UNSIGNED_INT, count, GL_FALSE, vbo });
			_stride += count * sizeof(unsigned int);
		}

		template<>
		void push<unsigned char>(const VertexBuffer& vbo, unsigned int count)
		{
			_layout.push_back(VertexBufferElement{ GL_UNSIGNED_BYTE, count, GL_FALSE, vbo });
			_stride += count * sizeof(unsigned char);
		}

		inline const std::vector<VertexBufferElement>& layout() const { return _layout; };
		inline size_t stride() const { return _stride; };

	private:
		std::vector<VertexBufferElement> _layout;
		size_t _stride;
	};
}
