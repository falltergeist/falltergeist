/*
 * Copyright 2012-2015 Falltergeist Developers.
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

// C++ standard includes
#include <sstream>

// Falltergeist includes
#include "../State/Credits.h"
#include "../Event/Keyboard.h"
#include "../Event/Mouse.h"
#include "../Event/State.h"
#include "../Font.h"
#include "../Game/Game.h"
#include "../UI/TextArea.h"
#include "../Input/Mouse.h"
#include "../ResourceManager.h"
#include "../Graphics/Renderer.h"
#include "../CrossPlatform.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

Credits::Credits() : State()
{
}

Credits::~Credits()
{
}

void Credits::init()
{
    if (_initialized) return;
    State::init();

    setModal(true);
    setFullscreen(true);

    Game::getInstance()->mouse()->pushState(Input::Mouse::Cursor::NONE);
    auto renderer = Game::getInstance()->renderer();
    setPosition(Point((renderer->size().width() - 640) / 2, renderer->size().height()));

    auto credits = ResourceManager::getInstance()->datFileItem("text/english/credits.txt");
    std::stringstream ss;
    credits->setPosition(0);
    ss << credits;
    std::string line;

    auto font_default = ResourceManager::getInstance()->font("font4.aaf", 0x907824ff);
    auto font_at = ResourceManager::getInstance()->font("font3.aaf", 0x706050ff);
    auto font_hash = ResourceManager::getInstance()->font("font4.aaf", 0x8c8c84ff);

    int y = 0;
    while (std::getline(ss, line))
    {
        Font* cur_font = font_default;
        int additionalGap = 0;
        if (line.find('\r') != std::string::npos)
        {
            line.erase(line.find('\r'));
        }
        if (line[0] == '#')
        {
            line.erase(line.begin());
            cur_font = font_hash;
        }
        else if (line[0] == '@')
        {
            line.erase(line.begin());
            cur_font = font_at;
            additionalGap = 6;
        }
        else if (line.empty())
        {
            line = "    ";
        }

        auto tx = new UI::TextArea(line, 0, y);
        tx->setFont(cur_font);
        tx->setSize({640, 0});
        tx->setHorizontalAlign(UI::TextArea::HorizontalAlign::CENTER);
        addUI(tx);
        _lines.push_back(tx);
        tx->calculateSize();
        y += tx->size().height() + cur_font->verticalGap() + additionalGap;
    }
    _lastTicks=SDL_GetTicks();
}

void Credits::think()
{
    State::think();

    unsigned long int nt = SDL_GetTicks();
    if (nt - _lastTicks > 50)
    {
        _position.ry() -= 1;
        long int _lastY = 0;
        for (auto ui: _lines)
        {
            ui->setY(ui->y()-1);

            if ( (ui->y() > -30) && (ui->y() < (int)(Game::getInstance()->renderer()->height()+10) ) )
            {
                ui->setVisible(true);
            }
            else
            {
                ui->setVisible(false);
            }

            _lastY = ui->y();
        }

        _lastTicks=nt;

        if (_lastY < -30)
        {
            this->onCreditsFinished();
        }
    }
}


void Credits::handle(Event::Event* event)
{
    if (auto mouseEvent = dynamic_cast<Event::Mouse*>(event))
    {
        if (mouseEvent->name() == "mouseup")
        {
            this->onCreditsFinished();
        }
    }

    if (auto keyboardEvent = dynamic_cast<Event::Keyboard*>(event))
    {
        if (keyboardEvent->name() == "keyup")
        {
            this->onCreditsFinished();
        }
    }
}

void Credits::onCreditsFinished()
{
    removeEventHandlers("fadedone");
    addEventHandler("fadedone", [this](Event::Event* event){ this->onCreditsFadeDone(dynamic_cast<Event::State*>(event)); });
    Game::getInstance()->renderer()->fadeOut(0,0,0,1000);
}

void Credits::onCreditsFadeDone(Event::State* event)
{
    removeEventHandlers("fadedone");
    Game::getInstance()->mouse()->popState();
    Game::getInstance()->popState();
}

void Credits::onStateActivate(Event::State* event)
{
    Game::getInstance()->renderer()->fadeIn(0,0,0,1000);
}

}
}
