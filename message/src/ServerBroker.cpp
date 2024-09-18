/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ServerBroker.cpp
*/

#include "ServerBroker.hpp"

ServerBroker* ServerBroker::_instance = nullptr;
std::mutex ServerBroker::_mutex;
