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

#ifndef FALLTERGEIST_PlayerPanel_H
#define FALLTERGEIST_PlayerPanel_H

// C++ standard inludes

// Falltergeist includes
#include "State.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

class PlayerPanel : public State
{
protected:
    void playWindowOpenSfx();
public:
    PlayerPanel();
    virtual ~PlayerPanel();

    virtual void init();
    virtual void render();
    virtual void think();
    virtual void handle(Event::Event* event);
    
    unsigned int height();

    void onChangeHandButtonClick(Event::Mouse* event);
    void onPanelMouseDown(Event::Mouse* event);
    void onInventoryButtonClick(Event::Mouse* event);
    void onOptionsButtonClick(Event::Mouse* event);
    void onSkilldexButtonClick(Event::Mouse* event);
    void onMapButtonClick(Event::Mouse* event);
    void onChaButtonClick(Event::Mouse* event);
    void onPipBoyButtonClick(Event::Mouse* event);
    void onPanelMouseIn(Event::Mouse* event);
    void onPanelMouseOut(Event::Mouse* event);
    void onPanelMouseUp(Event::Mouse* event);
    virtual void onKeyDown(Event::Keyboard* event);
    void toggleActiveHand();
    void openInventory();
    void openOptions();
    void openSkilldex();
    void openMap();
    void openPopBoy();
    void openCharacterScreen();
    void doLoadGame(bool quick = false);
    void doSaveGame(bool quick = false);
};

}
}

#endif // FALLTERGEIST_PlayerPanel_H
