/*
 * Copyright 2012-2015 Falltergeist Developers.
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

#ifndef FALLTERGEIST_ANIMATEDIMAGE_H
#define FALLTERGEIST_ANIMATEDIMAGE_H

// C++ standard includes
#include <string>

// Falltergeist includes
#include "../Graphics/ActiveUI.h"
#include "../Graphics/UI.h"

// Third party includes
#include <libfalltergeist.h>


namespace Falltergeist
{

class AnimatedImage : public ActiveUI
{
protected:
    std::vector<Texture*> _slimeTextures;
    std::vector<Texture*> _fireSlowTextures;
    std::vector<Texture*> _fireFastTextures;
    std::vector<Texture*> _shoreTextures;
    std::vector<Texture*> _monitorTextures;
    std::vector<Texture*> _reddotTextures;
public:
    AnimatedImage(libfalltergeist::Frm::File* frm, unsigned int direction);
    unsigned int width();
    unsigned int height();
    ~AnimatedImage();
    void render(bool eggTransparency = false);
};

}
#endif // FALLTERGEIST_ANIMATEDIMAGE_H
