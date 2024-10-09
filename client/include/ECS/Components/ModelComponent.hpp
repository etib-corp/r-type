/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Render
*/

#pragma once

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include <map>
#include <iostream>
#include "glm.hpp"
#include <string>
#include <vector>
#include "Vector3.hpp"
#include "Vector2.hpp"
#include "Matrix.hpp"
#include "Window.hpp"
#include "Shader.hpp"

class TextureError : public LE::Error {
    public:
        TextureError(const std::string &message) : LE::Error(message) {}
};

struct Texture {
    unsigned int _id;       ///< The id of the texture.
    std::string _type;      ///< The type of the texture.
    std::string _path;      ///< The path to the texture file.
    int _width;             ///< The width of the texture.
    int _height;            ///< The height of the texture.
    int _nrChannels;        ///< The number of channels in the texture.
};

struct Vertex {
        glm::vec3 _position;        ///< The position of the vertex in 3D space.
        glm::vec3 _normal;          ///< The normal vector of the vertex.
        glm::vec2 _texCoords;       ///< The texture coordinates of the vertex.
        glm::vec3 _tangent;         ///< The tangent vector at the vertex.
        glm::vec3 _bitangent;       ///< The bitangent vector at the vertex.
};

struct Mesh {
    std::vector<unsigned int> _indices;     ///< The indices of the mesh.
    std::vector<Texture *> _textures;         ///< The textures of the mesh.
    std::vector<Vertex> _vertices;          ///< The vertices of the mesh.
    unsigned int _vao;                      ///< The Vertex Array Object of the mesh.
    unsigned int _vbo;                      ///< The Vertex Buffer Object of the mesh.
    unsigned int _ebo;                      ///< The Element Buffer Object of the mesh.
};

struct ModelComponent {
    std::vector<Mesh *> _meshes;                                              ///< The meshes in the model.
    std::string _directory;                                                 ///< The directory of the model file.
    std::vector<Texture *> _texturesLoaded;                                   ///< The textures loaded for the model.
    static std::map<std::string, ModelComponent *> _modelsLoaded;           ///< The loaded models.
    LE::Matrix<4, 4, float> _originalModelMatrix;
    bool hidden = false;                                                   ///< The original model matrix.
};

ModelComponent *createModelComponent(const std::string &path);
Texture *createTexture(const std::string &path, bool flip);
std::vector<Texture *> loadMaterialTextures(ModelComponent *model, aiMaterial *mat, aiTextureType type, const std::string& typeName, bool flipTexture = false);
void processNode(aiNode *node, const aiScene *scene, ModelComponent *model);
Mesh *processMesh(ModelComponent *model, aiMesh *mesh, const aiScene *scene);
void setupMesh(Mesh *mesh);

void drawMesh(Mesh *mesh, LE::Shader *shader);