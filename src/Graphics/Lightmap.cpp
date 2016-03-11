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
#include "Lightmap.h"
#include <ResourceManager.h>
#include <Game/Game.h>
#include <iostream>
#include "Shader.h"
#include "../State/Location.h"

namespace Falltergeist {
namespace Graphics {


Lightmap::Lightmap(std::vector<glm::vec2> coords,std::vector<GLuint> indexes)
{
    GL_CHECK(glGenVertexArrays(1, &_vao));
    GL_CHECK(glBindVertexArray(_vao));

    // generate VBOs for verts and tex
    GL_CHECK(glGenBuffers(1, &_coords));
    GL_CHECK(glGenBuffers(1, &_lights));
    GL_CHECK(glGenBuffers(1, &_ebo));

    if (coords.size()<=0) return;

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _coords));
    //update coords
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, coords.size() * sizeof(glm::vec2), &coords[0], GL_STATIC_DRAW));


    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _lights));
    //update texcoords
//    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, textureCoords.size() * sizeof(glm::vec2), &textureCoords[0], GL_STATIC_DRAW));

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo));
    // update indexes
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(GLuint), &indexes[0], GL_DYNAMIC_DRAW));
    _indexes = indexes.size();

    GL_CHECK(glBindVertexArray(0));

    auto shader = ResourceManager::getInstance()->shader("lightmap");

    _uniformFade = shader->getUniform("fade");
    _uniformMVP = shader->getUniform("MVP");
    _uniformOffset = shader->getUniform("offset");

    _attribPos = shader->getAttrib("Position");
    _attribLights = shader->getAttrib("lights");
}

Lightmap::~Lightmap()
{

}

void Lightmap::render(const Falltergeist::Point &pos)
{
    if (_indexes<=0) return;

    GL_CHECK(glBlendFunc(GL_DST_COLOR, GL_SRC_COLOR));
    auto shader = ResourceManager::getInstance()->shader("lightmap");

    GL_CHECK(shader->use());

    GL_CHECK(shader->setUniform(_uniformMVP, Game::getInstance()->renderer()->getMVP()));

    // set camera offset
    GL_CHECK(shader->setUniform(_uniformOffset, glm::vec2((float)pos.x(), (float)pos.y()) ));

    GL_CHECK(shader->setUniform(_uniformFade,Game::getInstance()->renderer()->fadeColor()));


    GL_CHECK(glBindVertexArray(_vao));


    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _coords));
    GL_CHECK(glVertexAttribPointer(_attribPos, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));


    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _lights));

    GL_CHECK(glVertexAttribPointer(_attribLights, 1, GL_FLOAT, GL_FALSE, 0, (void*)0 ));

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo));


    GL_CHECK(glEnableVertexAttribArray(_attribPos));

    GL_CHECK(glEnableVertexAttribArray(_attribLights));

    GL_CHECK(glDrawElements(GL_TRIANGLES, _indexes, GL_UNSIGNED_INT, 0 ));

    GL_CHECK(glDisableVertexAttribArray(_attribPos));

    GL_CHECK(glDisableVertexAttribArray(_attribLights));

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CHECK(glBindVertexArray(0));

    GL_CHECK(shader->unuse());
    GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void Lightmap::update(std::vector<float> lights)
{
    GL_CHECK(glBindVertexArray(_vao));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _lights));
    //update lights
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, lights.size() * sizeof(float), &lights[0], GL_STATIC_DRAW));
    GL_CHECK(glBindVertexArray(0));

}
}
}