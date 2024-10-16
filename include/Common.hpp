/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Common
*/

#ifndef COMMON_HPP_
#define COMMON_HPP_

#include <cstdint>
#include "ECS/Components/TransformComponent.hpp"

struct UpdateEcs {
    std::uint8_t ecsId : 8;
    float position[3];
};

struct StartGame {
    std::uint8_t nbrPlayers : 3;
};

#endif /* !COMMON_HPP_ */
