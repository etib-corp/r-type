/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Button
*/

#include "GUI/Button.hpp"

LE::GUI::Button::Button(float x, float y, float width, float height, const std::string &content, Color *bgColor, Color *textColor)
{
    auto text = new LE::GUI::Text(280604, "assets/fonts/ARIAL.TTF", 24, content, textColor);
    _x = x;
    _y = y;
    _width = width;
    _height = height;

    _background = new LE::Shapes::Rectangle(x, y, width, height, bgColor);

    addChildren(text);
}

LE::GUI::Button::~Button()
{
}

void LE::GUI::Button::draw()

{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClear(GL_DEPTH_BUFFER_BIT);

    if (_background)
        _background->draw();
    glDisable(GL_DEPTH_TEST);

    for (auto &child : _children) {
        child->draw();
    }
}

void LE::GUI::Button::OnClick()
{
    std::cout << "Button clicked !" << std::endl;
}

void LE::GUI::Button::OnHover()
{
    _background->_color->set(LE::Color::CHAR, 0, 255, 0, 255);
}

void LE::GUI::Button::OnUnhover()
{
    _background->_color->set(LE::Color::CHAR, 255, 0, 0, 255);
}

