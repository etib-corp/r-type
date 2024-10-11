/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** globalLogger
*/

#ifndef GLOBALLOGGER_HPP_
#define GLOBALLOGGER_HPP_

#include "Logger.hpp"

void initLogger(void) __attribute__((constructor));

extern Logger *rtypeLog;

#endif /* !GLOBALLOGGER_HPP_ */
