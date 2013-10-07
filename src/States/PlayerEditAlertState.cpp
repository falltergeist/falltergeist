#include "../States/PlayerEditAlertState.h"
#include "../Engine/Game.h"
#include "../Engine/ResourceManager.h"
#include "../Engine/Surface.h"
#include "../UI/TextArea.h"
#include "../UI/ImageButton.h"

namespace Falltergeist
{

PlayerEditAlertState::PlayerEditAlertState(Game * game) : State(game)
{
}

PlayerEditAlertState::~PlayerEditAlertState()
{
}

void PlayerEditAlertState::setMessage(std::string message)
{
    _message = message;
}

void PlayerEditAlertState::init()
{
    State::init();

    Surface * bg = new Surface(_game->resourceManager()->surface("art/intrface/lgdialog.frm", 164, 173));

    TextArea * message = new TextArea(_message.c_str(), 194, 213);
    message->setWidth(250);
    message->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_CENTER);
    message->setColor(0xFFFF9F48);

    Surface * doneBox = new Surface(_game->resourceManager()->surface("art/intrface/donebox.frm", 254, 270));

    ImageButton * doneButton= new ImageButton("art/intrface/lilredup.frm", "art/intrface/lilreddn.frm", 264, 273);
    doneButton->onLeftButtonClick((EventHandler) &PlayerEditAlertState::onDoneButtonClick);

    libfalltergeist::MsgFileType * msg = _game->resourceManager()->msgFileType("text/english/game/editor.msg");
    TextArea * doneLabel = new TextArea(msg->message(100), 284, 273);
    doneLabel->setColor(0xffb89c28)->setFont("font3.aaf");

    add(bg);
    add(message);
    add(doneBox);
    add(doneButton);
    add(doneLabel);
}

void PlayerEditAlertState::onDoneButtonClick(Event * event)
{
    _game->popState();
}

}
