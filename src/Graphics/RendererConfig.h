#pragma once

#include "../Graphics/IRendererConfig.h"

namespace Falltergeist
{
    namespace Graphics
    {
        class RendererConfig final : public IRendererConfig
        {
            public:
                RendererConfig(
                    uint32_t width,
                    uint32_t height,
                    int32_t x,
                    int32_t y,
                    bool isFullscreen,
                    bool isAlwaysOnTop
                );

                uint32_t width() override;
                uint32_t height() override;
                int32_t x() override;
                int32_t y() override;
                bool isFullscreen() override;
                bool isAlwaysOnTop() override;

            private:
                uint32_t _width;
                uint32_t _height;
                int32_t _x;
                int32_t _y;
                bool _isFullscreen;
                bool _isAlwaysOnTop;
        };
    }
}
