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
#include <iostream>

// Falltergeist includes
#include "../Engine/Game.h"
#include "../Engine/Graphics/Renderer.h"
#include "../Engine/ResourceManager.h"
#include "../States/WorldMapState.h"
#include "../States/LocationState.h"
#include "../States/MainMenuState.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/ImageList.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{

WorldMapState::WorldMapState()
{
}

void WorldMapState::init()
{
    if (_initialized) return;
    State::init();

    setModal(true);
    setFullscreen(true);

    // background
    _background = new Image("art/intrface/wmapbox.frm");
    // loading map tiles
    _tiles = new ImageList((std::vector<std::string>){
                            "art/intrface/wrldmp00.frm",
                            "art/intrface/wrldmp01.frm",
                            "art/intrface/wrldmp02.frm",
                            "art/intrface/wrldmp03.frm",
                            "art/intrface/wrldmp04.frm",
                            "art/intrface/wrldmp05.frm",
                            "art/intrface/wrldmp06.frm",
                            "art/intrface/wrldmp07.frm",
                            "art/intrface/wrldmp08.frm",
                            "art/intrface/wrldmp09.frm",
                            "art/intrface/wrldmp10.frm",
                            "art/intrface/wrldmp11.frm",
                            "art/intrface/wrldmp12.frm",
                            "art/intrface/wrldmp13.frm",
                            "art/intrface/wrldmp14.frm",
                            "art/intrface/wrldmp15.frm",
                            "art/intrface/wrldmp16.frm",
                            "art/intrface/wrldmp17.frm",
                            "art/intrface/wrldmp18.frm",
                            "art/intrface/wrldmp19.frm"
                            }, 0, 0);

    //auto cross = new Image("art/intrface/wmaploc.frm");
    _hotspot = new ImageButton(ImageButton::TYPE_MAP_HOTSPOT, 0, 0);
    //addUI(_hotspot);

}

void WorldMapState::render()
{
    bool FULLSCREEN = false; // fullscreen or classic
    unsigned int tileWidth = 0;
    unsigned int tileHeight = 0;
    unsigned int screenWidth = 640; // default screen size X
    unsigned int screenHeight = 480; // default screen size Y
    unsigned int worldMapX = 140;
    unsigned int worldMapY = 160;

    if (FULLSCREEN)
    {
        screenWidth = Game::getInstance()->renderer()->width();
        screenHeight = Game::getInstance()->renderer()->height();
    }

    tileWidth = _tiles->width();
    tileHeight = _tiles->height();

    unsigned int tileX = worldMapX/tileWidth;
    unsigned int tileY = worldMapY/tileHeight;
    signed int originX = - (signed int)worldMapX + (signed int)screenWidth*0.5;
    signed int originY = - (signed int)worldMapY + (signed int)screenHeight*0.5;

    //correcting origin
    //if (originX>0)
    //{
    //    originX=0;
    //}
    //if (originY>0)
    //{
    //    originY=0;
    //}

//std::cout << "screenSize=" <<screenWidth << "x" << screenHeight << "\n";
//std::cout << "tileSize=" <<tileWidth << "x" << tileHeight << "\n";
//std::cout << "tile=" <<tileX << "," << tileY << "\n";
//std::cout << "origin=" <<originX << "," << originY << "\n";

    // tiles show

    unsigned int i = 0;
    for (unsigned int y=0; y<5; y++)
    {
        for (unsigned int x=0; x<4; x++)
        {
            _tiles->setCurrentImage(i);
            _tiles->setX(originX+x*tileWidth);
            _tiles->setY(originY+y*tileHeight);
            //void Renderer::drawTexture(Texture* texture, int x, int y, int sourceX, int sourceY, unsigned int sourceWidth, unsigned int sourceHeight)
            _tiles->render();
            i++;
        }
    }

    _hotspot->setX(screenWidth*0.5);
    _hotspot->setY(screenHeight*0.5);
    _hotspot->render();
    //addUI(_hotspot);


    // background
    // @todo: if FULLSCREEN, show only right panel
    auto backgroundX = (Game::getInstance()->renderer()->width() - _background->width())*0.5;
    auto backgroundY = (Game::getInstance()->renderer()->height() - _background->height())*0.5;
    _background->setX(backgroundX);
    _background->setY(backgroundY);
    _background->render();

}

void WorldMapState::handle(Event* event)
{
    auto game = Game::getInstance();
    if (auto keyboardEvent = dynamic_cast<KeyboardEvent*>(event))
    {
        switch (keyboardEvent->keyCode())
        {
            case SDLK_ESCAPE:
            {
                Game::getInstance()->popState();
            }
        }
    }
}

//void WorldMapState::onKeyboardUp(KeyboardEvent* event)
//{
//    if (event->keyCode() == SDLK_ESCAPE)
//    {
//        Game::getInstance()->popState();
//    }
//}


}

