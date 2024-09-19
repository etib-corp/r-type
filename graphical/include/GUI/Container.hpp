/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Container
*/

#pragma once

#include <vector>

#include "GUI/Component.hpp"

namespace LE {
    namespace GUI {
        class Container : public Component {
            public:
                virtual ~Container() = default;

                void addChildren(Component *child);
                void removeChildren(unsigned int id);
                void draw();

            protected:
                std::vector<Component *> _children;
                unsigned int _width;
                unsigned int _height;
        };
    }
}
