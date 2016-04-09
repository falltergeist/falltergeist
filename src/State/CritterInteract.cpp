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
#include "../Base/StlFeatures.h"
#include "../Format/Lst/File.h"
#include "../Game/CritterObject.h"
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Input/Mouse.h"
#include "../LocationCamera.h"
#include "../PathFinding/Hexagon.h"
#include "../ResourceManager.h"
#include "../State/CursorDropdown.h"
#include "../State/Location.h"
#include "../UI/Image.h"
#include "../UI/Animation.h"
#include "../UI/AnimationQueue.h"
#include "../Audio/Mixer.h"

// Third party includes

namespace Falltergeist
{
    namespace State
    {
        using Base::make_unique;

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
            if (_headID >= 0)
            {
                // stop music completely
                //Game::getInstance()->mixer()->stopMusic();
            }
            else
            {
                // lower music volume
                Game::getInstance()->mixer()->setMusicVolume(Game::getInstance()->mixer()->musicVolume()/2.0);
            }
        }

        void CritterInteract::onStateDeactivate(Event::State* event)
        {
            Game::getInstance()->mouse()->popState();
            if (_headID >= 0)
            {
                Game::getInstance()->mixer()->playACMMusic(Game::getInstance()->mixer()->lastMusic(), true);
            }
            else
            {
                // restore music volume
                Game::getInstance()->mixer()->setMusicVolume(Game::getInstance()->mixer()->musicVolume()*2.0);
            }
        }

        void CritterInteract::init()
        {
            if (_initialized) return;
            State::init();

            setFullscreen(false);
            setModal(true);

            setPosition((Game::getInstance()->renderer()->size() - Point(640, 480)) / 2);

            if (backgroundID() >= 0 && headID() >= 0)
            {
                auto lst = ResourceManager::getInstance()->lstFileType("art/backgrnd/backgrnd.lst");
                std::string bgImage = "art/backgrnd/" + lst->strings()->at(backgroundID());
                auto bg = new UI::Image(bgImage);
                bg->setPosition({128, 15});
                addUI(bg);

                auto headlst = ResourceManager::getInstance()->lstFileType("art/heads/heads.lst");
                std::string headImage = headlst->strings()->at(headID());
                headImage=headImage.substr(0,headImage.find(","));
                _headName = headImage;
                headImage+="gf2.frm";

                auto head = new UI::AnimationQueue();
                head->animations().push_back(make_unique<UI::Animation>("art/heads/" + headImage));
                head->setRepeat(true);
                head->start();

                head->setPosition({128, 15});
                addUI(head);
            }

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

        void CritterInteract::playSpeech(const std::string &speech)
        {
            Game::getInstance()->mixer()->playACMSpeech(_headName+"/"+speech+".acm");
            // start timer
        }


        void CritterInteract::think()
        {
            State::think();
            // switch state
            // if playing speech - set phoneme frame
        }


    }
}
