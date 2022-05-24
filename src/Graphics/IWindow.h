#pragma once

// Project includes
#include "../Graphics/Point.h"
#include "../Graphics/Size.h"
#include "../Graphics/Rectangle.h"

// Third-party includes

// stdlib
#include <string>

namespace Falltergeist {
    namespace Graphics {
        class IWindow {
        public:
            virtual ~IWindow() = default;

            virtual unsigned int id() const = 0;

            virtual const std::string& title() const = 0;

            virtual const Rectangle& boundaries() const = 0;

            virtual bool isFullscreen() const = 0;
        };
    }
}
