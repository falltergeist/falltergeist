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
#include "Sprite.h"
#include "Renderer.h"

namespace Falltergeist
{
namespace Graphics
{

Sprite::Sprite(std::string fname)
{
  _texture = ResourceManager::getInstance()->texture(fname);
}

void Sprite::render(int x, int y, unsigned int width, unsigned int height)
{
    std::vector<glm::vec2> vertices;

    // TODO: scaling
    glm::vec2 vertex_up_left    = glm::vec2( (float)x, (float)y);
    glm::vec2 vertex_up_right   = glm::vec2( (float)(x+_texture->textureWidth()), (float)y);
    glm::vec2 vertex_down_right = glm::vec2( (float)(x+_texture->textureWidth()), (float)(y+_texture->textureHeight()));
    glm::vec2 vertex_down_left  = glm::vec2( (float)x, (float)(y+_texture->textureHeight()));

    vertices.push_back(vertex_up_left   );
    vertices.push_back(vertex_down_left );
    vertices.push_back(vertex_up_right  );

    vertices.push_back(vertex_down_right);
    vertices.push_back(vertex_up_right);
    vertices.push_back(vertex_down_left);


    GL_CHECK(ResourceManager::getInstance()->shader("sprite")->use());

    GL_CHECK(_texture->bind(0));

    GL_CHECK(ResourceManager::getInstance()->shader("sprite")->setUniform("tex",0));

    GL_CHECK(ResourceManager::getInstance()->shader("sprite")->setUniform("MVP",
                                                                           Game::getInstance()->renderer()->getMVP()));


    GL_CHECK(glBindVertexArray(Game::getInstance()->renderer()->getVAO()));


    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Game::getInstance()->renderer()->getVVBO()));

    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_DYNAMIC_DRAW));

    GL_CHECK(glVertexAttribPointer(ResourceManager::getInstance()->shader("sprite")->getAttrib("Position"), 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));


    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Game::getInstance()->renderer()->getTVBO()));

    GL_CHECK(glVertexAttribPointer(ResourceManager::getInstance()->shader("sprite")->getAttrib("TexCoord"), 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Game::getInstance()->renderer()->getEBO()));

    GL_CHECK(glEnableVertexAttribArray(ResourceManager::getInstance()->shader("sprite")->getAttrib("Position")));

    GL_CHECK(glEnableVertexAttribArray(ResourceManager::getInstance()->shader("sprite")->getAttrib("TexCoord")));

    GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0 ));

    GL_CHECK(glDisableVertexAttribArray(ResourceManager::getInstance()->shader("sprite")->getAttrib("Position")));

    GL_CHECK(glDisableVertexAttribArray(ResourceManager::getInstance()->shader("sprite")->getAttrib("TexCoord")));

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GL_CHECK(glBindVertexArray(0));

    GL_CHECK(ResourceManager::getInstance()->shader("sprite")->unuse());
    GL_CHECK(_texture->unbind(0));
}

void Sprite::render(int x, int y)
{
    render(x, y, _texture->width(), _texture->height());
}
}
}