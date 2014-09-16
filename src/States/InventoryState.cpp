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
#include <sstream>

// Falltergeist includes
#include "../Engine/Game.h"
#include "../Engine/Graphics/Renderer.h"
#include "../Engine/ResourceManager.h"
#include "../Game/GameCritterObject.h"
#include "../Game/GameDudeObject.h"
#include "../States/GameMenuState.h"
#include "../States/InventoryState.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/TextArea.h"

// Third party includes

namespace Falltergeist
{

InventoryState::InventoryState() : State()
{
}

InventoryState::~InventoryState()
{
}

void InventoryState::init()
{
    if (_initialized) return;
    State::init();

    setModal(true);
    setFullscreen(false);

    // background
    auto background = std::shared_ptr<Image>(new Image("art/intrface/invbox.frm"));
    auto backgroundX = (Game::getInstance()->renderer()->width() - background->width())*0.5;
    auto backgroundY = (Game::getInstance()->renderer()->height() - background->height())*0.5-50;
    background->setX(backgroundX);
    background->setY(backgroundY);

    // buttons
    auto upButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_INVENTORY_UP_ARROW, backgroundX+128, backgroundY+40));
    auto downButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_INVENTORY_DOWN_ARROW, backgroundX+128, backgroundY+65));
    auto doneButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, backgroundX+438, backgroundY+328));

    // events
    doneButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &GameMenuState::onDoneButtonClick);

    // screen
    auto screenX = backgroundX + background->width() - 202;
    auto screenY = backgroundY + background->height() - 332; //330
    auto font = ResourceManager::font("font1.aaf");

    // name
    auto playerNameLabel = std::shared_ptr<TextArea>(new TextArea(Game::getInstance()->player()->name(), screenX, screenY));
//    skilldexLabel->setFont(font)->setWidth(76)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);

    auto line1 = std::shared_ptr<Image>(new Image(142, 1));
    line1->setX(screenX);
    line1->setY(screenY+16);
    line1->texture()->fill(0x3ff800ff); // default green color

    auto msg = ResourceManager::msgFileType("text/english/game/inventry.msg");
    // label: ST (0)
    auto stLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(0), screenX, screenY+20));
    // label: PE (1)
    auto peLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(1), screenX, screenY+20+10));
    // label: EN (2)
    auto enLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(2), screenX, screenY+20+10*2));
    // label: CH (3)
    auto chLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(3), screenX, screenY+20+10*3));
    // label: IN (4)
    auto inLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(4), screenX, screenY+20+10*4));
    // label: AG (5)
    auto agLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(5), screenX, screenY+20+10*5));
    // label: LK (6)
    auto lkLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(6), screenX, screenY+20+10*6));

    std::stringstream ss;
    for (unsigned int i=0; i<7; i++)
    {
        ss << Game::getInstance()->player()->stat(i) << "\n";
    }
    auto statsLabel = std::shared_ptr<TextArea>(new TextArea(ss.str(), screenX+22, screenY+20));

    ss.str("");
    for (unsigned int i=7; i<14; i++)
    {
        ss << msg->message(i)->text() << "\n";
    }
    auto textLabel = std::shared_ptr<TextArea>(new TextArea(ss.str(), screenX+40, screenY+20));

    // label: hit points
    ss.str("");
    ss << Game::getInstance()->player()->hitPoints();
    ss << "/";
    ss << Game::getInstance()->player()->hitPointsMax();
    auto hitPointsLabel = std::shared_ptr<TextArea>(new TextArea(ss.str(), screenX+94, screenY+20));
    hitPointsLabel->setFont(font)->setWidth(46)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);
    // label: armor class
    ss.str("");
    ss << Game::getInstance()->player()->armorClass();
    auto armorClassLabel = std::shared_ptr<TextArea>(new TextArea(ss.str(), screenX+94, screenY+30));
    armorClassLabel->setFont(font)->setWidth(46)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);

    // player->damageResist(DAMAGE_PLASMA);
    // label: damage levels
    ss.str("");
    ss << Game::getInstance()->player()->damageResist(GameCritterObject::DAMAGE_NORMAL) <<"/\n";
    ss << Game::getInstance()->player()->damageResist(GameCritterObject::DAMAGE_LASER) << "/\n";
    ss << Game::getInstance()->player()->damageResist(GameCritterObject::DAMAGE_FIRE) << "/\n";
    ss << Game::getInstance()->player()->damageResist(GameCritterObject::DAMAGE_PLASMA) << "/\n";
    ss << Game::getInstance()->player()->damageResist(GameCritterObject::DAMAGE_EXPLOSION) << "/";
    auto damageLevelsLabel = std::shared_ptr<TextArea>(new TextArea(ss.str(), screenX+94, screenY+40));
    damageLevelsLabel->setFont(font)->setWidth(26)->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);

    auto line2 = std::shared_ptr<Image>(new Image(142, 1));
    line2->setX(screenX);
    line2->setY(screenY+94);
    line2->texture()->fill(0x3ff800ff); // default green color

    // item1

    auto line3 = std::shared_ptr<Image>(new Image(142, 1));
    line3->setX(screenX);
    line3->setY(screenY+134);
    line3->texture()->fill(0x3ff800ff); // default green color

    // item2

    // label: Total Wt: (20)
    auto totalWtLabel = std::shared_ptr<TextArea>(new TextArea(msg->message(20), screenX+14, screenY+180));

    add(background);
    add(playerNameLabel);
    add(line1);
    add(stLabel);
    add(peLabel);
    add(enLabel);
    add(chLabel);
    add(inLabel);
    add(agLabel);
    add(lkLabel);
    add(statsLabel);
    add(textLabel);
    add(hitPointsLabel);
    add(armorClassLabel);
    add(damageLevelsLabel);
    add(line2);
    add(line3);
    add(totalWtLabel);
    add(upButton);
    add(downButton);
    add(doneButton);
}

void InventoryState::onDoneButtonClick(std::shared_ptr<MouseEvent> event)
{
    Game::getInstance()->popState();
}

}
