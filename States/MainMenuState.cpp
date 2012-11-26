#include "MainMenuState.h"
#include "Game.h"
#include "UI/ImageButton.h"
#include "UI/TextLabel.h"
#include "ResourceManager.h"
#include "States/NewGameState.h"
#include "Animation.h"


namespace Falltergeist
{

MainMenuState::MainMenuState(Game * game) : State(game)
{
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::init()
{
    State::init();
    _isFullscreen = true;
    // Background image
    add(_game->getResourceManager()->getSurface("art/intrface/mainmenu.frm"));

    // "Into" button
    ImageButton * introButton = new ImageButton("art/intrface/menuup.frm", "art/intrface/menudown.frm", 29, 19);

    // "New game" button
    ImageButton * newGameButton = new ImageButton("art/intrface/menuup.frm", "art/intrface/menudown.frm", 29, 19 + 41);
    newGameButton->onLeftButtonClick((EventHandler) &MainMenuState::onNewGameButtonClick);

    // "Load game" button
    ImageButton * loadGameButton = new ImageButton("art/intrface/menuup.frm", "art/intrface/menudown.frm", 29, 19 + 41*2);

    // "Settings" button
    ImageButton * settingsButton = new ImageButton("art/intrface/menuup.frm", "art/intrface/menudown.frm", 29, 19 + 41*3);

    // "Credits" button
    ImageButton * creditsButton = new ImageButton("art/intrface/menuup.frm", "art/intrface/menudown.frm", 29, 19 + 41*4);

    // "Exit" button
    ImageButton * exitButton = new ImageButton("art/intrface/menuup.frm", "art/intrface/menudown.frm", 29, 19 + 41*5);
    exitButton->onLeftButtonClick((EventHandler) &MainMenuState::onExitButtonClick);

    // "Intro" label
    TextLabel * introButtonLabel = new TextLabel("INTRO", 55, 20);
    introButtonLabel->setColor(0xb89c28ff);
    introButtonLabel->setFont("font4.aaf");
    introButtonLabel->setWidth(140);
    introButtonLabel->setHorizontalAlign(TextLabel::HORIZONTAL_ALIGN_CENTER);

    // "New Game" label
    TextLabel * newGameButtonLabel = new TextLabel("NEW GAME", 55, 20 + 41);
    newGameButtonLabel->setColor(0xb89c28ff);
    newGameButtonLabel->setFont("font4.aaf");
    newGameButtonLabel->setWidth(140);
    newGameButtonLabel->setHorizontalAlign(TextLabel::HORIZONTAL_ALIGN_CENTER);

    // "Load Game" label
    TextLabel * loadGameButtonLabel = new TextLabel("LOAD GAME", 55, 20 + 41*2);
    loadGameButtonLabel->setColor(0xb89c28ff);
    loadGameButtonLabel->setFont("font4.aaf");
    loadGameButtonLabel->setWidth(140);
    loadGameButtonLabel->setHorizontalAlign(TextLabel::HORIZONTAL_ALIGN_CENTER);

    // "Options" label
    TextLabel * optionsButtonLabel = new TextLabel("OPTIONS", 55, 20 + 41*3);
    optionsButtonLabel->setColor(0xb89c28ff);
    optionsButtonLabel->setFont("font4.aaf");
    optionsButtonLabel->setWidth(140);
    optionsButtonLabel->setHorizontalAlign(TextLabel::HORIZONTAL_ALIGN_CENTER);

    // "Credits" label
    TextLabel * creditsButtonLabel = new TextLabel("CREDITS", 55, 20 + 41*4);
    creditsButtonLabel->setColor(0xb89c28ff);
    creditsButtonLabel->setFont("font4.aaf");
    creditsButtonLabel->setWidth(140);
    creditsButtonLabel->setHorizontalAlign(TextLabel::HORIZONTAL_ALIGN_CENTER);

    // "Exit" label
    TextLabel * exitButtonLabel = new TextLabel("EXIT", 55, 20 + 41*5);
    exitButtonLabel->setColor(0xb89c28ff);
    exitButtonLabel->setFont("font4.aaf");
    exitButtonLabel->setWidth(140);
    exitButtonLabel->setHorizontalAlign(TextLabel::HORIZONTAL_ALIGN_CENTER);

    Animation * wait = new Animation("art/intrface/wait.frm",560,400);

    // buttons
    add(introButton);
    add(newGameButton);
    add(loadGameButton);
    add(settingsButton);
    add(creditsButton);
    add(exitButton);
    // labels
    add(introButtonLabel);
    add(newGameButtonLabel);
    add(loadGameButtonLabel);
    add(optionsButtonLabel);
    add(creditsButtonLabel);
    add(exitButtonLabel);

    add(wait);
}

void MainMenuState::think()
{
    State::think();
}

void MainMenuState::onExitButtonClick()
{
    _game->quit();
}

void MainMenuState::onNewGameButtonClick()
{
    _game->pushState(new NewGameState(_game));
}

}
