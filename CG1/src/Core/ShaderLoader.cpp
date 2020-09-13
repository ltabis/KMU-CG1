// ShaderLoader.hpp
// shader loader class implementation.

#include "ShaderLoader.hpp"

CG::ShaderLoader::ShaderLoader() {}

CG::Shader CG::ShaderLoader::findShader(std::string& line)
{
	for (auto &it : _shaderTypes) {
		std::size_t typeIndex = line.find(it.first);
		if (typeIndex != std::string::npos) {
			line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
			return Shader{ it.second, line.substr(typeIndex + it.first.length() - 1, line.size()) };
		}
	}

	return Shader();
}

std::string CG::ShaderLoader::getShaderSourceCode(std::ifstream& stream, std::string& line)
{
	std::ostringstream sourceCode;

	while (std::getline(stream, line)
		&& line.find("#shader") == std::string::npos)
		sourceCode << line << "\n";
	return sourceCode.str();
}

void CG::ShaderLoader::createShader(std::ifstream& stream, std::string& line)
{
	// creating the shader.
	Shader shader = findShader(line);

	if (shader.type == ShaderType::NONE)
		return;

	// adding the source code.
	shader.source = getShaderSourceCode(stream, line);

	// adding the current shader to the map.
	_shaders.push_back(shader);
}

bool CG::ShaderLoader::load(const std::string& name, const std::string& file)
{
	std::ifstream stream(file);
	std::string line;

	if (!stream.is_open())
		return false;

	return true;
}

bool CG::ShaderLoader::load(const std::string& file)
{
	std::ifstream stream(file);

	if (!stream.is_open())
		return false;

	std::string line;
	std::istream& output = std::getline(stream, line);

	while (output)
		if (line.find("#shader") == std::string::npos)
			std::getline(stream, line);
		else
			createShader(stream, line);
	return true;
}

CG::Shader& CG::ShaderLoader::get(const std::string& name)
{
	for (auto& it : _shaders)
		if (it.name == name)
			return it;
	return _shaders[0];
}
