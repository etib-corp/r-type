/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** TransformComponent
*/

#include "ECS/Components/PatternComponent.hpp"

std::ostream &operator<<(std::ostream &os, const TransformComponent &transform)
{
    os << "Position: " << transform.position << " Rotation: " << transform.rotation << " Scale: " << transform.scale;
    return os;
}