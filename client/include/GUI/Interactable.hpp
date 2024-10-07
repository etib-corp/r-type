/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Interactable
*/

#pragma once

#include "Engine.hpp"

#include "GUI/Container.hpp"

namespace LE {
    namespace GUI {
        /**
         * @brief Interface for interactable GUI objects
         */
        class Interactable : public Container {
            public:
                virtual ~Interactable() = default;

                virtual void OnClick() = 0;

                virtual void OnHover() = 0;

                virtual void OnUnhover() = 0;

                [[nodiscard]] bool isHover();
        };
    }
}
