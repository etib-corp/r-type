/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Text
*/

#pragma once

#include "GUI/Component.hpp"

#include <GLFW/glfw3.h>
#include "GL/glut.h"
#include "GL/freeglut.h"

namespace LE {
    namespace GUI {
        class Text final : public Component {
            public:
                Text(unsigned int id, const std::string &content);
                ~Text();

                void draw() override;
            protected:
                std::string _content;
                // Vector2<unsigned int> _size;
                // Color _color;
        };
    }
}
