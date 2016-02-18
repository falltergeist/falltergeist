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

#include <ResourceManager.h>
#include <Game/Game.h>
#include "Tilemap.h"
#include "Shader.h"

namespace Falltergeist {
namespace Graphics {


Tilemap::Tilemap(std::vector<Point> coords, std::vector<Point> textureCoords, SDL_Surface *surface)
{
    GL_CHECK(glGenVertexArrays(1, &_vao));
    GL_CHECK(glBindVertexArray(_vao));

    // generate VBOs for verts and tex
    GL_CHECK(glGenBuffers(1, &_coords));
    GL_CHECK(glGenBuffers(1, &_texCoords));
    GL_CHECK(glGenBuffers(1, &_ebo));

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _coords));
    //update coords

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _texCoords));
    //update texcoords

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo));
    GL_CHECK(glBindVertexArray(0));

    // set texture
    _texture = new Texture(surface->w, surface->h);
    _texture->loadFromSurface(surface);
}

Tilemap::~Tilemap()
{
    GL_CHECK(glDeleteBuffers(1, &_coords));
    GL_CHECK(glDeleteBuffers(1, &_texCoords));
    GL_CHECK(glDeleteBuffers(1, &_ebo));

    GL_CHECK(glDeleteVertexArrays(1, &_vao));
}

void Tilemap::render(const Point &pos, std::vector<GLuint> indexes)
{

    GL_CHECK(ResourceManager::getInstance()->shader("tilemap")->use());

    GL_CHECK(_texture->bind(0));

    GL_CHECK(ResourceManager::getInstance()->shader("tilemap")->setUniform("tex",0));

    GL_CHECK(ResourceManager::getInstance()->shader("tilemap")->setUniform("MVP",
                                                                          Game::getInstance()->renderer()->getMVP()));

    // set camera offset
    GL_CHECK(ResourceManager::getInstance()->shader("tilemap")->setUniform("offset", glm::vec2((float)pos.x(), (float(pos.y())) )));



    GL_CHECK(glBindVertexArray(_vao));


    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _coords));
    GL_CHECK(glVertexAttribPointer(ResourceManager::getInstance()->shader("tilemap")->getAttrib("Position"), 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));


    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _texCoords));

    GL_CHECK(glVertexAttribPointer(ResourceManager::getInstance()->shader("tilemap")->getAttrib("TexCoord"), 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo));

    // update indexes
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(GLushort), &indexes[0], GL_DYNAMIC_DRAW));

    GL_CHECK(glEnableVertexAttribArray(ResourceManager::getInstance()->shader("tilemap")->getAttrib("Position")));

    GL_CHECK(glEnableVertexAttribArray(ResourceManager::getInstance()->shader("tilemap")->getAttrib("TexCoord")));

    GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0 ));

    GL_CHECK(glDisableVertexAttribArray(ResourceManager::getInstance()->shader("tilemap")->getAttrib("Position")));

    GL_CHECK(glDisableVertexAttribArray(ResourceManager::getInstance()->shader("tilemap")->getAttrib("TexCoord")));

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CHECK(glBindVertexArray(0));

    GL_CHECK(ResourceManager::getInstance()->shader("tilemap")->unuse());
    GL_CHECK(_texture->unbind(0));
}

}
}