#include "../Input/SdlMouse.h"
#include "../Exception.h"

namespace Falltergeist {
    namespace Input {
        SdlMouse::SdlMouse(std::shared_ptr<Graphics::SdlWindow> sdlWindow) : _sdlWindow(sdlWindow){
        }

        const Graphics::Point& SdlMouse::position() const {
            SDL_GetMouseState(&_position.rx(), &_position.ry());
            return _position;
        }

        void SdlMouse::setPosition(const Graphics::Point& position) {
            SDL_WarpMouseInWindow(_sdlWindow->sdlWindowPtr(), position.x(), position.y());
        }

        void SdlMouse::setCursorState(IMouse::CursorState state) {
            auto sdlCursorState = SDL_ENABLE;
            if (state == IMouse::CursorState::Hidden) {
                sdlCursorState = SDL_DISABLE;
            }

            if (SDL_ShowCursor(sdlCursorState) < 0) {
                throw new Exception(std::string("Could not set mouse cursor state: ") + SDL_GetError());
            }
        }

        IMouse::CursorState SdlMouse::cursorState() const {
            auto sdlCursorState = SDL_ShowCursor(SDL_QUERY);
            if (sdlCursorState < 0) {
                throw new Exception(std::string("Could not get mouse cursor state: ") + SDL_GetError());
            }

            if (sdlCursorState == SDL_ENABLE) {
                return CursorState::Shown;
            }

            return CursorState::Hidden;
        }
    }
}
