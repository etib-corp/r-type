/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Transform
*/

#pragma once

#include "Vector3.hpp"
#include "Vector2.hpp"

struct TransformComponent {
    LE::Vector3<float> position;
    LE::Vector3<float> rotation;
    LE::Vector3<float> scale;
};
