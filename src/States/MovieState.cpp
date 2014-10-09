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

// Falltergeist includes
#include "../Engine/Event/KeyboardEvent.h"
#include "../Engine/Event/MouseEvent.h"
#include "../Engine/Game.h"
#include "../UI/MvePlayer.h"
#include "../Engine/Input/Mouse.h"
#include "../Engine/ResourceManager.h"
#include "../States/MovieState.h"
#include "../States/MainMenuState.h"
#include "../Engine/Graphics/Renderer.h"
#include "../Engine/Settings/IniParser.h"
#include "../Engine/Settings/IniFile.h"
#include "../Engine/CrossPlatform.h"

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

    std::string configFile = CrossPlatform::findFalltergeistDataPath() + "/data/movies.ini";
    std::ifstream stream(configFile);
    IniParser iniparser(stream);
    auto ini = iniparser.parse();
    std::string movie="art/cuts/"+(*ini).section("movies")->propertyString(std::to_string(_id),"");

    addUI("movie", new MvePlayer(ResourceManager::mveFileType(movie).get()));
}

void MovieState::think()
{
    State::think();

    if ((dynamic_cast<MvePlayer*>(getActiveUI("movie")))->finished())
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
        this->onVideoFinished();
    }
}

void MovieState::onVideoFinished()
{
    Game::getInstance()->mouse()->popState();
//    Game::getInstance()->setState(new MainMenuState());
    Game::getInstance()->popState();
}

}
