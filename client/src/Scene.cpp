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
    if (_guiManager)
        _guiManager->draw();
}

void LE::Scene::init()
{
    if (_guiManager)
        _guiManager->init();
}

Entity LE::Scene::getCameraEntity() const
{
    return _cameraEntity;
}