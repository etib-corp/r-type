/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ILogger
*/

#ifndef ILOGGER_HPP_
#define ILOGGER_HPP_

#include <string>
#include <ostream>
#include <format>

class ILoggable
{
    public:
        virtual ~ILoggable() = default;
        virtual void logInfo(const std::string& message, std::ostream* forcedStream = nullptr) = 0;
        virtual void logError(const std::string& message, std::ostream* forcedStream = nullptr) = 0;
        virtual void logWarning(const std::string& message, std::ostream* forcedStream = nullptr) = 0;
        virtual void logDebug(const std::string& message, std::ostream* forcedStream = nullptr) = 0;
        virtual void logCritical(const std::string& message, std::ostream* forcedStream = nullptr) = 0;
};

#endif /* !ILOGGER_HPP_ */
