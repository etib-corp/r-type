/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Text
*/

#pragma once

#include "Shader.hpp"
#include "GUI/Component.hpp"
#include "GUI/Font.hpp"

namespace LE {
    namespace GUI {
        class Text final : public Component {
            public:
                Text(unsigned int id, const std::string &fontPath, unsigned int fontHeight, const std::string &content = "Hello World !", unsigned int fontWidth = 0);
                ~Text();

                void draw() override;

                void init() override;

            protected:
                std::string _content;
                LE::GUI::Font *_font;
                GLuint _VAO;
                GLuint _VBO;
                // Vector2<unsigned int> _size;
                // Color _color;
        };
    }
}
