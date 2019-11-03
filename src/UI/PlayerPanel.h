#pragma once

#include <memory>
#include <vector>
#include "../UI/Base.h"
#include "../UI/ImageButton.h"

namespace Falltergeist
{
    namespace Event
    {
        class Keyboard;
    }
    namespace UI
    {
        class Image;
        class SmallCounter;
        class TextArea;

        class PlayerPanel : public UI::Base
        {
            public:
                PlayerPanel();
                ~PlayerPanel() override;

                Size size() const override;

                void render(bool eggTransparency = false) override;
                void handle(Event::Event *event) override;
                void think(float deltaTime) override;

                virtual bool opaque(const Point &pos) override;

                void displayMessage(const std::string& message);

                void playWindowOpenSfx();

            private:

                std::shared_ptr<Image> _background;
                std::shared_ptr<SmallCounter> _hitPoints;
                std::shared_ptr<SmallCounter> _armorClass;
                std::shared_ptr<TextArea> _messageLog;
                std::vector<std::shared_ptr<UI::Base>> _ui;

                bool _isAttackBtnPressed;

                char _scrollingLog = 0;
                // TODO: replace with real timer
                unsigned int _scrollingLogTimer = 0;

                void renderHandSlot();

                void changeHand();
                void openCharacterScreen();
                void openGameMenu();
                void openInventory();
                void openMap();
                void openPipBoy();
                void openSkilldex();
                void openSaveGame();
                void openLoadGame();

                void onKeyDown(Event::Keyboard* event);
        };
    }
}
