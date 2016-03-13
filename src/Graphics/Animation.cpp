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
#include "Animation.h"

// C++ standart includes
#include "../ResourceManager.h"
#include "../Point.h"
#include "../Game/Game.h"
#include "../TransFlags.h"
#include "../Format/Frm/File.h"
#include "../Format/Frm/Direction.h"
#include "../Format/Frm/Frame.h"
#include "Renderer.h"
#include "Shader.h"
#include "AnimatedPalette.h"
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
    GL_CHECK(glGenVertexArrays(1, &_vao));
    GL_CHECK(glBindVertexArray(_vao));

    // generate VBOs for verts and tex
    GL_CHECK(glGenBuffers(1, &_coordsVBO));
    GL_CHECK(glGenBuffers(1, &_texCoordsVBO));
    GL_CHECK(glGenBuffers(1, &_ebo));

    _texture = ResourceManager::getInstance()->texture(filename);

    Format::Frm::File* frm = ResourceManager::getInstance()->frmFileType(filename);

    _stride = frm->framesPerDirection();


    int offsetX=1;
    int offsetY=1;

    for (auto direction : *frm->directions())
    {
        offsetX = 1;
        for (unsigned int f = 0; f != frm->framesPerDirection(); ++f)
        {
            auto srcFrame = direction->frames()->at(f);

            _vertices.push_back(glm::vec2(0.0,0.0));
            _vertices.push_back(glm::vec2(0.0,(float)srcFrame->height()+2.0));
            _vertices.push_back(glm::vec2((float)srcFrame->width()+2.0,0.0));
            _vertices.push_back(glm::vec2((float)srcFrame->width()+2.0,(float)srcFrame->height()+2.0));

            _texCoords.push_back(glm::vec2( (float)(offsetX-1.0)/(float)_texture->textureWidth(), (float)(offsetY-1.0)/(float)_texture->textureHeight() ));
            _texCoords.push_back(glm::vec2( (float)(offsetX-1.0)/(float)_texture->textureWidth(), (float)(offsetY+srcFrame->height()+1.0)/(float)_texture->textureHeight() ));
            _texCoords.push_back(glm::vec2( (float)(offsetX+srcFrame->width()+1.0)/(float)_texture->textureWidth(), (float)(offsetY-1.0)/(float)_texture->textureHeight() ));
            _texCoords.push_back(glm::vec2( (float)(offsetX+srcFrame->width()+1.0)/(float)_texture->textureWidth(), (float)(offsetY+srcFrame->height()+1.0)/(float)_texture->textureHeight() ));

            offsetX+=srcFrame->width()+2;

        }
        offsetY+=direction->height();

    }

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _coordsVBO));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(glm::vec2), &_vertices[0], GL_STATIC_DRAW));

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _texCoordsVBO));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, _texCoords.size() * sizeof(glm::vec2), &_texCoords[0], GL_STATIC_DRAW));

    GL_CHECK(glBindVertexArray(0));

    auto shader = ResourceManager::getInstance()->shader("animation");

    _uniformTex = shader->getUniform("tex");
    _uniformFade = shader->getUniform("fade");
    _uniformMVP = shader->getUniform("MVP");
    _uniformCnt = shader->getUniform("cnt");
    _uniformLight = shader->getUniform("global_light");
    _uniformTrans = shader->getUniform("trans");
    _uniformOffset = shader->getUniform("offset");
    _uniformOutline = shader->getUniform("outline");

    _uniformTexStart = shader->getUniform("texStart");
    _uniformTexHeight = shader->getUniform("texHeight");

    _attribPos = shader->getAttrib("Position");
    _attribTex = shader->getAttrib("TexCoord");
}

Animation::~Animation()
{

}

void Animation::render(int x, int y, unsigned int direction, unsigned int frame, bool transparency, bool light, int outline, unsigned int lightValue)
{
    int pos = direction*_stride+frame;

    float texStart = _texCoords.at(pos*4).y;
    float texEnd = _texCoords.at(pos*4+3).y;
    float texHeight = texEnd-texStart;



    auto shader = ResourceManager::getInstance()->shader("animation");

    GL_CHECK(shader->use());

    GL_CHECK(_texture->bind(0));

    GL_CHECK(shader->setUniform(_uniformTex, 0));

    GL_CHECK(shader->setUniform(_uniformOffset, glm::vec2((float)x, (float)y)));

    GL_CHECK(shader->setUniform(_uniformMVP, Game::getInstance()->renderer()->getMVP()));

    GL_CHECK(shader->setUniform(_uniformFade, Game::getInstance()->renderer()->fadeColor()));

    GL_CHECK(shader->setUniform(_uniformCnt, Game::getInstance()->animatedPalette()->counters()));

    int lightLevel = 100;
    if (light)
    {
        if (auto state = Game::getInstance()->locationState())
        {
            if (lightValue<=state->lightLevel()) lightValue=state->lightLevel();
            lightLevel = lightValue / ((65536-655)/100);
        }
    }
    GL_CHECK(shader->setUniform(_uniformLight, lightLevel));

    GL_CHECK(shader->setUniform(_uniformTrans, _trans));
    GL_CHECK(shader->setUniform(_uniformOutline, outline));

    GL_CHECK(shader->setUniform(_uniformTexStart, texStart));
    GL_CHECK(shader->setUniform(_uniformTexHeight, texHeight));



    GL_CHECK(glBindVertexArray(_vao));


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

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CHECK(glBindVertexArray(0));

    GL_CHECK(shader->unuse());
    GL_CHECK(_texture->unbind(0));
}

bool Animation::opaque(unsigned int x, unsigned int y)
{
    return _texture->opaque(x, y);
}

void Animation::trans(Falltergeist::TransFlags::Trans trans)
{
    _trans=trans;
}

}
}


