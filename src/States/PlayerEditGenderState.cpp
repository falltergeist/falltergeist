#include "../States/PlayerEditGenderState.h"
#include "../Engine/SurfaceSet.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Game.h"
#include "../UI/TextArea.h"
#include "../UI/ImageButton.h"
#include "../Engine/Player.h"

namespace Falltergeist
{

PlayerEditGenderState::PlayerEditGenderState(Game * game) : State(game)
{
}

void PlayerEditGenderState::init()
{
    State::init();

    _maleImage = new SurfaceSet(260, 2);
    _maleImage->addSurface(new Surface(_game->resourceManager()->surface("art/intrface/maleoff.frm")));
    _maleImage->addSurface(new Surface(_game->resourceManager()->surface("art/intrface/maleon.frm")));
    _maleImage->onLeftButtonPress((EventHandler) &PlayerEditGenderState::onMaleButtonPress);
    if (_game->player()->gender() == Player::GENDER_MALE) _maleImage->setCurrentSurface(1);

    _femaleImage = new SurfaceSet(310,2);
    _femaleImage->addSurface(new Surface(_game->resourceManager()->surface("art/intrface/femoff.frm")));
    _femaleImage->addSurface(new Surface(_game->resourceManager()->surface("art/intrface/femon.frm")));
    _femaleImage->onLeftButtonPress((EventHandler) &PlayerEditGenderState::onFemaleButtonPress);
    if (_game->player()->gender() == Player::GENDER_FEMALE) _femaleImage->setCurrentSurface(1);

    Surface * bg = new Surface(_game->resourceManager()->surface("art/intrface/charwin.frm"));
    bg->x(236);
    bg->y(0);

    Surface * doneBox = new Surface(_game->resourceManager()->surface("art/intrface/donebox.frm"));
    doneBox->x(250);
    doneBox->y(42);

    libfalltergeist::MsgFileType * msg = _game->resourceManager()->msgFileType("text/english/game/editor.msg");
    TextArea * doneLabel = new TextArea(msg->message(100), 281, 45);
    doneLabel->setColor(0xffb89c28)->setFont("font3.aaf");

    ImageButton * doneButton= new ImageButton("art/intrface/lilredup.frm", "art/intrface/lilreddn.frm", 260, 45);
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
