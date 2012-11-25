#include "MainMenuState.h"
#include "Game.h"
#include "Screen.h"
#include <iostream>
#include "UI/RedCircleButton.h"
#include "UI/TextLabel.h"
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
    exitButton->onLeftButtonClick((EventHandler) &MainMenuState::onExitButtonClick);

    TextLabel * introButtonLabel = new TextLabel("INTRO", "font4.aaf",85,20);
    introButtonLabel->setColor(0xb89c28ff);

    TextLabel * newGameButtonLabel = new TextLabel("NEW GAME", "font4.aaf",65,20 + 41);
    newGameButtonLabel->setColor(0xb89c28ff);

    TextLabel * loadGameButtonLabel = new TextLabel("LOAD GAME", "font4.aaf",60,20 + 41*2);
    loadGameButtonLabel->setColor(0xb89c28ff);

    TextLabel * optionsButtonLabel = new TextLabel("OPTIONS", "font4.aaf",75,20 + 41*3);
    optionsButtonLabel->setColor(0xb89c28ff);

    TextLabel * creditsButtonLabel = new TextLabel("CREDITS", "font4.aaf",75,20 + 41*4);
    creditsButtonLabel->setColor(0xb89c28ff);

    TextLabel * exitButtonLabel = new TextLabel("EXIT", "font4.aaf",95,20 + 41*5);
    exitButtonLabel->setColor(0xb89c28ff);

    TextLabel * falltergeistVersion = new TextLabel("Falltergeist 0.0.1", "font1.aaf",525,464);
    falltergeistVersion->setColor(0x00FF00FF);

    add(introButton);
    add(newGameButton);
    add(loadGameButton);
    add(settingsButton);
    add(creditsButton);
    add(exitButton);

    add(introButtonLabel);
    add(newGameButtonLabel);
    add(loadGameButtonLabel);
    add(optionsButtonLabel);
    add(creditsButtonLabel);
    add(exitButtonLabel);

    add(falltergeistVersion);
}

void MainMenuState::think()
{
    State::think();
}

void MainMenuState::onExitButtonClick(Event * event)
{
    _game->quit();
}

}
