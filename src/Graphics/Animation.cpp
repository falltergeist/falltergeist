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
#include "../Graphics/Animation.h"

// C++ standart includes

// Falltergeist includes
#include "../Format/Frm/File.h"
#include "../Format/Frm/Direction.h"
#include "../Format/Frm/Frame.h"
#include "../Game/Game.h"
#include "../Graphics/AnimatedPalette.h"
#include "../Graphics/Point.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Shader.h"
#include "../Graphics/TransFlags.h"
#include "../ResourceManager.h"
#include "../State/Location.h"

// Third-party includes
#include <SDL_image.h>

namespace Falltergeist
{
namespace Graphics
{

Animation::Animation(const std::string &filename)
{
    // create buffers
    // generate VAO
    if (Game::getInstance()->renderer()->renderPath() == Renderer::RenderPath::OGL32)
    {
        GL_CHECK(glGenVertexArrays(1, &_vao));
        GL_CHECK(glBindVertexArray(_vao));
    }

    // generate VBOs for verts and tex
    GL_CHECK(glGenBuffers(1, &_coordsVBO));
    GL_CHECK(glGenBuffers(1, &_texCoordsVBO));
    GL_CHECK(glGenBuffers(1, &_ebo));

    _texture = ResourceManager::getInstance()->texture(filename);

    Format::Frm::File* frm = ResourceManager::getInstance()->frmFileType(filename);

    _stride = frm->framesPerDirection();

    int offsetX = 1;
    int offsetY = 1;

    for (auto& direction : frm->directions())
    {
        offsetX = 1;
        for (unsigned int f = 0; f != frm->framesPerDirection(); ++f)
        {
            auto& srcFrame = direction.frames().at(f);

            _vertices.push_back(glm::vec2(0.0, 0.0));
            _vertices.push_back(glm::vec2(0.0, (float)srcFrame.height() + 2.0));
            _vertices.push_back(glm::vec2((float)srcFrame.width() + 2.0, 0.0));
            _vertices.push_back(glm::vec2((float)srcFrame.width() + 2.0, (float)srcFrame.height() + 2.0));

            _texCoords.push_back(glm::vec2(
                (float)(offsetX - 1.0) / (float)_texture->textureWidth(),
                (float)(offsetY - 1.0) / (float)_texture->textureHeight()
            ));
            _texCoords.push_back(glm::vec2(
                (float)(offsetX - 1.0) / (float)_texture->textureWidth(),
                (float)(offsetY + srcFrame.height() + 1.0) / (float)_texture->textureHeight()
            ));
            _texCoords.push_back(glm::vec2(
                (float)(offsetX + srcFrame.width() + 1.0) / (float)_texture->textureWidth(),
                (float)(offsetY - 1.0) / (float)_texture->textureHeight()
            ));
            _texCoords.push_back(glm::vec2(
                (float)(offsetX + srcFrame.width() + 1.0) / (float)_texture->textureWidth(),
                (float)(offsetY + srcFrame.height() + 1.0) / (float)_texture->textureHeight()
            ));

            offsetX += srcFrame.width()+2;

        }
        offsetY += direction.height();

    }

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _coordsVBO));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glm::vec2), &_vertices[0], GL_STATIC_DRAW));

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _texCoordsVBO));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, _texCoords.size() * sizeof(glm::vec2), &_texCoords[0], GL_STATIC_DRAW));

    _shader = ResourceManager::getInstance()->shader("animation");

    _uniformTex = _shader->getUniform("tex");
    if (Game::getInstance()->renderer()->renderPath() == Renderer::RenderPath::OGL21)
    {
        _uniformTexSize = _shader->getUniform("texSize");
    }
    _uniformFade = _shader->getUniform("fade");
    _uniformMVP = _shader->getUniform("MVP");
    _uniformCnt = _shader->getUniform("cnt");
    _uniformLight = _shader->getUniform("global_light");
    _uniformTrans = _shader->getUniform("trans");
    _uniformOffset = _shader->getUniform("offset");
    _uniformOutline = _shader->getUniform("outline");

    _uniformTexStart = _shader->getUniform("texStart");
    _uniformTexHeight = _shader->getUniform("texHeight");

    _attribPos = _shader->getAttrib("Position");
    _attribTex = _shader->getAttrib("TexCoord");
}

