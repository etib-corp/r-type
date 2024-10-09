/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Interactable
*/

#include "GUI/Interactable.hpp"

bool LE::GUI::Interactable::isHover()
{
    double mouseX, mouseY;
    glfwGetCursorPos(LE::Engine::getInstance()->_window->_window, &mouseX, &mouseY);
    int windowWidth, windowHeight;
    glfwGetWindowSize(LE::Engine::getInstance()->_window->_window, &windowWidth, &windowHeight);

    mouseY = windowHeight - mouseY;
    if (mouseX < _x + _width && mouseX > _x) {
        if (mouseY < _y + _height && mouseY > _y) {
            return true;
        }
    }
    return false;
}
