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
    STOP_UP         = 0xAD,
    DOWN            = 0xAE,
    STOP_DOWN       = 0xAF,
    LEFT            = 0xB0,
    STOP_LEFT       = 0xB1,
    RIGHT           = 0xB2,
    STOP_RIGHT      = 0xB3,
    SHOOT           = 0xB4,
    READY           = 0xB5,
    A = 0x3E,
    START_GAME     = 0x3F,
    MAGIC_NUMBER    = 0xFF,
};

#endif /* !ENUMCLASS_HPP_ */
