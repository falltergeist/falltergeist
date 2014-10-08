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
    //bool FULLSCREEN = false; // fullscreen or classic
    //unsigned int tileWidth = 0;
    //unsigned int tileHeight = 0;
    //unsigned int screenWidth = 640; // screen size
    //unsigned int screenHeight = 480; // screen size
    //unsigned int worldMapX = 40;
    //unsigned int worldMapY = 600;

    //if (FULLSCREEN)
    //{
    //    screenWidth = Game::getInstance()->renderer()->width();
    //    screenHeight = Game::getInstance()->renderer()->height();
    //}

    if (_initialized) return;
    State::init();

    setModal(true);
    setFullscreen(false);

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

    //auto backgroundX = (Game::getInstance()->renderer()->width() - background->width())*0.5;
    //auto backgroundY = (Game::getInstance()->renderer()->height() - background->height())*0.5;
    //background->setX(backgroundX);
    //background->setY(backgroundY);
    //addUI(background);
    //_background->addEventHandler("keyup", this, (EventRecieverMethod) &WorldMapState::onKeyboardUp);

    //auto cross = new Image("art/intrface/wmaploc.frm");
    //auto hotspot = new ImageButton(ImageButton::TYPE_MAP_HOTSPOT, 0, 0);

    //tileWidth = tile00->width();
    //tileHeight = tile00->height();

    //unsigned int tileX = worldMapX/tileWidth;
    //unsigned int tileY = worldMapY/tileHeight;
    //signed int originX = - (signed int)worldMapX + (signed int)screenWidth*0.5;
    //signed int originY = - (signed int)worldMapY + (signed int)screenHeight*0.5;

    //check origin
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

    //// row 0
    //tile00->setX(originX+0*tileWidth);
    //tile00->setY(originY+0*tileHeight);
    //tile01->setX(originX+1*tileWidth);
    //tile01->setY(originY+0*tileHeight);
    //tile02->setX(originX+2*tileWidth);
    //tile02->setY(originY+0*tileHeight);
    //tile03->setX(originX+3*tileWidth);
    //tile03->setY(originY+0*tileHeight);
    //// row 1
    //tile04->setX(originX+0*tileWidth);
    //tile04->setY(originY+1*tileHeight);
    //tile05->setX(originX+1*tileWidth);
    //tile05->setY(originY+1*tileHeight);
    //tile06->setX(originX+2*tileWidth);
    //tile06->setY(originY+1*tileHeight);
    //tile07->setX(originX+3*tileWidth);
    //tile07->setY(originY+1*tileHeight);
    //// row 2
    //tile08->setX(originX+0*tileWidth);
    //tile08->setY(originY+2*tileHeight);
    //tile09->setX(originX+1*tileWidth);
    //tile09->setY(originY+2*tileHeight);
    //tile10->setX(originX+2*tileWidth);
    //tile10->setY(originY+2*tileHeight);
    //tile11->setX(originX+3*tileWidth);
    //tile11->setY(originY+2*tileHeight);
    //// row 3
    //tile12->setX(originX+0*tileWidth);
    //tile12->setY(originY+3*tileHeight);
    //tile13->setX(originX+1*tileWidth);
    //tile13->setY(originY+3*tileHeight);
    //tile14->setX(originX+2*tileWidth);
    //tile14->setY(originY+3*tileHeight);
    //tile15->setX(originX+3*tileWidth);
    //tile15->setY(originY+3*tileHeight);
    //// row 4
    //tile16->setX(originX+0*tileWidth);
    //tile16->setY(originY+4*tileHeight);
    //tile17->setX(originX+1*tileWidth);
    //tile17->setY(originY+4*tileHeight);
    //tile18->setX(originX+2*tileWidth);
    //tile18->setY(originY+4*tileHeight);
    //tile19->setX(originX+3*tileWidth);
    //tile19->setY(originY+4*tileHeight);

    //addUI(tile00);
    //addUI(tile01);
    //addUI(tile02);
    //addUI(tile03);
    //addUI(tile04);
    //addUI(tile05);
    //addUI(tile06);
    //addUI(tile07);
    //addUI(tile08);
    //addUI(tile09);
    //addUI(tile10);
    //addUI(tile11);
    //addUI(tile12);
    //addUI(tile13);
    //addUI(tile14);
    //addUI(tile15);
    //addUI(tile16);
    //addUI(tile17);
    //addUI(tile18);
    //addUI(tile19);


    //hotspot->setX(screenWidth*0.5);
    //hotspot->setY(screenHeight*0.5);
    //addUI(hotspot);
}

void WorldMapState::render()
{
    bool FULLSCREEN = false; // fullscreen or classic
    _background->render();
//void Renderer::drawTexture(Texture* texture, int x, int y, int sourceX, int sourceY, unsigned int sourceWidth, unsigned int sourceHeight)
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

