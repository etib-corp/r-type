/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Container
*/

#include "GUI/Container.hpp"

#include "GUI/Interactable.hpp"
#include "GUI/Text.hpp"

void LE::GUI::Container::addChildren(std::shared_ptr<Component> child)
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
    if (_background) {
        _background->resize(_width, _height);
        _background->draw();
    }
    glDisable(GL_DEPTH_TEST);

    for (auto& child : _children) {
        child->draw();
    }
}

void LE::GUI::Container::init()
{
    float totalHeight = 0.0f;

    for (auto child : _children) {
        if (child->getWidth() > _width) {
            _width = child->getWidth();
        }
        totalHeight += child->getHeight();
    }
    _height = totalHeight > _height ? totalHeight : _height;

    auto lastPos = _y + _height - ((_height / 2) - (totalHeight / 2));
    for (auto child : _children) {
        child->setPos(_x + (_width / 2) - (child->getWidth() / 2), lastPos - child->getHeight());
        lastPos -= child->getHeight();
        child->init();
    }
    if (_background)
        _background = new LE::Shapes::Rectangle(_width, _height, _x, _y, _background->_color);
    else
        _background = new LE::Shapes::Rectangle(_width, _height, _x, _y);

    _background->init();
}
