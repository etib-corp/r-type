/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Rtype
*/

#pragma once

#include "CallbackClient.hpp"
#include "message/ClientBroker.hpp"
#include "Engine.hpp"
#include "EnumClass.hpp"
#include "etibjson.hpp"
#include "GameScene.hpp"
#include "Utils.hpp"

class Rtype : public LE::Game {
    public:
        Rtype();
        ~Rtype();

        bool init() override;
        void update() override;

    private:
        ClientBroker *_clientBroker;
        INetworkModule *_networkModule;
        ResponsibilityChain _responsibilityChain;
};