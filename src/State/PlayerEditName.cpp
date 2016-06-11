/*
 * Copyright 2012-2016 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

// Related headers
#include "../State/PlayerEditName.h"

// C++ standard includes
#include <ctype.h>

// Falltergeist includes
#include "../functions.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../ResourceManager.h"
#include "../UI/TextArea.h"
#include "../UI/ImageButton.h"
#include "../UI/Image.h"
#include "../UI/Rectangle.h"

// Third party includes

namespace Falltergeist
{
    namespace State
    {
        PlayerEditName::PlayerEditName() : State()
        {
        }

        PlayerEditName::~PlayerEditName()
        {
        }

        void PlayerEditName::init()
        {
            if (_initialized) return;
            State::init();

            setFullscreen(false);
            setModal(true);

            Point bgPos = Point((Game::getInstance()->renderer()->size() - Point(640, 480)) / 2);
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

            _timer = SDL_GetTicks();

            auto bg = new UI::Image("art/intrface/charwin.frm");
            bg->setPosition(bgPos + Point(22, 0));

            auto nameBox = new UI::Image("art/intrface/namebox.frm");
            nameBox->setPosition(bgPos + Point(35, 10));

            auto doneBox = new UI::Image("art/intrface/donebox.frm");
            doneBox->setPosition(bgPos + Point(35, 40));

            auto doneLabel = new UI::TextArea(_t(MSG_EDITOR, 100), bgX+65, bgY+43);
            doneLabel->setFont("font3.aaf", {0xb8, 0x9c, 0x28, 0xff});

            auto doneButton = new UI::ImageButton(UI::ImageButton::Type::SMALL_RED_CIRCLE, bgX+45, bgY+43);
            doneButton->mouseClickHandler().add(std::bind(&PlayerEditName::onDoneButtonClick, this, std::placeholders::_1));

            _name = new UI::TextArea(Game::getInstance()->player()->name(), bgX+43, bgY+15);
            _name->keyDownHandler().add([this](Event::Event* event){ this->onTextAreaKeyDown(dynamic_cast<Event::Keyboard*>(event)); });

            _cursor = new UI::Rectangle(bgPos + Point(83, 15) ,{5,8}, {0x3F, 0xF8, 0x00, 0xFF});

            addUI(bg);
            addUI(nameBox);
            addUI(doneBox);
            addUI(doneLabel);
            addUI(doneButton);
            addUI(_name);
            addUI(_cursor);
        }

        void PlayerEditName::onTextAreaKeyDown(Event::Keyboard* event)
        {
            auto sender = dynamic_cast<UI::TextArea*>(event->target());

            std::string text = sender->text();

            if (event->keyCode() == SDLK_BACKSPACE) //backspace
            {
                if (text.length() > 0)
                {
                    text = text.substr(0, text.length() - 1);
                    sender->setText(text.c_str());
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

            if (event->keyCode() == SDLK_LSHIFT || event->keyCode() == SDLK_RSHIFT) return;
            if (event->keyCode() == SDLK_LCTRL || event->keyCode() == SDLK_RCTRL) return;
            if (event->keyCode() == SDLK_LALT || event->keyCode() == SDLK_RALT) return;

            if (text.length() == 11) return;

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
                sender->setText(text.c_str());
            }
        }

        void PlayerEditName::onDoneButtonClick(Event::Mouse* event)
        {
            doDone();
        }

        void PlayerEditName::think()
        {
            int bgX = (Game::getInstance()->renderer()->width() - 640) / 2;
            State::think();
            if (SDL_GetTicks() - _timer > 300)
            {
                _cursor->setVisible(!_cursor->visible());
                _timer = SDL_GetTicks();
            }
            _cursor->setPosition({bgX + _name->textSize().width() + 45, _cursor->position().y()});
        }

        void PlayerEditName::doBack()
        {
            Game::getInstance()->popState();
        }

        void PlayerEditName::doDone()
        {
            std::string text(_name->text());
            if (text.length() > 0)
            {
                Game::getInstance()->player()->setName(text.c_str());
            }
            Game::getInstance()->popState();
        }
    }
}
