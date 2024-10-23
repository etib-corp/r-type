/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Motion
*/

#pragma once

#include "Vector3.hpp"
#include <bitset>

#define MOVEMENT_UP 0
#define MOVEMENT_DOWN 1
#define MOVEMENT_LEFT 2
#define MOVEMENT_RIGHT 3

/**
 * @brief A motion component.
 *
 * This component represents the motion of an entity with velocity, max velocity, acceleration and friction.
 */
struct MotionComponent {
    LE::Vector3<float> velocity;        ///< The velocity of the entity
    LE::Vector3<float> maxVelocity;     ///< The maximum velocity of the entity
    LE::Vector3<float> acceleration;    ///< The acceleration of the entity
    LE::Vector3<float> maxAcceleration; ///< The maximum acceleration of the entity
    std::bitset<4> direction;            ///< The direction of the entity
};
