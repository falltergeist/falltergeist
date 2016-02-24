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


#include <iosfwd>
#include <ResourceManager.h>
#include <Point.h>
#include <Game/Game.h>
#include <SDL_image.h>
#include <TransFlags.h>
#include "Animation.h"
#include "../Format/Frm/File.h"
#include "../Format/Frm/Direction.h"
#include "../Format/Frm/Frame.h"
#include "Renderer.h"
#include "Shader.h"
#include "AnimatedPalette.h"
#include "../State/Location.h"


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
    GL_CHECK(glGenBuffers(1, &_coords));
    GL_CHECK(glGenBuffers(1, &_texCoords));
    GL_CHECK(glGenBuffers(1, &_ebo));

    _texture = ResourceManager::getInstance()->texture(filename);

    Format::Frm::File* frm = ResourceManager::getInstance()->frmFileType(filename);

    _stride = frm->framesPerDirection();

    std::vector<glm::vec2> vertices;
    std::vector<glm::vec2> texCoords;

    int offsetX=0;
    int offsetY=0;

    for (auto direction : *frm->directions())
    {
        offsetX = 0;
        for (unsigned int f = 0; f != frm->framesPerDirection(); ++f)
        {
            auto srcFrame = direction->frames()->at(f);

            vertices.push_back(glm::vec2(0.0,0.0));
            vertices.push_back(glm::vec2(0.0,(float)srcFrame->height()));
            vertices.push_back(glm::vec2((float)srcFrame->width(),0.0));
            vertices.push_back(glm::vec2((float)srcFrame->width(),(float)srcFrame->height()));

            texCoords.push_back(glm::vec2( (float)offsetX/(float)_texture->textureWidth(), (float)offsetY/(float)_texture->textureHeight() ));
            texCoords.push_back(glm::vec2( (float)offsetX/(float)_texture->textureWidth(), (float)(offsetY+srcFrame->height())/(float)_texture->textureHeight() ));
            texCoords.push_back(glm::vec2( (float)(offsetX+srcFrame->width())/(float)_texture->textureWidth(), (float)offsetY/(float)_texture->textureHeight() ));
            texCoords.push_back(glm::vec2( (float)(offsetX+srcFrame->width())/(float)_texture->textureWidth(), (float)(offsetY+srcFrame->height())/(float)_texture->textureHeight() ));

            offsetX+=srcFrame->width();

        }
        offsetY+=direction->height();

    }

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _coords));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW));

    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _texCoords));
    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(glm::vec2), &texCoords[0], GL_STATIC_DRAW));

    GL_CHECK(glBindVertexArray(0));
}

Animation::~Animation()
{

}

void Animation::render(int x, int y, unsigned int direction, unsigned int frame, bool transparency, bool light)
{
    int pos = direction*_stride+frame;

    GL_CHECK(ResourceManager::getInstance()->shader("animation")->use());

    GL_CHECK(_texture->bind(0));

    GL_CHECK(ResourceManager::getInstance()->shader("animation")->setUniform("tex",0));

    GL_CHECK(ResourceManager::getInstance()->shader("animation")->setUniform("offset",glm::vec2((float)x, (float)y)));

    GL_CHECK(ResourceManager::getInstance()->shader("animation")->setUniform("MVP",
                                                                          Game::getInstance()->renderer()->getMVP()));

    GL_CHECK(ResourceManager::getInstance()->shader("animation")->setUniform("fade",Game::getInstance()->renderer()->fadeColor()));

    GL_CHECK(ResourceManager::getInstance()->shader("animation")->setUniform("cnt", Game::getInstance()->animatedPalette()->counters()));

    int lightLevel = 100;
    if (light)
    {
        if (auto state = Game::getInstance()->locationState())
        {
            lightLevel = state->lightLevel();
        }
    }
    GL_CHECK(ResourceManager::getInstance()->shader("animation")->setUniform("global_light", lightLevel));

    GL_CHECK(ResourceManager::getInstance()->shader("animation")->setUniform("trans", _trans));



    GL_CHECK(glBindVertexArray(_vao));


    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _coords));
    GL_CHECK(glVertexAttribPointer(ResourceManager::getInstance()->shader("animation")->getAttrib("Position"), 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));


    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _texCoords));
    GL_CHECK(glVertexAttribPointer(ResourceManager::getInstance()->shader("animation")->getAttrib("TexCoord"), 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo));

    GLushort indexes[6] = {(GLushort) (pos * 4), (GLushort) (pos * 4 + 1), (GLushort) (pos * 4 + 2), (GLushort) (pos * 4 + 3), (GLushort) (pos * 4 + 2), (GLushort) (pos * 4 + 1)};


    GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(GLushort), indexes, GL_STATIC_DRAW));

    GL_CHECK(glEnableVertexAttribArray(ResourceManager::getInstance()->shader("animation")->getAttrib("Position")));
    GL_CHECK(glEnableVertexAttribArray(ResourceManager::getInstance()->shader("animation")->getAttrib("TexCoord")));

    GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0 ));

    GL_CHECK(glDisableVertexAttribArray(ResourceManager::getInstance()->shader("animation")->getAttrib("Position")));

    GL_CHECK(glDisableVertexAttribArray(ResourceManager::getInstance()->shader("animation")->getAttrib("TexCoord")));

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CHECK(glBindVertexArray(0));

    GL_CHECK(ResourceManager::getInstance()->shader("animation")->unuse());
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


