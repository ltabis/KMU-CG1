#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "WorldObjects/Primitives/Mesh.hpp"

namespace CG {
	class Model
	{
	private:
		std::vector<std::unique_ptr<Mesh>> m_Meshes;
		std::string m_ModelPath;
		std::string m_DirectoryPath;

		void loadModel(const aiScene* scene, const aiNode* node);
		std::vector<Texture> loadMaterial(const aiMaterial* material, aiTextureType type, const std::string& typeName) const;
		void createMesh(const aiScene* scene, const aiNode* node, unsigned int meshIndex);
	public:
		Model(const std::string& modelPath, const glm::vec3& position = glm::vec3(0.f), const glm::vec3& rotation = glm::vec3(0.f), const glm::vec3& scale = glm::vec3(1.f));
		~Model() = default;

		inline const std::vector<std::unique_ptr<Mesh>>& meshes() const { return m_Meshes; };

		Transform transform;
	};
}