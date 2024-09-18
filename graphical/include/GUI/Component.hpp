/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Component
*/

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <string>

// #include "Maths/Vector2.hpp"

namespace LE {
    namespace GUI {
        class Component {
            public:
                virtual ~Component() = default;

                virtual void draw() = 0;

                size_t getId() const { return _id; }

            protected:
                size_t _id;
                // Vector2<unsigned int> _position;
        };
    }
}

#endif /* !COMPONENT_HPP_ */
