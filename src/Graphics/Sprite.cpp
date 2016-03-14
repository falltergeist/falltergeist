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
#include "Sprite.h"

// C++ standard headers

// Falltergeist headers
#include "AnimatedPalette.h"
#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../LocationCamera.h"
#include "../PathFinding/Hexagon.h"
#include "Renderer.h"
#include "../ResourceManager.h"
#include "Shader.h"
#include "../State/Location.h"
#include "../TransFlags.h"

// Third-party includes

namespace Falltergeist
{
namespace Graphics
{

Sprite::Sprite(const std::string& fname)
{
  _texture = ResourceManager::getInstance()->texture(fname);

    auto shader = ResourceManager::getInstance()->shader("sprite");

    _uniformTex = shader->getUniform("tex");
    if (Game::getInstance()->renderer()->renderPath() == Renderer::RenderPath::OGL21)
    {
        _uniformTexSize = shader->getUniform("texSize");
    }
    _uniformEggTex = shader->getUniform("eggTex");
    _uniformFade = shader->getUniform("fade");
    _uniformMVP = shader->getUniform("MVP");
    _uniformCnt = shader->getUniform("cnt");
    _uniformLight = shader->getUniform("global_light");
    _uniformTrans = shader->getUniform("trans");
    _uniformDoEgg = shader->getUniform("doegg");
    _uniformEggPos = shader->getUniform("eggpos");
    _uniformOutline = shader->getUniform("outline");

    _attribPos = shader->getAttrib("Position");
    _attribTex = shader->getAttrib("TexCoord");
}

Sprite::Sprite(Format::Frm::File *frm) : Sprite(frm->filename())
{

}

Size Sprite::size() const {
    return _texture->size();
}

unsigned int Sprite::width() const
{
    return _texture->width();
}

unsigned int Sprite::height() const
{
    return _texture->height();
}

// render, optionally scaled
void Sprite::renderScaled(int x, int y, unsigned int width, unsigned int height, bool transparency, bool light, int outline, unsigned int lightValue)
{
    std::vector<glm::vec2> vertices;
    std::vector<glm::vec2> UV;

    vertices.reserve(4);
    UV.reserve(4);

    glm::vec2 vertex_up_left    = glm::vec2( (float)x-1.0, (float)y-1.0);
    glm::vec2 vertex_up_right   = glm::vec2( (float)(x+width+1.0), (float)y-1.0);
    glm::vec2 vertex_down_right = glm::vec2( (float)(x+width+1.0), (float)(y+height+1.0));
    glm::vec2 vertex_down_left  = glm::vec2( (float)x-1.0, (float)(y+height+1.0));

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

    glm::vec2 eggVec;
    if (transparency)
    {
        auto dude = Game::getInstance()->player();
        if (!dude || !Game::getInstance()->locationState()) {
            transparency = false;
        }
        else {
            auto camera = Game::getInstance()->locationState()->camera();
            Point eggPos = dude->hexagon()->position() - camera->topLeft() + dude->eggOffset();

            SDL_Rect egg_rect = {eggPos.x(), eggPos.y(), 129, 98};
            SDL_Rect tex_rect = {x, y, (int) _texture->width(), (int) _texture->height()};

            if (!SDL_HasIntersection(&egg_rect, &tex_rect)) {
                transparency = false;
            }
            else {
                eggVec = glm::vec2((float) (eggPos.x()-x), (float) (eggPos.y()-y));
            }
        }
    }



    auto shader = ResourceManager::getInstance()->shader("sprite");

    GL_CHECK(shader->use());

    GL_CHECK(_texture->bind(0));
    GL_CHECK(Game::getInstance()->renderer()->egg()->bind(1));

    GL_CHECK(shader->setUniform(_uniformTex,0));
    GL_CHECK(shader->setUniform(_uniformEggTex,1));

    GL_CHECK(shader->setUniform(_uniformEggPos, eggVec));

    GL_CHECK(shader->setUniform(_uniformDoEgg, transparency));

    GL_CHECK(shader->setUniform(_uniformOutline, outline));


    GL_CHECK(shader->setUniform(_uniformFade, Game::getInstance()->renderer()->fadeColor()));

    GL_CHECK(shader->setUniform(_uniformMVP, Game::getInstance()->renderer()->getMVP()));

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

    if (Game::getInstance()->renderer()->renderPath() == Renderer::RenderPath::OGL21)
    {
        GL_CHECK(shader->setUniform(_uniformTexSize, glm::vec2( (float)_texture->textureWidth(), (float)_texture->textureHeight() )));
    }

    GL_CHECK(glBindVertexArray(Game::getInstance()->renderer()->getVAO()));


    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Game::getInstance()->renderer()->getVVBO()));

    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_DYNAMIC_DRAW));

    GL_CHECK(glVertexAttribPointer(_attribPos, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));


    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Game::getInstance()->renderer()->getTVBO()));

    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, UV.size() * sizeof(glm::vec2), &UV[0], GL_DYNAMIC_DRAW));

    GL_CHECK(glVertexAttribPointer(_attribTex, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Game::getInstance()->renderer()->getEBO()));

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
    GL_CHECK(Game::getInstance()->renderer()->egg()->unbind(1));

}

