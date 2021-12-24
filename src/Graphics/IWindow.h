#pragma once

#include <string>
#include "../Graphics/Point.h"
#include "../Graphics/Size.h"
#include "../Graphics/Rectangle.h"

namespace Falltergeist {
    namespace Graphics {
        class IWindow {
        public:
            virtual ~IWindow() = default;

            virtual const std::string& title() const = 0;

            virtual const Rectangle& boundaries() const = 0;

            virtual bool isFullscreen() const = 0;

            virtual void pollEvents() = 0;
        };
    }
}
