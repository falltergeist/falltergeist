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

// Falltergeist includes
#include "../Event/KeyboardEvent.h"
#include "../Event/MouseEvent.h"
#include "../Game/Game.h"
#include "../UI/MvePlayer.h"
#include "../UI/TextArea.h"
#include "../Input/Mouse.h"
#include "../ResourceManager.h"
#include "../State/Movie.h"
#include "../State/MainMenu.h"
#include "../Graphics/Renderer.h"
#include "../Ini/Parser.h"
#include "../Ini/File.h"
#include "../CrossPlatform.h"
#include "../Audio/AudioMixer.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

Movie::Movie(int id) : _id(id)
{
}

Movie::~Movie()
{
}

void Movie::init()
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

    auto cfglst = ResourceManager::lstFileType("data/moviecfgs.lst");
    std::string moviecfgfile = "art/cuts/" + cfglst->strings()->at(_id);
    _effects.push_back({0,1, 0, 0, 0, 1});

    if (cfglst->strings()->at(_id)!="reserved.cfg")
    {
        auto moviecfg = ResourceManager::datFileItem(moviecfgfile);
        //parse ini
        moviecfg->setPosition(0);
        std::istream str(moviecfg);
        auto inifile = new Ini::Parser(str);
        auto ini = inifile->parse();
        int total_effects = ini->section("info")->propertyInt("total_effects",0);
        auto effect_frames = ini->section("info")->propertyArray("effect_frames");
        for (int i =0;i<total_effects;i++)
        {
            unsigned int effect_frame = effect_frames.at(i).intValue();
            std::string effect_section = effect_frames.at(i).value();
            int dir = (ini->section(effect_section)->propertyString("fade_type","in") == "in" ? -1 : 1);
            int steps = ini->section(effect_section)->propertyInt("fade_steps",0);
            auto colors = ini->section(effect_section)->propertyArray("fade_color");
            int r = colors[0].intValue()*4;
            int g = colors[1].intValue()*4;
            int b = colors[2].intValue()*4;
            _effects.push_back({effect_frame, dir, r, g, b, steps/15*1000});
        }
    }
    else
    {
        _effects.push_back({1,-1, 0, 0, 0, 1});
    }

    auto sublst = ResourceManager::lstFileType("data/subtitles.lst");
    std::string subfile = "text/english/cuts/" + sublst->strings()->at(_id);

    if (sublst->strings()->at(_id)!="reserved.sve")
    {
        _subs = ResourceManager::sveFileType(subfile);
        if (_subs) _hasSubs = true;
    }
    addUI("movie", new MvePlayer(ResourceManager::mveFileType(movie)));

    auto font0_ffffffff = ResourceManager::font("font1.aaf", 0xffffffff);
    auto subLabel = new TextArea("", 0, 320+35);

    subLabel->setFont(font0_ffffffff)->setWidth(640)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);
    addUI("subs",subLabel);

    if (_hasSubs)
        _nextSubLine = _subs->getSubLine(0);
    else
        _nextSubLine = std::pair<int,std::string>(999999,"");
}

void Movie::think()
{
    State::think();

    unsigned int frame = dynamic_cast<MvePlayer*>(getUI("movie"))->frame();
    if ( frame >= _nextSubLine.first)
    {
        dynamic_cast<TextArea*>(getUI("subs"))->setText(_nextSubLine.second);
        if (_hasSubs) _nextSubLine = _subs->getSubLine(dynamic_cast<MvePlayer*>(getUI("movie"))->frame());
    }
    if (_effect_index<_effects.size() && frame>=_effects[_effect_index].frame)
    {
        if (_effects[_effect_index].direction < 0)
        {
            Game::getInstance()->renderer()->fadeIn(_effects[_effect_index].r, _effects[_effect_index].g, _effects[_effect_index].b, _effects[_effect_index].frames, true);
        }
        else
        {
            Game::getInstance()->renderer()->fadeOut(_effects[_effect_index].r, _effects[_effect_index].g, _effects[_effect_index].b, _effects[_effect_index].frames, true);
        }
        _effect_index++;
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


void Movie::handle(Event* event)
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

void Movie::onVideoFinished()
{
    Game::getInstance()->mixer()->stopMusic();
    Game::getInstance()->mouse()->popState();
    Game::getInstance()->popState();
}

}
}
