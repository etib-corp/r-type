/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Text
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include "GUI/Component.hpp"

#include <GLFW/glfw3.h>
#include "GL/glut.h"

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

#endif /* !TEXT_HPP_ */
