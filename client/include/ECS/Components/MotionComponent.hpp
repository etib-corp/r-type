/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Motion
*/

#pragma once

#include "Vector3.hpp"

struct Motion {
    LE::Vector3<float> velocity;
    LE::Vector3<float> maxVelocity;
    LE::Vector3<float> acceleration;
    LE::Vector3<float> friction;
};