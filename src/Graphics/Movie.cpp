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
#include "../Graphics/Movie.h"

// C++ standard includes

// Falltergeist includes
#include "../Game/Game.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/Shader.h"
#include "../ResourceManager.h"

// Third party includes

namespace Falltergeist
{
namespace Graphics
{

Movie::Movie()
{
    // 640x320
    _texture = new Graphics::Texture(640,320);
}

Movie::~Movie()
{
    if (_texture)
    {
        delete _texture;
    }
}

unsigned int Movie::width() const
{
    return _texture->width();
}

unsigned int Movie::height() const
{
    return _texture->height();
}

void Movie::loadFromSurface(SDL_Surface* surface)
{
    _texture->loadFromSurface(surface);
}

void Movie::render(int x, int y)
{
    std::vector<glm::vec2> vertices;
    std::vector<glm::vec2> UV;

    int width = 640;
    int height = 320;

    glm::vec2 vertex_up_left    = glm::vec2( (float)x, (float)y);
    glm::vec2 vertex_up_right   = glm::vec2( (float)(x+width), (float)y);
    glm::vec2 vertex_down_right = glm::vec2( (float)(x+width), (float)(y+height));
    glm::vec2 vertex_down_left  = glm::vec2( (float)x, (float)(y+height));

    vertices.push_back(vertex_up_left   );
    vertices.push_back(vertex_down_left );
    vertices.push_back(vertex_up_right  );
    vertices.push_back(vertex_down_right);

    glm::vec2 uv_up_left    = glm::vec2( 0.0, 0.0 );
    glm::vec2 uv_up_right   = glm::vec2( (float)_texture->width()/(float)_texture->textureWidth(), 0.0 );
    glm::vec2 uv_down_right = glm::vec2( (float)_texture->width()/(float)_texture->textureWidth(), (float)_texture->height()/(float)_texture->textureHeight() );
    glm::vec2 uv_down_left  = glm::vec2( 0.0, (float)_texture->height()/(float)_texture->textureHeight() );

    UV.push_back(uv_up_left   );
    UV.push_back(uv_down_left );
    UV.push_back(uv_up_right  );
    UV.push_back(uv_down_right);

    // TODO: different shader

    GL_CHECK(ResourceManager::getInstance()->shader("sprite")->use());

    GL_CHECK(_texture->bind(0));

    GL_CHECK(ResourceManager::getInstance()->shader("sprite")->setUniform("tex",0));

    GL_CHECK(ResourceManager::getInstance()->shader("sprite")->setUniform("fade",Game::getInstance()->renderer()->fadeColor()));

    GL_CHECK(ResourceManager::getInstance()->shader("sprite")->setUniform("MVP", Game::getInstance()->renderer()->getMVP()));

    GLint curvao;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &curvao);
    GLint vao = Game::getInstance()->renderer()->getVAO();
    if (curvao != vao)
    {
        GL_CHECK(glBindVertexArray(vao));
    }


    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Game::getInstance()->renderer()->getVVBO()));

    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_DYNAMIC_DRAW));

    GL_CHECK(glVertexAttribPointer(ResourceManager::getInstance()->shader("sprite")->getAttrib("Position"), 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));


    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Game::getInstance()->renderer()->getTVBO()));

    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, UV.size() * sizeof(glm::vec2), &UV[0], GL_DYNAMIC_DRAW));

    GL_CHECK(glVertexAttribPointer(ResourceManager::getInstance()->shader("sprite")->getAttrib("TexCoord"), 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Game::getInstance()->renderer()->getEBO()));

    GL_CHECK(glEnableVertexAttribArray(ResourceManager::getInstance()->shader("sprite")->getAttrib("Position")));

    GL_CHECK(glEnableVertexAttribArray(ResourceManager::getInstance()->shader("sprite")->getAttrib("TexCoord")));

    GL_CHECK(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0 ));

    GL_CHECK(glDisableVertexAttribArray(ResourceManager::getInstance()->shader("sprite")->getAttrib("Position")));

    GL_CHECK(glDisableVertexAttribArray(ResourceManager::getInstance()->shader("sprite")->getAttrib("TexCoord")));

//    GL_CHECK(glBindVertexArray(0));
}

}
}
