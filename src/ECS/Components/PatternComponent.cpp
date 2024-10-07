/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** PatternComponent
*/

#include "ECS/Components/PatternComponent.hpp"

std::ostream &operator<<(std::ostream &os, const PatternComponent &pattern)
{
    os << "PatternComponent: {"
       << "pattern_name: " << pattern.pattern_name
       << ", end_pos: " << pattern.end_pos
       << ", speed: " << pattern.speed
       << ", seek: " << pattern.seek
       << "}";
    return os;
}