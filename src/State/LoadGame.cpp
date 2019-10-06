#include <sstream>
#include "../State/LoadGame.h"
#include "../Event/Event.h"
#include "../Event/Mouse.h"
#include "../Event/State.h"
#include "../functions.h"
#include "../Game/Game.h"
#include "../Graphics/Point.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../ResourceManager.h"
#include "../State/State.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/ImageList.h"
#include "../UI/TextArea.h"

namespace Falltergeist
{
    namespace State
    {
        LoadGame::LoadGame() : State()
        {
        }

        LoadGame::~LoadGame()
        {
        }

        void LoadGame::init()
        {
            if (_initialized) return;
            State::init();

            setModal(true);
            setFullscreen(true);

            auto game = Game::getInstance();
            //auto player = Game::getInstance()->player();

            // background
            auto bg = new UI::Image("art/intrface/lsgame.frm");
            Point bgPos = Point((game->renderer()->size() - bg->size()) / 2);
            auto bgX = bgPos.x();
            auto bgY = bgPos.y();
            bg->setPosition(bgPos);
            addUI(bg);

            // BUTTONS

            // button: up arrow
            addUI("button_up", new UI::ImageButton(UI::ImageButton::Type::SMALL_UP_ARROW, bgX+35, bgY+58));
            // button: down arrow
            addUI("button_down", new UI::ImageButton(UI::ImageButton::Type::SMALL_DOWN_ARROW, bgX+35, bgY+72));

            // button: Done
            auto doneButton = new UI::ImageButton(UI::ImageButton::Type::SMALL_RED_CIRCLE, bgX+391, bgY+349);
            doneButton->mouseClickHandler().add(std::bind(&LoadGame::onDoneButtonClick, this, std::placeholders::_1));
            addUI(doneButton);

            // button: Cancel
            auto cancelButton = new UI::ImageButton(UI::ImageButton::Type::SMALL_RED_CIRCLE, bgX+495, bgY+349);
            cancelButton->mouseClickHandler().add([this](Event::Event* event){ this->doCancel(); });
            addUI(cancelButton);

            // LABELS

            auto font3_907824ff = ResourceManager::getInstance()->font("font3.aaf");
            SDL_Color color = {0x90, 0x78, 0x24, 0xff};

            // LOAD GAME LABEL
            auto saveGameLabel = new UI::TextArea(_t(MSG_LOAD_SAVE, 110), bgX+48, bgY+27);
            saveGameLabel->setFont(font3_907824ff, color);
            addUI(saveGameLabel);

            // DONE BUTTON LABEL
            auto doneButtonLabel = new UI::TextArea(_t(MSG_OPTIONS, 300), bgX+410, bgY+348);
            doneButtonLabel->setFont(font3_907824ff, color);
            addUI(doneButtonLabel);

            // CANCEL BUTTON LABEL
            auto cancelButtonLabel = new UI::TextArea(_t(MSG_OPTIONS, 121), bgX+515, bgY+348);
            cancelButtonLabel->setFont(font3_907824ff, color);
            addUI(cancelButtonLabel);
        }

        void LoadGame::onDoneButtonClick(Event::Mouse* event)
        {
            Game::getInstance()->popState();
        }

        void LoadGame::doCancel()
        {
            if (!Game::getInstance()->locationState())
            {
                fadeDoneHandler().clear();
                fadeDoneHandler().add([this](Event::Event* event){ this->onCancelFadeDone(dynamic_cast<Event::State*>(event)); });
                Game::getInstance()->renderer()->fadeOut(255,255,255,1000);
            }
            else
            {
                Game::getInstance()->popState();
            }
        }

        void LoadGame::onCancelFadeDone(Event::State* event)
        {
            fadeDoneHandler().clear();
            Game::getInstance()->popState();
        }

        void LoadGame::onStateActivate(Event::State* event)
        {
            if (!Game::getInstance()->locationState())
                Game::getInstance()->renderer()->fadeIn(0,0,0,1000);
            Game::getInstance()->mouse()->pushState(Input::Mouse::Cursor::BIG_ARROW);
        }

        void LoadGame::onStateDeactivate(Event::State* event)
        {
            Game::getInstance()->mouse()->popState();
        }

        void LoadGame::onKeyDown(Event::Keyboard* event)
        {
            switch (event->keyCode())
            {
                case SDLK_ESCAPE:
                    doCancel();
                    break;
            }
        }
    }
}
