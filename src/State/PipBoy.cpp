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

// C++ standard includes

// Falltergeist includes
#include "../Game/Game.h"
#include "../Game/Time.h"
#include "../Graphics/Renderer.h"
#include "../Event/Keyboard.h"
#include "../Input/Mouse.h"
#include "../ResourceManager.h"
#include "../State/PipBoy.h"
#include "../UI/Image.h"
#include "../UI/ImageButton.h"
#include "../UI/MonthCounter.h"
#include "../UI/SmallCounter.h"

// Third party includes

namespace Falltergeist
{
namespace State
{

PipBoy::PipBoy() : State()
{
}

PipBoy::~PipBoy()
{
    Game::getInstance()->mouse()->popState();
}

void PipBoy::init()
{
    if (_initialized) return;
    State::init();

    setModal(true);
    setFullscreen(true);

    Game::getInstance()->mouse()->pushState(Input::Mouse::Cursor::BIG_ARROW);

    // Background
    auto background = std::make_shared<UI::Image>("art/intrface/pip.frm");
    auto backgroundX = (Game::getInstance()->renderer()->width() - background->width())*0.5;
    auto backgroundY = (Game::getInstance()->renderer()->height() - background->height())*0.5;
    background->setX(backgroundX);
    background->setY(backgroundY);

    // Buttons
    auto alarmButton = std::make_shared<UI::ImageButton>(UI::ImageButton::Type::PIPBOY_ALARM_BUTTON, backgroundX+124, backgroundY+13);
    auto statusButton = std::make_shared<UI::ImageButton>(UI::ImageButton::Type::SMALL_RED_CIRCLE, backgroundX+53, backgroundY+340);
    auto automapsButton = std::make_shared<UI::ImageButton>(UI::ImageButton::Type::SMALL_RED_CIRCLE, backgroundX+53, backgroundY+394);
    auto archivesButton = std::make_shared<UI::ImageButton>(UI::ImageButton::Type::SMALL_RED_CIRCLE, backgroundX+53, backgroundY+423);
    auto closeButton = std::make_shared<UI::ImageButton>(UI::ImageButton::Type::SMALL_RED_CIRCLE, backgroundX+53, backgroundY+448);
    closeButton->addEventHandler("mouseleftclick", [this](Event::Event* event){ this->onCloseButtonClick(dynamic_cast<Event::Mouse*>(event)); });
    // Date and time

    // Date
    auto day = std::make_shared<UI::SmallCounter>(backgroundX+21, backgroundY+17);
    day->setNumber(Game::getInstance()->gameTime()->day());
    day->setColor(UI::SmallCounter::Color::WHITE);
    day->setType(UI::SmallCounter::Type::UNSIGNED);
    day->setLength(2);

    auto month = std::make_shared<UI::MonthCounter>(static_cast<UI::MonthCounter::Month>(Game::getInstance()->gameTime()->month()), backgroundX+46, backgroundY+18);

    auto year = std::make_shared<UI::SmallCounter>(backgroundX+84, backgroundY+17);
    year->setNumber(Game::getInstance()->gameTime()->year());
    year->setColor(UI::SmallCounter::Color::WHITE);
    year->setType(UI::SmallCounter::Type::UNSIGNED);
    year->setLength(4);

    // Time
    auto time = std::make_shared<UI::SmallCounter>(backgroundX+160, backgroundY+17);
    time->setNumber((Game::getInstance()->gameTime()->hours() * 100) + Game::getInstance()->gameTime()->minutes());
    time->setColor(UI::SmallCounter::Color::WHITE);
    time->setType(UI::SmallCounter::Type::UNSIGNED);
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

void PipBoy::onCloseButtonClick(Event::Mouse* event)
{
    Game::getInstance()->popState();
}

void PipBoy::onKeyDown(Event::Keyboard* event)
{
    if (event->keyCode() == SDLK_ESCAPE)
    {
        Game::getInstance()->popState();
    }
}

}
}
