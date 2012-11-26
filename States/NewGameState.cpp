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
    prevCharacterButton->onLeftButtonClick((EventHandler) &NewGameState::onPrevCharacterButtonClick);

    RightArrowButton * nextCharacterButton = new RightArrowButton(318,320);
    nextCharacterButton->onLeftButtonClick((EventHandler) &NewGameState::onNextCharacterButtonClick);

    _selectedCharacter = 0;

    _characterImages = new Surface[3];
    _characterImages[0].loadFromSurface(_game->getResourceManager()->getSurface("art/intrface/combat.frm",27,23));
    _characterImages[1].loadFromSurface(_game->getResourceManager()->getSurface("art/intrface/stealth.frm",27,23));
    _characterImages[2].loadFromSurface(_game->getResourceManager()->getSurface("art/intrface/diplomat.frm",27,23));

    _characterImage = _characterImages[_selectedCharacter];

    add(beginGameButton);
    add(editButton);
    add(createButton);
    add(backButton);
    add(prevCharacterButton);
    add(nextCharacterButton);

    add(&_characterImage);
}

void NewGameState::think()
{
    State::think();
}

void NewGameState::onBackButtonClick()
{
    _game->popState();
}

void NewGameState::onPrevCharacterButtonClick()
{
    if (_selectedCharacter > 0)
    {
        _selectedCharacter--;
    }
    else
    {
        _selectedCharacter = 2;
    }
    _characterImage = _characterImages[_selectedCharacter];
}

void NewGameState::onNextCharacterButtonClick()
{
    if (_selectedCharacter < 2)
    {
        _selectedCharacter++;
    }
    else
    {
        _selectedCharacter = 0;
    }
    _characterImage = _characterImages[_selectedCharacter];
}

}
