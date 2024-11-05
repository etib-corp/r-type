/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** main
*/

#include "interface/IEngine.hpp"
#include "GraphicalLib.hpp"
#include "Rtype.hpp"
#include "GameScene.hpp"
#include "MenuScene.hpp"

std::shared_ptr<LE::IEngine> g_engine;

int main(int ac, char **av)
{
    try {
        g_engine = instanciateEngine();
    } catch (const LE::IEngineError &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    g_engine->setGame<Rtype>();

    // auto sceneMenu = g_engine->addScene<MenuScene>("MenuScene");

    auto sceneSnake = g_engine->addScene<GameScene>("GameScene");

    // g_engine->playScene("MenuScene");

    g_engine->run();
    return 0;
}
