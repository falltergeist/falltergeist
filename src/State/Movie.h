#pragma once

#include "../State/State.h"

namespace Falltergeist
{
    namespace Format
    {
        namespace Sve
        {
            class File;
        }
    }
    class MvePlayer;

    namespace State
    {
        typedef struct
        {
            unsigned int frame;
            int direction;
            int r;
            int g;
            int b;
            int frames;
        } effect_t;

        class Movie final : public State
        {
            public:
                Movie(std::shared_ptr<Input::Mouse> mouse, int id);

                ~Movie() override;

                void init() override;

                void think(const float &deltaTime) override;

                void handle(Event::Event* event) override;

                void onStateActivate(Event::State* event) override;

                void onStateDeactivate(Event::State* event) override;

                void onVideoFinished();

            private:
                int _id;

                bool _started = false;

                std::pair<unsigned int,std::string> _nextSubLine;

                Format::Sve::File* _subs = nullptr;

                bool _hasSubs = false;

                std::vector<effect_t> _effects;

                unsigned int _effectIndex = 0;

                Input::Mouse::Cursor _previousCursor = Input::Mouse::Cursor::NONE;
        };
    }
}
