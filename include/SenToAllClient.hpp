/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** SenToAllClient
*/

#ifndef SENTOALLCLIENT_HPP_
#define SENTOALLCLIENT_HPP_

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

void sendToAllClient(std::uint8_t ecsInput, std::deque<std::shared_ptr<ISession>> sessions, ServerBroker *server_broker, Message *message);


#endif /* !SENTOALLCLIENT_HPP_ */
