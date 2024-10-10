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

    MainContainer *mainContainer = new MainContainer();
    LE::GUI::Button *play = new LE::GUI::Button(560, 340, 200, 100, "Play", new LE::Color(LE::Color::CHAR, 255, 255, 255, 255), new LE::Color(LE::Color::CHAR, 0, 0, 0, 255));
    LE::GUI::Button *quit = new LE::GUI::Button(560, 540, 200, 100, "Quit", new LE::Color(LE::Color::CHAR, 255, 255, 255, 255), new LE::Color(LE::Color::CHAR, 0, 0, 0, 255));

    play->setOnClickCallback([]() {
        std::cout << "Play button clicked" << std::endl;
        // LE::Engine::getInstance()->selectScene("game");
    });

    quit->setOnClickCallback([]() {
        std::cout << "Quit button clicked" << std::endl;
        exit(0);
    });

    mainContainer->addChildren(play);
    mainContainer->addChildren(quit);

    _guiManager->addChildren(mainContainer);
}

Menu::~Menu()
{
}

void Menu::play()
{
    _guiManager->draw();
    _eventManager->pollEvents();
}

void Menu::stop()
{
}

Menu::MainContainer::MainContainer()
{
    _x = 560;
    _y = 340;
    _width = 800;
    _height = 400;

    _background = new LE::Shapes::Rectangle(_x, _y, _width, _height, new LE::Color(LE::Color::CHAR, 33, 33, 33, 255));

    LE::GUI::Button *title = new LE::GUI::Button(0, 0, 200, 100, "R-Type", new LE::Color(LE::Color::CHAR, 33, 33, 33, 255), new LE::Color(LE::Color::CHAR, 255, 255, 255, 255));

    addChildren(title);
}

Menu::MainContainer::~MainContainer()
{
}

