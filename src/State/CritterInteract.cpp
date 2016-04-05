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
#include "../State/CritterInteract.h"

// C++ standard includes

// Falltergeist includes
#include "../Game/CritterObject.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../LocationCamera.h"
#include "../PathFinding/Hexagon.h"
#include "../State/CursorDropdown.h"
#include "../State/Location.h"
#include "../UI/Image.h"

// Third party includes

namespace Falltergeist
{
    namespace State
    {
        CritterInteract::CritterInteract() : State()
        {
        }

        CritterInteract::~CritterInteract()
        {
            auto camera = Game::getInstance()->locationState()->camera();
            camera->setCenter(_oldCameraCenter);
        }

        void CritterInteract::onStateActivate(Event::State* event)
        {
            Game::getInstance()->mouse()->pushState(Input::Mouse::Cursor::BIG_ARROW);
        }

        void CritterInteract::onStateDeactivate(Event::State* event)
        {
            Game::getInstance()->mouse()->popState();
        }

        void CritterInteract::init()
        {
            if (_initialized) return;
            State::init();

            setFullscreen(false);
            setModal(true);

            setPosition((Game::getInstance()->renderer()->size() - Point(640, 480)) / 2);

            addUI("background", new UI::Image("art/intrface/alltlk.frm"));

            // Centering camera on critter position
            auto locationState = Game::getInstance()->locationState();
            _oldCameraCenter = locationState->camera()->center();

            locationState->camera()->setCenter(critter()->hexagon()->position() + Point(0, 100));
        }

        int CritterInteract::backgroundID()
        {
            return _backgroundID;
        }

        void CritterInteract::setBackgroundID(int backgroundID)
        {
            _backgroundID = backgroundID;
        }

        int CritterInteract::headID()
        {
            return _headID;
        }

        void CritterInteract::setHeadID(int headID)
        {
            _headID = headID;
        }

        int CritterInteract::mood()
        {
            return _mood;
        }

        void CritterInteract::setMood(int mood)
        {
            _mood = mood;
        }

        Game::CritterObject* CritterInteract::critter()
        {
            return _critter;
        }

        void CritterInteract::setCritter(Game::CritterObject* critter)
        {
            _critter = critter;
        }

        int CritterInteract::msgFileID()
        {
            return _msgFileID;
        }

        void CritterInteract::setMsgFileID(int value)
        {
            _msgFileID = value;
        }

        VM::Script* CritterInteract::script()
        {
            return _script;
        }

        void CritterInteract::setScript(VM::Script* script)
        {
            _script = script;
        }
    }
}
