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

// Falltergeist includes
#include "../Game.h"
#include "../Graphics/Renderer.h"
#include "../Event/KeyboardEvent.h"
#include "../Input/Mouse.h"
#include "../ResourceManager.h"
#include "../States/PipBoyState.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/MonthCounter.h"
#include "../UI/SmallCounter.h"

// Third party includes

namespace Falltergeist
{

PipBoyState::PipBoyState() : State()
{
}

PipBoyState::~PipBoyState()
{
    Game::getInstance()->mouse()->popState();
}

void PipBoyState::init()
{
    if (_initialized) return;
    State::init();

    setModal(true);
    setFullscreen(true);

    Game::getInstance()->mouse()->pushState(Mouse::BIG_ARROW);

    // Background
    auto background = new Image("art/intrface/pip.frm");
    auto backgroundX = (Game::getInstance()->renderer()->width() - background->width())*0.5;
    auto backgroundY = (Game::getInstance()->renderer()->height() - background->height())*0.5;
    background->setX(backgroundX);
    background->setY(backgroundY);

    // Close PipBoy when ESC is hit
    background->addEventHandler("keyup", [this](Event* event){ this->onKeyboardUp(dynamic_cast<KeyboardEvent*>(event)); });

    // Buttons
    auto alarmButton = new ImageButton(ImageButton::TYPE_PIPBOY_ALARM_BUTTON, backgroundX+124, backgroundY+13);
    auto statusButton = new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, backgroundX+53, backgroundY+340);
    auto automapsButton = new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, backgroundX+53, backgroundY+394);
    auto archivesButton = new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, backgroundX+53, backgroundY+423);
    auto closeButton = new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, backgroundX+53, backgroundY+448);
    closeButton->addEventHandler("mouseleftclick", [this](Event* event){ this->onCloseButtonClick(dynamic_cast<MouseEvent*>(event)); });
    // Date and time
    // FIXME: use current in-game datetime
    // Date
    auto day = new SmallCounter(backgroundX+21, backgroundY+17);
    day->setNumber(9);
    day->setColor(SmallCounter::COLOR_WHITE);
    day->setType(SmallCounter::UNSIGNED);
    day->setLength(2);

    auto month = new MonthCounter(MonthCounter::JUNE, backgroundX+46, backgroundY+18);

    auto year = new SmallCounter(backgroundX+84, backgroundY+17);
    year->setNumber(2242);
    year->setColor(SmallCounter::COLOR_WHITE);
    year->setType(SmallCounter::UNSIGNED);
    year->setLength(4);

    // Time
    auto time = new SmallCounter(backgroundX+160, backgroundY+17);
    time->setNumber(800);
    time->setColor(SmallCounter::COLOR_WHITE);
    time->setType(SmallCounter::UNSIGNED);
    time->setLength(4);

    addUI(background);

    addUI(alarmButton);
    addUI(statusButton);
    addUI(automapsButton);
    addUI(archivesButton);

    addUI(day);
    addUI(month);
    addUI(year);
    addUI(time);

    addUI(closeButton);
}

void PipBoyState::onCloseButtonClick(MouseEvent* event)
{
    Game::getInstance()->popState();
}

void PipBoyState::onKeyboardUp(KeyboardEvent* event)
{
    if (event->keyCode() == SDLK_ESCAPE)
    {
        Game::getInstance()->popState();
    }
}

}
