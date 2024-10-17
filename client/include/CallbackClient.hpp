/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** CallbackClient
*/

#ifndef CALLBACKCLIENT_HPP_
#define CALLBACKCLIENT_HPP_

#include "ResolvingLib.hpp"
#include "PackUnpack.hpp"
#include "ECS/Ecs.hpp"
#include "Engine.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Components/ModelComponent.hpp"
#include "ECS/Components/PatternComponent.hpp"
#include "ECS/Components/MotionComponent.hpp"
#include "GameClock.hpp"
#include "message/ClientBroker.hpp"
#include "EnumClass.hpp"
#include "Utils.hpp"
#include "ResponsibilityChain.hpp"
#include "Common.hpp"
#include "CallBack.hpp"

void attributeClientCallback(ResponsibilityChain *chain, ClientBroker *client_broker);


#endif /* !CALLBACKCLIENT_HPP_ */
