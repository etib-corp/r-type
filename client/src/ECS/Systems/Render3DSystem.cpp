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
    Entity cameraEntity = ecs->getCameraEntity();
    TransformComponent cameraTransform = ecs->getComponent<TransformComponent>(cameraEntity);
    MotionComponent cameraMotion = ecs->getComponent<MotionComponent>(cameraEntity);
    CameraComponent camera = ecs->getComponent<CameraComponent>(cameraEntity);

for (auto &entity : _entities) {
        auto &model = ecs->getComponent<ModelComponent>(entity);
        auto &transform = ecs->getComponent<TransformComponent>(entity);
        auto &motion = ecs->getComponent<MotionComponent>(entity);

        if (model.hidden)
            continue;

        // limit the location of the entity -20,-20,0 to 20,20,0
        if (transform.position.x < -20.0f || transform.position.x > 20.0f) {
            motion.velocity.x = 0;
        }
        if (transform.position.y < -20.0f || transform.position.y > 20.0f) {
            motion.velocity.y = 0;
        }
        transform.position += motion.velocity;


        _shader->use();

        glm::mat4 projection = glm::perspective(glm::radians(camera.fovy), camera.width / camera.height, camera.near, camera.far);
        _shader->setMat<4>("projection", LE::Matrix<4, 4, float>(projection));

        glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 25.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
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
