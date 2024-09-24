/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Manager
*/

#pragma once

#include <vector>

#include "Container.hpp"

namespace LE {
    namespace GUI {
        class Manager final : public Container {
            public:
                Manager(unsigned int width, unsigned int height);
                ~Manager();

                void init();
        };
    }
}
