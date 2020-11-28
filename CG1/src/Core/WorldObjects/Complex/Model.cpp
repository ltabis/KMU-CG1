#include "Model.hpp"

CG::Model::Model(const std::string &filePath, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	transform = Transform(position, rotation, scale);
}

CG::Model::~Model()
{
}
