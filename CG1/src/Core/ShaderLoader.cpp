// ShaderLoader.hpp
// shader loader class implementation.

#include "ShaderLoader.hpp"

CG::ShaderLoader::ShaderLoader() {}

/* parses the header line of a shader and create a shader. */
CG::Shader CG::ShaderLoader::findShader(std::string& line)
{
	for (auto& it : _shaderTypes) {
		std::size_t typeIndex = line.find(it.first);
		if (typeIndex != std::string::npos) {
			line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
			return Shader{ it.second, line.substr(typeIndex + it.first.length() - 1, line.size()) };
		}
	}

	return Shader();
}

/* fetch the shader source code and returns it. */
std::string CG::ShaderLoader::getShaderSourceCode(std::ifstream& stream, std::string& line)
{
	std::ostringstream sourceCode;

	while (std::getline(stream, line)
		&& line.find("#shader") == std::string::npos)
		sourceCode << line << "\n";
	return sourceCode.str();
}

/* create a shader and adds it to the shader pool. */
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

/* public api, load a shader by its name and file. */
bool CG::ShaderLoader::load(const std::string& name, const std::string& file)
{
	std::ifstream stream(file);

	if (!stream.is_open())
		return false;

	std::string line;
	std::istream& output = std::getline(stream, line);

	while (output)
		if (line.find("#shader") != std::string::npos
			&& line.find(name) != std::string::npos) {
			createShader(stream, line);
			return true;
		}
		else
			std::getline(stream, line);
	return false;
}

/* public api, load all shaders from a file. */
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

/* unload a shader from the shader pool. */
void CG::ShaderLoader::unload(const std::string& name)
{
	for (auto it = _shaders.begin(); it != _shaders.end(); ++it)
		if ((*it).name == name) {
			_shaders.erase(it);
			return;
		}
}

/* get a shader object from its name. */
CG::Shader& CG::ShaderLoader::get(const std::string& name)
{
	for (auto& it : _shaders)
		if (it.name == name)
			return it;
	return _shaders[0];
}
