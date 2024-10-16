/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** GameScene
*/

#include "GameScene.hpp"
#include "Engine.hpp"

GameScene::GameScene() : LE::Scene()
{
    _ecs->setScene(this);
    _ecs->registerComponent<TransformComponent>();
    _ecs->registerComponent<SpriteComponent>();
    _ecs->registerComponent<ModelComponent>();
    _ecs->registerComponent<PatternComponent>();
    _ecs->registerComponent<MotionComponent>();
    _ecs->registerComponent<CameraComponent>();
    _ecs->registerComponent<HurtBox>();
    _ecs->registerComponent<HitBox>();
    Signature signatureRender2D;
    signatureRender2D.set(_ecs->getComponentType<TransformComponent>());
    signatureRender2D.set(_ecs->getComponentType<SpriteComponent>());
    _ecs->registerSystem<Render2DSystem>();
    _ecs->setSignature<Render2DSystem>(signatureRender2D);

    Signature signatureRender3D;
    signatureRender3D.set(_ecs->getComponentType<TransformComponent>());
    signatureRender3D.set(_ecs->getComponentType<ModelComponent>());
    signatureRender3D.set(_ecs->getComponentType<MotionComponent>());
    _ecs->registerSystem<Render3DSystem>();
    _ecs->setSignature<Render3DSystem>(signatureRender3D);

    Signature signaturePattern;
    signaturePattern.set(_ecs->getComponentType<TransformComponent>());
    signaturePattern.set(_ecs->getComponentType<PatternComponent>());
    signaturePattern.set(_ecs->getComponentType<MotionComponent>());
    std::shared_ptr<PatternSystem> patternSystem = _ecs->registerSystem<PatternSystem>();
    _ecs->setSignature<PatternSystem>(signaturePattern);

    Signature signatureCamera;
    signatureCamera.set(_ecs->getComponentType<TransformComponent>());
    signatureCamera.set(_ecs->getComponentType<CameraComponent>());
    signatureCamera.set(_ecs->getComponentType<MotionComponent>());
    _ecs->registerSystem<CameraSystem>();
    _ecs->setSignature<CameraSystem>(signatureCamera);

    Signature signatureCollision;
    signatureCollision.set(_ecs->getComponentType<TransformComponent>());
    signatureCollision.set(_ecs->getComponentType<HitBox>());
    signatureCollision.set(_ecs->getComponentType<HurtBox>());
    _ecs->registerSystem<CollisionSystem>();
    _ecs->setSignature<CollisionSystem>(signatureCollision);

    patternSystem->addPattern("line", [](PatternComponent &pattern, TransformComponent &transform, MotionComponent &motion) {
        if (transform.position.x != pattern.end_pos.x) {
            motion.velocity.x = pattern.speed * (pattern.end_pos.x - transform.position.x > 0 ? 1 : -1);
        }
        if (transform.position.y != pattern.end_pos.y) {
            motion.velocity.y = pattern.speed * (pattern.end_pos.y - transform.position.y > 0 ? 1 : -1);
        }
        if (transform.position.z != pattern.end_pos.z) {
            motion.velocity.z = pattern.speed * (pattern.end_pos.z - transform.position.z > 0 ? 1 : -1);
        }
    });

    Entity cameraEntity = _ecs->createEntity();
    _ecs->addComponent<TransformComponent>(cameraEntity, (TransformComponent){{0, 0, -50}, {0, 0, 0}, {1.0f, 1.0f, 1.0f}});
    _ecs->addComponent<CameraComponent>(cameraEntity, (CameraComponent){static_cast<float>(LE::Engine::getInstance()->getWindowWidth()), static_cast<float>(LE::Engine::getInstance()->getWindowHeight()), 0.0f, 1000.0f, 45.0f, static_cast<float>(LE::Engine::getInstance()->getWindowWidth()) / static_cast<float>(LE::Engine::getInstance()->getWindowHeight()), {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}});
    _ecs->addComponent<MotionComponent>(cameraEntity, (MotionComponent){{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
    _ecs->setCameraEntity(cameraEntity);
}

GameScene::~GameScene()
{
}

void GameScene::init()
{
    _eventManager->addEventListener({LE::KEYBOARD, LE_KEY_ESCAPE, LE::JUST_PRESSED, false}, [&](LE::Engine *engine, float dt) {
        exit(0);
    });
    _eventManager->addEventListener({LE::KEYBOARD, LE_KEY_UP, LE::JUST_PRESSED, false}, [&](LE::Engine *engine, float dt) {
        try {
            int id = _clientBroker->getECSId();
            auto& motion = _ecs->getComponent<MotionComponent>(id);
            Request request = {0};
            request.header.Action = asChar(ActionCode::UP);
            request.header.BodyLength = 0;
            request.header.EmmiterdEcsId = id;
            request.header.MagicNumber = 0xFF;
            request.header.ReceiverEcsId = 0;
            request.header.TopicID = 1;
            Message *message = new Message();
            message->setRequest(request);
            _clientBroker->addMessage(0, 1, message);
            std::cout << "UP" << std::endl;
        } catch (const std::exception &e) {}
    });
    _eventManager->addEventListener({LE::KEYBOARD, LE_KEY_UP, LE::PRESSED, false}, [&](LE::Engine *engine, float dt) {
        try {
            int id = _clientBroker->getECSId();
            auto& motion = _ecs->getComponent<MotionComponent>(id);
            if (motion.velocity[1] == 0.0f)
                motion.velocity[1] = 1.0f;
            else
                motion.velocity[1] = 0.0f;
        } catch (const std::exception &e) {
        }
    });
    _eventManager->addEventListener({LE::KEYBOARD, LE_KEY_UP, LE::JUST_RELEASED, false}, [&](LE::Engine *engine, float dt) {
        try {
            int id = _clientBroker->getECSId();
            auto& motion = _ecs->getComponent<MotionComponent>(id);
            Request request = {0};
            request.header.Action = asChar(ActionCode::UP);
            request.header.BodyLength = 0;
            request.header.EmmiterdEcsId = _clientBroker->getECSId();
            request.header.MagicNumber = 0xFF;
            request.header.ReceiverEcsId = 0;
            request.header.TopicID = 1;
            Message *message = new Message();
            message->setRequest(request);
            _clientBroker->addMessage(0, 1, message);
        } catch (const std::exception &e) {}
    });
    _eventManager->addEventListener({LE::KEYBOARD, LE_KEY_UP, LE::RELEASED, false}, [&](LE::Engine *engine, float dt) {
        try {
            int id = _clientBroker->getECSId();
            auto& motion = _ecs->getComponent<MotionComponent>(id);
            if (motion.velocity[1] == 1.0f)
                motion.velocity[1] = 0.0f;
        } catch (const std::exception &e) {
        }
    });
    _eventManager->addEventListener({LE::KEYBOARD, LE_KEY_DOWN, LE::JUST_PRESSED, false}, [&](LE::Engine *engine, float dt) {
        try {
            int id = _clientBroker->getECSId();
            auto& motion = _ecs->getComponent<MotionComponent>(id);
            Request request = {0};
            request.header.Action = asChar(ActionCode::DOWN);
            request.header.BodyLength = 0;
            request.header.EmmiterdEcsId = _clientBroker->getECSId();
            request.header.MagicNumber = 0xFF;
            request.header.ReceiverEcsId = 0;
            request.header.TopicID = 1;
            Message *message = new Message();
            message->setRequest(request);
            _clientBroker->addMessage(0, 1, message);
        } catch (const std::exception &e) {}
    });
    _eventManager->addEventListener({LE::KEYBOARD, LE_KEY_DOWN, LE::PRESSED, false}, [&](LE::Engine *engine, float dt) {
        try {
            int id = _clientBroker->getECSId();
            auto& motion = _ecs->getComponent<MotionComponent>(id);
            if (motion.velocity[1] == 0.0f)
                motion.velocity[1] = -1.0f;
            else
                motion.velocity[1] = 0.0f;
        } catch (const std::exception &e) {
        }
    });
    _eventManager->addEventListener({LE::KEYBOARD, LE_KEY_DOWN, LE::JUST_RELEASED, false}, [&](LE::Engine *engine, float dt) {
        try {
            int id = _clientBroker->getECSId();
            auto& motion = _ecs->getComponent<MotionComponent>(id);
            Request request = {0};
            request.header.Action = asChar(ActionCode::DOWN);
            request.header.BodyLength = 0;
            request.header.EmmiterdEcsId = _clientBroker->getECSId();
            request.header.MagicNumber = 0xFF;
            request.header.ReceiverEcsId = 0;
            request.header.TopicID = 1;
            Message *message = new Message();
            message->setRequest(request);
            _clientBroker->addMessage(0, 1, message);
        } catch (const std::exception &e) {}
    });
    _eventManager->addEventListener({LE::KEYBOARD, LE_KEY_DOWN, LE::RELEASED, false}, [&](LE::Engine *engine, float dt) {
        try {
            int id = _clientBroker->getECSId();
            auto& motion = _ecs->getComponent<MotionComponent>(id);
            if (motion.velocity[1] == -1.0f)
                motion.velocity[1] = 0.0f;
        } catch (const std::exception &e) {
        }
    });
    _eventManager->addEventListener({LE::KEYBOARD, LE_KEY_LEFT, LE::JUST_PRESSED, false}, [&](LE::Engine *engine, float dt) {
        try {
            int id = _clientBroker->getECSId();
            auto& motion = _ecs->getComponent<MotionComponent>(id);
            Request request = {0};
            request.header.Action = asChar(ActionCode::LEFT);
            request.header.BodyLength = 0;
            request.header.EmmiterdEcsId = _clientBroker->getECSId();
            request.header.MagicNumber = 0xFF;
            request.header.ReceiverEcsId = 0;
            request.header.TopicID = 1;
            Message *message = new Message();
            message->setRequest(request);
            _clientBroker->addMessage(0, 1, message);
        } catch (const std::exception &e) {}
    });
    _eventManager->addEventListener({LE::KEYBOARD, LE_KEY_LEFT, LE::PRESSED, false}, [&](LE::Engine *engine, float dt) {
        try {
            int id = _clientBroker->getECSId();
            auto& motion = _ecs->getComponent<MotionComponent>(id);
            if (motion.velocity[0] == 0.0f)
                motion.velocity[0] = -1.0f;
            else
                motion.velocity[0] = 0.0f;
        } catch (const std::exception &e) {
        }
    });
    _eventManager->addEventListener({LE::KEYBOARD, LE_KEY_LEFT, LE::JUST_RELEASED, false}, [&](LE::Engine *engine, float dt) {
        try {
            int id = _clientBroker->getECSId();
            auto& motion = _ecs->getComponent<MotionComponent>(id);
            Request request = {0};
            request.header.Action = asChar(ActionCode::LEFT);
            request.header.BodyLength = 0;
            request.header.EmmiterdEcsId = _clientBroker->getECSId();
            request.header.MagicNumber = 0xFF;
            request.header.ReceiverEcsId = 0;
            request.header.TopicID = 1;
            Message *message = new Message();
            message->setRequest(request);
            _clientBroker->addMessage(0, 1, message);
        } catch (const std::exception &e) {}
    });
    _eventManager->addEventListener({LE::KEYBOARD, LE_KEY_LEFT, LE::RELEASED, false}, [&](LE::Engine *engine, float dt) {
        try {
            int id = _clientBroker->getECSId();
            auto& motion = _ecs->getComponent<MotionComponent>(id);
            if (motion.velocity[0] == -1.0f)
                motion.velocity[0] = 0.0f;
        } catch (const std::exception &e) {
        }
    });
    _eventManager->addEventListener({LE::KEYBOARD, LE_KEY_RIGHT, LE::JUST_PRESSED, false}, [&](LE::Engine *engine, float dt) {
        try {
            int id = _clientBroker->getECSId();
            auto& motion = _ecs->getComponent<MotionComponent>(id);
            Request request = {0};
            request.header.Action = asChar(ActionCode::RIGHT);
            request.header.BodyLength = 0;
            request.header.EmmiterdEcsId = _clientBroker->getECSId();
            request.header.MagicNumber = 0xFF;
            request.header.ReceiverEcsId = 0;
            request.header.TopicID = 1;
            Message *message = new Message();
            message->setRequest(request);
            _clientBroker->addMessage(0, 1, message);
        } catch (const std::exception &e) {}
    });
    _eventManager->addEventListener({LE::KEYBOARD, LE_KEY_RIGHT, LE::PRESSED, false}, [&](LE::Engine *engine, float dt) {
        try {
            int id = _clientBroker->getECSId();
            auto& motion = _ecs->getComponent<MotionComponent>(id);
            if (motion.velocity[0] == 0.0f)
                motion.velocity[0] = 1.0f;
            else
                motion.velocity[0] = 0.0f;
        } catch (const std::exception &e) {
        }
    });
    _eventManager->addEventListener({LE::KEYBOARD, LE_KEY_RIGHT, LE::JUST_RELEASED, false}, [&](LE::Engine *engine, float dt) {
        try {
            int id = _clientBroker->getECSId();
            auto& motion = _ecs->getComponent<MotionComponent>(id);
            Request request = {0};
            request.header.Action = asChar(ActionCode::RIGHT);
            request.header.BodyLength = sizeof(LE::Vector3Data<float>);
            request.header.EmmiterdEcsId = _clientBroker->getECSId();
            request.header.MagicNumber = 0xFF;
            request.header.ReceiverEcsId = 0;
            request.header.TopicID = 1;
            Message *message = new Message();
            message->setRequest(request);
            _clientBroker->addMessage(0, 1, message);
        } catch (const std::exception &e) {}
    });
    _eventManager->addEventListener({LE::KEYBOARD, LE_KEY_RIGHT, LE::RELEASED, false}, [&](LE::Engine *engine, float dt) {
        try {
            int id = _clientBroker->getECSId();
            auto& motion = _ecs->getComponent<MotionComponent>(id);
            if (motion.velocity[0] == 1.0f)
                motion.velocity[0] = 0.0f;
        } catch (const std::exception &e) {
        }
    });
    _eventManager->addEventListener({LE::KEYBOARD, LE_KEY_SPACE, LE::JUST_PRESSED, false}, [&](LE::Engine *engine, float dt) {
        try {
            int id = _clientBroker->getECSId();
            auto transform = _ecs->getComponent<TransformComponent>(id);
            Request request = {0};
            request.header.Action = asChar(ActionCode::SHOOT);
            request.header.BodyLength = 0;
            request.header.EmmiterdEcsId = _clientBroker->getECSId();
            request.header.MagicNumber = 0xFF;
            request.header.ReceiverEcsId = 0;
            request.header.TopicID = 1;
            Message *message = new Message();
            message->setRequest(request);
            _clientBroker->addMessage(0, 1, message);

            Entity entity = _ecs->createEntity();
            _ecs->addComponent<TransformComponent>(entity, (TransformComponent){transform.position, {0, 0, 0}, {1.0f, 1.0f, 1.0f}});
            _ecs->addComponent<MotionComponent>(entity, (MotionComponent){{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
            _ecs->addComponent<PatternComponent>(entity, (PatternComponent){"line", LE::Vector3<float>(transform.position.x + 50, transform.position.y, transform.position.z), 0.1, PatternEnd::DESTROY});
            HitBox hitbox = {5, 5, 0, 0};
            hitbox.masks.set(3);
            _ecs->addComponent<HitBox>(entity, hitbox);
            _ecs->addComponent<HurtBox>(entity, (HurtBox){5, 5, 0, 0, []() {
                std::cout << "Hurtbox on hit" << std::endl;
            }});
            ModelComponent *model = createModelComponent("assets/models/bullet/bullet.obj");
            _ecs->addComponent<ModelComponent>(entity, *model);
            std::cout << "SHIP " << id << " SHOOT" << std::endl;
        } catch (const std::exception &e) {}
    });
    _eventManager->addEventListener({LE::KEYBOARD, LE_KEY_ENTER, LE::JUST_PRESSED, false}, [&](LE::Engine *engine, float dt) {
        Request request = {0};
        request.header.Action = asChar(ActionCode::READY);
        request.header.BodyLength = 0;
        request.header.EmmiterdEcsId = _clientBroker->getECSId();
        request.header.MagicNumber = 0xFF;
        request.header.ReceiverEcsId = 0;
        request.header.TopicID = 1;
        Message *message = new Message();
        message->setRequest(request);
        message->setReliable(true);
        _clientBroker->addMessage(0, 1, message);
        std::cout << "############### SENT GAME START MESSAGE ###############################" << std::endl;
    });
}
