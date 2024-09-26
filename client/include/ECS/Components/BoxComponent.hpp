/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Box
*/

#pragma once

#include <bitset>
#include "Vector3.hpp"

#define NB_LAYERS 8
#define NB_MASKS NB_LAYERS

struct Box {
    int width;
    int height;
    int depth;
    std::bitset<NB_LAYERS> layers;
    std::bitset<NB_MASKS> masks;
};