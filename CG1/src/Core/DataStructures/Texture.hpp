#pragma once

#include <GL/glew.h>
#include <string>

#include "Logger.hpp"
#include "stb_image.hpp"

namespace CG
{
	class Texture
	{
	public:
		Texture(const std::string &filePath, const std::string &type);
		~Texture();

		bool loadTexture(const std::string &filePath, unsigned int slot = 0);

		void bind(unsigned int slot = 0) const;
		void unbind() const;

		inline std::string type() const { return m_Type; };
	private:

		unsigned int m_Id;
		unsigned char* m_Buffer;

		std::string m_FilePath;
		std::string m_Type;
		int m_Width;
		int m_Height;
		int m_BytePerPixel;
	};
}