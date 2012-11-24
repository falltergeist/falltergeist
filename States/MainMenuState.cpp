#include "MainMenuState.h"
#include "Game.h"
#include "Screen.h"
#include <iostream>
#include "UI/Button.h"
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
    //add(_game->getResourceManager()->getSurface("art/intrface/about.frm"));
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
