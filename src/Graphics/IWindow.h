#pragma once

#include <string>
#include "../Graphics/Point.h"
#include "../Graphics/Size.h"

namespace Falltergeist {
    namespace Graphics {
        class IWindow {
        public:
            virtual ~IWindow() = default;

            virtual const std::string& title() const = 0;

            virtual const Point& position() const = 0;

            virtual const Size& size() const = 0;

            virtual bool isFullscreen() const = 0;
        };
    }
}