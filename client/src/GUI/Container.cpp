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
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClear(GL_DEPTH_BUFFER_BIT);

    if (_background)
        _background->draw();
    glDisable(GL_DEPTH_TEST);

    for (auto& child : _children) {
        child->draw();
    }
}

void LE::GUI::Container::init()
{
    float totalHeight = 0.0f;

    for (auto child : _children) {
        if (child->getWidth() > _width)
            _width = child->getWidth();
        totalHeight += child->getHeight();
    }
    _height = totalHeight > _height ? totalHeight : _height;
    if (_height > _y)
        _y = _height;

    auto tmpHeight = _y + (_height / 2);
    for (auto child : _children) {
        auto newX = child->getWidth() == _width ? _x : _x + (_width / 2) - (child->getWidth() / 2);
        child->setPos(newX, tmpHeight + (child->getHeight() / 2));
        tmpHeight -= child->getHeight();
        child->init();
        child->setPos(newX - (child->getWidth() / 2), child->getY());
    }
    _background = new LE::Shapes::Rectangle(_width, _height, _x, _y);

    _background->init();
}
