/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** globalLogger
*/

#include "globalLogger.hpp"

Logger *rtypeLog = nullptr;

// WARN : do not call iostream method in this function
// TODO : add doc
void initLogger(void)
{
    rtypeLog = &Logger::getInstance(LogOutput::STDOUT);

    rtypeLog->setColorEnabled(true);
}
