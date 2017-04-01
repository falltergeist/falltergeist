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
#include "TextArea.h"

// C++ standard includes
#include <algorithm>
#include <sstream>

// Falltergeist includes
#include "../CrossPlatform.h"
#include "../Event/Mouse.h"
#include "../Game/Game.h"
#include "../Graphics/Font.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Texture.h"
#include "../ResourceManager.h"
#include "../Logger.h"

// Third party includes
#include <SDL.h>

namespace Falltergeist
{
namespace Graphics
{

TextArea::TextArea()
{
    if (Game::getInstance()->renderer()->renderPath() == Renderer::RenderPath::OGL32)
    {
        GL_CHECK(glGenVertexArrays(1, &_vao));
        GL_CHECK(glBindVertexArray(_vao));
    }

    // generate VBOs for verts and tex
    GL_CHECK(glGenBuffers(1, &_coords));
    GL_CHECK(glGenBuffers(1, &_texCoords));
    GL_CHECK(glGenBuffers(1, &_ebo));
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo));
//    GL_CHECK(glBindVertexArray(0));

    _shader = ResourceManager::getInstance()->shader("font");

    _uniformTex = _shader->getUniform("tex");
    if (Game::getInstance()->renderer()->renderPath() == Graphics::Renderer::RenderPath::OGL21)
    {
        _uniformTexSize = _shader->getUniform("texSize");
    }
    _uniformFade = _shader->getUniform("fade");
    _uniformMVP = _shader->getUniform("MVP");
    _uniformOffset = _shader->getUniform("offset");
    _uniformColor = _shader->getUniform("color");
    _uniformOutline = _shader->getUniform("outlineColor");

    _attribPos = _shader->getAttrib("Position");
    _attribTex = _shader->getAttrib("TexCoord");
}

TextArea::~TextArea()
{
    GL_CHECK(glDeleteBuffers(1, &_coords));
    GL_CHECK(glDeleteBuffers(1, &_texCoords));
    GL_CHECK(glDeleteBuffers(1, &_ebo));
    if (Game::getInstance()->renderer()->renderPath() == Renderer::RenderPath::OGL32)
    {
        GL_CHECK(glDeleteVertexArrays(1, &_vao));
    }
}


void TextArea::render(Point& pos, Graphics::Font* font, SDL_Color _color, SDL_Color _outlineColor)
{
    if (!_cnt)
    {
        return;
    }

    GL_CHECK(_shader->use());

    GL_CHECK(font->texture()->bind(0));

    GL_CHECK(_shader->setUniform(_uniformTex, 0));

    GL_CHECK(_shader->setUniform(_uniformMVP, Game::getInstance()->renderer()->getMVP()));
    GL_CHECK(_shader->setUniform(_uniformOffset, glm::vec2((float)pos.x(), (float(pos.y())) )));
    GL_CHECK(_shader->setUniform(_uniformColor, glm::vec4((float)_color.r / 255.f, (float)_color.g / 255.f, (float)_color.b / 255.f, (float)_color.a / 255.f)));
    GL_CHECK(_shader->setUniform(_uniformOutline, glm::vec4((float)_outlineColor.r / 255.f, (float)_outlineColor.g / 255.f, (float)_outlineColor.b / 255.f, (float)_outlineColor.a / 255.f)));
    GL_CHECK(_shader->setUniform(_uniformFade, Game::getInstance()->renderer()->fadeColor()));
    if (Game::getInstance()->renderer()->renderPath() == Graphics::Renderer::RenderPath::OGL21)
    {
        GL_CHECK(_shader->setUniform(_uniformTexSize, glm::vec2((float)font->texture()->textureWidth(), (float)font->texture()->textureHeight() )));
    }

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


    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _texCoords));
    GL_CHECK(glVertexAttribPointer(_attribTex, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo));

    GL_CHECK(glEnableVertexAttribArray(_attribPos));
    GL_CHECK(glEnableVertexAttribArray(_attribTex));

    GL_CHECK(glDrawElements(GL_TRIANGLES, _cnt, GL_UNSIGNED_SHORT, 0 ));

    GL_CHECK(glDisableVertexAttribArray(_attribPos));
    GL_CHECK(glDisableVertexAttribArray(_attribTex));
}

void TextArea::updateBuffers(std::vector<glm::vec2> vertices, std::vector<glm::vec2> UV,  std::vector<GLushort> indexes)
{
    if (!vertices.size())
    {
        _cnt = 0;
        return;
    }
    _cnt = static_cast<int>(indexes.size());

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
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_DYNAMIC_DRAW));


    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _texCoords));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, UV.size() * sizeof(glm::vec2), &UV[0], GL_DYNAMIC_DRAW));

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo));
    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(GLushort), &indexes[0], GL_DYNAMIC_DRAW));

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

}
}
