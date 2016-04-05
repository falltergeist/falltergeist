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

// Related headers
#include "../State/PipBoy.h"

// C++ standard includes

// Falltergeist includes
#include "../Event/Keyboard.h"
#include "../Game/Game.h"
#include "../Game/Time.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../ResourceManager.h"
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
            auto background = new UI::Image("art/intrface/pip.frm");
            Point backgroundPos = Point((Game::getInstance()->renderer()->size() - background->size()) / 2);
            int backgroundX = backgroundPos.x();
            int backgroundY = backgroundPos.y();
            background->setPosition(backgroundPos);

            // Buttons
            auto alarmButton = new UI::ImageButton(UI::ImageButton::Type::PIPBOY_ALARM_BUTTON, backgroundX+124, backgroundY+13);
            auto statusButton = new UI::ImageButton(UI::ImageButton::Type::SMALL_RED_CIRCLE, backgroundX+53, backgroundY+340);
            auto automapsButton = new UI::ImageButton(UI::ImageButton::Type::SMALL_RED_CIRCLE, backgroundX+53, backgroundY+394);
            auto archivesButton = new UI::ImageButton(UI::ImageButton::Type::SMALL_RED_CIRCLE, backgroundX+53, backgroundY+423);
            auto closeButton = new UI::ImageButton(UI::ImageButton::Type::SMALL_RED_CIRCLE, backgroundX+53, backgroundY+448);
            closeButton->mouseClickHandler().add(std::bind(&PipBoy::onCloseButtonClick, this, std::placeholders::_1));
            // Date and time

            // Date
            auto day = new UI::SmallCounter(backgroundPos + Point(21, 17));
            day->setLength(2);
            day->setNumber(Game::getInstance()->gameTime()->day());
            day->setColor(UI::SmallCounter::Color::WHITE);
            day->setType(UI::SmallCounter::Type::UNSIGNED);

            auto month = new UI::MonthCounter(
                static_cast<UI::MonthCounter::Month>(Game::getInstance()->gameTime()->month()),
                backgroundPos + Point(46, 18)
            );

            auto year = new UI::SmallCounter(backgroundPos + Point(84, 17));
            year->setLength(4);
            year->setNumber(Game::getInstance()->gameTime()->year());
            year->setColor(UI::SmallCounter::Color::WHITE);
            year->setType(UI::SmallCounter::Type::UNSIGNED);

            // Time
            auto time = new UI::SmallCounter(backgroundPos + Point(160, 17));
            time->setLength(4);
            time->setNumber((Game::getInstance()->gameTime()->hours() * 100) + Game::getInstance()->gameTime()->minutes());
            time->setColor(UI::SmallCounter::Color::WHITE);
            time->setType(UI::SmallCounter::Type::UNSIGNED);

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
