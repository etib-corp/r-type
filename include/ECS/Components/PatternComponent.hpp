/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** PatternComponent
*/

#ifndef PATTERNCOMPONENT_HPP_
#define PATTERNCOMPONENT_HPP_

#include "Maths/Vector3.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include <functional>

/**
 * @brief Enum for the end of a pattern
 *
 * LOOP: The pattern will loop
 * STAY: The pattern will stay at the end position
 * HIDE: The pattern will hide at the end position
 * DESTROY: The pattern will be destroyed at the end position
 */
enum PatternEnd {
    LOOP,
    STAY,
    HIDE,
    DESTROY
};

struct PatternComponent {
    LE::Vector3<float> velocity;
    std::string pattern_name;
    LE::Vector3<float> end_pos;
    double speed;
    double seek;
    PatternEnd end;
};

std::ostream &operator<<(std::ostream &os, const PatternComponent &pattern);

PatternComponent createPatternComponent(std::string pattern_name, LE::Vector3<float> end_pos, double speed, PatternEnd end);

#endif /* !PATTERNCOMPONENT_HPP_ */
