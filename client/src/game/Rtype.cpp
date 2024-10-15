/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Rtype
*/

#include "Rtype.hpp"

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
        ecs->addComponent<TransformComponent>(entity, transform);
        ecs->addComponent<PatternComponent>(entity, pattern);
        ecs->addComponent<MotionComponent>(entity, motion);
        model = createModelComponent(jsonValue->getObjectValue()["texture_obj"]->getStringValue());
        ecs->addComponent<ModelComponent>(entity, *model);
    }
    return true;
}



Rtype::Rtype() : LE::Game()
{
    std::cout << "Rtype constructor" << std::endl;
    std::shared_ptr<LE::Scene> scene = std::make_shared<GameScene>();
    addScene("game", scene);
    _sceneManager->initScenes();
}

Rtype::~Rtype()
{
    LE::Game::~Game();
}

bool Rtype::init()
{
    LE::Game::init();
    std::cout << "Rtype init" << std::endl;
    attributeClientCallback(&_responsibilityChain, _clientBroker);
    return true;
}

void Rtype::update()
{
    LE::Game::update();
    _sceneManager->play("game"); // ! currently useless
}
