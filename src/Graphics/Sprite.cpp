#include "../Game/DudeObject.h"
#include "../Game/Game.h"
#include "../Graphics/AnimatedPalette.h"
#include "../Graphics/GLCheck.h"
#include "../Graphics/Sprite.h"
#include "../LocationCamera.h"
#include "../PathFinding/Hexagon.h"
#include "../ResourceManager.h"
#include "../State/Location.h"

namespace Falltergeist
{
    namespace Graphics
    {
        using Game::Game;

        Sprite::Sprite(const std::string& fname)
        {
            _texture = ResourceManager::getInstance()->texture(fname);
            _shader = ResourceManager::getInstance()->shader("sprite");

            _uniformTex = _shader->getUniform("tex");
            if (Game::getInstance()->renderer()->renderPath() == Renderer::RenderPath::OGL21)
            {
                _uniformTexSize = _shader->getUniform("texSize");
            }
            _uniformEggTex = _shader->getUniform("eggTex");
            _uniformFade = _shader->getUniform("fade");
            _uniformMVP = _shader->getUniform("MVP");
            _uniformCnt = _shader->getUniform("cnt");
            _uniformLight = _shader->getUniform("global_light");
            _uniformTrans = _shader->getUniform("trans");
            _uniformDoEgg = _shader->getUniform("doegg");
            _uniformEggPos = _shader->getUniform("eggpos");
            _uniformOutline = _shader->getUniform("outline");

            _attribPos = _shader->getAttrib("Position");
            _attribTex = _shader->getAttrib("TexCoord");
        }

        Sprite::Sprite(Format::Frm::File *frm) : Sprite(frm->filename())
        {
        }

        const Size& Sprite::size() const
        {
            return _texture->size();
        }

        // render, optionally scaled
        void Sprite::renderScaled(const Point& point, const Size& size, bool transparency, bool light, int outline, unsigned int lightValue)
        {
            glm::vec2 vertices[4] = {
                glm::vec2((float) point.x(), (float) point.y()),
                glm::vec2((float) point.x(), (float)(point.y() + size.height())),
                glm::vec2((float)(point.x() + size.width()), (float) point.y()),
                glm::vec2((float)(point.x() + size.width()), (float)(point.y() + size.height()))
            };
            glm::vec2 UV[4] = {
                glm::vec2(0.0, 0.0),
                glm::vec2(0.0, 1.0),
                glm::vec2(1.0, 0.0),
                glm::vec2(1.0, 1.0)
            };

            glm::vec2 eggVec;
            if (transparency)
            {
                auto dude = Game::getInstance()->player();
                if (!dude || !Game::getInstance()->locationState()) {
                    transparency = false;
                }
                else {
                    auto camera = Game::getInstance()->locationState()->camera();
                    Rectangle eggRectangle(
                        dude->hexagon()->position() - camera->topLeft() + dude->eggOffset(),
                        Size(129, 98)
                    );

                    Rectangle textureRectangle(point, _texture->size());

                    if (!eggRectangle.hasIntersectionWith(textureRectangle)) {
                        transparency = false;
                    }
                    else {
                        eggVec = glm::vec2((float) (eggRectangle.position().x() - point.x()), (float) (eggRectangle.position().y() - point.y()));
                    }
                }
            }

            _shader->use();

            _texture->bind(0);
            Game::getInstance()->renderer()->egg()->bind(1);

            _shader->setUniform(_uniformTex, 0);
            _shader->setUniform(_uniformEggTex, 1);

            _shader->setUniform(_uniformEggPos, eggVec);

            _shader->setUniform(_uniformDoEgg, transparency);

            _shader->setUniform(_uniformOutline, outline);


            _shader->setUniform(_uniformFade, Game::getInstance()->renderer()->fadeColor());

            _shader->setUniform(_uniformMVP, Game::getInstance()->renderer()->getMVP());

            _shader->setUniform(_uniformCnt, Game::getInstance()->animatedPalette()->counters());

            int lightLevel = 100;
            if (light)
            {
                if (auto state = Game::getInstance()->locationState())
                {
                    if (lightValue<=state->lightLevel()) lightValue=state->lightLevel();
                    lightLevel = lightValue / ((65536-655)/100);
                }
            }
            _shader->setUniform(_uniformLight, lightLevel);
            _shader->setUniform(_uniformTrans, _trans);

            if (Game::getInstance()->renderer()->renderPath() == Renderer::RenderPath::OGL21)
            {
                _shader->setUniform(_uniformTexSize, glm::vec2((float)_texture->size().width(), (float)_texture->size().height()));
            }

            VertexArray vertexArray;

            std::unique_ptr<VertexBuffer> coordinatesVertexBuffer = std::make_unique<VertexBuffer>(
                    &vertices[0],
                    sizeof(vertices),
                    VertexBuffer::UsagePattern::DynamicDraw
            );
            VertexBufferLayout coordinatesVertexBufferLayout;
            coordinatesVertexBufferLayout.addAttribute({
                    (unsigned int) _attribPos,
                    2,
                    VertexBufferAttribute::Type::Float,
                    false,
                    0
            });
            vertexArray.addBuffer(coordinatesVertexBuffer, coordinatesVertexBufferLayout);

            std::unique_ptr<VertexBuffer> textureCoordinatesVertexBuffer = std::make_unique<VertexBuffer>(
                    &UV[0],
                    sizeof(UV),
                    VertexBuffer::UsagePattern::DynamicDraw
            );
            VertexBufferLayout textureCoordinatesVertexBufferLayout;
            textureCoordinatesVertexBufferLayout.addAttribute({
                    (unsigned int) _attribTex,
                    2,
                    VertexBufferAttribute::Type::Float,
                    false,
                    0
            });
            vertexArray.addBuffer(textureCoordinatesVertexBuffer, textureCoordinatesVertexBufferLayout);

            static unsigned int indexes[6] = { 0, 1, 2, 3, 2, 1 };
            IndexBuffer indexBuffer(indexes, 6, IndexBuffer::UsagePattern::StaticDraw);

            GL_CHECK(glDrawElements(GL_TRIANGLES, indexBuffer.count(), GL_UNSIGNED_INT, nullptr));
        }

