#include <cstdint>
#include "../State/PlayerEditName.h"
#include "../functions.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../ResourceManager.h"
#include "../UI/Factory/ImageButtonFactory.h"
#include "../UI/TextArea.h"
#include "../UI/ImageButton.h"
#include "../UI/Image.h"
#include "../UI/Rectangle.h"

namespace Falltergeist
{
    using ImageButtonType = UI::Factory::ImageButtonFactory::Type;

    namespace State
    {
        PlayerEditName::PlayerEditName(std::shared_ptr<UI::IResourceManager> resourceManager)
            : State(), _resourceManager(resourceManager) {
            _imageButtonFactory = std::make_unique<UI::Factory::ImageButtonFactory>(_resourceManager);
        }

        void PlayerEditName::init()
        {
            if (_initialized) {
                return;
            }
            State::init();

            setFullscreen(false);
            setModal(true);

            Point bgPos = Point((Game::Game::getInstance()->renderer()->size() - Point(640, 480)) / 2);
            int bgX = bgPos.x();
            int bgY = bgPos.y();

            _keyCodes.insert(std::make_pair(SDLK_a, 'a'));
            _keyCodes.insert(std::make_pair(SDLK_b, 'b'));
            _keyCodes.insert(std::make_pair(SDLK_c, 'c'));
            _keyCodes.insert(std::make_pair(SDLK_d, 'd'));
            _keyCodes.insert(std::make_pair(SDLK_e, 'e'));
            _keyCodes.insert(std::make_pair(SDLK_f, 'f'));
            _keyCodes.insert(std::make_pair(SDLK_g, 'g'));
            _keyCodes.insert(std::make_pair(SDLK_h, 'h'));
            _keyCodes.insert(std::make_pair(SDLK_i, 'i'));
            _keyCodes.insert(std::make_pair(SDLK_j, 'j'));
            _keyCodes.insert(std::make_pair(SDLK_k, 'k'));
            _keyCodes.insert(std::make_pair(SDLK_l, 'l'));
            _keyCodes.insert(std::make_pair(SDLK_m, 'm'));
            _keyCodes.insert(std::make_pair(SDLK_n, 'n'));
            _keyCodes.insert(std::make_pair(SDLK_o, 'o'));
            _keyCodes.insert(std::make_pair(SDLK_p, 'p'));
            _keyCodes.insert(std::make_pair(SDLK_q, 'q'));
            _keyCodes.insert(std::make_pair(SDLK_r, 'r'));
            _keyCodes.insert(std::make_pair(SDLK_s, 's'));
            _keyCodes.insert(std::make_pair(SDLK_t, 't'));
            _keyCodes.insert(std::make_pair(SDLK_u, 'u'));
            _keyCodes.insert(std::make_pair(SDLK_v, 'v'));
            _keyCodes.insert(std::make_pair(SDLK_w, 'w'));
            _keyCodes.insert(std::make_pair(SDLK_x, 'x'));
            _keyCodes.insert(std::make_pair(SDLK_y, 'y'));
            _keyCodes.insert(std::make_pair(SDLK_z, 'z'));
            _keyCodes.insert(std::make_pair(SDLK_1, '1'));
            _keyCodes.insert(std::make_pair(SDLK_2, '2'));
            _keyCodes.insert(std::make_pair(SDLK_3, '3'));
            _keyCodes.insert(std::make_pair(SDLK_4, '4'));
            _keyCodes.insert(std::make_pair(SDLK_5, '5'));
            _keyCodes.insert(std::make_pair(SDLK_6, '6'));
            _keyCodes.insert(std::make_pair(SDLK_7, '7'));
            _keyCodes.insert(std::make_pair(SDLK_8, '8'));
            _keyCodes.insert(std::make_pair(SDLK_9, '9'));
            _keyCodes.insert(std::make_pair(SDLK_0, '0'));

            auto bg = _resourceManager->getImage("art/intrface/charwin.frm");
            bg->setPosition(bgPos + Point(22, 0));

            auto nameBox = _resourceManager->getImage("art/intrface/namebox.frm");
            nameBox->setPosition(bgPos + Point(35, 10));

            auto doneBox = _resourceManager->getImage("art/intrface/donebox.frm");
            doneBox->setPosition(bgPos + Point(35, 40));

            auto doneLabel = new UI::TextArea(_t(MSG_EDITOR, 100), bgX+65, bgY+43);
            doneLabel->setFont("font3.aaf", {0xb8, 0x9c, 0x28, 0xff});

            auto doneButton = _imageButtonFactory->getByType(ImageButtonType::SMALL_RED_CIRCLE, {bgX + 45, bgY + 43});
            doneButton->mouseClickHandler().add(std::bind(&PlayerEditName::onDoneButtonClick, this, std::placeholders::_1));

            _name = new UI::TextArea(Game::Game::getInstance()->player()->name(), bgX+43, bgY+15);
            _name->keyDownHandler().add([=](Event::Event* event){
                _onTextAreaKeyDown(dynamic_cast<Event::Keyboard*>(event), _name);
            });

            _cursor = new UI::Rectangle(bgPos + Point(83, 15) ,{5,8}, {0x3F, 0xF8, 0x00, 0xFF});

            addUI(bg);
            addUI(nameBox);
            addUI(doneBox);
            addUI(doneLabel);
            addUI(doneButton);
            addUI(_name);
            addUI(_cursor);
        }

