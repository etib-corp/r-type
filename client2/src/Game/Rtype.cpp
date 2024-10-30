/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Rtype
*/

#include "Game/Rtype.hpp"

static bool parseJsonAndCreateEnemy(std::shared_ptr<Ecs> ecs, std::string path)
{
    JsonParser parser(path);
    if (!parser.parseFile()) {
        std::cerr << parser.getErrorMessage() << std::endl;
        return false;
    }
    auto jsonEnemy = (*parser.getJsonValue())["enemy"];
    if (jsonEnemy == nullptr) {
        std::cerr << "Error: No enemy found in the json file." << std::endl;
        return false;
    }
    for (auto jsonValue : jsonEnemy->getArrayValue()) {
        Entity entity = ecs->createEntity();
        MotionComponent motion = {};
        ModelComponent *model = {};
        auto jsonStartPos = jsonValue->getObjectValue()["start_pos"];
        TransformComponent transform = createTransformComponent(
            LE::Vector3<float>(jsonStartPos->getArrayValue()[0]->getNumberValue(), jsonStartPos->getArrayValue()[1]->getNumberValue(), jsonStartPos->getArrayValue()[2]->getNumberValue()),
            LE::Vector3<float>(jsonValue->getObjectValue()["rotation"]->getArrayValue()[0]->getNumberValue(), jsonValue->getObjectValue()["rotation"]->getArrayValue()[1]->getNumberValue(), jsonValue->getObjectValue()["rotation"]->getArrayValue()[2]->getNumberValue()),
            LE::Vector3<float>(jsonValue->getObjectValue()["scale"]->getNumberValue(), jsonValue->getObjectValue()["scale"]->getNumberValue(), jsonValue->getObjectValue()["scale"]->getNumberValue())
        );
        auto jsonEndPos = jsonValue->getObjectValue()["end_pos"];
        PatternComponent pattern = createPatternComponent(
            jsonValue->getObjectValue()["pattern"]->getStringValue(),
            LE::Vector3<float>(jsonEndPos->getArrayValue()[0]->getNumberValue(), jsonEndPos->getArrayValue()[1]->getNumberValue(), jsonEndPos->getArrayValue()[2]->getNumberValue()),
            jsonValue->getObjectValue()["speed"]->getNumberValue(),
            PatternEnd::STAY
        );
        HurtBox hurtbox;
        HitBox hitbox;
        auto jsonHurtBox = jsonValue->getObjectValue()["hurtbox"];
        if (jsonHurtBox != nullptr) {
            hurtbox.width = jsonHurtBox->getObjectValue()["width"]->getNumberValue();
            hurtbox.height = jsonHurtBox->getObjectValue()["height"]->getNumberValue();
            std::vector<std::shared_ptr<JsonValue>> layers = jsonHurtBox->getObjectValue()["layers"]->getArrayValue();
            std::vector<std::shared_ptr<JsonValue>> masks = jsonHurtBox->getObjectValue()["masks"]->getArrayValue();
            std::cout << "nbr layers: " << layers.size() << std::endl;
            std::cout << "nbr masks: " << masks.size() << std::endl;
            for (const auto index : layers) {
                std::cout << "Hurtbox layers: " << index->getNumberValue() << std::endl;
                hurtbox.layers.set(index->getNumberValue());
            }
            for (const auto index : masks) {
                hurtbox.masks.set(index->getNumberValue());
            }
            hurtbox.onHit = [entity, ecs]() {
                ecs->destroyEntity(entity);
            };
        }

        auto jsonHitBox = jsonValue->getObjectValue()["hitbox"];
        if (jsonHitBox != nullptr) {
            hitbox.width = jsonHitBox->getObjectValue()["width"]->getNumberValue();
            hitbox.height = jsonHitBox->getObjectValue()["height"]->getNumberValue();
            std::vector<std::shared_ptr<JsonValue>> layers = jsonHitBox->getObjectValue()["layers"]->getArrayValue();
            std::vector<std::shared_ptr<JsonValue>> masks = jsonHitBox->getObjectValue()["masks"]->getArrayValue();
            for (const auto index : layers) {
                hitbox.layers.set(index->getNumberValue());
            }
            for (const auto index : masks) {
                hitbox.masks.set(index->getNumberValue());
            }
        }

        ecs->addComponent<TransformComponent>(entity, transform);
        ecs->addComponent<PatternComponent>(entity, pattern);
        ecs->addComponent<MotionComponent>(entity, motion);
        model = createModelComponent(jsonValue->getObjectValue()["texture_obj"]->getStringValue());
        ecs->addComponent<ModelComponent>(entity, *model);
        ecs->addComponent<HurtBox>(entity, hurtbox);
        ecs->addComponent<HitBox>(entity, hitbox);
    }
    return true;
}

Rtype::Rtype() : LE::IGame()
{
    std::cout << "Rtype constructor" << std::endl;
    std::shared_ptr<LE::Scene> scene = std::make_shared<GameScene>();
    std::shared_ptr<LE::Scene> menu = std::make_shared<Menu>();
    addScene("menu", menu);
    // _sceneManager->setCurrentScene("menu");
    addScene("game", scene);
}

Rtype::~Rtype()
{
    LE::Game::~Game();
}

bool Rtype::init()
{
    _sceneManager->initScenes();
    LE::Game::init();
    std::cout << "Rtype init" << std::endl;
    attributeClientCallback(&_responsibilityChain, _clientBroker);
    _responsibilityChain.addActionCallback(asChar(ActionCode::START_GAME), [](const Request &req, std::shared_ptr<Ecs> ecs) -> bool {
        std::cout << "Game start" << std::endl;
        parseJsonAndCreateEnemy(ecs, "assets/config/vague_1.json");
        return true;
    });
    return true;
}

void Rtype::update()
{
    LE::Game::update();
    // _sceneManager->play("game"); // ! currently useless
}
