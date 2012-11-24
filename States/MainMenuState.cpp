#include "MainMenuState.h"
#include "Game.h"
#include "Screen.h"
#include <iostream>
#include "UI/RedCircleButton.h"
#include "SaveMenuState.h"
#include "Fallout/FrmFileType.h"
#include "ResourceManager.h"

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
    // background
    add(_game->getResourceManager()->getSurface("art/intrface/mainmenu.frm"));

    // "Into" button
    RedCircleButton * introButton = new RedCircleButton(29,19);

    // "New game" button
    RedCircleButton * newGameButton = new RedCircleButton(29,19 + 41);

    // "Load game" button
    RedCircleButton * loadGameButton = new RedCircleButton(29,19 + 41*2);

    // "Settings" button
    RedCircleButton * settingsButton = new RedCircleButton(29,19 + 41*3);

    // "Credits" button
    RedCircleButton * creditsButton = new RedCircleButton(29,19 + 41*4);

    // "Exit" button
    RedCircleButton * exitButton = new RedCircleButton(29,19 + 41*5);

    add(introButton);
    add(newGameButton);
    add(loadGameButton);
    add(settingsButton);
    add(creditsButton);
    add(exitButton);
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
