/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** CallbackServer
*/

#pragma once

#include "ECS/Ecs.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/MotionComponent.hpp"
#include "GameClock.hpp"
#include "message/ServerBroker.hpp"
#include "EnumClass.hpp"
#include "Utils.hpp"
#include "ResponsibilityChain.hpp"
#include "Common.hpp"

bool checkMagicNumber(const Request& req, std::shared_ptr<LE::Ecs> _ecs);
void attributeServerCallback(std::shared_ptr<LE::ServerBroker> server, std::shared_ptr<LE::ResponsibilityChain> chain);
