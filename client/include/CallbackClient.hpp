/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** CallbackClient
*/

#pragma once

#include "interface/IEngine.hpp"
#include "GameClock.hpp"
#include "message/ClientBroker.hpp"
#include "EnumClass.hpp"
#include "Utils.hpp"
#include "ResponsibilityChain.hpp"
#include "Common.hpp"

void attributeClientCallback(std::shared_ptr<LE::ResponsibilityChain> chain, std::shared_ptr<LE::ClientBroker> client_broker);
