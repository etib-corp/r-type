/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** GameScene
*/

#include "GameScene.hpp"

GameScene::GameScene(LE::IEngine *engine) : LE::Scene(engine)
{
}
GameScene::~GameScene()
{
}

void GameScene::init()
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

    _eventManager->addEventListener({LE::KEYBOARD, LE::Event::KEY_ENTER, LE::JUST_PRESSED, false}, [&](LE::IEngine &engine, float dt) {
        Request request = {0};
        request.header.Action = asChar(ActionCode::READY);
        request.header.BodyLength = 0;
        request.header.EmmiterdEcsId = _engine->getGame()->getClientBroker()->getECSId();
        request.header.MagicNumber = 0xFF;
        request.header.ReceiverEcsId = 0;
        request.header.TopicID = 1;
        std::shared_ptr<LE::Message> message = std::make_shared<LE::Message>();
        message->setRequest(request);
        message->setReliable(true);
        _engine->getGame()->getClientBroker()->addMessage(0, 1, message);
        std::cout << "############### SENT GAME START MESSAGE ###############################" << std::endl;
    });

    _eventManager->addEventListener({LE::KEYBOARD, LE::Event::KEY_UP, LE::JUST_PRESSED, false}, [&](LE::IEngine &engine, float dt) {
    try {
        int id =  _engine->getGame()->getClientBroker()->getECSId();
        Request request = {0};
        request.header.Action = asChar(ActionCode::UP);
        request.header.BodyLength = 0;
        request.header.EmmiterdEcsId = id;
        request.header.MagicNumber = 0xFF;
        request.header.ReceiverEcsId = 0;
        request.header.TopicID = 1;
        std::shared_ptr<LE::Message> message = std::make_shared<LE::Message>();
        message->setRequest(request);
        _engine->getGame()->getClientBroker()->addMessage(0, 1, message);
    } catch (const std::exception &e) {}
    });

    _eventManager->addEventListener({LE::KEYBOARD, LE::Event::KEY_UP, LE::JUST_RELEASED, false}, [&](LE::IEngine &engine, float dt) {
    try {
        int id = _engine->getGame()->getClientBroker()->getECSId();
        Request request = {0};
        request.header.Action = asChar(ActionCode::UP);
        request.header.BodyLength = 0;
        request.header.EmmiterdEcsId = id;
        request.header.MagicNumber = 0xFF;
        request.header.ReceiverEcsId = 0;
        request.header.TopicID = 1;
        std::shared_ptr<LE::Message> message = std::make_shared<LE::Message>();
        message->setRequest(request);
        _engine->getGame()->getClientBroker()->addMessage(0, 1, message);
    } catch (const std::exception &e) {}
    });

    _eventManager->addEventListener({LE::KEYBOARD, LE::Event::KEY_DOWN, LE::JUST_PRESSED, false}, [&](LE::IEngine &engine, float dt) {
    try {
        int id =  _engine->getGame()->getClientBroker()->getECSId();
        Request request = {0};
        request.header.Action = asChar(ActionCode::DOWN);
        request.header.BodyLength = 0;
        request.header.EmmiterdEcsId = id;
        request.header.MagicNumber = 0xFF;
        request.header.ReceiverEcsId = 0;
        request.header.TopicID = 1;
        std::shared_ptr<LE::Message> message = std::make_shared<LE::Message>();
        message->setRequest(request);
        _engine->getGame()->getClientBroker()->addMessage(0, 1, message);
    } catch (const std::exception &e) {}
    });

    _eventManager->addEventListener({LE::KEYBOARD, LE::Event::KEY_DOWN, LE::JUST_RELEASED, false}, [&](LE::IEngine &engine, float dt) {
    try {
        int id =  _engine->getGame()->getClientBroker()->getECSId();
        Request request = {0};
        request.header.Action = asChar(ActionCode::DOWN);
        request.header.BodyLength = 0;
        request.header.EmmiterdEcsId = id;
        request.header.MagicNumber = 0xFF;
        request.header.ReceiverEcsId = 0;
        request.header.TopicID = 1;
        std::shared_ptr<LE::Message> message = std::make_shared<LE::Message>();
        message->setRequest(request);
        _engine->getGame()->getClientBroker()->addMessage(0, 1, message);
    } catch (const std::exception &e) {}
    });

    _eventManager->addEventListener({LE::KEYBOARD, LE::Event::KEY_LEFT, LE::JUST_PRESSED, false}, [&](LE::IEngine &engine, float dt) {
    try {
        int id =  _engine->getGame()->getClientBroker()->getECSId();
        Request request = {0};
        request.header.Action = asChar(ActionCode::LEFT);
        request.header.BodyLength = 0;
        request.header.EmmiterdEcsId = id;
        request.header.MagicNumber = 0xFF;
        request.header.ReceiverEcsId = 0;
        request.header.TopicID = 1;
        std::shared_ptr<LE::Message> message = std::make_shared<LE::Message>();
        message->setRequest(request);
        _engine->getGame()->getClientBroker()->addMessage(0, 1, message);
    } catch (const std::exception &e) {}
    });

    _eventManager->addEventListener({LE::KEYBOARD, LE::Event::KEY_LEFT, LE::JUST_RELEASED, false}, [&](LE::IEngine &engine, float dt) {
    try {
        int id =  _engine->getGame()->getClientBroker()->getECSId();
        Request request = {0};
        request.header.Action = asChar(ActionCode::LEFT);
        request.header.BodyLength = 0;
        request.header.EmmiterdEcsId = id;
        request.header.MagicNumber = 0xFF;
        request.header.ReceiverEcsId = 0;
        request.header.TopicID = 1;
        std::shared_ptr<LE::Message> message = std::make_shared<LE::Message>();
        message->setRequest(request);
        _engine->getGame()->getClientBroker()->addMessage(0, 1, message);
    } catch (const std::exception &e) {}
    });

    _eventManager->addEventListener({LE::KEYBOARD, LE::Event::KEY_RIGHT, LE::JUST_PRESSED, false}, [&](LE::IEngine &engine, float dt) {
    try {
        int id =  _engine->getGame()->getClientBroker()->getECSId();
        Request request = {0};
        request.header.Action = asChar(ActionCode::RIGHT);
        request.header.BodyLength = 0;
        request.header.EmmiterdEcsId = id;
        request.header.MagicNumber = 0xFF;
        request.header.ReceiverEcsId = 0;
        request.header.TopicID = 1;
        std::shared_ptr<LE::Message> message = std::make_shared<LE::Message>();
        message->setRequest(request);
        _engine->getGame()->getClientBroker()->addMessage(0, 1, message);
    } catch (const std::exception &e) {}
    });

    _eventManager->addEventListener({LE::KEYBOARD, LE::Event::KEY_RIGHT, LE::JUST_RELEASED, false}, [&](LE::IEngine &engine, float dt) {
    try {
        int id =  _engine->getGame()->getClientBroker()->getECSId();
        Request request = {0};
        request.header.Action = asChar(ActionCode::RIGHT);
        request.header.BodyLength = 0;
        request.header.EmmiterdEcsId = id;
        request.header.MagicNumber = 0xFF;
        request.header.ReceiverEcsId = 0;
        request.header.TopicID = 1;
        std::shared_ptr<LE::Message> message = std::make_shared<LE::Message>();
        message->setRequest(request);
        _engine->getGame()->getClientBroker()->addMessage(0, 1, message);
    } catch (const std::exception &e) {}
    });

    _eventManager->addEventListener({LE::KEYBOARD, LE::Event::KEY_SPACE, LE::JUST_PRESSED, false}, [&](LE::IEngine &engine, float dt) {
    try {
        int id =  _engine->getGame()->getClientBroker()->getECSId();
        Request request = {0};
        request.header.Action = asChar(ActionCode::SHOOT);
        request.header.BodyLength = 0;
        request.header.EmmiterdEcsId = id;
        request.header.MagicNumber = 0xFF;
        request.header.ReceiverEcsId = 0;
        request.header.TopicID = 1;
        std::shared_ptr<LE::Message> message = std::make_shared<LE::Message>();
        message->setRequest(request);
        _engine->getGame()->getClientBroker()->addMessage(0, 1, message);
    } catch (const std::exception &e) {}
    });
}
