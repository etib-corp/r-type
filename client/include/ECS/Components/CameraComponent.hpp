/*
** EPITECH PROJECT, 2024
** Visual Studio Live Share (Workspace)
** File description:
** CameraComponent
*/

#ifndef CAMERACOMPONENT_HPP_
    #define CAMERACOMPONENT_HPP_

#include "Maths/Vector3.hpp"
#include "Maths/Vector2.hpp"

struct CameraComponent {
    float width;
    float height;
    float near;
    float far;
    float fovy;
    float aspect;
    LE::Vector3<float> speed;
    LE::Vector2<float> sensitivity;
};

#endif /* !CAMERACOMPONENT_HPP_ */
