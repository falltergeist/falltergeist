#pragma once

// Project includes
#include "../Graphics/Point.h"

// Third-party includes

// stdlib

namespace Falltergeist {
    namespace Input {
        /**
         * This class is an abstraction for platform specific mouse handling details
         */
        class IMouse {
        public:
            enum class CursorState {
                Shown,
                Hidden
            };

            virtual ~IMouse() = default;

            virtual const Graphics::Point& position() const = 0;

            virtual void setPosition(const Graphics::Point& position) = 0;

            virtual void setCursorState(CursorState state) = 0;

            virtual CursorState cursorState() const = 0;
        };
    }
}
