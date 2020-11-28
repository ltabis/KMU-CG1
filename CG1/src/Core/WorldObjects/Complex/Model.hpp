#pragma once

#include "WorldObjects/Primitives/Mesh.hpp"

namespace CG {
	class Model
	{
	private:
		std::vector<Mesh> m_Meshes;
	public:
		Model(const std::string &filePath, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
		~Model();

		Transform transform;
	};
}