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

    _bgColor = bgColor;
    _textColor = textColor;

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

    if (isHover()) {
        OnHover();
        LE::Engine::getInstance()->_sceneManager->getCurrentScene()->_eventManager->addEventListener({LE::MOUSE, LE_MOUSE_BUTTON_LEFT, LE::JUST_PRESSED}, [this](LE::Engine *engine, float dt) {
            if (isHover())
                OnClick();
        });
    } else {
        OnUnhover();
    }

    if (_background)
        _background->draw();
    glDisable(GL_DEPTH_TEST);

    for (auto &child : _children) {
        child->draw();
    }
}

void LE::GUI::Button::setOnClickCallback(std::function<void()> onClick)
{
    _onClick = onClick;
}

void LE::GUI::Button::setOnHoverCallback(std::function<void()> onHover)
{
    _onHover = onHover;
}

void LE::GUI::Button::setOnUnhoverCallback(std::function<void()> onUnhover)
{
    _onUnhover = onUnhover;
}

void LE::GUI::Button::OnClick()
{
    _bgColor->_a = 0.2;
    if (_onClick)
        _onClick();
}

void LE::GUI::Button::OnHover()
{
    if (_bgColor->_a >= 0.5)
        _bgColor->_a = 0.5;
    if (_onHover)
        _onHover();
}

void LE::GUI::Button::OnUnhover()
{
    _bgColor->_a = 1.0;
    _textColor->_a = 1.0;
    if (_onUnhover)
        _onUnhover();
    _background->resize(_width, _height);
}
