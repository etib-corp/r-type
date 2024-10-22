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

#if __cplusplus >= 202002L
    #include <format>
    using std::vformat;
    using std::make_format_args;
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    // #include <fmt/core.h>
    // using fmt::vformat;
    // using fmt::make_format_args;
    #include <format>
    using std::vformat;
    using std::make_format_args;
#endif

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
