/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** ModelComponent
*/

#include "ECS/Components/ModelComponent.hpp"
#include "stb_image.h"

std::map<std::string, ModelComponent *> g_models;

ModelComponent *createModelComponent(const std::string &path)
{
    if (g_models.find(path) != g_models.end())
        return g_models[path];
    ModelComponent *model = new ModelComponent();
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return nullptr;
    }
    model->_directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene, model);

    g_models[path] = model;
    return model;
}

void processNode(aiNode *node, const aiScene *scene, ModelComponent *model)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        model->_meshes.push_back(processMesh(model, mesh, scene));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene, model);
    }
}

Mesh *processMesh(ModelComponent *model, aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture *> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex._position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex._normal = vector;

        if (mesh->mTextureCoords[0]) {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex._texCoords = vec;

            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex._tangent = vector;

            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex._bitangent = vector;

        } else {
            vertex._texCoords = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    if (mesh->mMaterialIndex >= 0) {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<Texture *> diffuseMaps = loadMaterialTextures(model, material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    }
    Mesh *newMesh = new Mesh();
    newMesh->_indices = indices;
    newMesh->_textures = textures;
    newMesh->_vertices = vertices;
    setupMesh(newMesh);
    return newMesh;
}

void setupMesh(Mesh *mesh)
{
    glGenVertexArrays(1, &mesh->_vao);
    glGenBuffers(1, &mesh->_vbo);
    glGenBuffers(1, &mesh->_ebo);

    glBindVertexArray(mesh->_vao);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->_vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh->_vertices.size() * sizeof(Vertex), &mesh->_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->_indices.size() * sizeof(unsigned int), &mesh->_indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, _normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, _texCoords));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, _tangent));

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, _bitangent));
    glBindVertexArray(0);
}

void drawMesh(Mesh *mesh, LE::Shader *shader)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;

    std::cout << "Drawing mesh with " << mesh->_textures.size() << " textures" << std::endl;

    for (unsigned int i = 0; i < mesh->_textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string number;
        std::string name = mesh->_textures[i]->_type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);
        else if (name == "texture_normal")
            number = std::to_string(normalNr++);
        else if (name == "texture_height")
            number = std::to_string(heightNr++);

        std::cout << "Setting texture " << name + number << " to " << i << std::endl;
        shader->setInt((name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, mesh->_textures[i]->_id);
    }

    glBindVertexArray(mesh->_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->_ebo);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(mesh->_indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}

std::vector<Texture *> loadMaterialTextures(ModelComponent *model, aiMaterial *mat, aiTextureType type, const std::string& typeName, bool flipTexture)
{
    std::vector<Texture *> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for (auto &texture : model->_texturesLoaded) {
            if (texture->_path == str.C_Str()) {
                textures.push_back(texture);
                skip = true;
                break;
            }
        }
        if (!skip) {
            std::string path = model->_directory + "/" + str.C_Str();
            Texture *texture = createTexture(path, flipTexture);
            texture->_type = typeName;
            texture->_path = str.C_Str();
            textures.push_back(texture);
            model->_texturesLoaded.push_back(texture);
        }
    }
    return textures;
}

Texture *createTexture(const std::string& path, bool flip)
{
    stbi_set_flip_vertically_on_load(flip);
    GLenum format;
    Texture *texture = new Texture();
    glGenTextures(1, &texture->_id);


    unsigned char *data = stbi_load(path.c_str(), &texture->_width, &texture->_height, &texture->_nrChannels, STBI_default);

    if (data) {
        if (texture->_nrChannels == 1)
            format = GL_RED;
        else if (texture->_nrChannels == 3)
            format = GL_RGB;
        else if (texture->_nrChannels == 4)
            format = GL_RGBA;
        else {
            stbi_image_free(data);
            throw TextureError("Texture format with " + std::to_string(format) + " channels are not supported : " + path);
        }
        glBindTexture(GL_TEXTURE_2D, texture->_id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, texture->_width, texture->_height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        stbi_image_free(data);
        throw TextureError("Failed to load texture : " + path);
    }

    texture->_path = path;
    return texture;
}