void Sprite::render(int x, int y, bool transparency, bool light, int outline, unsigned int lightValue)
{
    renderScaled(x, y, _texture->width(), _texture->height(), transparency, light, outline, lightValue);
}

// render just a part of texture, unscaled
void Sprite::renderCropped(int x, int y, int dx, int dy, unsigned int width, unsigned int height, bool transparency,
                           bool light, unsigned int lightValue)
{
    std::vector<glm::vec2> vertices;
    std::vector<glm::vec2> UV;

    glm::vec2 vertex_up_left    = glm::vec2( (float)x, (float)y);
    glm::vec2 vertex_up_right   = glm::vec2( (float)(x+width), (float)y);
    glm::vec2 vertex_down_right = glm::vec2( (float)(x+width), (float)(y+height));
    glm::vec2 vertex_down_left  = glm::vec2( (float)x, (float)(y+height));

    vertices.push_back(vertex_up_left   );
    vertices.push_back(vertex_down_left );
    vertices.push_back(vertex_up_right  );
    vertices.push_back(vertex_down_right);

    glm::vec2 uv_up_left    = glm::vec2( (float)dx/(float)_texture->textureWidth(), (float)dy/(float)_texture->textureHeight() );
    glm::vec2 uv_up_right   = glm::vec2( (float)(dx+width)/(float)_texture->textureWidth(), (float)dy/(float)_texture->textureHeight() );
    glm::vec2 uv_down_right = glm::vec2( (float)(dx+width)/(float)_texture->textureWidth(), (float)(dy+height)/(float)_texture->textureHeight() );
    glm::vec2 uv_down_left  = glm::vec2( (float)dx/(float)_texture->textureWidth(), (float)(dy+height)/(float)_texture->textureHeight() );

    UV.push_back(uv_up_left   );
    UV.push_back(uv_down_left );
    UV.push_back(uv_up_right  );
    UV.push_back(uv_down_right);

    glm::vec2 eggVec;
    if (transparency)
    {
        auto dude = Game::getInstance()->player();
        if (!dude || !Game::getInstance()->locationState()) {
            transparency = false;
        }
        else {
            auto camera = Game::getInstance()->locationState()->camera();
            Point eggPos = dude->hexagon()->position() - camera->topLeft() + dude->eggOffset();

            SDL_Rect egg_rect = {eggPos.x(), eggPos.y(), 129, 98};
            SDL_Rect tex_rect = {x, y, (int) _texture->width(), (int) _texture->height()};

            if (!SDL_HasIntersection(&egg_rect, &tex_rect))
            {
                transparency = false;
            }
            else
            {
                eggVec = glm::vec2((float) (eggPos.x() - x), (float) (eggPos.y() - y));
            }
        }

    }

    auto shader = ResourceManager::getInstance()->shader("sprite");

    GL_CHECK(shader->use());

    GL_CHECK(_texture->bind(0));
    GL_CHECK(Game::getInstance()->renderer()->egg()->bind(1));

    GL_CHECK(shader->setUniform(_uniformTex, 0));
    GL_CHECK(shader->setUniform(_uniformEggTex, 1));

    GL_CHECK(shader->setUniform(_uniformFade, Game::getInstance()->renderer()->fadeColor()));

    GL_CHECK(shader->setUniform(_uniformMVP, Game::getInstance()->renderer()->getMVP()));

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

    GL_CHECK(shader->setUniform(_uniformEggPos, eggVec));

    GL_CHECK(shader->setUniform(_uniformDoEgg, transparency));

    GL_CHECK(shader->setUniform(_uniformOutline, false));

    if (Game::getInstance()->renderer()->renderPath() == Renderer::RenderPath::OGL21)
    {
        GL_CHECK(shader->setUniform(_uniformTexSize, glm::vec2( (float)_texture->textureWidth(), (float)_texture->textureHeight() )));
    }


    GL_CHECK(glBindVertexArray(Game::getInstance()->renderer()->getVAO()));


    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Game::getInstance()->renderer()->getVVBO()));

    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_DYNAMIC_DRAW));

    GL_CHECK(glVertexAttribPointer(_attribPos, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));


    GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, Game::getInstance()->renderer()->getTVBO()));

    GL_CHECK(glBufferData(GL_ARRAY_BUFFER, UV.size() * sizeof(glm::vec2), &UV[0], GL_DYNAMIC_DRAW));

    GL_CHECK(glVertexAttribPointer(_attribTex, 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));

    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Game::getInstance()->renderer()->getEBO()));

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
    GL_CHECK(Game::getInstance()->renderer()->egg()->unbind(1));
}

bool Sprite::opaque(unsigned int x, unsigned int y)
{
    return _texture->opaque(x+1, y+1);
}

void Sprite::trans(Falltergeist::TransFlags::Trans trans)
{
    _trans=trans;
}
}
}