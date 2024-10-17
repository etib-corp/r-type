#ifdef __linux__
    #define LIBRARY_API
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

    #ifdef LIBRARY_EXPORTS
        #define LIBRARY_API __declspec(dllexport)
    #else
        #define LIBRARY_API __declspec(dllimport)
    #endif

#endif
