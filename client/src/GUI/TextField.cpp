/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** TextField
*/

#include "GUI/TextField.hpp"

LE::GUI::TextField::TextField(float x, float y, float width, float height, const std::string &label, LE::Color *bgColor, LE::Color *textColor)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    _focused = false;
    _initialWidth = _width;

    _label = new LE::GUI::Text(280604, "assets/fonts/ARIAL.TTF", 24, label, textColor);
    _label->setPos(x, y + height - 24);
    _content = new LE::GUI::Text(280602, "assets/fonts/ARIAL.TTF", 32, "", textColor);
    _content->setPos(x, y + height - 32 - 24);
    _background = new LE::Shapes::Rectangle(x, y, width, height, bgColor);

    addChildren(_content);
    addChildren(_label);
}

LE::GUI::TextField::~TextField()
{
}

void LE::GUI::TextField::draw()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClear(GL_DEPTH_BUFFER_BIT);

    if (isHover()) {
        OnHover();
    } else {
        OnUnhover();
    }

    float maxWidth = 0.0f;

    for (auto &child : _children) {
        if (child->getWidth() > maxWidth)
            maxWidth = child->getWidth();
    }

    _width = maxWidth > _initialWidth ? maxWidth : _initialWidth;

    if (_background) {
        _background->resize(_width, _height);
        _background->draw();
    }
    glDisable(GL_DEPTH_TEST);

    for (auto &child : _children) {
        child->draw();
    }
}

void LE::GUI::TextField::OnClick()
{
    _focused = !_focused;
}

void LE::GUI::TextField::OnHover()
{
}

void LE::GUI::TextField::OnUnhover()
{
}

void LE::GUI::TextField::setMaxChars(unsigned int maxChars)
{
    _maxChars = maxChars;
}

