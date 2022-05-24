#pragma once

// Project includes

// Third-party includes

// stdlib
#include <cstdint>

namespace Falltergeist
{
    namespace Graphics
    {
        class IRendererConfig
        {
            public:
                virtual ~IRendererConfig() = default;
                virtual uint32_t width() = 0;
                virtual uint32_t height() = 0;
                virtual int32_t x() = 0;
                virtual int32_t y() = 0;
                virtual bool isFullscreen() = 0;
                virtual bool isAlwaysOnTop() = 0;
        };
    }
}
