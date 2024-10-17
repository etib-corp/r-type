/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Game
*/

#pragma once

#include "CallbackClient.hpp"
#include "message/ClientBroker.hpp"
#include <memory>
#include "ResponsibilityChain.hpp"
#include "SceneManager.hpp"

namespace LE {
    class Game {
        public:
            Game();
            ~Game();

            virtual bool init();
            virtual void update();

            void addScene(const std::string& name, const std::shared_ptr<Scene> &scene);

            ClientBroker *_clientBroker;
            INetworkModule *_networkModule;
            ResponsibilityChain _responsibilityChain;
            std::shared_ptr<SceneManager> _sceneManager;
    };
}
