/*
 * Copyright 2012-2014 Falltergeist Developers.
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
 *
 */

// C++ standard includes
#include <sstream>

// Falltergeist includes
#include "../States/CreditsState.h"
#include "../Engine/Event/KeyboardEvent.h"
#include "../Engine/Event/MouseEvent.h"
#include "../Engine/Game.h"
#include "../UI/TextArea.h"
#include "../Engine/Input/Mouse.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Graphics/Renderer.h"
#include "../Engine/CrossPlatform.h"

// Third party includes

namespace Falltergeist
{

CreditsState::CreditsState() : State()
{
}

CreditsState::~CreditsState()
{
}

void CreditsState::init()
{
    if (_initialized) return;
    State::init();

    setModal(true);
    setFullscreen(true);

    Game::getInstance()->mouse()->pushState(Mouse::NONE);
    auto renderer = Game::getInstance()->renderer();
    setX((renderer->width()  - 640)*0.5);
    setY(renderer->height());

    auto credits = ResourceManager::datFileItem("text/english/credits.txt");
    std::stringstream ss;
    credits->setPosition(0);
    ss << credits.get();
    std::string line;

    auto font_default = ResourceManager::font("font4.aaf", 0xb89c28FF);
    auto font_at = ResourceManager::font("font3.aaf", 0x907824FF);
    auto font_hash = ResourceManager::font("font4.aaf", 0xccccccFF);

    int y = 0;
    while (std::getline(ss, line))
    {
        auto cur_font = font_default;
        if (line.find('\r')!=std::string::npos) line.erase(line.find('\r'));
        if (line[0]=='#')
        {
            line.erase(line.begin());
            cur_font = font_hash;
        }
        else if (line[0]=='@')
        {
            line.erase(line.begin());
            cur_font = font_at;
        }
        else if (line.empty())
        {
            line = "    ";
        }

        auto tx = new TextArea(line,0,y);
        tx->setFont(cur_font)->setWidth(640)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);
        addUI(tx);
        _lines.push_back(tx);
        y+=tx->height();
    }
    _lastTicks=SDL_GetTicks();
}

void CreditsState::think()
{
    State::think();

    unsigned long int nt = SDL_GetTicks();
    if (nt-_lastTicks > 38)
    {
        setY(y()-1);
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


void CreditsState::handle(Event* event)
{
    if (auto mouseEvent = dynamic_cast<MouseEvent*>(event))
    {
        if (mouseEvent->name() == "mouseup")
        {
            this->onCreditsFinished();
        }
    }

    if (auto keyboardEvent = dynamic_cast<KeyboardEvent*>(event))
    {
        if (keyboardEvent->name() == "keyup")
        {
            this->onCreditsFinished();
        }
    }
}

void CreditsState::onCreditsFinished()
{
    Game::getInstance()->mouse()->popState();
    Game::getInstance()->popState();
}

}
