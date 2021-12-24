#pragma once

#include <memory>
#include "../Graphics/SdlWindow.h"
#include "../Input/IMouse.h"

namespace Falltergeist {
    namespace Input {
        class SdlMouse final : public IMouse {
        public:
            SdlMouse(std::shared_ptr<Graphics::SdlWindow> sdlWindow);

            ~SdlMouse() override = default;

            const Graphics::Point& position() const override;

            void setPosition(const Graphics::Point& position) override;

            void setCursorState(CursorState state) override;

            CursorState cursorState() const override;

        private:
            mutable Graphics::Point _position;

            std::shared_ptr<Graphics::SdlWindow> _sdlWindow;
        };
    }
}
