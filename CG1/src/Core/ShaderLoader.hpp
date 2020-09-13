// ShaderLoader.hpp
// a class that will load shaders from a file.

#pragma once

#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

namespace CG {

	enum ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };

	struct Shader
	{
		Shader(const ShaderType &type = NONE, const std::string &name = "")
			: type   { type }
			, name   { name }
			, source { ""   } {}

		Shader(const ShaderType& type, const std::string &name, const std::string &source)
			: type   { type   }
			, name   { name   }
			, source { source } {}

		ShaderType type;
		std::string name;
		std::string source;
	};

	class ShaderLoader
	{
		private:
			std::string _folder;
			std::vector<Shader> _shaders
			{
				Shader(),
			};
			std::unordered_map<std::string, ShaderType> _shaderTypes
			{
				{ "VERTEX", VERTEX },
				{ "FRAGMENT", FRAGMENT }
			};

			Shader findShader(std::string& line);
			void pushShader(std::string &line, std::string &currentDirective, std::ostringstream &currentSrc, Shader &currentShader);

		public:
			ShaderLoader();
			ShaderLoader(const std::string& path);

			bool load(const std::string &name, const std::string &file);
			bool load(const std::string &file);
			Shader &get(const std::string &name);
	};
}

