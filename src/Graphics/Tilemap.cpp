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

// C++ standard includes

// Falltergeist includes

#include "../Base/StlFeatures.h"
#include "../Game/Game.h"
#include "../Graphics/AnimatedPalette.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Sprite.h"
#include "../Graphics/Tilemap.h"
#include "../ResourceManager.h"
#include "../State/Location.h"

// Third party includes

namespace Falltergeist
{
namespace Graphics
{

using Base::make_unique;

Tilemap::Tilemap(std::vector<glm::vec2> coords, std::vector<glm::vec2> textureCoords)
{

    GL_CHECK(glGenVertexArrays(1, &_vao));
    GL_CHECK(glBindVertexArray(_vao));

    // generate VBOs for verts and tex
    GL_CHECK(glGenBuffers(1, &_coords));
    GL_CHECK(glGenBuffers(1, &_texCoords));
    GL_CHECK(glGenBuffers(1, &_ebo));

    if (coords.size()<=0 || textureCoords.size() <=0) return;

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _coords));
    //update coords
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, coords.size() * sizeof(glm::vec2), &coords[0], GL_STATIC_DRAW));


    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _texCoords));
    //update texcoords
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, textureCoords.size() * sizeof(glm::vec2), &textureCoords[0], GL_STATIC_DRAW));

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo));
    GL_CHECK(glBindVertexArray(0));

    _shader = ResourceManager::getInstance()->shader("tilemap");

    _uniformTex = _shader->getUniform("tex");
    _uniformFade = _shader->getUniform("fade");
    _uniformMVP = _shader->getUniform("MVP");
    _uniformCnt = _shader->getUniform("cnt");
    _uniformLight = _shader->getUniform("global_light");
    _uniformOffset = _shader->getUniform("offset");

    _attribPos = _shader->getAttrib("Position");
    _attribTex = _shader->getAttrib("TexCoord");

}

Tilemap::~Tilemap()
{
    GL_CHECK(glDeleteBuffers(1, &_coords));
    GL_CHECK(glDeleteBuffers(1, &_texCoords));
    GL_CHECK(glDeleteBuffers(1, &_ebo));

    GL_CHECK(glDeleteVertexArrays(1, &_vao));
}

void Tilemap::render(const Point &pos, std::vector<GLuint> indexes, uint32_t atlas)
{
    if (indexes.size()<=0) return;

    GL_CHECK(_shader->use());

    GL_CHECK(_textures.at(atlas).get()->bind(0));

    GL_CHECK(_shader->setUniform(_uniformTex, 0));

    GL_CHECK(_shader->setUniform(_uniformMVP, Game::getInstance()->renderer()->getMVP()));

    // set camera offset
    GL_CHECK(_shader->setUniform(_uniformOffset, glm::vec2((float)pos.x()+1.0, (float)pos.y()+2.0) ));

    GL_CHECK(_shader->setUniform(_uniformFade, Game::getInstance()->renderer()->fadeColor()));

    GL_CHECK(_shader->setUniform(_uniformCnt, Game::getInstance()->animatedPalette()->counters()));

    int lightLevel = 100;
    if (auto state = Game::getInstance()->locationState())
    {
        if ( state->lightLevel() < 0xA000 )
        {
            lightLevel = (state->lightLevel() - 0x4000) * 100 / 0x6000;

        }
        else if ( state->lightLevel() == 0xA000 )
        {
            lightLevel = 50;
        }
        else
        {
            lightLevel = (state->lightLevel() - 0xA000) * 100 / 0x6000;
        }
    }
    GL_CHECK(_shader->setUniform(_uniformLight, lightLevel));

    GLint curvao;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &curvao);
    if ((GLuint)curvao != _vao)
    {
        GL_CHECK(glBindVertexArray(_vao));
    }

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _coords));
    GL_CHECK(glVertexAttribPointer(_attribPos, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));


    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _texCoords));

    GL_CHECK(glVertexAttribPointer(_attribTex, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo));

    // update indexes
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(GLuint), &indexes[0], GL_DYNAMIC_DRAW));

    GL_CHECK(glEnableVertexAttribArray(_attribPos));

    GL_CHECK(glEnableVertexAttribArray(_attribTex));

    GL_CHECK(glDrawElements(GL_TRIANGLES, indexes.size(), GL_UNSIGNED_INT, 0 ));

    GL_CHECK(glDisableVertexAttribArray(_attribPos));

    GL_CHECK(glDisableVertexAttribArray(_attribTex));
}

void Tilemap::addTexture(SDL_Surface *surface)
{
    _textures.push_back(make_unique<Texture>(surface->w, surface->h));
    _textures.back().get()->loadFromSurface(surface);
}

}
}
