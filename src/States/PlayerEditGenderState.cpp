/*
 * Copyright 2012-2013 Falltergeist Developers.
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
#include "../States/PlayerEditGenderState.h"
#include "../Engine/SurfaceSet.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Game.h"
#include "../UI/TextArea.h"
#include "../UI/ImageButton.h"
#include "../Engine/Player.h"

// Third party includes

namespace Falltergeist
{

PlayerEditGenderState::PlayerEditGenderState(Game * game) : State(game)
{
}

void PlayerEditGenderState::init()
{
    State::init();

    _maleImage = new SurfaceSet((std::vector<std::string>){
                                    "art/intrface/maleoff.frm",
                                    "art/intrface/maleon.frm"
                                }, 260, 2);
    _maleImage->onLeftButtonPress((EventHandler) &PlayerEditGenderState::onMaleButtonPress);
    if (_game->player()->gender() == Player::GENDER_MALE) _maleImage->setCurrentSurface(1);

    _femaleImage = new SurfaceSet((std::vector<std::string>){
                                      "art/intrface/femoff.frm",
                                      "art/intrface/femon.frm"
                                  }, 310, 2);
    _femaleImage->onLeftButtonPress((EventHandler) &PlayerEditGenderState::onFemaleButtonPress);
    if (_game->player()->gender() == Player::GENDER_FEMALE) _femaleImage->setCurrentSurface(1);

    Surface * bg = new Surface(_game->resourceManager()->surface("art/intrface/charwin.frm"));
    bg->setX(236);
    bg->setY(0);
    bg->setXOffset(0);
    bg->setYOffset(0);


    Surface * doneBox = new Surface(_game->resourceManager()->surface("art/intrface/donebox.frm"));
    doneBox->setX(250);
    doneBox->setY(42);
    doneBox->setXOffset(0);
    doneBox->setYOffset(0);

    libfalltergeist::MsgFileType * msg = _game->resourceManager()->msgFileType("text/english/game/editor.msg");
    TextArea * doneLabel = new TextArea(msg->message(100), 281, 45);
    doneLabel->setColor(0xffb89c28)->setFont("font3.aaf");

    ImageButton * doneButton= new ImageButton(ImageButton::BUTTON_SMALL_RED_CIRCLE, 260, 45);
    doneButton->onLeftButtonClick((EventHandler) &PlayerEditGenderState::onDoneButtonClick);

    add(bg);
    add(doneBox);
    add(doneButton);
    add(doneLabel);
    add(_maleImage);
    add(_femaleImage);
}

void PlayerEditGenderState::onDoneButtonClick(Event * event)
{
    _game->popState();
}

void PlayerEditGenderState::onFemaleButtonPress(Event * event)
{
    _game->player()->setGender(Player::GENDER_FEMALE);
    _maleImage->setCurrentSurface(0);
    _femaleImage->setCurrentSurface(1);
}

void PlayerEditGenderState::onMaleButtonPress(Event * event)
{
    _game->player()->setGender(Player::GENDER_MALE);
    _maleImage->setCurrentSurface(1);
    _femaleImage->setCurrentSurface(0);
}

}
