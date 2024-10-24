/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** Render2DSystem
*/

#include "ECS/Systems/Render2DSystem.hpp"
#include "ECS/SystemManager.hpp"
#include "Shader.hpp"
#include "ECS/Ecs.hpp"


Render2DSystem::Render2DSystem()
{
    _shader = std::make_shared<LE::Shader>("assets/shaders/sprite.vert", "assets/shaders/sprite.frag");
}

Render2DSystem::~Render2DSystem()
{
}

void Render2DSystem::update(Ecs *ecs, float dt)
{
    Entity cameraEntity = ecs->getCameraEntity();
    TransformComponent cameraTransform = ecs->getComponent<TransformComponent>(cameraEntity);
    MotionComponent cameraMotion = ecs->getComponent<MotionComponent>(cameraEntity);
    CameraComponent camera = ecs->getComponent<CameraComponent>(cameraEntity);

    for (auto entity : _entities) {
        auto sprite = ecs->getComponent<SpriteComponent>(entity);
        auto transform = ecs->getComponent<TransformComponent>(entity);

        if (sprite.hidden)
            continue;

        float vertices[] {
        0.0f, 0.0f,                     sprite.rect[0], sprite.rect[1], // top-left
        static_cast<float>(sprite.width), 0.0f,                       sprite.rect[0] + sprite.rect[2], sprite.rect[1], // top-right
        0.0f, static_cast<float>(sprite.height),                       sprite.rect[0], sprite.rect[1] + sprite.rect[3], // bottom-left
        static_cast<float>(sprite.width), static_cast<float>(sprite.height),                         sprite.rect[0] + sprite.rect[2], sprite.rect[1] + sprite.rect[3],  // bottom-right
        };
        glBindTexture(GL_TEXTURE_2D, sprite.id);

        glBindVertexArray(sprite.quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, sprite.quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);

        _shader->use();

        _shader->setInt("image", 0);

        glm::mat4 projection = glm::ortho(0.0f, camera.width, camera.height, 0.0f, camera.near, camera.far);
        _shader->setMat<4>("projection", projection);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, transform.position.toGlmVec3());

        model = glm::translate(model, glm::vec3(0.5f * sprite.width * transform.scale.x, 0.5f * sprite.height * transform.scale.y, 0.0f));
        model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::translate(model, glm::vec3(-0.5f * sprite.width * transform.scale.x , -0.5f * sprite.height * transform.scale.y, 0.0f));

        model = glm::scale(model, glm::vec3(transform.scale.toGlmVec3()));
         _shader->setMat<4>("model", model);
        _shader->setVec3("spriteColor", LE::Vector3<float>(1.0f, 1.0f, 1.0f));

        glActiveTexture(GL_TEXTURE0);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);
    }
}
