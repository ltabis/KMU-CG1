#pragma once

#include <GL/glew.h>
#include <string>

#include "stb_image.hpp"

namespace CG
{
	class Texture
	{
	public:
		Texture(const std::string &filePath);
		~Texture();

		void bind(unsigned int slot = 0) const;
		void unbind() const;
	private:
		unsigned int m_Id;

		unsigned char* m_Buffer;

		std::string m_FilePath;
		int m_Width;
		int m_Height;
		int m_BytePerPixel;
	};
}