/*
 * Copyright 2012-2013 Falltergeist Developers.
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
#include <cmath>

// Falltergeist includes
#include "../Engine/Animation.h"
#include "../Engine/Game.h"
#include "../Engine/Screen.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/InteractiveSurface.h"
#include "../Engine/Location.h"
#include "../Engine/LocationCamera.h"
#include "../Engine/LocationObject.h"
#include "../States/LocationState.h"
#include "../Engine/Mouse.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{

LocationState::LocationState(Game * game) : State(game)
{
    _scrollTicks = 0;
    _location = 0;
    _background = 0;
    _hexagonalGrid = false;
}

LocationState::~LocationState()
{
}

void LocationState::init()
{
    State::init();

    std::string maps[] = {"arbridge.map", "broken2.map", "city1.map", "coast12.map", "cowbomb.map", "desert4.map", "dnslvrun.map", "geckpwpl.map", "klaratcv.map", "modshit.map", "ncr2.map",
                          "newrba.map", "redmtun.map", "rndholy2.map", "sfelronb.map", "vault15.map", "arcaves.map", "cardesrt.map" ,"city2.map", "coast1.map", "denbus1.map", "desert5.map",
                          "encdet.map", "gecksetl.map", "klatoxcv.map", "modwell.map", "ncr3.map", "newrcs.map", "redwame.map", "rndparih.map", "sfshutl1.map", "vctycocl.map", "ardead.map",
                          "cave0.map", "city3.map", "coast2.map", "denbus2.map", "desert6.map", "encdock.map", "gecktunl.map", "klatrap.map", "mountn1.map", "ncr4.map", "newrgo.map", "redwan1.map",
                          "rndshutl.map", "sfshutl2.map", "vctyctyd.map", "argarden.map", "cave1.map", "city4.map", "coast3.map", "denres1.map", "desert7.map", "encfite.map", "gstcav1.map", "mbase12.map", "mountn2.map",
                          "ncrent.map", "newrst.map", "rndbess.map", "rndtinwd.map", "sftanker.map", "vctydwtn.map", "artemple.map", "cave2.map", "city5.map", "coast4.map", "depolv1.map", "desert8.map",
                          "encgd.map", "gstcav2.map", "mbase34.map", "mountn3.map", "newr1a.map", "newrvb.map", "rndbhead.map", "rndtoxic.map", "v13ent.map", "vctyvlt.map", "arvill2.map", "cave3.map", "city6.map",
                          "coast5.map", "depolva.map", "desert9.map", "encpres.map", "gstfarm.map", "mbclose.map", "mountn4.map", "newr1.map", "raiders1.map", "rndbridg.map", "rnduvilg.map", "v13_orig.map",
                          "arvillag.map", "cave4.map", "city7.map", "coast6.map", "depolvb.map", "desrt10.map", "encrctr.map", "klacanyn.map", "modbrah.map", "mountn5.map", "newr2a.map", "raiders2.map",
                          "rndcafe.map", "rndwhale.map", "v15ent.map", "bhrnddst.map", "cave5.map", "city8.map", "coast7.map", "desert1.map", "desrt11.map", "enctrp.map", "kladwtwn.map", "modgard.map",
                          "mountn6.map", "newr2.map", "reddown.map", "rndexcow.map", "sfchina2.map", "v15_orig.map", "bhrndmtn.map", "cave6.map", "coast10.map", "coast8.map", "desert2.map",
                          "desrt12.map", "gammovie.map", "klagraz.map", "modinn.map", "navarro.map", "newr3.map", "reddtun.map", "rndforvr.map", "sfchina.map", "v15sent.map", "broken1.map", "cave7.map",
                          "coast11.map", "coast9.map", "desert3.map", "desrt13.map", "geckjunk.map", "klamall.map", "modmain.map", "ncr1.map", "newr4.map", "redment.map", "rndholy1.map", "sfdock.map", "vault13.map" };



    _location = new Location(_game->resourceManager()->mapFileType("maps/artemple.map"));
    _background = new InteractiveSurface(_location->tilesBackground());
    add(_background);

    _background->onLeftButtonClick((EventHandler) &LocationState::onBackgroundClick);
    _background->onKeyboardRelease((EventHandler) &LocationState::onKeyboardRelease);
}

void LocationState::onBackgroundClick(Event * event)
{
    std::cout << "test" << std::endl;
}

void LocationState::onKeyboardRelease(Event * event)
{
    if (event->keyCode() == SDLK_g) // "g" button - enable\disable hex grid
    {
        if (_hexagonalGrid)
        {
            _hexagonalGrid = false;
        }
        else
        {
            _hexagonalGrid = true;
        }
    }
}

void LocationState::blit()
{

    State::blit();

    if (_location == 0) return;

    _drawHexagonalGrid();

    for (std::vector<LocationObject *>::iterator it = _location->objectsToRender()->begin(); it != _location->objectsToRender()->end(); ++it)
    {
        LocationObject * object = *it;

        int oldX = object->x();
        int oldY = object->y();
        int newX = oldX - _location->camera()->x();
        int newY = oldY - _location->camera()->y();

        object->setX(newX);
        object->setY(newY);
        object->blit(_game->screen()->surface());
        object->setX(oldX);
        object->setY(oldY);
    }
}

void LocationState::_drawHexagonalGrid()
{
    if (!_hexagonalGrid) return;
    Surface * hexagon = ResourceManager::surface("art/intrface/msef000.frm");
    hexagon->setXOffset(0 - hexagon->width()/2);
    hexagon->setYOffset(0 - hexagon->height()/2);
    for (unsigned int i = 0; i != 200*200; ++i)
    {
        int x = _location->hexagonToX(i) - _location->camera()->x();
        int y = _location->hexagonToY(i) - _location->camera()->y();
        hexagon->setX(x);
        hexagon->setY(y);
        hexagon->blit(_game->screen()->surface());
    }
}

void LocationState::think()
{
    if (!_location) return;
    _location->think();

    if (SDL_GetTicks() >= _scrollTicks + 10)
    {
        bool moved;
        _scrollTicks = SDL_GetTicks();
        if (_game->mouse()->cursorX() < 5) // LEFT
        {
            if (_game->mouse()->cursorY() < 5) //  LEFT-UP
            {
                moved = _location->scroll(true, false, true, false);
                if (moved)
                {
                    _game->mouse()->setCursor(Mouse::SCROLL_NW);
                }
                else
                {
                    _game->mouse()->setCursor(Mouse::SCROLL_NW_X);
                }
            }
            else if (_game->mouse()->cursorY() > 475) //LEFT-DOWN
            {
                moved = _location->scroll(false, true, true, false);
                if (moved)
                {
                    _game->mouse()->setCursor(Mouse::SCROLL_SW);
                }
                else
                {
                    _game->mouse()->setCursor(Mouse::SCROLL_SW_X);
                }
            }
            else
            {
                moved = _location->scroll(false, false, true, false);
                if (moved)
                {
                    _game->mouse()->setCursor(Mouse::SCROLL_W);
                }
                else
                {
                    _game->mouse()->setCursor(Mouse::SCROLL_W_X);
                }
            }
        }
        else if (_game->mouse()->cursorX() > 635) // RIGHT
        {
            if (_game->mouse()->cursorY() < 5) //  RIGHT-UP
            {
                moved = _location->scroll(true, false, false, true);
                if (moved)
                {
                    _game->mouse()->setCursor(Mouse::SCROLL_NE);
                }
                else
                {
                    _game->mouse()->setCursor(Mouse::SCROLL_NE_X);
                }
            }
            else if (_game->mouse()->cursorY() > 475) //RIGHT-DOWN
            {
                moved = _location->scroll(false, true, false, true);
                if (moved)
                {
                    _game->mouse()->setCursor(Mouse::SCROLL_SE);
                }
                else
                {
                    _game->mouse()->setCursor(Mouse::SCROLL_SE_X);
                }
            }
            else
            {
                moved = _location->scroll(false, false, false, true);
                if (moved)
                {
                    _game->mouse()->setCursor(Mouse::SCROLL_E);
                }
                else
                {
                    _game->mouse()->setCursor(Mouse::SCROLL_E_X);
                }
            }
        }
        else if (_game->mouse()->cursorY() < 5) // UP
        {
            moved = _location->scroll(true, false, false, false);
            if (moved)
            {
                _game->mouse()->setCursor(Mouse::SCROLL_N);
            }
            else
            {
                _game->mouse()->setCursor(Mouse::SCROLL_N_X);
            }
        }
        else if (_game->mouse()->cursorY() > 475) // DOWN
        {
            moved = _location->scroll(false, true, false, false);
            if (moved)
            {
                _game->mouse()->setCursor(Mouse::SCROLL_S);
            }
            else
            {
                _game->mouse()->setCursor(Mouse::SCROLL_S_X);
            }
        }
        else
        {
            _game->mouse()->setCursor(Mouse::BIG_ARROW);
        }

        if(moved)
        {
            _background->loadFromSurface(_location->tilesBackground());
        }
    }

}

}
