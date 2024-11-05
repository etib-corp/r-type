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
    std::shared_ptr<LE::GUI::ITextField> ip = _engine->createTextField([this](std::shared_ptr<LE::GUI::ITextField> textField) {
        textField->setPos(560, 140);
        textField->setWidth(200);
        textField->setHeight(100);
        textField->setFont(g_engine->createFont("assets/fonts/ARIAL.ttf", 30, 30));
        textField->setLabel("IP: ");
        textField->setMaxChar(15);
        textField->setPlaceholder("Enter IP");
        textField->setBackgroundColor(std::make_shared<LE::Color>(255, 0, 0, 255));
        textField->bind(_engine);
    });

    std::shared_ptr<LE::GUI::IButton> play = _engine->createButton([](std::shared_ptr<LE::GUI::IButton> button) {
        button->setPos(560, 340);
        button->setWidth(200);
        button->setHeight(100);
        button->setContent("Play");
        button->setFont(g_engine->createFont("assets/fonts/ARIAL.ttf", 30, 30));
    });

    play->setOnClickCallback([ip, this](){
        std::cout << "IP: " << ip->getInputContent() << std::endl;
        try {
            auto client = std::make_shared<LE::ClientBroker>(_engine->getNetworkModule(), ip->getInputContent(), 8080);
            _engine->getGame()->setClientBroker(client);
            _engine->getGame()->getSceneManager()->play("GameScene");
        } catch (const std::exception &e) {
            ip->setLabel("Invalid IP");
        }
    });
    _guiManager->addChildren(ip);
    _guiManager->addChildren(play);
}
