/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** LoaderLib
*/

#ifndef LOADERLIB_HPP_
#define LOADERLIB_HPP_

#include <iostream>
#include <exception>
#include <memory>
#include <map>
#include <functional>
#include "interface/INetworkModule/INetworkModule.hpp"
#include "interface/INetworkModule/IClient.hpp"

#ifdef __linux__
#include <dlfcn.h>
#define LIB_HANDLE void *
#define OPEN_SYM(path, var) var = dlopen(path.c_str(), RTLD_LAZY)
#define CLOSE_SYM(handle) dlclose(handle)
#define LOAD_SYM(libHandle, var, sym, type) \
    var = (type)dlsym(libHandle, sym);      \
    if (!var)                               \
        throw LoaderLibError("Can't load symbol " + std::string(sym));
#elif defined(__APPLE__)
#include <dlfcn.h>
#define LIB_HANDLE void *
#define OPEN_SYM(path, var) var = dlopen(path.c_str(), RTLD_LAZY)
#define CLOSE_SYM(handle) dlclose(handle)
#define LOAD_SYM(libHandle, var, sym, type) \
    var = (type)dlsym(libHandle, sym);      \
    if (!var)                               \
        throw LoaderLibError("Can't load symbol " + std::string(sym));
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <windows.h>
#define LIB_HANDLE HMODULE
#define OPEN_SYM(path, var) var = LoadLibrary(path.c_str())
#define CLOSE_SYM(handle) FreeLibrary(handle)
#define LOAD_SYM(libHandle, var, sym, type)     \
    var = (type)GetProcAddress(libHandle, sym); \
    if (!var)                                   \
        throw LoaderLibError("Can't load symbol " + std::string(sym));
#else
#error "Unsupported platform"
#endif

/**
 * @class LoaderLibError
 * @brief Exception class for loader errors.
 */
class LoaderLibError : public std::exception
{
public:
    explicit LoaderLibError(const std::string &message) : _message(message) {}
    const char *what() const noexcept override { return _message.c_str(); }

private:
    std::string _message;
};

/**
 * @class LoaderLib
 * @brief Responsible for dynamically loading network and core modules.
 */
class LoaderLib
{
public:
    /**
     * @brief Constructs a LoaderLib object.
     * @param NetworkModule Path to the network module.
     * @param CoreModule Path to the core module.
     */
    LoaderLib(const std::string &NetworkModule, const std::string &CoreModule);

    /**
     * @brief Destructor cleans up loaded modules.
     */
    ~LoaderLib();

    /**
     * @brief Loads both the network and core modules.
     * @throws LoaderLibError If either module fails to load.
     */
    void LoadModule();

    /**
     * @brief Creates a network module instance.
     * @return A pointer to the created network module instance.
     */
    INetworkModule *createNetworkModule();

    // Future: Implement core module creation
    // ICoreModule* createCoreModule();

protected:
    std::string _pathNetworkModule; ///< Path to the network module.
    std::string _pathCoreModule;    ///< Path to the core module.

    std::function<INetworkModule *()> _createNetworkModule; ///< Function to create a network module.

    LIB_HANDLE _handleNetworkModule; ///< Handle to the network module.
    LIB_HANDLE _handleCoreModule;    ///< Handle to the core module.
};

#endif /* !LOADERLIB_HPP_ */
