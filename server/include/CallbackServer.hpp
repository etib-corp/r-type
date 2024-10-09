/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** CallbackServer
*/

#ifndef CALLBACKSERVER_HPP_
    #define CALLBACKSERVER_HPP_

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
#include "SenToAllClient.hpp"
#include "CallBack.hpp"

void attributeServerCallback(ResponsibilityChain *chain, std::deque<std::shared_ptr<ISession>> sessions, ServerBroker *server_broker);

#endif /* !CALLBACKSERVER_HPP_ */
