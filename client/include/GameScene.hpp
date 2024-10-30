/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** GameScene
*/

#ifndef GAMESCENE_HPP_
    #define GAMESCENE_HPP_

    #include "Scene.hpp"

class GameScene : public LE::Scene {
    public:
        GameScene(LE::IEngine *engine) : LE::Scene(engine)
        {
        }

        ~GameScene() {}

        void init() override
        {
            std::shared_ptr<PatternSystem> patternSystem = _ecs->getSystem<PatternSystem>();

            patternSystem->addPattern("line", [](PatternComponent &pattern, TransformComponent &transform) {
            if (transform.position.x != pattern.end_pos.x) {
                pattern.velocity.x = pattern.speed * (pattern.end_pos.x - transform.position.x > 0 ? 1 : -1);
            }
            if (transform.position.y != pattern.end_pos.y) {
                pattern.velocity.y = pattern.speed * (pattern.end_pos.y - transform.position.y > 0 ? 1 : -1);
            }
            if (transform.position.z != pattern.end_pos.z) {
                pattern.velocity.z = pattern.speed * (pattern.end_pos.z - transform.position.z > 0 ? 1 : -1);
            }
            });

            patternSystem->addPattern("sinus_x", [](PatternComponent &pattern, TransformComponent &transform) {
                if (transform.position.x != pattern.end_pos.x) {
                    pattern.velocity.x = pattern.speed * (pattern.end_pos.x - transform.position.x > 0 ? 1 : -1);
                    pattern.velocity.y = sin(pattern.seek) * 10 * pattern.speed;
                    pattern.seek += 0.1;
                }
            });

            Entity cameraEntity = _ecs->createEntity();
            _ecs->addComponent<TransformComponent>(cameraEntity, (TransformComponent){{0, 0, -100}, {0, 0, 0}, {1.0f, 1.0f, 1.0f}});
            auto camera = _engine->createCameraComponent({0, 0}, {800, 600});
            _ecs->addComponent<std::shared_ptr<LE::ICameraComponent>>(cameraEntity, camera);
            _ecs->addComponent<MotionComponent>(cameraEntity, (MotionComponent){{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
            _ecs->setCameraEntity(cameraEntity);
        }

    protected:
    private:
};

#endif /* !GAMESCENE_HPP_ */
