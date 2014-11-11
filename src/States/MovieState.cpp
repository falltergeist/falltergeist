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
 */

// C++ standard includes

// Falltergeist includes
#include "../Engine/Event/KeyboardEvent.h"
#include "../Engine/Event/MouseEvent.h"
#include "../Engine/Game.h"
#include "../UI/MvePlayer.h"
#include "../UI/TextArea.h"
#include "../Engine/Input/Mouse.h"
#include "../Engine/ResourceManager.h"
#include "../States/MovieState.h"
#include "../States/MainMenuState.h"
#include "../Engine/Graphics/Renderer.h"
#include "../Engine/Settings/IniParser.h"
#include "../Engine/Settings/IniFile.h"
#include "../Engine/CrossPlatform.h"
#include "../Engine/Audio/AudioMixer.h"

// Third party includes

namespace Falltergeist
{

MovieState::MovieState(int id) : _id(id)
{
}

MovieState::~MovieState()
{
}

void MovieState::init()
{
    if (_initialized) return;
    State::init();

    setFullscreen(true);
    setModal(true);

    Game::getInstance()->mouse()->pushState(Mouse::NONE);
    auto renderer = Game::getInstance()->renderer();
    setX((renderer->width()  - 640)*0.5);
    setY((renderer->height() - 320)*0.5);

    auto lst = ResourceManager::lstFileType("data/movies.lst");
    std::string movie = "art/cuts/" + lst->strings()->at(_id);

    auto sublst = ResourceManager::lstFileType("data/subtitles.lst");
    std::string subfile = "text/english/cuts/" + sublst->strings()->at(_id);

    if (sublst->strings()->at(_id)!="reserved.sve")
    {
        _subs = ResourceManager::sveFileType(subfile).get();
        if (_subs) _hasSubs = true;
    }
    addUI("movie", new MvePlayer(ResourceManager::mveFileType(movie).get()));

    auto font0_ffffffff = ResourceManager::font("font1.aaf", 0xffffffff);
    auto subLabel = new TextArea("", 0, 320+35);

    subLabel->setFont(font0_ffffffff)->setWidth(640)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);
    addUI("subs",subLabel);

    if (_hasSubs)
        _nextSubLine = _subs->getSubLine(0);
    else
        _nextSubLine = std::pair<int,std::string>(999999,"");
}

void MovieState::think()
{
    State::think();

    if (dynamic_cast<MvePlayer*>(getUI("movie"))->frame() >= _nextSubLine.first)
    {
        dynamic_cast<TextArea*>(getUI("subs"))->setText(_nextSubLine.second);
        if (_hasSubs) _nextSubLine = _subs->getSubLine(dynamic_cast<MvePlayer*>(getUI("movie"))->frame());
    }

    if (!_started)
    {
        Game::getInstance()->mixer()->playMovieMusic(dynamic_cast<MvePlayer*>(getUI("movie")));
        _started = true;
    }
    if ((dynamic_cast<MvePlayer*>(getUI("movie")))->finished())
    {
        this->onVideoFinished();
    }
}


void MovieState::handle(Event* event)
{
    if (auto mouseEvent = dynamic_cast<MouseEvent*>(event))
    {
        if (mouseEvent->name() == "mouseup")
        {
            this->onVideoFinished();
        }
    }

    if (auto keyboardEvent = dynamic_cast<KeyboardEvent*>(event))
    {
        if (keyboardEvent->name() == "keyup")
        {
            this->onVideoFinished();
        }
    }
}

void MovieState::onVideoFinished()
{
    Game::getInstance()->mixer()->stopMusic();
    Game::getInstance()->mouse()->popState();
    Game::getInstance()->popState();
}

}
