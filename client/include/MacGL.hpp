#pragma once

#ifdef __APPLE__
    #include <OpenGL/gl.h>
#else
    #include <GL/gl.h>
#endif

#ifdef __APPLE__
    #define glBindVertexArray glBindVertexArrayAPPLE
    #define glDeleteVertexArrays glDeleteVertexArraysAPPLE
#endif

#ifdef __APPLE__
    #define glGenVertexArrays glGenVertexArraysAPPLE
    #define glDeleteVertexArrays glDeleteVertexArraysAPPLE
#endif