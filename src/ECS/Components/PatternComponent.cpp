/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** PatternComponent
*/

#include "ECS/Components/PatternComponent.hpp"

PatternComponent createPatternComponent(std::string pattern_name, LE::Vector3<float> end_pos, double speed, PatternEnd end)
{
    PatternComponent pattern;
    pattern.pattern_name = pattern_name;
    pattern.end_pos = end_pos;
    pattern.speed = speed;
    pattern.end = end;
    return pattern;
}

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