/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Common
*/

#ifndef COMMON_HPP_
#define COMMON_HPP_

#include <cstdint>

struct UpdateEcs {
    std::uint8_t ecs_id;
    std::uint8_t actionInput;
};

struct StartGame {
    std::uint8_t nbrPlayers : 3;
};

#endif /* !COMMON_HPP_ */
