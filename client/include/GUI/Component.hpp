/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Component
*/

#pragma once

#include <string>

// #include "Maths/Vector2.hpp"

namespace LE {
    namespace GUI {
        class Component {
            public:
                virtual ~Component() = default;

                virtual void draw() = 0;

                size_t getId() const { return _id; }

                virtual void init() = 0;

            protected:
                size_t _id;
                unsigned int _x;
                unsigned int _y;
        };
    }
}
