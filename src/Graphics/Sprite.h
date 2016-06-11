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

#ifndef FALLTERGEIST_GRAPHICS_SPRITE_H
#define FALLTERGEIST_GRAPHICS_SPRITE_H

// C++ standard includes
#include <string>

// Falltergeist includes
#include "../Graphics/Point.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Texture.h"
#include "../Graphics/TransFlags.h"
#include "../Format/Frm/File.h"

// Third party includes

namespace Falltergeist
{
namespace Graphics
{

class Sprite
{

public:
    Sprite(const std::string& filename);
    Sprite(Format::Frm::File* frm);
    void renderScaled(int x, int y, unsigned int width, unsigned int height, bool transparency = false,
                      bool light = false, int outline = 0, unsigned int lightValue=0);
    void render(int x, int y, bool transparency = false, bool light = false, int outline = 0, unsigned int lightValue=0);
    void renderCropped(int x, int y, int dx, int dy, unsigned int width, unsigned int height, bool transparency = false,
                       bool light = false, unsigned int lightValue=0);
    unsigned int width() const;
    unsigned int height() const;
    Size size() const;
    bool opaque(unsigned int x, unsigned int y);
    void trans(Graphics::TransFlags::Trans _trans);

private:
    Texture* _texture;
    Graphics::TransFlags::Trans _trans = Graphics::TransFlags::Trans::NONE;

    GLint _uniformTex;
    GLint _uniformTexSize;
    GLint _uniformEggTex;
    GLint _uniformFade;
    GLint _uniformMVP;
    GLint _uniformCnt;
    GLint _uniformLight;
    GLint _uniformTrans;
    GLint _uniformDoEgg;
    GLint _uniformEggPos;
    GLint _uniformOutline;

    GLint _attribPos;
    GLint _attribTex;
    Graphics::Shader*_shader;
};

}
}
#endif //FALLTERGEIST_GRAPHICS_SPRITE_H
