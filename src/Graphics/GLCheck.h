#pragma once

#include <cstdlib>
#include <cstdio>
#include <GL/glew.h>

#define GL_CHECK(x) do { \
            x; \
            int _err = glGetError(); \
            if (_err) { \
                printf("GL Error %d at %d, %s in %s", _err, __LINE__, __func__, __FILE__); \
                exit(-1); \
            } \
        } while (0)
