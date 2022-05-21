#pragma once

#include <memory>
#include <vector>
#include "../UI/Base.h"
#include "../ILogger.h"
#include "../UI/ImageButton.h"

namespace Falltergeist
{
    namespace Event
    {
        class Keyboard;
    }
    namespace UI
    {
        namespace Factory
        {
            class ImageButtonFactory;
        }
        class Image;
        class SmallCounter;
        class TextArea;

        class PlayerPanel final : public UI::Base
        {
            public:
                PlayerPanel(std::shared_ptr<ILogger> logger);

                ~PlayerPanel() override;

                const Graphics::Size& size() const override;

                void render(bool eggTransparency = false) override;

                void handle(Event::Event *event) override;

                void think(const float &deltaTime) override;

                virtual bool opaque(const Graphics::Point &pos) override;

                void displayMessage(const std::string& message);

                void playWindowOpenSfx();

            private:
                void _renderHandSlot();

                void _changeHand();

                void _openCharacterScreen();

                void _openGameMenu();

                void _openInventory();

                void _openMap();

                void _openPipBoy();

                void _openSkilldex();

                void _openSaveGame();

                void _openLoadGame();

                void _onKeyDown(Event::Keyboard* event);

                std::shared_ptr<ILogger> _logger;

                std::shared_ptr<UI::IResourceManager> _resourceManager;

                std::unique_ptr<UI::Factory::ImageButtonFactory> _imageButtonFactory;

                std::shared_ptr<Image> _background;

                std::shared_ptr<SmallCounter> _hitPoints;

                std::shared_ptr<SmallCounter> _armorClass;

                std::shared_ptr<TextArea> _messageLog;

                std::vector<std::shared_ptr<UI::Base>> _ui;

                Input::Mouse::Cursor _previousCursor = Input::Mouse::Cursor::NONE;

                bool _isAttackBtnPressed;

                char _scrollingLog = 0;

                // TODO: replace with real timer
                unsigned int _scrollingLogTimer = 0;
        };
    }
}
