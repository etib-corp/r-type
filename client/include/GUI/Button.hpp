/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Button
*/

#pragma once

#include "GUI/Interactable.hpp"
#include "GUI/Text.hpp"

namespace LE {
    namespace GUI {
        class Button : public Interactable {
            public:
                Button(float x, float y, float width, float height, const std::string &content, Color *bgColor, Color *textColor);
                ~Button();

                void draw() override;

                void OnClick() override;

                void OnHover() override;
        };
    }
}
