#pragma once

#include <vector>
#include "State.h"

namespace Falltergeist
{
    namespace Game
    {
        class DudeObject;
    }
    namespace State
    {
        class NewGame : public State
        {
            public:
                NewGame();
                ~NewGame() override;

                void init() override;
                void think() override;

                void onBackButtonClick(Event::Mouse* event);
                void onBackFadeDone(Event::State* event);
                void onBeginGameButtonClick(Event::Mouse* event);
                void onEditButtonClick(Event::Mouse* event);
                void onCreateButtonClick(Event::Mouse* event);
                void onPrevCharacterButtonClick(Event::Mouse* event);
                void onNextCharacterButtonClick(Event::Mouse* event);
                void onStateActivate(Event::State* event) override;
                void doBeginGame();
                void doEdit();
                void doCreate();
                void doBack();
                void doNext();
                void doPrev();
                void onKeyDown(Event::Keyboard* event) override;

            protected:
                unsigned char _selectedCharacter = 0;
                std::vector<std::unique_ptr<Game::DudeObject>> _characters;

                void _changeCharacter();
        };
    }
}
