#include "MainMenuState.h"
#include "Game.h"
#include "Screen.h"
#include <iostream>
#include "UI/Button.h"
#include "SaveMenuState.h"

namespace Falltergeist
{

MainMenuState::MainMenuState(Game * game) : State(game)
{
    init();
}

void MainMenuState::init()
{
    State::init();
    _isFullscreen = true;
    Button * button1 = new Button(30,30);
    button1->loadFromBMP("button.bmp");
    button1->onLeftButtonPress((EventHandler)&MainMenuState::onButton1Click);
    add(button1);

    Button * button2 = new Button(30,30,50,50);
    button2->loadFromBMP("button2.bmp");
    button2->onLeftButtonPress((EventHandler)&MainMenuState::onButton2Press);
    add(button2);
}

void MainMenuState::think()
{
    State::think();
}

void MainMenuState::onButton1Click()
{
    _game->pushState(new SaveMenuState(_game));
}
void MainMenuState::onButton1Press()
{
    std::cout<< "button1 press" << std::endl;
}
void MainMenuState::onButton1Release()
{
    std::cout<< "button1 release" << std::endl;
}
void MainMenuState::onButton2Press()
{
    throw Exception("Test exception...");
}

}
