/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** MenuScene
*/

#include "MenuScene.hpp"

MenuScene::MenuScene(LE::IEngine *engine)
    : LE::Scene(engine)
{
}

MenuScene::~MenuScene()
{
}

void MenuScene::init()
{
    std::shared_ptr<LE::GUI::ITextField> ip = _engine->createTextField([](std::shared_ptr<LE::GUI::ITextField> textField) {
        textField->setPos(560, 140);
        textField->setWidth(200);
        textField->setHeight(50);
        textField->setFont(g_engine->createFont("assets/fonts/ARIAL.ttf", 30, 30));
    });

    std::shared_ptr<LE::GUI::IButton> play = _engine->createButton([](std::shared_ptr<LE::GUI::IButton> button) {
        button->setPos(560, 340);
        button->setWidth(200);
        button->setHeight(100);
        button->setContent("Play");
        button->setFont(g_engine->createFont("assets/fonts/ARIAL.ttf", 30, 30));

    });
}
