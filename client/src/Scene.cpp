/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** Scene
*/

#include "Engine.hpp"
#include "Scene.hpp"

LE::Scene::Scene()
{
    auto engine = LE::Engine::getInstance();
    _eventManager = std::make_shared<LE::EventManager>();
    _guiManager = std::make_shared<LE::GUI::Manager>(engine->getWindowWidth(), engine->getWindowHeight());
    _ecs = std::make_shared<Ecs>();
}

void LE::Scene::draw()
{
    _guiManager->draw();
    _ecs->update(LE::Engine::getInstance()->getDeltaTime());
    _eventManager->pollEvents();
}

void LE::Scene::init()
{
    _guiManager->init();
}
