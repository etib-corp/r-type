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
#include "ECS/Components/MotionComponent.hpp"
#include <functional>

struct PatternComponent {
    std::string pattern_name;
    LE::Vector3<float> end_pos;
    double speed;
    double seek;
};

std::ostream &operator<<(std::ostream &os, const PatternComponent &pattern);

#endif /* !PATTERNCOMPONENT_HPP_ */
