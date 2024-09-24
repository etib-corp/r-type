/*
** EPITECH PROJECT, 2024
** client
** File description:
** common
*/

#pragma once

#include <array>
#include <bitset>
#include <cmath>
#include "Error.hpp"
#include <map>
#include <memory>
#include <queue>
#include <unordered_map>

typedef unsigned int Entity;
const Entity MAX_ENTITIES = 5000;

typedef unsigned int ComponentType;
const ComponentType MAX_COMPONENTS = 64;

typedef std::bitset<MAX_COMPONENTS> Signature;

/**
 * @brief Define a component
 *
 * @param name The name of the component
 * @return struct name##Component
 */
#define COMPONENT(name) struct name##Component
