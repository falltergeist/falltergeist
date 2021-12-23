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
            SdlWindow(const std::string& title, const Point& position, const Size& size, bool isFullscreen, std::shared_ptr<ILogger> logger);

            ~SdlWindow() override;

            const std::string& title() const override;

            const Point& position() const override;

            const Size& size() const override;

            bool isFullscreen() const override;

            const Point& mousePosition() const override;

            void setMousePosition(const Point& position) override;

            void pollEvents() override;

            SDL_Window* sdlWindowPtr() const;

        private:
            friend class Game::Game;

            std::string _title;

            Point _position;

            Size _size;

            bool _isFullscreen;

            mutable Point _mousePosition{320, 240};

            SDL_Window* _sdlWindow = nullptr;

            std::shared_ptr<ILogger> _logger;
        };
    }
}