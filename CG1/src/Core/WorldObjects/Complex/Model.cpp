#include "Model.hpp"

CG::Model::Model(const std::string &modelPath, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
	: m_ModelPath { modelPath							 }
	, transform   { Transform(position, rotation, scale) }
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(modelPath,
        aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType);

    // TODO: add more details to the error.
    if (!scene || !scene->mRootNode) {
        CG_LOG_ERROR("Couldn't load '{}' model", modelPath);
        return;
    }

    loadModel(scene);
}

CG::Model::~Model()
{
}

void CG::Model::loadModel(const aiScene* scene)
{
    for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
        createMesh(scene, i);
    }
}

void CG::Model::createMesh(const aiScene* scene, unsigned int meshIndex)
{
    const aiMesh* mesh = scene->mMeshes[meshIndex];
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {

        glm::vec3 vertex = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
        glm::vec3 normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };

        vertices.push_back({ vertex, normal, glm::vec3(0.f) });
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
        aiFace face = mesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; ++j)
            indices.push_back(face.mIndices[j]);
    }

    std::unique_ptr<Mesh> meshObject = std::make_unique<Mesh>(
        vertices,
        indices
    );

    // no texture for the moment.
    m_Meshes.push_back(std::move(meshObject));
}
