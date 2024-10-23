/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Menu
*/

#include "Game/Menu.hpp"

Menu::Menu()
{
    _guiManager = std::make_shared<LE::GUI::Manager>(1920, 1080);
    _eventManager = std::make_shared<LE::EventManager>();

    std::shared_ptr<MainContainer> mainContainer = std::make_shared<MainContainer>();
    std::shared_ptr<LE::GUI::Button> play = std::make_shared<LE::GUI::Button>(560, 340, 200, 100, "Play", new LE::Color(LE::Color::CHAR, 255, 255, 255, 255), new LE::Color(LE::Color::CHAR, 0, 0, 0, 255));
    std::shared_ptr<LE::GUI::TextField> ipField = std::make_shared<LE::GUI::TextField>(560, 440, 200, 100, "IP :", new LE::Color(LE::Color::CHAR, 255, 255, 255, 255), new LE::Color(LE::Color::CHAR, 0, 0, 0, 255));
    std::shared_ptr<LE::GUI::Button> quit = std::make_shared<LE::GUI::Button>(560, 540, 200, 100, "Quit", new LE::Color(LE::Color::CHAR, 255, 255, 255, 255), new LE::Color(LE::Color::CHAR, 0, 0, 0, 255));

    mainContainer->addChildren(play);
    mainContainer->addChildren(ipField);
    mainContainer->addChildren(quit);

    ipField->setMaxChars(12);
    play->setOnClickCallback([=]() {
        try {
            if (!LE::Engine::getInstance()->getGame()->_clientBroker)
                LE::Engine::getInstance()->getGame()->_clientBroker = new ClientBroker(LE::Engine::getInstance()->getGame()->_networkModule, ipField->getContent(), 8080);
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            return;
        }
        if (!LE::Engine::getInstance()->getGame()->_clientBroker) {
            LE::Engine::getInstance()->getGame()->_clientBroker = new ClientBroker(LE::Engine::getInstance()->getGame()->_networkModule, "127.0.0.1", 8080);
        }
        LE::Engine::getInstance()->getGame()->_sceneManager->play("game");
    });

    quit->setOnClickCallback([]() {
        exit(0);
    });

    _guiManager->addChildren(mainContainer);
}

Menu::~Menu()
{
}

Menu::MainContainer::MainContainer()
{
    _x = 560;
    _y = 340;
    _width = 800;
    _height = 400;

    _background = new LE::Shapes::Rectangle(_x, _y, _width, _height, new LE::Color(LE::Color::CHAR, 33, 33, 33, 255));

    std::shared_ptr<LE::GUI::Button> title = std::make_shared<LE::GUI::Button>(0, 0, 200, 100, "R-Type", new LE::Color(LE::Color::CHAR, 33, 33, 33, 255), new LE::Color(LE::Color::CHAR, 255, 255, 255, 255));

    addChildren(title);
}

Menu::MainContainer::~MainContainer()
{
}

bool Menu::isValidIP(const std::string &ip)
{
    std::regex ipRegex("^(?:[0-9]{1,3}\\.){3}[0-9]{1,3}$");

    return std::regex_match(ip, ipRegex);
}
