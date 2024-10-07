/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Motion
*/

#pragma once

#include "Vector3.hpp"

/**
 * @brief A motion component.
 *
 * This component represents the motion of an entity with velocity, max velocity, acceleration and friction.
 */
struct MotionComponent {
    LE::Vector3<float> velocity;        ///< The velocity of the entity
    LE::Vector3<float> maxVelocity;     ///< The maximum velocity of the entity
    LE::Vector3<float> acceleration;    ///< The acceleration of the entity
    LE::Vector3<float> friction;        ///< The friction of the entity
};