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
    // Drawing logic from ECS
    _guiManager->draw();
}
