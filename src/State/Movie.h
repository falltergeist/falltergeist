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

        class Movie : public State
        {
            public:
                Movie(int id);
                ~Movie() override;

                void init() override;
                void think() override;
                void handle(Event::Event* event) override;

                void onVideoFinished();

            private:
                int _id;
                bool _started = false;
                std::pair<unsigned int,std::string> _nextSubLine;
                Format::Sve::File* _subs = nullptr;
                bool _hasSubs = false;
                std::vector<effect_t> _effects;
                unsigned int _effect_index=0;
        };
    }
}
