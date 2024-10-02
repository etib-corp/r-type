/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Interactable
*/

#include "GUI/Interactable.hpp"

void LE::GUI::Interactable::OnClick()
{

    auto width = LE::Engine::getInstance()->_window->_width;
    auto height = LE::Engine::getInstance()->_window->_height;

    if (_x < width && _x > 0) {
        if (_y < height && _y > 0) {
            _hovered = true;
            glfwSetMouseButtonCallback(LE::Engine::getInstance()->_window->_window, _onClickCallback);
            return;
        }
    }
    _hovered = false;
}

void LE::GUI::Interactable::OnHover()
{
    auto width = LE::Engine::getInstance()->_window->_width;
    auto height = LE::Engine::getInstance()->_window->_height;

    if (_x < width && _x > 0) {
        if (_y < height && _y > 0) {
            _hovered = true;
            return;
        }
    }
    _hovered = false;
}