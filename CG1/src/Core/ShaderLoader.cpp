// ShaderLoader.hpp
// shader loader class implementation.

#include "ShaderLoader.hpp"

CG::ShaderLoader::ShaderLoader()
	: _folder  { "./" }
{}

CG::ShaderLoader::ShaderLoader(const std::string& path)
	: _folder { !std::filesystem::exists(path) ? "./" : path }
{}

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

void CG::ShaderLoader::pushShader(std::string &line, std::string &currentDirective, std::ostringstream &currentSrc, Shader &currentShader)
{
	// adding the current shader to the map.
	if (currentShader.type != ShaderType::NONE) {
		currentShader.source = currentSrc.str();
		_shaders.push_back(currentShader);
	}

	// clearing data and changing directive.
	currentSrc.str("");
	currentDirective = line;
	currentShader = findShader(line);
}

bool CG::ShaderLoader::load(const std::string &file)
{
	std::ifstream stream(_folder + "/" +  file);

	if (!stream.is_open())
		return false;

	std::ostringstream currentSrc;
	std::string currentDirective;
	Shader currentShader;
	std::string line;

	while (std::getline(stream, line)) {

		// finding the #shader directive.
		std::size_t index = line.find("#shader");

		if (index != std::string::npos)
			pushShader(line, currentDirective, currentSrc, currentShader);
		else
			currentSrc << line << "\n";
	}
	pushShader(line, currentDirective, currentSrc, currentShader);
	return true;
}

#include <iostream>

CG::Shader &CG::ShaderLoader::get(const std::string &name)
{
	for (auto& it : _shaders) {
		std::cout << it.name << std::endl;
		if (it.name == name)
			return it;
	}
	return _shaders[0];
}
