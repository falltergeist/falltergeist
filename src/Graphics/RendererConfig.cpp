#include "../Graphics/RendererConfig.h"

namespace Falltergeist
{
    namespace Graphics
    {
        RendererConfig::RendererConfig(
            uint32_t width,
            uint32_t height,
            int32_t x,
            int32_t y,
            bool isFullscreen,
            bool isAlwaysOnTop
        ) {
            _width = width;
            _height = height;
            _x = x;
            _y = y;
            _isFullscreen = isFullscreen;
            _isAlwaysOnTop = isAlwaysOnTop;
        }

        uint32_t RendererConfig::width()
        {
            return _width;
        }

        uint32_t RendererConfig::height()
        {
            return _height;
        }

        int32_t RendererConfig::x()
        {
            return _x;
        }

        int32_t RendererConfig::y()
        {
            return _y;
        }

        bool RendererConfig::isFullscreen()
        {
            return _isFullscreen;
        }

        bool RendererConfig::isAlwaysOnTop()
        {
            return _isAlwaysOnTop;
        }
    }
}
