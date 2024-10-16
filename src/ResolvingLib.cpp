/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** ResolvingLib
*/

#include "ResolvingLib.hpp"

bool isWindows(void)
{
    #if defined(_WIN32) || defined(_WIN64)
    return true;
    #else
    return false;
    #endif
}

bool isMacOS(void)
{
    #if defined(__APPLE__) || defined(__MACH__)
    return true;
    #else
    return false;
    #endif
}

bool isLinux(void)
{
    #if defined(__linux__)
    return true;
    #else
    return false;
    #endif
}


std::string getExtensionKernel(void)
{
    if (isLinux())
        return ".so";
    if (isWindows())
        return ".dll";
    if (isMacOS())
        return ".dylib";
    return "";
}

std::string getPathOfNetworkDynLib(void)
{
    if (isLinux())
        return "./build/lib/NetworkModule/libNetworkModule";
    if (isWindows())
        return ".\\build\\lib\\NetworkModule\\Debug\\NetworkModuled";
    if (isMacOS())
        return "./build/lib/NetworkModule/libNetworkModule";
    return "";
}
