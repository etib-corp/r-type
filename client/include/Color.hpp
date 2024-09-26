/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Color
*/

#pragma once

using Color = union {
    unsigned int value;
    struct {
        unsigned char r, g, b, a;
    };
};