        void Sprite::render(const Point& point, bool transparency, bool light, int outline, unsigned int lightValue)
        {
            renderScaled(point, _texture->size(), transparency, light, outline, lightValue);
        }

        // render just a part of texture, unscaled
        void Sprite::renderCropped(const Point& point, const Rectangle& part, bool transparency,
                                   bool light, unsigned int lightValue)
        {
            glm::vec2 vertices[4] = {
                glm::vec2((float) point.x(), (float) point.y()),
                glm::vec2((float)point.x(), (float)(point.y() + part.size().height())),
                glm::vec2((float)(point.x() + part.size().width()), (float)point.y()),
                glm::vec2((float)(point.x() + part.size().width()), (float)(point.y() + part.size().height()))
            };
            glm::vec2 UV[4] = {
                glm::vec2((float)part.position().x() / (float)_texture->size().width(), (float)part.position().y() / (float)_texture->size().height()),
                glm::vec2((float)part.position().x() / (float)_texture->size().width(), (float)(part.position().y() + part.size().height()) / (float)_texture->size().height()),
                glm::vec2((float)(part.position().x() + part.size().width()) / (float)_texture->size().width(), (float)part.position().y() / (float)_texture->size().height()),
                glm::vec2((float)(part.position().x() + part.size().width()) / (float)_texture->size().width(), (float)(part.position().y() + part.size().height()) / (float)_texture->size().height())
            };

            glm::vec2 eggVec;
            if (transparency)
            {
                auto dude = Game::getInstance()->player();
                if (!dude || !Game::getInstance()->locationState()) {
                    transparency = false;
                } else {
                    auto camera = Game::getInstance()->locationState()->camera();
                    Rectangle eggRectangle(
                        dude->hexagon()->position() - camera->topLeft() + dude->eggOffset(),
                        Size(129, 98)
                    );

                    Rectangle textureRectangle(point, _texture->size());

                    if (!eggRectangle.hasIntersectionWith(textureRectangle)) {
                        transparency = false;
                    } else {
                        eggVec = glm::vec2((float) (eggRectangle.position().x() - point.x()), (float) (eggRectangle.position().y() - point.y()));
                    }
                }

            }

            _shader->use();

            _texture->bind(0);
            Game::getInstance()->renderer()->egg()->bind(1);

            _shader->setUniform(_uniformTex, 0);
            _shader->setUniform(_uniformEggTex, 1);

            _shader->setUniform(_uniformFade, Game::getInstance()->renderer()->fadeColor());

            _shader->setUniform(_uniformMVP, Game::getInstance()->renderer()->getMVP());

            _shader->setUniform(_uniformCnt, Game::getInstance()->animatedPalette()->counters());

            int lightLevel = 100;
            if (light)
            {
                if (auto state = Game::getInstance()->locationState())
                {
                    if (lightValue<=state->lightLevel()) lightValue=state->lightLevel();
                    lightLevel = lightValue / ((65536-655)/100);
                }
            }
            _shader->setUniform(_uniformLight, lightLevel);

            _shader->setUniform(_uniformTrans, _trans);

            _shader->setUniform(_uniformEggPos, eggVec);

            _shader->setUniform(_uniformDoEgg, transparency);

            _shader->setUniform(_uniformOutline, false);

            if (Game::getInstance()->renderer()->renderPath() == Renderer::RenderPath::OGL21) {
                _shader->setUniform(_uniformTexSize, glm::vec2((float)_texture->size().width(), (float)_texture->size().height()));
            }

            VertexArray vertexArray;

            std::unique_ptr<VertexBuffer> coordinatesVertexBuffer = std::make_unique<VertexBuffer>(
                    &vertices[0],
                    sizeof(vertices),
                    VertexBuffer::UsagePattern::DynamicDraw
            );
            VertexBufferLayout coordinatesVertexBufferLayout;
            coordinatesVertexBufferLayout.addAttribute({
                   (unsigned int) _attribPos,
                   2,
                   VertexBufferAttribute::Type::Float,
                   false,
                   0
            });
            vertexArray.addBuffer(coordinatesVertexBuffer, coordinatesVertexBufferLayout);

            std::unique_ptr<VertexBuffer> textureCoordinatesVertexBuffer = std::make_unique<VertexBuffer>(
                    &UV[0],
                    sizeof(UV),
                    VertexBuffer::UsagePattern::DynamicDraw
            );
            VertexBufferLayout textureCoordinatesVertexBufferLayout;
            textureCoordinatesVertexBufferLayout.addAttribute({
                  (unsigned int) _attribTex,
                  2,
                  VertexBufferAttribute::Type::Float,
                  false,
                  0
            });
            vertexArray.addBuffer(textureCoordinatesVertexBuffer, textureCoordinatesVertexBufferLayout);

            static unsigned int indexes[6] = { 0, 1, 2, 3, 2, 1 };
            IndexBuffer indexBuffer(indexes, 6, IndexBuffer::UsagePattern::StaticDraw);

            GL_CHECK(glDrawElements(GL_TRIANGLES, indexBuffer.count(), GL_UNSIGNED_INT, nullptr));
        }

        bool Sprite::opaque(const Point& point)
        {
            return _texture->opaque(point.x() + 1, point.y() + 1);
        }

        void Sprite::trans(Graphics::TransFlags::Trans trans)
        {
            _trans=trans;
        }
    }
}
