/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** globalLogger
*/

#ifndef GLOBALLOGGER_HPP_
#define GLOBALLOGGER_HPP_

#include "Logger.hpp"

#include <stdio.h>
#include <stdlib.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

    #ifdef __cplusplus
        #define INITIALIZER(f) \
            static void f(void); \
            struct f##_t_ { f##_t_(void) { f(); } }; static f##_t_ f##_; \
            static void f(void)
    #elif defined(_MSC_VER)
        #pragma section(".CRT$XCU",read)
        #define INITIALIZER2_(f,p) \
            static void f(void); \
            __declspec(allocate(".CRT$XCU")) void (*f##_)(void) = f; \
            __pragma(comment(linker,"/include:" p #f "_")) \
            static void f(void)
        #ifdef _WIN64
            #define INITIALIZER(f) INITIALIZER2_(f,"")
        #else
            #define INITIALIZER(f) INITIALIZER2_(f,"_")
        #endif
    #else
        #define INITIALIZER(f) \
            static void f(void) __attribute__((constructor)); \
            static void f(void)
    #endif
#endif

#if defined(__linux__) || defined(__APPLE__)

void initLogger(void) __attribute__((constructor));

#endif

extern Logger *rtypeLog;

#endif /* !GLOBALLOGGER_HPP_ */
