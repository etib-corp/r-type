/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Container
*/

#include "GUI/Container.hpp"

void LE::GUI::Container::addChildren(Component *child)
{
    _children.push_back(child);
}

void LE::GUI::Container::removeChildren(unsigned int id)
{
    for (auto it = _children.begin(); it != _children.end(); it++) {
        if ((*it)->getId() == id) {
            _children.erase(it);
            break;
        }
    }
}

void LE::GUI::Container::draw()
{
    for (auto child : _children) {
        child->draw();
    }
}
