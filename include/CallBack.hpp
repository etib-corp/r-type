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

void executeCallbacks(
    const std::vector<std::function<void(
        const Header&, std::shared_ptr<Ecs>
    )>>& callbacks,
    const Header& header,
    std::shared_ptr<Ecs> _ecs
);
void processHeader(const Header& header, std::shared_ptr<Ecs> _ecs, ResponsibilityChain chain);

#endif /* !CALLBACK_HPP_ */
