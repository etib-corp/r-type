/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Triangle
*/

#include "Shapes/Triangle.hpp"

LE::Shapes::Triangle::Triangle(Vector3<float> p1, Vector3<float> p2, Vector3<float> p3)
{
    _p1 = p1;
    _p2 = p2;
    _p3 = p3;

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);

    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);

    float vertices[] = {
        _p1.x, _p1.y, _p1.z,
        _p2.x, _p2.y, _p2.z,
        _p3.x, _p3.y, _p3.z
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
    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);

    float vertices[] = {
        _p1.x, _p1.y, _p1.z,
        _p2.x, _p2.y, _p2.z,
        _p3.x, _p3.y, _p3.z
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    triangleShader->use();
    glBindVertexArray(_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void LE::Shapes::Triangle::init()
{
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
}
