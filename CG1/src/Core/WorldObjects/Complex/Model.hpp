#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "WorldObjects/Primitives/Mesh.hpp"

namespace CG {
	class Model
	{
	private:
		std::vector<std::unique_ptr<AShape>> m_Meshes;
		std::string m_ModelPath;

		void loadModel(const aiScene* scene);
		void createMesh(const aiScene* scene, unsigned int meshIndex);
	public:
		Model(const std::string & modelPath, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
		~Model();

		inline const std::vector<std::unique_ptr<AShape>>& meshes() const { return m_Meshes; };

		Transform transform;
	};
}