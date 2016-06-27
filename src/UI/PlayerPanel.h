/*
 * Copyright 2012-2016 Falltergeist Developers.
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

#ifndef FALLTERGEIST_UI_PLAYERPANEL_H
#define FALLTERGEIST_UI_PLAYERPANEL_H

// C++ standard includes
#include <memory>
#include <vector>

// Falltergeist includes
#include "../UI/Base.h"
#include "../UI/ImageButton.h"
// Third party includes

namespace Falltergeist
{
namespace Event
{
    class Keyboard;
}
namespace UI
{
class Image;
class SmallCounter;
class TextArea;

class PlayerPanel : public UI::Base
{

public:
    PlayerPanel();
    ~PlayerPanel() override;

    Size size() const override;

    void render(bool eggTransparency = false) override;
    void handle(Event::Event *event) override;
    void think() override;

    virtual bool opaque(const Point &pos) override;

    void displayMessage(const std::string& message);

    void playWindowOpenSfx();

private:

    std::shared_ptr<Image> _background;
    std::shared_ptr<SmallCounter> _hitPoints;
    std::shared_ptr<SmallCounter> _armorClass;
    std::shared_ptr<TextArea> _messageLog;
    std::vector<std::shared_ptr<UI::Base>> _ui;

    bool _isAttackBtnPressed;

    char _scrollingLog = 0;
    // TODO: replace with real timer
    unsigned int _scrollingLogTimer = 0;

    void renderHandSlot();

    void changeHand();
    void openCharacterScreen();
    void openGameMenu();
    void openInventory();
    void openMap();
    void openPipBoy();
    void openSkilldex();
    void openSaveGame();
    void openLoadGame();

    void onKeyDown(Event::Keyboard* event);
};

}
}
#endif // FALLTERGEIST_UI_PLAYERPANEL_H
