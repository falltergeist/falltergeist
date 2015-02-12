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
public:
    PlayerPanel();
    virtual ~PlayerPanel();

    virtual void init();
    virtual void render();
    virtual void think();
    virtual void handle(Event* event);

    void onChangeHandButtonClick(MouseEvent* event);
    void onPanelMouseDown(MouseEvent* event);
    void onInventoryButtonClick(MouseEvent* event);
    void onOptionsButtonClick(MouseEvent* event);
    void onSkilldexButtonClick(MouseEvent* event);
    void onMapButtonClick(MouseEvent* event);
    void onChaButtonClick(MouseEvent* event);
    void onPipBoyButtonClick(MouseEvent* event);
    void onPanelMouseIn(MouseEvent* event);
    void onPanelMouseOut(MouseEvent* event);
    void onPanelMouseUp(MouseEvent* event);
    virtual void onKeyDown(KeyboardEvent* event);
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
