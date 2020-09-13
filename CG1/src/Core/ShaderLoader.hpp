// ShaderLoader.hpp
// a class that will load shaders from a file.

#pragma once

#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

namespace CG {

	enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };

	struct Shader
	{
		Shader(const ShaderType& type = ShaderType::NONE, const std::string& name = "")
			: type{ type }
			, name{ name }
			, source{ "" } {}

		Shader(const ShaderType& type, const std::string& name, const std::string& source)
			: type{ type }
			, name{ name }
			, source{ source } {}

		ShaderType type;
		std::string name;
		std::string source;
	};

	class ShaderLoader
	{
	private:
		std::vector<Shader> _shaders
		{
			Shader(),
		};
		std::unordered_map<std::string, ShaderType> _shaderTypes
		{
			{ "VERTEX",   ShaderType::VERTEX },
			{ "FRAGMENT", ShaderType::FRAGMENT }
		};

		Shader findShader(std::string& line);
		void createShader(std::ifstream& stream, std::string& line);
		std::string getShaderSourceCode(std::ifstream& stream, std::string& line);

	public:
		ShaderLoader();

		bool load(const std::string& name, const std::string& file);
		bool load(const std::string& file);
		void unload(const std::string& name);
		Shader& get(const std::string& name);
	};
}

