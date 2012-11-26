#include "NewGameState.h"
#include "Game.h"
#include "ResourceManager.h"
#include "UI/ImageButton.h"

namespace Falltergeist
{

NewGameState::NewGameState(Game * game) : State(game)
{
    init();
}

void NewGameState::init()
{
    _isFullscreen = true;
    // background
    add(ResourceManager::getSurface("art/intrface/pickchar.frm"));

    // Begin game button
    ImageButton * beginGameButton= new ImageButton("art/intrface/lilredup.frm", "art/intrface/lilreddn.frm", 81, 322);

    // Edit character button
    ImageButton * editButton= new ImageButton("art/intrface/lilredup.frm", "art/intrface/lilreddn.frm", 436, 319);

    // Create character button
    ImageButton * createButton= new ImageButton("art/intrface/lilredup.frm", "art/intrface/lilreddn.frm", 81, 424);

    // Back to mainmenu button
    ImageButton * backButton= new ImageButton("art/intrface/lilredup.frm", "art/intrface/lilreddn.frm", 461, 424);
    backButton->onLeftButtonClick((EventHandler) &NewGameState::onBackButtonClick);

    // Previous character button
    ImageButton * prevCharacterButton = new ImageButton("art/intrface/slu.frm", "art/intrface/sld.frm", 292, 320);
    prevCharacterButton->onLeftButtonClick((EventHandler) &NewGameState::onPrevCharacterButtonClick);

    // Next character button
    ImageButton * nextCharacterButton = new ImageButton("art/intrface/sru.frm", "art/intrface/srd.frm", 318, 320);
    nextCharacterButton->onLeftButtonClick((EventHandler) &NewGameState::onNextCharacterButtonClick);

    _selectedCharacter = 0;

    _characterImages = new Surface[3];
    _characterImages[0].loadFromSurface(ResourceManager::getSurface("art/intrface/combat.frm", 27, 23));
    _characterImages[1].loadFromSurface(ResourceManager::getSurface("art/intrface/stealth.frm", 27, 23));
    _characterImages[2].loadFromSurface(ResourceManager::getSurface("art/intrface/diplomat.frm", 27, 23));

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
