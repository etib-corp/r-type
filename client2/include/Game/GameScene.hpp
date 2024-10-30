/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** GameScene
*/

#pragma once

#include "SceneManager.hpp"

namespace LE {
    class Engine;
}

class GameScene : public LE::Scene {
    public:
        GameScene();
        ~GameScene();

        void init();
};