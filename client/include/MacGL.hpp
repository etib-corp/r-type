#pragma once

#ifdef __APPLE__
    #define glBindVertexArray glBindVertexArrayAPPLE
    #define glDeleteVertexArrays glDeleteVertexArraysAPPLE
#endif

#ifdef __APPLE__
    #define glGenVertexArrays glGenVertexArraysAPPLE
    #define glDeleteVertexArrays glDeleteVertexArraysAPPLE
#endif