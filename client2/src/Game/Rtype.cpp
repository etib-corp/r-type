/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Rtype
*/

#include "Game/Rtype.hpp"


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
