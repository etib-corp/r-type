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
#include "interface/INetworkModule.hpp"

#ifdef __linux__
    #include <dlfcn.h>

    /**
     * @brief Opens a library.
     */
    #define OPEN_SYM(path, var) \
        var = dlopen(path.c_str(), RTLD_LAZY)

    /**
     * @brief Loads a symbol from a library.
     */
    #define LOAD_SYM(libHandle, var, sym, type) \
        if ((type)dlsym(libHandle, sym) != NULL) \
                var = (type)dlsym(libHandle, sym);

#endif // __linux__

#ifdef __APPLE__
    #include <dlfcn.h>

    /**
     * @brief Opens a library.
     */
    #define OPEN_SYM(path, var) \
        var = dlopen(path.c_str(), RTLD_LAZY)

    /**
     * @brief Loads a symbol from a library.
     */
    #define LOAD_SYM(libHandle, var, sym, type) \
        if ((type)dlsym(libHandle, sym) != NULL) \
                var = (type)dlsym(libHandle, sym);

#endif // __APPLE__

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #include <windows.h>

    /**
     * @brief Opens a library.
     */
    #define OPEN_SYM(path, var) \
        var = LoadLibrary(path.c_str())

    /**
     * @brief Loads a symbol from a library.
     */
    #define LOAD_SYM(libHandle, var, sym, type) \
        if ((type)GetProcAddress(libHandle, sym) != NULL) \
                var = (type)GetProcAddress(libHandle, sym);

#endif // __WIN__

class LoaderLibError : public std::exception {
    public:
        LoaderLibError(const std::string& message): _message(message) {};
        const char *what() const noexcept override { return _message.c_str(); }

    protected:
        std::string _message;
};

/**
 * @class LoaderLib
 * @brief The LoaderLib class is responsible for loading network and core modules dynamically.
 *
 * The LoaderLib class provides functionality to load network and core modules dynamically. It allows creating network modules and checking if the modules are currently being loaded.
 *
 * @note This class assumes that the network and core modules are implemented using the INetworkModule interface.
 */
class LoaderLib {
    public:
        /**
         * @brief Constructs a LoaderLib object with the specified network module and core module.
         *
         * @param NetworkModule The path to the network module.
         * @param CoreModule The path to the core module.
         */
        LoaderLib(const std::string& NetworkModule, const std::string& CoreModule);
        ~LoaderLib();
        /**
         * @brief Checks if the loader is currently loading.
         *
         * This function checks if the loader is currently loading by attempting to load the network module.
         * If the network module fails to load, an exception of type LoaderLibError is thrown with the corresponding error message.
         *
         * @throws LoaderLibError If the network module fails to load.
         */
        void LoadModule(void);

        /**
         * @brief Creates a network module.
         *
         * @return Pointer to an INetworkModule object.
         */
        INetworkModule *createNetworkModule(void);

    protected:

        /**
         * @brief Path to the network module.
         */
        std::string _pathNetworkModule;

        /**
         * @brief Path to the core module.
         */
        std::string _pathCoreModule;

        /**
         * @brief Function to create a network module.
         */
        std::function<INetworkModule*()> _createNetworkModule;

        /**
         * @brief Contains the handle to the network module.
         */
        void *_handleNetworkModule;

        /**
         * @brief Contains the handle to the core module.
         */
        void *_handleCoreModule;
    private:
};

#endif /* !LOADERLIB_HPP_ */
