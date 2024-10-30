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

std::shared_ptr<LE::IEngine> g_engine;

int main(int ac, char **av)
{
    LE::GraphicalLib lib("/home/julithein/delivery/etib/lion-engine/build/lib/SFML/liblion-engine-SFML.so");
    try {
        g_engine = lib.createEngine();
    } catch (const LE::IEngineError &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    g_engine->init();

    g_engine->setFramerateLimit(60);

    g_engine->setGame<Rtype>();

    auto sceneSnake = g_engine->addScene<GameScene>("GameScene");

    g_engine->playScene("GameScene");

    g_engine->run();
    return 0;
}
