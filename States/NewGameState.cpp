#include "NewGameState.h"
#include "Game.h"
#include "ResourceManager.h"
#include "UI/RedSmallCircleButton.h"
#include "UI/LeftArrowButton.h"
#include "UI/RightArrowButton.h"

namespace Falltergeist
{

NewGameState::NewGameState(Game * game) : State(game)
{
    init();
}

void NewGameState::init()
{
    State::init();
    _isFullscreen = true;
    // background
    add(_game->getResourceManager()->getSurface("art/intrface/pickchar.frm"));

    // Begin game button
    RedSmallCircleButton * beginGameButton= new RedSmallCircleButton(81,322);

    // Edit character button
    RedSmallCircleButton * editButton= new RedSmallCircleButton(436,319);

    // Create character button
    RedSmallCircleButton * createButton= new RedSmallCircleButton(81,424);

    // Back to mainmenu button
    RedSmallCircleButton * backButton= new RedSmallCircleButton(461,424);
    backButton->onLeftButtonClick((EventHandler) &NewGameState::onBackButtonClick);

    LeftArrowButton * prevCharacterButton = new LeftArrowButton(292,320);
    RightArrowButton * nextCharacterButton = new RightArrowButton(318,320);

    add(beginGameButton);
    add(editButton);
    add(createButton);
    add(backButton);
    add(prevCharacterButton);
    add(nextCharacterButton);

}

void NewGameState::think()
{
    State::think();
}

void NewGameState::onBackButtonClick(Event * event)
{
    _game->popState();
}

}
