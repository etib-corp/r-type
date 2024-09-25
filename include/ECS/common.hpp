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
#include <set>
#include <unordered_map>

typedef unsigned int Entity;                    ///< An entity is a unique identifier for an object in the ECS
const Entity MAX_ENTITIES = 5000;               ///< The maximum number of entities

typedef unsigned int ComponentType;             ///< A component type is a unique identifier for a component
const ComponentType MAX_COMPONENTS = 64;        ///< The maximum number of components

typedef std::bitset<MAX_COMPONENTS> Signature;  ///< A signature is a bitset that represents the components an entity has

