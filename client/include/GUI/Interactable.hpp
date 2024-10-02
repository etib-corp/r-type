/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Interactable
*/

#pragma once

#include "Engine.hpp"

#include "GUI/Component.hpp"

namespace LE {
    namespace GUI {
        /**
         * @brief Interface for interactable GUI objects
         */
        class Interactable : public Component {
            public:
                /**
                 * @brief Destroy the Interactable object
                 */
                virtual ~Interactable() = default;

                void OnClick();

                void OnHover();

                bool _hovered = false;

            protected:
                void (*_onClickCallback)(GLFWwindow* window, int button, int action, int mods);
        };
    }
}
