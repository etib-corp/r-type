/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** LogDef
*/

#ifndef LOG_DEF_HPP_
#define LOG_DEF_HPP_

enum class LogOutput {
    STDOUT  = 0,
    STDERR  = 1,
    FILE    = 2
};

enum class LogType {
    INFO        = 0,
    ERR         = 1,
    WARN        = 2,
    DEBUG       = 3,
    CRITICAL    = 4
};

#endif /* !LOG_DEF_HPP_ */