        void PlayerEditName::_onTextAreaKeyDown(Event::Keyboard* event, UI::TextArea* target)
        {
            std::string text = target->text();

            if (event->keyCode() == SDLK_BACKSPACE) //backspace
            {
                if (text.length() > 0)
                {
                    text = text.substr(0, text.length() - 1);
                    target->setText(text.c_str());
                    return;
                }
                return;
            }

            if (event->keyCode() == SDLK_RETURN) //enter
            {
                doDone();
                return;
            }

            if (event->keyCode() == SDLK_ESCAPE)
            {
                doBack();
                return;
            }

            if (event->keyCode() == SDLK_LSHIFT || event->keyCode() == SDLK_RSHIFT) {
                return;
            }
            if (event->keyCode() == SDLK_LCTRL || event->keyCode() == SDLK_RCTRL) {
                return;
            }
            if (event->keyCode() == SDLK_LALT || event->keyCode() == SDLK_RALT) {
                return;
            }

            if (text.length() == 11) {
                return;
            }

            if (_keyCodes.find(event->keyCode()) != _keyCodes.end())
            {
                char chr = _keyCodes.at(event->keyCode());

                if (event->shiftPressed())
                {
                    text += toupper(chr);
                }
                else
                {
                    text += chr;
                }
                target->setText(text.c_str());
            }
        }

        void PlayerEditName::onDoneButtonClick(Event::Mouse* event)
        {
            doDone();
        }

        void PlayerEditName::think(const float &deltaTime)
        {
            int bgX = (Game::Game::getInstance()->renderer()->size().width() - 640) / 2;
            State::think(deltaTime);

            _blinkingCursorMillisecondsTracked += deltaTime;
            if (_blinkingCursorMillisecondsTracked >= 300.0f) {
                _blinkingCursorMillisecondsTracked -= 300.0f;
                _cursor->setVisible(!_cursor->visible());
            }
            _cursor->setPosition({bgX + _name->textSize().width() + 45, _cursor->position().y()});
        }

        void PlayerEditName::doBack()
        {
            Game::Game::getInstance()->popState();
        }

        void PlayerEditName::doDone()
        {
            std::string text(_name->text());
            if (text.length() > 0)
            {
                Game::Game::getInstance()->player()->setName(text.c_str());
            }
            Game::Game::getInstance()->popState();
        }
    }
}
