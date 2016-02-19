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

#include "../Base/StlFeatures.h"
#include <ResourceManager.h>
#include <Game/Game.h>
#include <iostream>
#include "Tilemap.h"
#include "Shader.h"
#include "Sprite.h"

namespace Falltergeist {
namespace Graphics {

using Base::make_unique;

Tilemap::Tilemap(std::vector<glm::vec2> coords, std::vector<glm::vec2> textureCoords)
{
    GL_CHECK(glGenVertexArrays(1, &_vao));
    GL_CHECK(glBindVertexArray(_vao));

    // generate VBOs for verts and tex
    GL_CHECK(glGenBuffers(1, &_coords));
    GL_CHECK(glGenBuffers(1, &_texCoords));
    GL_CHECK(glGenBuffers(1, &_ebo));

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _coords));
    //update coords
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, coords.size() * sizeof(glm::vec2), &coords[0], GL_STATIC_DRAW));


    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _texCoords));
    //update texcoords
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, textureCoords.size() * sizeof(glm::vec2), &textureCoords[0], GL_STATIC_DRAW));

    std::cout << "cs " << coords.size() << " ts " << textureCoords.size() << std::endl;
    for (int i =0; i<10; i++)
    {
        std::cout << coords.at(i).x << " " << coords.at(i).y << std::endl;
    }

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo));
    GL_CHECK(glBindVertexArray(0));

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

    GL_CHECK(ResourceManager::getInstance()->shader("tilemap")->use());

    GL_CHECK(_textures.at(atlas).get()->bind(0));

    GL_CHECK(ResourceManager::getInstance()->shader("tilemap")->setUniform("tex",0));

    GL_CHECK(ResourceManager::getInstance()->shader("tilemap")->setUniform("MVP",
                                                                          Game::getInstance()->renderer()->getMVP()));

    // set camera offset
    GL_CHECK(ResourceManager::getInstance()->shader("tilemap")->setUniform("offset", glm::vec2((float)pos.x(), (float)pos.y()) ));

    GL_CHECK(glBindVertexArray(_vao));


    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _coords));
    GL_CHECK(glVertexAttribPointer(ResourceManager::getInstance()->shader("tilemap")->getAttrib("Position"), 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));


    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _texCoords));

    GL_CHECK(glVertexAttribPointer(ResourceManager::getInstance()->shader("tilemap")->getAttrib("TexCoord"), 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo));

    //std::cout << pos.x() << " : " << pos.y() << " | " << indexes.size();
    // update indexes
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(GLuint), &indexes[0], GL_DYNAMIC_DRAW));

    GL_CHECK(glEnableVertexAttribArray(ResourceManager::getInstance()->shader("tilemap")->getAttrib("Position")));

    GL_CHECK(glEnableVertexAttribArray(ResourceManager::getInstance()->shader("tilemap")->getAttrib("TexCoord")));

    GL_CHECK(glDrawElements(GL_TRIANGLES, indexes.size(), GL_UNSIGNED_INT, 0 ));

    GL_CHECK(glDisableVertexAttribArray(ResourceManager::getInstance()->shader("tilemap")->getAttrib("Position")));

    GL_CHECK(glDisableVertexAttribArray(ResourceManager::getInstance()->shader("tilemap")->getAttrib("TexCoord")));

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CHECK(glBindVertexArray(0));

    GL_CHECK(ResourceManager::getInstance()->shader("tilemap")->unuse());
    GL_CHECK(_textures.at(atlas).get()->unbind(0));
}

void Tilemap::addTexture(SDL_Surface *surface)
{
    _textures.push_back(make_unique<Texture>(surface->w, surface->h));
    _textures.back().get()->loadFromSurface(surface);

}
}
}