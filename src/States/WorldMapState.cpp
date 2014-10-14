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
    // fallout2
    // tileSize: 350x300
    // map size: 4x5 tiles
    // texture size: 1400x1500

    unsigned int tileWidth = 0;
    unsigned int tileHeight = 0;

    if (_initialized) return;
    State::init();

    setModal(true);
    setFullscreen(true);

    // panel
    _panel = new Image("art/intrface/wmapbox.frm");
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

    // calculating tile size
    tileWidth = _tiles->width();
    tileHeight = _tiles->height();

    // creating map texture
    _map = new Image(1400, 1500);
    for (unsigned int y=0; y<5; y++)
    {
        for (unsigned int x=0; x<4; x++)
        {
            _tiles->setCurrentImage(y*4+x);
            _tiles->texture()->copyTo(_map->texture(), x*tileWidth, y*tileHeight);
        }
    }
    // creating screen
    // @todo: correct coordinates!
    if (WorldMapFullscreen)
    {
        _screen = new Image (Game::getInstance()->renderer()->width(), Game::getInstance()->renderer()->height());
        _screen->setX(0);
        _screen->setY(0);
    }
    else
    {
        _screen = new Image (430, 420);
        _screen->setX((Game::getInstance()->renderer()->width() - 640)*0.5 + 25);
        _screen->setY((Game::getInstance()->renderer()->height() - 480)*0.5 + 25);
    }
}

void WorldMapState::render()
{
    unsigned int renderWidth = 640; // default current render size X
    unsigned int renderHeight = 480; // default current render size Y
    unsigned int screenWidth = 640; // default screen size X
    unsigned int screenHeight = 480; // default screen size Y
    unsigned int screenMinX = 0;
    unsigned int screenMaxX = 640;
    unsigned int screenMinY = 0;
    unsigned int screenMaxY = 480;

    unsigned int worldMapX = 5;
    unsigned int worldMapY = 10;

    // calculating render size, screen size, etc
    renderWidth = Game::getInstance()->renderer()->width();
    renderHeight = Game::getInstance()->renderer()->height();
    screenMaxX = renderWidth;
    screenMaxY = renderHeight;

    if (WorldMapFullscreen)
    {
    }
    else
    {
        screenWidth = renderWidth;
        screenHeight = renderHeight;
        screenMinX = (renderWidth - 640)*0.5;
        screenMaxX = (renderWidth + 640)*0.5;
        screenMinY = (renderHeight - 480)*0.5;
        screenMaxY = (renderHeight + 480)*0.5;
    }

    // map show
    // calculating upper left corner
    signed int sx1 = (signed int)worldMapX - (signed int)screenWidth*0.5; // screen left X in map coordinates
    signed int sy1 = (signed int)worldMapY - (signed int)screenHeight*0.5;
    //correcting upper left corner coordinates
    if (sx1<0)
    {
        sx1=0;
    }
    if (sy1<0)
    {
        sy1=0;
    }
    // calculate lower right corner
    unsigned int sx2 = (signed int)worldMapX + (signed int)screenWidth*0.5; // screen left X in map coordinates
    unsigned int sy2 = (signed int)worldMapY + (signed int)screenHeight*0.5;
    //correcting lower right corner coordinates
    if (sx2>300)
    {
        sx2=300;
    }
    if (sy2>300)
    {
        sy2=300;
    }


//std::cout << "\n";
//std::cout << "sm=" << smx << "x" << smy << "\n";
//std::cout << "screenSize=" <<screenWidth << "x" << screenHeight << "\n";
//std::cout << "screenX=" <<screenMinX << "x" << screenMaxX << "\n";
//std::cout << "screenY=" <<screenMinY << "x" << screenMaxY << "\n";
//std::cout << "tileSize=" <<tileWidth << "x" << tileHeight << "\n";
//std::cout << "tile=" <<tileX << "," << tileY << "\n";
//std::cout << "origin=" <<originX << "," << originY << "\n";

    //void Texture::copyTo(Texture* destination, 
    //unsigned int destinationX, unsigned int destinationY, 
    //unsigned int sourceX, unsigned int sourceY, 
    //unsigned int sourceWidth, unsigned int sourceHeight)
    _map->texture()->copyTo(_screen->texture(), 0, 0, 0, 0, screenWidth-190, screenHeight-160);
    //_map->texture()->copyTo(_screen->texture(), 0, 0, sx1, sy1, sx2-sx1, sy2-sy1);
    _screen->render();

    // panel
    // @todo: if FULLSCREEN, show only right panel
    auto panelX = (renderWidth - _panel->width())*0.5;
    auto panelY = (renderHeight - _panel->height())*0.5;
    _panel->setX(panelX);
    _panel->setY(panelY);
    _panel->render();

    // hostpot show
    _hotspot->setX(screenWidth*0.5);
    _hotspot->setY(screenHeight*0.5);
    _hotspot->render();
    //addUI(_hotspot);
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