Animation::~Animation()
{
    GL_CHECK(glDeleteBuffers(1, &_coordsVBO));
    GL_CHECK(glDeleteBuffers(1, &_texCoordsVBO));
    GL_CHECK(glDeleteBuffers(1, &_ebo));

    if (Game::getInstance()->renderer()->renderPath() == Renderer::RenderPath::OGL32)
    {
        GL_CHECK(glDeleteVertexArrays(1, &_vao));
    }
}

void Animation::render(int x, int y, unsigned int direction, unsigned int frame, bool transparency, bool light, int outline, unsigned int lightValue)
{
    int pos = direction*_stride+frame;

    float texStart = _texCoords.at(pos*4).y;
    float texEnd = _texCoords.at(pos*4+3).y;
    float texHeight = texEnd-texStart;

    GL_CHECK(_shader->use());

    GL_CHECK(_texture->bind(0));

    GL_CHECK(_shader->setUniform(_uniformTex, 0));

    GL_CHECK(_shader->setUniform(_uniformOffset, glm::vec2((float)x, (float)y)));

    GL_CHECK(_shader->setUniform(_uniformMVP, Game::getInstance()->renderer()->getMVP()));

    GL_CHECK(_shader->setUniform(_uniformFade, Game::getInstance()->renderer()->fadeColor()));

    GL_CHECK(_shader->setUniform(_uniformCnt, Game::getInstance()->animatedPalette()->counters()));

    int lightLevel = 100;
    if (light)
    {
        if (auto state = Game::getInstance()->locationState())
        {
            if (lightValue<=state->lightLevel()) lightValue=state->lightLevel();
            lightLevel = lightValue / ((65536-655)/100);
        }
    }
    GL_CHECK(_shader->setUniform(_uniformLight, lightLevel));

    GL_CHECK(_shader->setUniform(_uniformTrans, _trans));
    GL_CHECK(_shader->setUniform(_uniformOutline, outline));

    GL_CHECK(_shader->setUniform(_uniformTexStart, texStart));
    GL_CHECK(_shader->setUniform(_uniformTexHeight, texHeight));
    if (Game::getInstance()->renderer()->renderPath() == Renderer::RenderPath::OGL21)
    {
        GL_CHECK(_shader->setUniform(_uniformTexSize, glm::vec2((float)_texture->textureWidth(), (float)_texture->textureHeight() ) ));
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

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _coordsVBO));
    GL_CHECK(glVertexAttribPointer(_attribPos, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));


    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _texCoordsVBO));
    GL_CHECK(glVertexAttribPointer(_attribTex, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo));

    GLushort indexes[6] = {(GLushort) (pos * 4), (GLushort) (pos * 4 + 1), (GLushort) (pos * 4 + 2), (GLushort) (pos * 4 + 3), (GLushort) (pos * 4 + 2), (GLushort) (pos * 4 + 1)};


    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(GLushort), indexes, GL_STATIC_DRAW));

    GL_CHECK(glEnableVertexAttribArray(_attribPos));
    GL_CHECK(glEnableVertexAttribArray(_attribTex));

    GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0 ));

    GL_CHECK(glDisableVertexAttribArray(_attribPos));

    GL_CHECK(glDisableVertexAttribArray(_attribTex));
}

bool Animation::opaque(unsigned int x, unsigned int y)
{
    return _texture->opaque(x, y);
}

void Animation::trans(Graphics::TransFlags::Trans trans)
{
    _trans=trans;
}

}
}
