/*
 * Copyright 2012-2016 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FALLTERGEIST_STATE_MOVIE_H
#define FALLTERGEIST_STATE_MOVIE_H

// C++ standard includes

// Falltergeist includes
#include "../State/State.h"

// Third party includes

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
                bool _started;
                std::pair<unsigned int,std::string> _nextSubLine;
                Format::Sve::File* _subs = nullptr;
                bool _hasSubs = false;
                std::vector<effect_t> _effects;
                unsigned int _effect_index=0;
        };
    }
}
#endif // FALLTERGEIST_STATE_MOVIE_H
