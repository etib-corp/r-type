/*
** EPITECH PROJECT, 2024
** graphical
** File description:
** Scene
*/

#include "Scene.hpp"

LE::Scene::Scene()
{
    _eventManager = std::make_shared<LE::EventManager>();
}

void LE::Scene::draw()
{
    _guiManager->draw();
}

void LE::Scene::init()
{
    _guiManager->init();
}
