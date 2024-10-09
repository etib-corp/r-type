/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** TextField
*/

#pragma once

#include "GUI/Interactable.hpp"
#include "GUI/Text.hpp"

namespace LE {
    namespace GUI {
        class TextField : public Interactable {
            public:
                TextField(float x, float y, float width, float height, const std::string &label, LE::Color *bgColor, LE::Color *textColor);
                ~TextField();

                void setMaxChars(unsigned int maxChars);

                void draw() override;

                void init() override;

                void OnClick() override;

                void OnHover() override;

                void OnUnhover() override;

            protected:
                LE::GUI::Text *_label;
                LE::GUI::Text *_content;
                bool _focused;
                unsigned int _maxChars = 18;
        };
    }
}
