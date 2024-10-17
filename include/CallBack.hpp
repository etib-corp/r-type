/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** CallBack
*/

#ifndef CALLBACK_HPP_
#define CALLBACK_HPP_

#include "LoaderLib.hpp"
#include "ResolvingLib.hpp"
#include "PackUnpack.hpp"
#include "ECS/Ecs.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "GameClock.hpp"
#include "message/ServerBroker.hpp"
#include "EnumClass.hpp"
#include "Utils.hpp"
#include "ResponsibilityChain.hpp"
#include "Common.hpp"
#include <iostream>
#include "LogDef.hpp"
#include "globalLogger.hpp"


void executeCallbacks(
    const std::vector<CallBackFunc>& callbacks,
    const Request& req,
    std::shared_ptr<Ecs> _ecs
);
void processRequest(const Request& req, std::shared_ptr<Ecs> _ecs, ResponsibilityChain chain);

#endif /* !CALLBACK_HPP_ */
