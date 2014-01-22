/*
 * Copyright 2012-2013 Falltergeist Developers.
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

// C++ standard includes
#include <cmath>
#include <iostream>

// Falltergeist includes
#include "../Engine/AudioMixer.h"
#include "../Engine/Exception.h"
#include "../Engine/CrossPlatform.h"

// Third party includes

namespace Falltergeist
{

AudioMixer::AudioMixer()
{
    _init();
}

void AudioMixer::_init()
{
    std::string message = "[AUDIO] - SDL_Init - ";
    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
    {
        debug(message + "[FAIL]", DEBUG_CRITICAL);
        throw Exception(SDL_GetError());
    }
    debug(message + "[OK]", DEBUG_INFO);

     SDL_AudioSpec *desired, *obtained;
     desired  = (SDL_AudioSpec *) malloc(sizeof(SDL_AudioSpec));
     obtained = (SDL_AudioSpec *) malloc(sizeof(SDL_AudioSpec));

     desired->freq = 22050;
     desired->format = AUDIO_S8;
     desired->samples = 4096;
     desired->callback = &AudioMixer::callback;
     desired->userdata = this;
     desired->channels = 0; // Mono

     if ( SDL_OpenAudio(desired, obtained) < 0 )
     {
         throw Exception("AudioMixer::init() - initialization error" + std::string(SDL_GetError()));
     }
     //SDL_PauseAudio(0);
}

void AudioMixer::callback(void* userdata, Uint8* stream, int len)
{
    AudioMixer* mixer = static_cast<AudioMixer*>(userdata);

    static double angle = 0.0 ;
    int i = 0 ;

    unsigned int rnd = (rand() % 100) + 1;

    if (rnd < 40)
    {
        for(i=0; i<len; i++) *stream++ = 0;
        return;
    }


    for(i=0; i<len; i++)
    {
        *stream++ = 255*cos(angle) ; // I think that this should be 128 * cos(angle) as cos is (-1,1)
        angle += 3.14159/rnd ;       // and a Uint8 is only 8 bits (256 values)
        if( angle > 2.0*3.14159 )
        {
            angle -= 2.0*3.14159 ;
        }
    }
    std::cout << "Callback: " << len <<  std::endl;
}

};
