/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ClientBroker.cpp
*/

#include "ClientBroker.hpp"

ClientBroker* ClientBroker::_instance = nullptr;
std::mutex ClientBroker::_mutex;