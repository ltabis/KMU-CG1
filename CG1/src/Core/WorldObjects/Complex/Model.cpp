#include "Model.hpp"

CG::Model::Model(const std::string &modelPath, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
	: m_ModelPath { modelPath							 }
	, transform   { Transform(position, rotation, scale) }
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_GenNormals);// aiProcessPreset_TargetRealtime_Quality);

    // TODO: add more details to the error.
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        CG_LOG_ERROR("Couldn't load '{}' model: {}", modelPath, importer.GetErrorString());
        return;
    }

    // saving the directory to load additional resources.
    m_DirectoryPath = modelPath.substr(0, modelPath.find_last_of('\\')) + '\\';

    // TODO: use reserve to prevent vector from doubling in size.
    m_Meshes.reserve(scene->mNumMeshes);
    loadModel(scene, scene->mRootNode);
}

void CG::Model::loadModel(const aiScene* scene, const aiNode* node)
{
    for (unsigned int i = 0; i < node->mNumMeshes; ++i)
        createMesh(scene, node->mMeshes[i]);

    for (unsigned int i = 0; i < node->mNumChildren; ++i)
        loadModel(scene, node->mChildren[i]);
}

std::vector<std::shared_ptr<CG::Texture>> CG::Model::loadMaterial(const aiMaterial* material, aiTextureType type, const std::string& typeName) const
{
    std::vector<std::shared_ptr<Texture>> textures;

    for (unsigned int i = 0; i < material->GetTextureCount(type); ++i) {
        aiString path;
        material->GetTexture(type, i, &path);

        std::shared_ptr<Texture> texture = std::make_shared<Texture>(m_DirectoryPath + path.C_Str(), typeName);
        textures.push_back(texture);
    }

    return textures;
}

void CG::Model::createMesh(const aiScene* scene, unsigned int meshIndex)
{
    const aiMesh* mesh = scene->mMeshes[meshIndex];
    std::vector<Vertex> vertices;
    std::vector<std::shared_ptr<Texture>> textures;
    std::vector<unsigned int> indices;

    // reserving vectors allows us to prevent vectors doubling in size.
    vertices.reserve(mesh->mNumVertices);
    indices.reserve(mesh->mNumFaces * 3);

    CG_CONSOLE_CRITICAL("mesh->mNumVertices: {}", mesh->mNumVertices);
    CG_CONSOLE_CRITICAL("mesh->mNumFaces: {}", mesh->mNumFaces);

    // loading vertices.
    for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {

        glm::vec3 vertex = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
        glm::vec3 normal = glm::vec3(0.f);
        glm::vec2 textureCoords = glm::vec2(0.f);

        if (mesh->HasNormals())
            normal = { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z };

        if (mesh->HasTextureCoords(0))
            textureCoords = { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y };

        vertices.push_back({ vertex, normal, textureCoords });
    }

    // loading indecies.
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
        aiFace face = mesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; ++j)
            indices.push_back(face.mIndices[j]);
    }

    // loading textures.
    if (mesh->mMaterialIndex >= 0) {

        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        auto diffuse = loadMaterial(material, aiTextureType_DIFFUSE, "texture_diffuse");
        auto specular = loadMaterial(material, aiTextureType_SPECULAR, "texture_specular");

        textures.insert(textures.end(), diffuse.begin(), diffuse.end());
        textures.insert(textures.end(), specular.begin(), specular.end());
    }

    std::unique_ptr<Mesh> meshObject = std::make_unique<Mesh>(vertices, indices, textures);

    m_Meshes.push_back(std::move(meshObject));
}