#include "States/NewGameState.h"
#include "Engine/Game.h"
#include "Engine/ResourceManager.h"
#include "UI/ImageButton.h"
#include "UI/TextArea.h"
#include "Engine/SurfaceSet.h"
#include <iostream>
#include <sstream>

namespace Falltergeist
{

NewGameState::NewGameState(Game * game) : State(game)
{
}

NewGameState::~NewGameState()
{
}

void NewGameState::init()
{
    State::init();
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

    // Characters images
    _selectedCharacter = 0;
    _characterImages = new SurfaceSet(27,23);
    _characterImages->addSurface(ResourceManager::getSurface("art/intrface/combat.frm"));
    _characterImages->addSurface(ResourceManager::getSurface("art/intrface/stealth.frm"));
    _characterImages->addSurface(ResourceManager::getSurface("art/intrface/diplomat.frm"));

    // Character data textarea

    //std::cout <<    ;


    std::stringstream ss;
    //ss << _t(100, "text/english/game/stat.msg") << " 01\r\n"
    //   << _t(101, "text/english/game/stat.msg") << " 01\r\n"
    ss   << _t(100,"text/english/game/stat.msg") << " 01\r\n";
    ss   << _t(101,"text/english/game/stat.msg") << " 01\r\n";
    //ss   << _t(102,"text/english/game/stat.msg") << " 01\r\n";
    //ss   << _t(103,"text/english/game/stat.msg") << " 01\r\n";
    //ss   << _t(104,"text/english/game/stat.msg") << " 01\r\n";
    ss   << _t(105,"text/english/game/stat.msg") << " 01";





    _textArea1 = new TextArea("",300,100);
    _textArea1->setText((char *)ss.str().c_str());
    _textArea1->setFont("font1.aaf");
    _textArea1->setHorizontalAlign(TextArea::HORIZONTAL_ALIGN_RIGHT);




    add(beginGameButton);
    add(editButton);
    add(createButton);
    add(backButton);
    add(prevCharacterButton);
    add(nextCharacterButton);

    add(_characterImages);
    add(_textArea1);
}

void NewGameState::think()
{
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
    _characterImages->currentSurface = _selectedCharacter;
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
    _characterImages->currentSurface = _selectedCharacter;
}

}
