/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** Render3DSystem
*/

#include "ECS/Systems/Render3DSystem.hpp"
#include "ECS/SystemManager.hpp"
#include "Shader.hpp"
#include "ECS/Ecs.hpp"

Render3DSystem::Render3DSystem()
{
    _shader = std::make_shared<LE::Shader>("assets/shaders/model.vert", "assets/shaders/model.frag");
}

Render3DSystem::~Render3DSystem()
{
}

void Render3DSystem::update(Ecs *ecs, float delta)
{
    for (auto &entity : _entities) {
        auto &model = ecs->getComponent<ModelComponent>(entity);
        auto &transform = ecs->getComponent<TransformComponent>(entity);

        _shader->use();

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)1920 / (float)1080, 0.1f, 100.0f);
        _shader->setMat<4>("projection", LE::Matrix<4, 4, float>(projection));

        glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, -50.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        _shader->setMat<4>("view", LE::Matrix<4, 4, float>(view));

        glm::mat4 modelMat = glm::mat4(1.0f);
        modelMat = glm::translate(modelMat, transform.position.toGlmVec3());
        modelMat = glm::rotate(modelMat, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        modelMat = glm::rotate(modelMat, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        modelMat = glm::rotate(modelMat, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        // modelMat = glm::shear(modelMat, this->_position.toGlmVec3(), glm::vec2(this->_shear.x, this->_shear.z), glm::vec2(this->_shear.y, this->_shear.z), glm::vec2(this->_shear.x, this->_shear.y));
        modelMat = glm::scale(modelMat, transform.scale.toGlmVec3());
        _shader->setMat<4>("model", LE::Matrix<4, 4, float>(modelMat));
        for (auto &mesh : model._meshes) {
            drawMesh(mesh, _shader.get());
        }
    }
}