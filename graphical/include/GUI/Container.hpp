/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Container
*/

#ifndef CONTAINER_HPP_
#define CONTAINER_HPP_

#include <vector>

#include "GUI/Component.hpp"

namespace LE {
    namespace GUI {
        class Container : public Component {
            public:
                virtual ~Container() = default;

                void addChildren(Component *child);
                void removeChildren(unsigned int id);
                void draw() override;

            protected:
                std::vector<Component *> _children;
        };
    }
}

#endif /* !CONTAINER_HPP_ */
