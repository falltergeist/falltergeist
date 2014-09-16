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
#include "../Engine/Game.h"
#include "../Engine/Graphics/Renderer.h"
#include "../Engine/ResourceManager.h"
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
}

void PipBoyState::init()
{
    if (_initialized) return;
    State::init();

    setModal(true);
    setFullscreen(true);

    // Background
    auto background = std::shared_ptr<Image>(new Image("art/intrface/pip.frm"));
    auto backgroundX = (Game::getInstance()->renderer()->width() - background->width())*0.5;
    auto backgroundY = (Game::getInstance()->renderer()->height() - background->height())*0.5;
    background->setX(backgroundX);
    background->setY(backgroundY);

    // Close PipBoy when ESC is hit
    background->addEventHandler("keyup", this, (EventRecieverMethod) &PipBoyState::onKeyboardUp);

    // Buttons
    auto alarmButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_PIPBOY_ALARM_BUTTON, backgroundX+124, backgroundY+13));
    auto statusButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, backgroundX+53, backgroundY+340));
    auto automapsButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, backgroundX+53, backgroundY+394));
    auto archivesButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, backgroundX+53, backgroundY+423));
    auto closeButton = std::shared_ptr<ImageButton>(new ImageButton(ImageButton::TYPE_SMALL_RED_CIRCLE, backgroundX+53, backgroundY+448));
    closeButton->addEventHandler("mouseleftclick", this, (EventRecieverMethod) &PipBoyState::onCloseButtonClick);

    // Date and time
    // FIXME: use current in-game datetime
    // Date
    auto day = std::shared_ptr<SmallCounter>(new SmallCounter(backgroundX+21, backgroundY+17));
    day->setNumber(9);
    day->setColor(SmallCounter::COLOR_WHITE);
    day->setType(SmallCounter::UNSIGNED);
    day->setLength(2);

    auto month = std::shared_ptr<MonthCounter>(new MonthCounter(MonthCounter::JUNE, backgroundX+46, backgroundY+18));

    auto year = std::shared_ptr<SmallCounter>(new SmallCounter(backgroundX+84, backgroundY+17));
    year->setNumber(2242);
    year->setColor(SmallCounter::COLOR_WHITE);
    year->setType(SmallCounter::UNSIGNED);
    year->setLength(4);

    // Time
    auto time = std::shared_ptr<SmallCounter>(new SmallCounter(backgroundX+160, backgroundY+17));
    time->setNumber(800);
    time->setColor(SmallCounter::COLOR_WHITE);
    time->setType(SmallCounter::UNSIGNED);
    time->setLength(4);

    add(background);

    add(alarmButton);
    add(statusButton);
    add(automapsButton);
    add(archivesButton);

    add(day);
    add(month);
    add(year);
    add(time);

    add(closeButton);
}

void PipBoyState::onCloseButtonClick(std::shared_ptr<MouseEvent> event)
{
    Game::getInstance()->popState();
}

void PipBoyState::onKeyboardUp(std::shared_ptr<KeyboardEvent> event)
{
    if (event->keyCode() == SDLK_ESCAPE)
    {
        Game::getInstance()->popState();
    }
}

}