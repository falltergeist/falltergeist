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

#ifndef FALLTERGEIST_GRAPHICS_TILEMAP_H
#define FALLTERGEIST_GRAPHICS_TILEMAP_H

#include "../Point.h"
#include "Renderer.h"
#include "Texture.h"

namespace Falltergeist
{
namespace Graphics
{

class Tilemap
{
public:
    Tilemap(std::vector<glm::vec2> coords, std::vector<glm::vec2> textureCoords);
    ~Tilemap();
    void render(const Point &pos, std::vector<GLuint> indexes, uint32_t atlas);
    void addTexture(SDL_Surface* surface);

private:
    GLuint _vao;
    GLuint _coords;
    GLuint _texCoords;
    GLuint _ebo;
    std::vector<std::unique_ptr<Texture>> _textures;

    GLint _uniformTex;
    GLint _uniformFade;
    GLint _uniformMVP;
    GLint _uniformCnt;
    GLint _uniformLight;
    GLint _uniformOffset;

    GLint _attribPos;
    GLint _attribTex;
};

}
}
#endif //FALLTERGEIST_GRAPHICS_TILEMAP_H
