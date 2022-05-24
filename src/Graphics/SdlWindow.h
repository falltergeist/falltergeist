#pragma once

// Project includes
#include "../Graphics/IWindow.h"
#include "../ILogger.h"

// Third-party includes
#include <SDL.h>

// stdlib
#include <memory>

namespace Falltergeist {
    namespace Game {
        class Game;
    }
    namespace Graphics {
        class SdlWindow final : public IWindow {
        public:
            SdlWindow(const std::string& title, const Rectangle& boundaries, bool isFullscreen, std::shared_ptr<ILogger> logger);

            ~SdlWindow() override;

            unsigned int id() const override;

            const std::string& title() const override;

            const Rectangle& boundaries() const override;

            bool isFullscreen() const override;

            SDL_Window* sdlWindowPtr() const;

        private:
            friend class Game::Game;

            const unsigned int DEFAULT_DISPLAY_NUMBER = 0;

            unsigned int _id = 0;

            std::string _title;

            Rectangle _boundaries;

            bool _isFullscreen;

            SDL_Window* _sdlWindow = nullptr;

            std::shared_ptr<ILogger> _logger;
        };
    }
}
