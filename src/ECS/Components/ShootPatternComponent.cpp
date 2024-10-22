/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ShootPatternComponent
*/

#include "ECS/Components/ShootPatternComponent.hpp"

ShootPatternComponent createShootPatternComponent(std::string pattern_name, double speed, ShootPatternEnd end, double time)
{
    ShootPatternComponent pattern;
    pattern.pattern_name = pattern_name;
    pattern.speed = speed;
    pattern.end = end;
    pattern.time = time;
    pattern.currentTime = 0;
    return pattern;
}