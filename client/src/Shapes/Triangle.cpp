/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Triangle
*/

#include "Shapes/Triangle.hpp"

#include "Engine.hpp"

LE::Shapes::Triangle::Triangle(Vector3<float> p1, Vector3<float> p2, Vector3<float> p3, Color *color)
{
    _p1 = p1;
    _p2 = p2;
    _p3 = p3;

    _color = color ? color : new Color(LE::Color::FLOAT, 1.0f, 0.0f, 0.0f, 1.0f);

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);

    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);

    float vertices[] = {
        _p1.x, _p1.y, static_cast<float>(_p1.z),
        _p2.x, _p2.y, static_cast<float>(_p2.z),
        _p3.x, _p3.y, static_cast<float>(_p3.z)
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

LE::Shapes::Triangle::~Triangle()
{
}

void LE::Shapes::Triangle::move(Vector3<float> offset)
{
    _p1 += offset;
    _p2 += offset;
    _p3 += offset;
}

void LE::Shapes::Triangle::draw()
{
    auto width = Engine::getInstance()->_window->_width;
    auto height = Engine::getInstance()->_window->_height;

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));

    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);

    float vertices[9] = {
        ((2 * _p1.x) / width) - 1, ((2 * _p1.y) / height) - 1, static_cast<float>(_p1.z - 0.1),
        ((2 * _p2.x) / width) - 1, ((2 * _p2.y) / height) - 1, static_cast<float>(_p2.z - 0.1),
        ((2 * _p3.x) / width) - 1, ((2 * _p3.y) / height) - 1, static_cast<float>(_p3.z - 0.1)
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    triangleShader->use();
    triangleShader->setVec4("color", _color->toVector4());
    glUniformMatrix4fv(glGetUniformLocation(triangleShader->getID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glBindVertexArray(_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void LE::Shapes::Triangle::init()
{
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
}

void LE::Shapes::Triangle::resize(float width, float height)
{
    auto x = _p1.x;
    auto y = _p1.y;
    auto z = _p1.z;

    _p1 = Vector3<float>((2 * x) / width, (2 * y) / height, z);
    x = _p2.x;
    y = _p2.y;
    z = _p2.z;
    _p2 = Vector3<float>((2 * x) / width, (2 * y) / height, z);
    x = _p3.x;
    y = _p3.y;
    z = _p3.z;
    _p3 = Vector3<float>((2 * x) / width, (2 * y) / height, z);
}
