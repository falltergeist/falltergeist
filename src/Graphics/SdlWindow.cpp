#include "../Graphics/SdlWindow.h"
#include "../Graphics/SdlDisplay.h"

namespace Falltergeist {
    namespace Graphics {
        SdlWindow::SdlWindow(const std::string& title, const Rectangle& boundaries, bool isFullscreen, std::shared_ptr<ILogger> logger)
            : _title(title), _boundaries(boundaries), _isFullscreen(isFullscreen), _logger(logger) {

//            // enumerate displays
//            int displays = SDL_GetNumVideoDisplays();
//            assert( displays > 1 );  // assume we have secondary monitor
//
//            // get display bounds for all displays
//            vector< SDL_Rect > displayBounds;
//            for( int i = 0; i < displays; i++ ) {
//                displayBounds.push_back( SDL_Rect() );
//                SDL_GetDisplayBounds( i, &displayBounds.back() );
//            }
//
//            // window of dimensions 500 * 500 offset 100 pixels on secondary monitor
//            int x = displayBounds[ 1 ].x + 100;
//            int y = displayBounds[ 1 ].y + 100;
//            int w = 500;
//            int h = 500;
//
//            // so now x and y are on secondary display
//            SDL_Window * window = SDL_CreateWindow( "title", x, y, w, h, FLAGS... );


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

            auto sdlDisplay = SdlDisplay::getAvailableDisplays().at(0);
            auto windowPosition = _boundaries.position() + sdlDisplay.boundaries().position();

            _sdlWindow = SDL_CreateWindow(
                _title.c_str(),
                windowPosition.x(),
                windowPosition.y(),
                _boundaries.size().width(),
                _boundaries.size().height(),
                flags
            );

            if (_sdlWindow == nullptr) {
                _logger->critical() << "Could not create SDL window: " << SDL_GetError() << std::endl;
            }

            _id = SDL_GetWindowID(_sdlWindow);
            if (_id == 0) {
                _logger->critical() << "Could not get window id: " << SDL_GetError() << std::endl;
            }
        }

        unsigned int SdlWindow::id() const {
            return _id;
        }

        SdlWindow::~SdlWindow() {
            SDL_DestroyWindow(_sdlWindow);
        }

        const std::string& SdlWindow::title() const {
            return _title;
        }

        const Rectangle& SdlWindow::boundaries() const {
            return _boundaries;
        }

        bool SdlWindow::isFullscreen() const {
            return _isFullscreen;
        }

        SDL_Window* SdlWindow::sdlWindowPtr() const {
            return _sdlWindow;
        }
    }
}
