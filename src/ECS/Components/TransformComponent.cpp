/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** TransformComponent
*/

#include "ECS/Components/PatternComponent.hpp"

TransformComponent createTransformComponent(LE::Vector3<float> position, LE::Vector3<float> rotation, LE::Vector3<float> scale)
{
    TransformComponent transform;
    transform.position = position;
    transform.rotation = rotation;
    transform.scale = scale;
    return transform;
}

std::ostream &operator<<(std::ostream &os, const TransformComponent &transform)
{
    os << "Position: " << transform.position << " Rotation: " << transform.rotation << " Scale: " << transform.scale;
    return os;
}