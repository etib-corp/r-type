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
#include "Scene.hpp"
#include "Utils.hpp"

class Rtype : public LE::Scene {
    public:
        Rtype();
        ~Rtype();

        void init();
        void loop();

    private:
        ClientBroker *_clientBroker;
        INetworkModule *_networkModule;
        ResponsibilityChain _responsibilityChain;
};