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
// #include "CallBack.hpp"
#include <iostream>

// void callbackInputUp(const Request& req, std::shared_ptr<Ecs> _ecs);
// void callbackInputDown(const Request& req, std::shared_ptr<Ecs> _ecs);
// void callbackInputLeft(const Request& req, std::shared_ptr<Ecs> _ecs);
// void callbackInputRight(const Request& req, std::shared_ptr<Ecs> _ecs);
// void checkMagicNumber(const Request& req, std::shared_ptr<Ecs> _ecs);
// void attributeServerCallback(ResponsibilityChain *chain, std::deque<std::shared_ptr<ISession>> sessions, ServerBroker *server_broker, Message *message);
void executeCallbacks(
    const std::vector<CallBackFunc>& callbacks,
    const Request& req,
    std::shared_ptr<Ecs> _ecs
);
void processRequest(const Request& req, std::shared_ptr<Ecs> _ecs, ResponsibilityChain chain);

#endif /* !CALLBACK_HPP_ */
