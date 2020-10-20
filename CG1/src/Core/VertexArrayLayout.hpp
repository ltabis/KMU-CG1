#pragma once

#include <vector>
#include <GL/glew.h>

namespace CG
{
	struct VertexBufferElement
	{
		unsigned int type;
		unsigned int count;
		unsigned char normalized;
	};

	class VertexArrayLayout
	{
	public:
		template<typename T>
		void push(unsigned int count)
		{
			throw "Cannot use this type to create a layout.";
		}

		template<>
		void push<float>(unsigned int count)
		{
			_layout.push_back(VertexBufferElement{ GL_FLOAT, count, GL_FALSE });
			_stride += count * sizeof(float);
		}

		template<>
		void push<unsigned int>(unsigned int count)
		{
			_layout.push_back(VertexBufferElement{ GL_UNSIGNED_INT, count, GL_FALSE });
			_stride += count * sizeof(unsigned int);
		}

		template<>
		void push<unsigned char>(unsigned int count)
		{
			_layout.push_back(VertexBufferElement{ GL_UNSIGNED_BYTE, count, GL_FALSE });
			_stride += count * sizeof(unsigned char);
		}

		inline const std::vector<VertexBufferElement>& layout() const { return _layout; };
		inline size_t stride() const { return _stride; };

	private:
		std::vector<VertexBufferElement> _layout;
		size_t _stride;
	};
}
