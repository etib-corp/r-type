/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** EnumClass
*/

#ifndef ENUMCLASS_HPP_
#define ENUMCLASS_HPP_

#include <cstdint>

enum class EcsMovement {
    UP      = 0,
    DOWN    = 1,
    RIGHT   = 2,
    LEFT    = 3
};

enum class Axes3D {
    X       = 0,
    Y       = 1,
    Z       = 2,
};

enum class ActionCode : std::uint8_t {
    NEW_CONNECTION  = 0x01,
    INPUT           = 0x02,
    Rollback        = 0x56,
    UPDATE_ECS      = 0x57,
    USERNAME        = 0xAB,
    UP              = 0xAC,
    DOWN            = 0xAD,
    RIGHT           = 0xAE,
    LEFT            = 0xAF,
    STOP            = 0xB0,
    READY           = 0xB1,
    SHOOT           = 0xB2,
    A = 0x3E,
    START_GAME     = 0x3F,
    MAGIC_NUMBER    = 0xFF,
};

#endif /* !ENUMCLASS_HPP_ */
