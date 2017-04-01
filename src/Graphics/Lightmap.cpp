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

// Related headers
#include "../Graphics/Lightmap.h"

// C++ standard includes

// Falltergeist includes
#include "../Game/Game.h"
#include "../Graphics/Shader.h"
#include "../ResourceManager.h"
#include "../State/Location.h"

// Third-party includes

namespace Falltergeist
{
namespace Graphics
{

Lightmap::Lightmap(std::vector<glm::vec2> coords, std::vector<GLuint> indexes)
{
    if (Game::getInstance()->renderer()->renderPath() == Renderer::RenderPath::OGL32)
    {
        GL_CHECK(glGenVertexArrays(1, &_vao));
        GL_CHECK(glBindVertexArray(_vao));
    }

    // generate VBOs for verts and tex
    GL_CHECK(glGenBuffers(1, &_coords));
    GL_CHECK(glGenBuffers(1, &_lights));
    GL_CHECK(glGenBuffers(1, &_ebo));

    if (coords.size()<=0) return;

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _coords));
    //update coords
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, coords.size() * sizeof(glm::vec2), &coords[0], GL_STATIC_DRAW));


    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _lights));

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo));
    // update indexes
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(GLuint), &indexes[0], GL_DYNAMIC_DRAW));
    _indexes = static_cast<unsigned>(indexes.size());


    _shader = ResourceManager::getInstance()->shader("lightmap");

    _uniformFade = _shader->getUniform("fade");
    _uniformMVP = _shader->getUniform("MVP");
    _uniformOffset = _shader->getUniform("offset");

    _attribPos = _shader->getAttrib("Position");
    _attribLights = _shader->getAttrib("lights");
}

Lightmap::~Lightmap()
{
    GL_CHECK(glDeleteBuffers(1, &_coords));
    GL_CHECK(glDeleteBuffers(1, &_lights));
    GL_CHECK(glDeleteBuffers(1, &_ebo));

    if (Game::getInstance()->renderer()->renderPath() == Renderer::RenderPath::OGL32)
    {
        GL_CHECK(glDeleteVertexArrays(1, &_vao));
    }
}

void Lightmap::render(const Point &pos)
{
    if (_indexes<=0) return;

    GL_CHECK(glBlendFunc(GL_DST_COLOR, GL_SRC_COLOR));

    GL_CHECK(_shader->use());

    GL_CHECK(_shader->setUniform(_uniformMVP, Game::getInstance()->renderer()->getMVP()));

    // set camera offset
    GL_CHECK(_shader->setUniform(_uniformOffset, glm::vec2((float)pos.x(), (float)pos.y()) ));

    GL_CHECK(_shader->setUniform(_uniformFade, Game::getInstance()->renderer()->fadeColor()));

    if (Game::getInstance()->renderer()->renderPath() == Renderer::RenderPath::OGL32)
    {
        GLint curvao;
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &curvao);
        if ((GLuint)curvao != _vao)
        {
            GL_CHECK(glBindVertexArray(_vao));
        }
    }


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

    GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void Lightmap::update(std::vector<float> lights)
{
    if (Game::getInstance()->renderer()->renderPath() == Renderer::RenderPath::OGL32)
    {
        GLint curvao;
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &curvao);
        if ((GLuint)curvao != _vao)
        {
            GL_CHECK(glBindVertexArray(_vao));
        }
    }

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _lights));
    //update lights
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, lights.size() * sizeof(float), &lights[0], GL_STATIC_DRAW));
}

}
}
