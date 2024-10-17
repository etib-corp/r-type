/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** Logger
*/

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <iostream>
#include <fstream>
#include <mutex>
#include <memory>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "interface/ILogger/ILogger.hpp"
#include "LogDef.hpp"

class Logger : public ILoggable
{
    public:
        [[nodiscard]] static Logger &getInstance(LogOutput output = LogOutput::FILE, const std::string &fileName = "server.log", bool enableColor = true)
        {
            static Logger instance(output, fileName, enableColor);
            return instance;
        }

        void logInfo(const std::string& message, std::ostream* forcedStream = nullptr) override
        {
            logMessage("[INFO]: " + message, LogColor::GREEN, forcedStream);
        }

        void logError(const std::string &message, std::ostream *forcedStream = nullptr) override
        {
            logMessage("[ERROR]: " + message, LogColor::RED, forcedStream);
        }

        void logWarning(const std::string &message, std::ostream *forcedStream = nullptr) override
        {
            logMessage("[WARNING]: " + message, LogColor::YELLOW, forcedStream);
        }

        void logDebug(const std::string &message, std::ostream *forcedStream = nullptr) override
        {
            logMessage("[DEBUG]: " + message, LogColor::BLUE, forcedStream);
        }

        void logCritical(const std::string &message, std::ostream *forcedStream = nullptr) override
        {
            logMessage("[CRITICAL]: " + message, LogColor::MAGENTA, forcedStream);
        }

        template<LogType logType = LogType::INFO, std::ostream *streamOverride = nullptr, typename ...Args>
        void log(const std::string &format, Args&&... args)
        {
            std::lock_guard<std::mutex> lock(_mutex);

            switch (logType)
            {
                case LogType::INFO:
                    logInfo(vformat(format, make_format_args(args...)), streamOverride);
                    break;
                case LogType::ERR:
                    logError(vformat(format, make_format_args(args...)), streamOverride);
                    break;
                case LogType::WARN:
                    logWarning(vformat(format, make_format_args(args...)), streamOverride);
                    break;
                case LogType::DEBUG:
                    logDebug(vformat(format, make_format_args(args...)), streamOverride);
                    break;
                case LogType::CRITICAL:
                    logCritical(vformat(format, make_format_args(args...)), streamOverride);
                    break;
                default:
                    logMessage("[DEFAULT]: " + vformat(format, make_format_args(args...)), LogColor::GREEN, streamOverride);
            }
        }

        void setColorEnabled(bool enable)
        {
            _colorEnabled = enable;
        }

    private:
        std::ofstream _logFile;
        std::mutex _mutex;
        LogOutput _logOutput;
        bool _colorEnabled;

        Logger(LogOutput output, const std::string &fileName, bool enableColor)
            : _logOutput(output), _colorEnabled(enableColor)
        {
            if (_logOutput == LogOutput::FILE)
            {
                _logFile.open(fileName, std::ios::app);
                if (!_logFile.is_open())
                    std::cerr << "Error: Could not open log file!" << std::endl;
            }
        }

        ~Logger()
        {
            if (_logOutput == LogOutput::FILE && _logFile.is_open())
                _logFile.close();
        }

        Logger(const Logger&) = delete;
        Logger &operator=(const Logger&) = delete;

        enum class LogColor {
            DEFAULT = 0,
            BLUE    = 1,
            GREEN   = 2,
            MAGENTA = 3,
            RED     = 4,
            YELLOW  = 5,
        };

        [[nodiscard]] std::string getColorCode(LogColor color) const
        {
            if (!_colorEnabled)
                return "";

            switch (color)
            {
                case LogColor::RED:
                    return "\033[31m";
                case LogColor::GREEN:
                    return "\033[32m";
                case LogColor::YELLOW:
                    return "\033[33m";
                case LogColor::BLUE:
                    return "\033[34m";
                case LogColor::MAGENTA:
                    return "\033[35m";
                case LogColor::DEFAULT:
                    return "\033[0m";
            }
            return "\033[0m";
        }

        void logMessage(const std::string &message, LogColor color, std::ostream *forcedStream = nullptr)
        {
            std::string timestampedMessage = getCurrentTime() + " " + message;
            std::string colorCode = getColorCode(color);
            std::string resetCode = getColorCode(LogColor::DEFAULT);

            if (forcedStream)
                *forcedStream << timestampedMessage << std::endl;

            switch (_logOutput)
            {
                case LogOutput::FILE:
                    if (_logFile.is_open())
                        _logFile << timestampedMessage << std::endl;
                    break;
                case LogOutput::STDOUT:
                    std::cout << colorCode << timestampedMessage << resetCode << std::endl;
                    break;
                case LogOutput::STDERR:
                    std::cerr << colorCode << timestampedMessage << resetCode << std::endl;
                    break;
                default:
                    std::cerr << "Unknown log output." << std::endl;
                    break;
            }
        }

        [[nodiscard]] std::string getCurrentTime(void)
        {
            auto now = std::chrono::system_clock::now();
            auto now_time_t = std::chrono::system_clock::to_time_t(now);
            std::ostringstream oss;

            oss << std::put_time(std::localtime(&now_time_t), "%Y-%m-%d %H:%M:%S");
            return oss.str();
        }
};

#endif /* !LOGGER_HPP_ */
