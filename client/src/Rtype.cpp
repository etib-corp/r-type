/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** Rtype
*/

#include "Rtype.hpp"
#include "etibjson.hpp"

static bool parseJsonAndCreateEnemy(std::shared_ptr<LE::Ecs> ecs, std::string path)
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
        auto jsonStartPos = jsonValue->getObjectValue()["start_pos"];
        TransformComponent transform = {
            LE::Vector3<float>(jsonStartPos->getArrayValue()[0]->getNumberValue(), jsonStartPos->getArrayValue()[1]->getNumberValue(), jsonStartPos->getArrayValue()[2]->getNumberValue()),
            LE::Vector3<float>(jsonValue->getObjectValue()["rotation"]->getArrayValue()[0]->getNumberValue(), jsonValue->getObjectValue()["rotation"]->getArrayValue()[1]->getNumberValue(), jsonValue->getObjectValue()["rotation"]->getArrayValue()[2]->getNumberValue()),
            LE::Vector3<float>(jsonValue->getObjectValue()["scale"]->getNumberValue(), jsonValue->getObjectValue()["scale"]->getNumberValue(), jsonValue->getObjectValue()["scale"]->getNumberValue())
        };
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
        auto images = g_engine->getAssetManager()->getAsset<ImageAsset>(jsonValue->getObjectValue()["image"]->getStringValue());
        std::vector<uint8_t> imageData = images->getImageData();
        std::string imageDataStr(imageData.begin(), imageData.end());
        auto sprite = g_engine->createSpriteComponentFromMemory(imageDataStr);
        ecs->addComponent<std::shared_ptr<LE::ISpriteComponent>>(entity, sprite);
        ecs->addComponent<HurtBox>(entity, hurtbox);
        ecs->addComponent<HitBox>(entity, hitbox);
    }
    return true;
}

static void processRequest(const Request& req, std::shared_ptr<LE::Ecs> _ecs, std::shared_ptr<LE::ResponsibilityChain> chain)
{
    auto callbacks = chain->getActionCallbacks(req.header.Action);
    bool callbackState = false;

    for (const auto& callback : callbacks)
    {
        callbackState =  callback(req, _ecs);
        if (!callbackState)
        {
            break;
        }
    }
}

static void receiveFromServer(std::shared_ptr<LE::ClientBroker> client_broker, std::shared_ptr<LE::Ecs> _ecs, std::shared_ptr<LE::ResponsibilityChain> chain)
{
    try {
        std::shared_ptr<LE::Message> message = nullptr;
        message = client_broker->getMessageFromTopic(1);
        if (message == nullptr)
            return;
        std::cout << "Message received from server" << std::endl;
        Request req = message->getRequest();
        processRequest(req, _ecs, chain);
        std::cout << "getBody()=" << message->getBody()._buffer << std::endl;
        std::cout << "getReceiverID()=" << (int)message->getReceiverID() << std::endl;
        std::cout << "getEmmiterID()=" << (int)message->getEmmiterID() << std::endl;
        // delete message;
    } catch (const std::exception &e) {
    }
}

Rtype::Rtype()
{
}

Rtype::~Rtype()
{
}

void Rtype::init(LE::IEngine& engine)
{
    _sceneManager = engine.createSceneManager();
    _responsibilityChain = std::make_shared<LE::ResponsibilityChain>();
    _clientBroker = std::make_shared<LE::ClientBroker>(engine.getNetworkModule(), "127.0.0.1", 8080);

    attributeClientCallback(_responsibilityChain, _clientBroker);

    _responsibilityChain->addActionCallback(asChar(ActionCode::START_GAME), [&](const Request& req, std::shared_ptr<LE::Ecs> ecs) -> bool {
        std::cout << "Game start" << std::endl;
        std::shared_ptr<ConfigAsset> config = engine.getAssetManager()->getAsset<ConfigAsset>("vague_1.json");
        parseJsonAndCreateEnemy(ecs , config->getConfigFile());
        return true;
    });
}

void Rtype::update()
{
    if (_clientBroker) {
        std::cout << "toto" << std::endl;
        receiveFromServer(_clientBroker, _sceneManager->getCurrentScene()->getEcs(), _responsibilityChain);
    }
}
