/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Text
*/

#include "GUI/Text.hpp"

LE::GUI::Text::Text(unsigned int id, const std::string &content) : _content(content)
{
    _id = id;
}

LE::GUI::Text::~Text()
{
}

void LE::GUI::Text::draw()
{
    // const char *string = _content.c_str();

    // glColor3f(1, 1, 1);
    // glRasterPos2f(0, 0);
    // for (int i = 0; i < _content.size(); i++) {
    //     glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, string[i]);
    // }
}