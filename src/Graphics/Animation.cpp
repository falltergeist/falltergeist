#include <SDL_image.h>
#include "../Format/Frm/File.h"
#include "../Game/Game.h"
#include "../Graphics/AnimatedPalette.h"
#include "../Graphics/Animation.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/GLCheck.h"
#include "../ResourceManager.h"
#include "../State/Location.h"

namespace Falltergeist
{
    namespace Graphics
    {
        using Game::Game;

        Animation::Animation(const std::string &filename)
        {
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

            _vertexArray = std::make_unique<VertexArray>();

            _coordinatesVertexBuffer = std::make_unique<VertexBuffer>(
                    &_vertices[0],
                    _vertices.size() * sizeof(glm::vec2),
                    VertexBuffer::UsagePattern::StaticDraw
            );
            VertexBufferLayout coordinatesVertexBufferLayout;
            coordinatesVertexBufferLayout.addAttribute({
                   (unsigned int) _attribPos,
                   2,
                   VertexBufferAttribute::Type::Float,
                   false,
                   0
            });
            _vertexArray->addBuffer(_coordinatesVertexBuffer, coordinatesVertexBufferLayout);

            _textureCoordinatesVertexBuffer = std::make_unique<VertexBuffer>(
                    &_texCoords[0],
                    _texCoords.size() * sizeof(glm::vec2),
                    VertexBuffer::UsagePattern::StaticDraw
            );
            VertexBufferLayout textureCoordinatesVertexBufferLayout;
            textureCoordinatesVertexBufferLayout.addAttribute({
                  (unsigned int) _attribTex,
                  2,
                  VertexBufferAttribute::Type::Float,
                  false,
                  0
            });
            _vertexArray->addBuffer(_textureCoordinatesVertexBuffer, textureCoordinatesVertexBufferLayout);
        }

        Animation::~Animation()
        {
        }

        void Animation::render(int x, int y, unsigned int direction, unsigned int frame, bool transparency, bool light, int outline, unsigned int lightValue)
        {
            unsigned pos = direction * _stride + frame;

            float texStart = _texCoords.at(pos*4).y;
            float texEnd = _texCoords.at(pos*4+3).y;
            float texHeight = texEnd-texStart;

            _shader->use();

            _texture->bind(0);

            _shader->setUniform(_uniformTex, 0);

            _shader->setUniform(_uniformOffset, glm::vec2((float)x, (float)y));

            _shader->setUniform(_uniformMVP, Game::getInstance()->renderer()->getMVP());

            _shader->setUniform(_uniformFade, Game::getInstance()->renderer()->fadeColor());

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
            _shader->setUniform(_uniformOutline, outline);

            _shader->setUniform(_uniformTexStart, texStart);
            _shader->setUniform(_uniformTexHeight, texHeight);
            if (Game::getInstance()->renderer()->renderPath() == Renderer::RenderPath::OGL21)
            {
                _shader->setUniform(_uniformTexSize, glm::vec2((float)_texture->textureWidth(), (float)_texture->textureHeight()));
            }

            _vertexArray->bind();

            unsigned int indexes[6] = {
                (pos * 4), (pos * 4 + 1),
                (pos * 4 + 2), (pos * 4 + 3),
                (pos * 4 + 2), (pos * 4 + 1)
            };
            IndexBuffer indexBuffer(indexes, 6, IndexBuffer::UsagePattern::StaticDraw);
            indexBuffer.bind();

            GL_CHECK(glDrawElements(GL_TRIANGLES, indexBuffer.count(), GL_UNSIGNED_INT, nullptr));
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
