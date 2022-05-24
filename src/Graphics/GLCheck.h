#pragma once

// Project includes

// Third-party includes
#include <GL/glew.h>

// stdlib
#include <cstdlib>
#include <cstdio>

#define GL_CHECK(x) do { \
            x; \
            int _err = glGetError(); \
            if (_err) { \
                printf("GL Error %d at %d, %s in %s", _err, __LINE__, __func__, __FILE__); \
                exit(-1); \
            } \
        } while (0)
