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

#include "Font.h"
#include "Renderer.h"
#include "../ResourceManager.h"
#include "../Game/Game.h"
#include "Shader.h"

namespace Falltergeist {
namespace Graphics {

Font::Font()
{
    GL_CHECK(glGenVertexArrays(1, &_vao));
    GL_CHECK(glBindVertexArray(_vao));

    // generate VBOs for verts and tex
    GL_CHECK(glGenBuffers(1, &_coords));
    GL_CHECK(glGenBuffers(1, &_texCoords));
    GL_CHECK(glGenBuffers(1, &_ebo));
    GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo));
    GL_CHECK(glBindVertexArray(0));

}

Font::~Font()
{

}

void Font::render(std::vector<TextSymbol> _symbols, Point& pos, SDL_Color color, SDL_Color outline)
{
        std::vector<glm::vec2> vertices;
        std::vector<glm::vec2> UV;
        std::vector<GLushort> indexes;

        int cnt = 0;
        auto tex = _texture.get();
        for ( auto symbol: _symbols )
        {
            float textureX = (symbol.chr%16) * width();
            float textureY = (symbol.chr/16) * height();

            Point drawPos = symbol.position + pos;

            glm::vec2 vertex_up_left    = glm::vec2( (float)drawPos.x(), (float)drawPos.y() );
            glm::vec2 vertex_up_right   = glm::vec2( (float)drawPos.x()+(float)width(), (float)drawPos.y() );
            glm::vec2 vertex_down_left  = glm::vec2( (float)drawPos.x(), (float)drawPos.y()+(float)width() );
            glm::vec2 vertex_down_right = glm::vec2( (float)drawPos.x()+(float)width(), (float)drawPos.y()+(float)width() );

            vertices.push_back(vertex_up_left   );
            vertices.push_back(vertex_up_right  );
            vertices.push_back(vertex_down_left );
            vertices.push_back(vertex_down_right);

            glm::vec2 tex_up_left    = glm::vec2( textureX/(float)tex->width(), textureY/(float)tex->height() );
            glm::vec2 tex_up_right   = glm::vec2( (textureX+(float)width())/(float)tex->width(), textureY/(float)tex->height() );
            glm::vec2 tex_down_left  = glm::vec2( textureX/(float)tex->width(), (textureY+(float)height())/(float)tex->height() );
            glm::vec2 tex_down_right = glm::vec2( (textureX+(float)width())/(float)tex->width(), (textureY+(float)height())/(float)tex->height() );

            UV.push_back(tex_up_left   );
            UV.push_back(tex_up_right  );
            UV.push_back(tex_down_left );
            UV.push_back(tex_down_right);

            indexes.push_back(cnt*4);
            indexes.push_back(cnt*4+1);
            indexes.push_back(cnt*4+2);
            indexes.push_back(cnt*4+3);
            indexes.push_back(cnt*4+2);
            indexes.push_back(cnt*4+1);
            cnt++;
        }

        GL_CHECK(ResourceManager::getInstance()->shader("font")->use());

        GL_CHECK(_texture.get()->bind(0));

        GL_CHECK(ResourceManager::getInstance()->shader("font")->setUniform("tex",0));

        GL_CHECK(ResourceManager::getInstance()->shader("font")->setUniform("MVP", Game::getInstance()->renderer()->getMVP()));


        GL_CHECK(glBindVertexArray(_vao));


        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _coords));
        GL_CHECK(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_DYNAMIC_DRAW));
        GL_CHECK(glVertexAttribPointer(ResourceManager::getInstance()->shader("font")->getAttrib("Position"), 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));


        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, _texCoords));
        GL_CHECK(glBufferData(GL_ARRAY_BUFFER, UV.size() * sizeof(glm::vec2), &UV[0], GL_DYNAMIC_DRAW));
        GL_CHECK(glVertexAttribPointer(ResourceManager::getInstance()->shader("font")->getAttrib("TexCoord"), 2, GL_FLOAT, GL_FALSE, 0, (void*)0 ));

        GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo));
        GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(GLushort), &indexes[0], GL_DYNAMIC_DRAW));

        GL_CHECK(glEnableVertexAttribArray(ResourceManager::getInstance()->shader("font") ->getAttrib("Position")));
        GL_CHECK(glEnableVertexAttribArray(ResourceManager::getInstance()->shader("font")->getAttrib("TexCoord")));

        GL_CHECK(glDrawElements(GL_TRIANGLES, indexes.size(), GL_UNSIGNED_SHORT, 0 ));

        GL_CHECK(glDisableVertexAttribArray(ResourceManager::getInstance()->shader("font")->getAttrib("Position")));
        GL_CHECK(glDisableVertexAttribArray(ResourceManager::getInstance()->shader("font")->getAttrib("TexCoord")));

        GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
        GL_CHECK(glBindVertexArray(0));

        GL_CHECK(ResourceManager::getInstance()->shader("font")->unuse());

}


}
}