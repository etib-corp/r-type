/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** CallbackClient
*/

#include "CallbackClient.hpp"

bool callbackStartGame(const Request& req, const std::shared_ptr<LE::Ecs> &_ecs)
{
    StartGame sg;
    ::memmove(&sg, &req.body, sizeof(StartGame));

    for (int i = 0; i < sg.nbrPlayers; i++) {
        Entity player = _ecs->createEntity();
        _ecs->addComponent<TransformComponent>(player, {{0, 0, 0}, {0, 90, 0}, {1, 1, 1}});
        std::shared_ptr<ImageAsset> image = g_engine->getAssetManager()->getAsset<ImageAsset>("ship_1.png");
        std::shared_ptr<LE::ISpriteComponent> sprite = g_engine->createSpriteComponent(image->getImageFile());
        _ecs->addComponent<std::shared_ptr<LE::ISpriteComponent>>(player, sprite);
        _ecs->addComponent<MotionComponent>(player, (MotionComponent){{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
    }
    g_engine->restartClock();
    return true;
}

bool callbackUp(const Request& req, std::shared_ptr<LE::Ecs> _ecs)
{
    std::uint8_t id = req.header.EmmiterdEcsId;
    std::cout << "Up : " << static_cast<int>(id) << std::endl;
    auto& motion = _ecs->getComponent<MotionComponent>(id);
    motion.direction[MOVEMENT_UP] = motion.direction[MOVEMENT_UP] == 0 ? 1 : 0;
    return true;
}

bool callbackDown(const Request& req, std::shared_ptr<LE::Ecs> _ecs)
{
    std::uint8_t id = req.header.EmmiterdEcsId;
    auto& motion = _ecs->getComponent<MotionComponent>(id);
    motion.direction[MOVEMENT_DOWN] = motion.direction[MOVEMENT_DOWN] == 0 ? 1 : 0;
    return true;
}


bool callbackRight(const Request& req, std::shared_ptr<LE::Ecs> _ecs)
{
    std::uint8_t id = req.header.EmmiterdEcsId;
    auto& motion = _ecs->getComponent<MotionComponent>(id);
    auto& transform = _ecs->getComponent<TransformComponent>(id);
    motion.direction[MOVEMENT_RIGHT] = motion.direction[MOVEMENT_RIGHT] == 0 ? 1 : 0;
    return true;
}

bool callbackLeft(const Request& req, std::shared_ptr<LE::Ecs> _ecs)
{
    std::uint8_t id = req.header.EmmiterdEcsId;
    auto& motion = _ecs->getComponent<MotionComponent>(id);
    motion.direction[MOVEMENT_LEFT] = motion.direction[MOVEMENT_LEFT] == 0 ? 1 : 0;
    return true;
}

bool callbackUpdateEcs(const Request& req, std::shared_ptr<LE::Ecs> _ecs)
{
    UpdateEcs updateEcs1;
    UpdateEcs updateEcs2;
    ::memmove(&updateEcs1, &req.body._buffer, sizeof(UpdateEcs));
    ::memmove(&updateEcs2, &req.body._buffer[sizeof(updateEcs1)], sizeof(UpdateEcs));
    std::cout << "UpdateEcs1 : " << static_cast<int>(updateEcs1.ecsId) << std::endl;
    std::cout << "UpdateEcs2 : " << static_cast<int>(updateEcs2.ecsId) << std::endl;
    std::cout << updateEcs1.position[0] << "  " <<  updateEcs1.position[1] << "  " << updateEcs1.position[2] << std::endl;
    _ecs->getComponent<TransformComponent>(updateEcs1.ecsId).position = {updateEcs1.position[0], updateEcs1.position[1], updateEcs1.position[2]};
    _ecs->getComponent<TransformComponent>(updateEcs2.ecsId).position = {updateEcs2.position[0], updateEcs2.position[1], updateEcs2.position[2]};
    return true;
}

bool callbackShoot(const Request& req, std::shared_ptr<LE::Ecs> _ecs)
{
    auto transform = _ecs->getComponent<TransformComponent>(req.header.EmmiterdEcsId);
    Entity entity = _ecs->createEntity();
    _ecs->addComponent<TransformComponent>(entity, (TransformComponent){{transform.position.x + 3, transform.position.y + 0.3f, transform.position.z}, {0, 0, 0}, {0.3f, 0.1f, 0.1f}});
    _ecs->addComponent<MotionComponent>(entity, (MotionComponent){{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
    auto& motion = _ecs->getComponent<MotionComponent>(entity);
    motion.direction[MOVEMENT_RIGHT] = 1;
    _ecs->addComponent<PatternComponent>(entity, (PatternComponent){{0, 0, 0,}, "line", LE::Vector3<float>(transform.position.x + 50, transform.position.y + 0.3f, transform.position.z), 0.1, PatternEnd::DESTROY});
    HitBox hitbox = {5, 5, 0, 0};
    hitbox.masks.set(3);
    _ecs->addComponent<HitBox>(entity, hitbox);
    _ecs->addComponent<HurtBox>(entity, (HurtBox){5, 5, 0, 0, []() {
        std::cout << "Hurtbox on hit" << std::endl;
    }});
    std::shared_ptr<ImageAsset> image = g_engine->getAssetManager()->getAsset<ImageAsset>("bullet.png");
    std::shared_ptr<LE::ISpriteComponent> sprite = g_engine->createSpriteComponent(image->getImageFile());

    _ecs->addComponent<std::shared_ptr<LE::ISpriteComponent>>(entity, sprite);
    return true;
}


void attributeClientCallback(std::shared_ptr<LE::ResponsibilityChain> chain, std::shared_ptr<LE::ClientBroker> client_broker)
{
    chain->addActionCallback(asChar(ActionCode::START_GAME), callbackStartGame);

    chain->addActionCallback(asChar(ActionCode::UP), callbackUp);

    chain->addActionCallback(asChar(ActionCode::DOWN), callbackDown);

    chain->addActionCallback(asChar(ActionCode::RIGHT), callbackRight);

    chain->addActionCallback(asChar(ActionCode::LEFT), callbackLeft);

    chain->addActionCallback(asChar(ActionCode::UPDATE_ECS), callbackUpdateEcs);

    chain->addActionCallback(asChar(ActionCode::SHOOT), callbackShoot);
}
