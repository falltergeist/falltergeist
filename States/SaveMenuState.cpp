#include "SaveMenuState.h"
#include "UI/Button.h"

namespace Falltergeist
{

SaveMenuState::SaveMenuState(Game * game) : State(game)
{
    _isFullscreen = true;
    Button * button1 = new Button(30,30,60,60);
    button1->loadFromBMP("button.bmp");
    add(button1);

    Button * button2 = new Button(30,30,150,150);
    button2->loadFromBMP("button2.bmp");
    button2->onLeftButtonPress((EventHandler)&SaveMenuState::onButton2Click);
    add(button2);

}

void SaveMenuState::think()
{

}

void SaveMenuState::init()
{

}

void SaveMenuState::onButton2Click()
{
    _game->popState();
}

}
