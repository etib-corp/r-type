/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** globalLogger
*/

#include "globalLogger.hpp"

Logger *globalLogger = nullptr;

// WARN : do not call iostream method in this function
// TODO : add doc
void initLogger(void)
{
    globalLogger = &Logger::getInstance(LogOutput::STDOUT);

    globalLogger->setColorEnabled(true);
}
