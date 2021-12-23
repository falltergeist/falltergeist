#include "../Graphics/SdlWindow.h"

namespace Falltergeist {
    namespace Graphics {
        SdlWindow::SdlWindow(const std::string& title, const Point& position, const Size& size, bool isFullscreen, std::shared_ptr<ILogger> logger)
            : _title(title), _position(position), _size(size), _isFullscreen(isFullscreen), _logger(logger) {

            Uint32 flags = SDL_WindowFlags::SDL_WINDOW_SHOWN | SDL_WindowFlags::SDL_WINDOW_OPENGL;

            if (_isFullscreen) {
                flags |= SDL_WindowFlags::SDL_WINDOW_FULLSCREEN;
            }

//            if (_rendererConfig->isAlwaysOnTop()) {
//                // SDL_WINDOW_ALWAYS_ON_TOP is available on X11 only, >= SDL 2.0.5
//                flags |= 0x00008000; // Copied from SDL_WindowFlags::SDL_WINDOW_ALWAYS_ON_TOP
//            }

            if (SDL_WasInit(SDL_INIT_VIDEO) == 0) {
                if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
                    logger->critical() << "Could not init SDL video subsystem: " << SDL_GetError() << std::endl;
                }
            }

            _sdlWindow = SDL_CreateWindow(
                _title.c_str(),
                _position.x(),
                _position.y(),
                _size.width(),
                _size.height(),
                flags
            );

            if (_sdlWindow == nullptr) {
                _logger->critical() << "Could not create SDL window: " << SDL_GetError() << std::endl;
            }

            SDL_ShowCursor(0); // Hide cursor
        }

        SdlWindow::~SdlWindow() {
            SDL_ShowCursor(1); // Show cursor
            SDL_DestroyWindow(_sdlWindow);
        }

        const std::string& SdlWindow::title() const {
            return _title;
        }

        const Point& SdlWindow::position() const {
            return _position;
        }

        const Size& SdlWindow::size() const {
            return _size;
        }

        bool SdlWindow::isFullscreen() const {
            return _isFullscreen;
        }

        const Point& SdlWindow::mousePosition() const {
            return _mousePosition;
        }

        void SdlWindow::setMousePosition(const Point& position) {
            _mousePosition = position;
            SDL_WarpMouseInWindow(_sdlWindow, _mousePosition.x(), _mousePosition.y());
        }

        void SdlWindow::pollEvents() {
            SDL_GetMouseState(&_mousePosition.rx(), &_mousePosition.ry());
        }

        SDL_Window* SdlWindow::sdlWindowPtr() const {
            return _sdlWindow;
        }
    }
}