void LE::GUI::TextField::init()
{
    LE::Engine *engine = LE::Engine::getInstance();
    std::shared_ptr<LE::Scene> scene = engine->_sceneManager->getCurrentScene();
    std::shared_ptr<LE::EventManager> eventManager = scene->_eventManager;

    LE::Engine::getInstance()->_sceneManager->getCurrentScene()->_eventManager->addEventListener({LE::MOUSE, LE_MOUSE_BUTTON_LEFT, LE::JUST_PRESSED}, [this](LE::Engine *engine, float dt) {
        if (isHover()) {
            OnClick();
        } else {
            _focused = false;
        }
    });
    eventManager->addEventListener({LE::KEYBOARD, LE_KEY_ENTER, LE::JUST_PRESSED}, [this](LE::Engine *, float dt) {
        _focused = false;
    });
    eventManager->addEventListener({LE::KEYBOARD, LE_KEY_NUMPAD_ENTER, LE::JUST_PRESSED}, [this](LE::Engine *, float dt) {
        _focused = false;
    });
    for (int key = LE_KEY_A; key <= LE_KEY_Z; key++) {
        eventManager->addEventListener({LE::KEYBOARD, key, LE::JUST_PRESSED}, [this, key](LE::Engine *, float dt) {
            if (_focused && _content->getContent().size() < _maxChars)
                _content->setContent(_content->getContent() + std::string(1, key));
        });
    }
    for (int key = LE_KEY_0; key <= LE_KEY_9; key++) {
        eventManager->addEventListener({LE::KEYBOARD, key, LE::JUST_PRESSED}, [this, key](LE::Engine *, float dt) {
            if (_focused && _content->getContent().size() < _maxChars)
                _content->setContent(_content->getContent() + std::string(1, key));
        });
    }
    for (int key = LE_KEY_NUMPAD_0; key <= LE_KEY_NUMPAD_9; key++) {
        eventManager->addEventListener({LE::KEYBOARD, key, LE::JUST_PRESSED}, [this, key](LE::Engine *, float dt) {
            if (_focused && _content->getContent().size() < _maxChars)
                _content->setContent(_content->getContent() + std::string(1, key));
        });
    }
    eventManager->addEventListener({LE::KEYBOARD, LE_KEY_SPACE, LE::JUST_PRESSED}, [this](LE::Engine *, float dt) {
        if (_focused && _content->getContent().size() < _maxChars)
            _content->setContent(_content->getContent() + " ");
    });
    eventManager->addEventListener({LE::KEYBOARD, LE_KEY_BACKSPACE, LE::JUST_PRESSED}, [this](LE::Engine *, float dt) {
        if (_content->getContent().size() > 0 && _focused)
            _content->setContent(_content->getContent().substr(0, _content->getContent().size() - 1));
    });
    eventManager->addEventListener({LE::KEYBOARD, LE_KEY_DELETE, LE::JUST_PRESSED}, [this](LE::Engine *, float dt) {
        if (_focused && _content->getContent().size() < _maxChars)
            _content->setContent("");
    });
    eventManager->addEventListener({LE::KEYBOARD, LE_KEY_MINUS, LE::JUST_PRESSED}, [this](LE::Engine *, float dt) {
        if (_focused && _content->getContent().size() < _maxChars)
            _content->setContent(_content->getContent() + "-");
    });
    eventManager->addEventListener({LE::KEYBOARD, LE_KEY_NUMPAD_MINUS, LE::JUST_PRESSED}, [this](LE::Engine *, float dt) {
        if (_focused && _content->getContent().size() < _maxChars)
            _content->setContent(_content->getContent() + "-");
    });
    eventManager->addEventListener({LE::KEYBOARD, LE_KEY_EQUALS, LE::JUST_PRESSED}, [this](LE::Engine *, float dt) {
        if (_focused && _content->getContent().size() < _maxChars)
            _content->setContent(_content->getContent() + "=");
    });
    eventManager->addEventListener({LE::KEYBOARD, LE_KEY_PERIOD, LE::JUST_PRESSED}, [this](LE::Engine *, float dt) {
        if (_focused && _content->getContent().size() < _maxChars)
            _content->setContent(_content->getContent() + ".");
    });
    eventManager->addEventListener({LE::KEYBOARD, LE_KEY_COMMA, LE::JUST_PRESSED}, [this](LE::Engine *, float dt) {
        if (_focused && _content->getContent().size() < _maxChars)
            _content->setContent(_content->getContent() + ",");
    });
    eventManager->addEventListener({LE::KEYBOARD, LE_KEY_SLASH, LE::JUST_PRESSED}, [this](LE::Engine *, float dt) {
        if (_focused && _content->getContent().size() < _maxChars)
            _content->setContent(_content->getContent() + "/");
    });
    eventManager->addEventListener({LE::KEYBOARD, LE_KEY_SEMICOLON, LE::JUST_PRESSED}, [this](LE::Engine *, float dt) {
        if (_focused && _content->getContent().size() < _maxChars)
            _content->setContent(_content->getContent() + ";");
    });
    eventManager->addEventListener({LE::KEYBOARD, LE_KEY_QUOTE, LE::JUST_PRESSED}, [this](LE::Engine *, float dt) {
        if (_focused && _content->getContent().size() < _maxChars)
            _content->setContent(_content->getContent() + "'");
    });
    eventManager->addEventListener({LE::KEYBOARD, LE_KEY_LEFTBRACKET, LE::JUST_PRESSED}, [this](LE::Engine *, float dt) {
        if (_focused && _content->getContent().size() < _maxChars)
            _content->setContent(_content->getContent() + "[");
    });
    eventManager->addEventListener({LE::KEYBOARD, LE_KEY_RIGHTBRACKET, LE::JUST_PRESSED}, [this](LE::Engine *, float dt) {
        if (_focused && _content->getContent().size() < _maxChars)
            _content->setContent(_content->getContent() + "]");
    });
    eventManager->addEventListener({LE::KEYBOARD, LE_KEY_BACKSLASH, LE::JUST_PRESSED}, [this](LE::Engine *, float dt) {
        if (_focused && _content->getContent().size() < _maxChars)
            _content->setContent(_content->getContent() + "\\");
    });
    eventManager->addEventListener({LE::KEYBOARD, LE_KEY_TAB, LE::JUST_PRESSED}, [this](LE::Engine *, float dt) {
        if (_focused && _content->getContent().size() < _maxChars)
            _content->setContent(_content->getContent() + "\t");
    });

    float totalHeight = 0.0f;

    for (auto child : _children) {
        if (child->getWidth() > _width)
            _width = child->getWidth();
        totalHeight += child->getHeight();
    }
    _height = totalHeight > _height ? totalHeight : _height;

    auto lastPos = _y;
    for (auto child : _children) {
        if (child->getY() < _y || child->getY() > _y + _height) {
            child->setPos(child->getX(), lastPos);
        }
        if (child->getX() < _x || child->getX() > _x + _width)
            child->setPos(_x, child->getY());
        lastPos -= child->getHeight();
        child->init();
    }
    _background = new LE::Shapes::Rectangle(_width, _height, _x, _y);

    _background->init();
}
