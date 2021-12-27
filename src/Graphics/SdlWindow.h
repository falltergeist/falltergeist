#pragma once

#include <memory>
#include "../Graphics/IWindow.h"
#include "../ILogger.h"
#include "SDL.h"

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

            unsigned int _id = 0;

            std::string _title;

            Rectangle _boundaries;

            bool _isFullscreen;

            SDL_Window* _sdlWindow = nullptr;

            std::shared_ptr<ILogger> _logger;
        };
    }
}
