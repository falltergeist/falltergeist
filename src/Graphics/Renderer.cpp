#include <cmath>
#include <memory>

#define GLM_FORCE_RADIANS

#include "../Base/Buffer.h"
#include "../CrossPlatform.h"
#include "../Event/State.h"
#include "../Exception.h"
#include "../Game/Game.h"
#include "../Graphics/GLCheck.h"
#include "../Graphics/IRendererConfig.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/Point.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/SdlWindow.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Texture.h"
#include "../Graphics/VertexArray.h"
#include "../Graphics/VertexBuffer.h"
#include "../Input/Mouse.h"
#include "../ResourceManager.h"
#include "../Settings.h"
#include "../State/State.h"
#include <SDL_image.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Falltergeist {
    namespace Graphics {
        using Game::Game;

        Renderer::Renderer(std::unique_ptr<IRendererConfig> rendererConfig, std::shared_ptr<ILogger> logger, std::shared_ptr<SdlWindow> sdlWindow)
            : _rendererConfig(std::move(rendererConfig)), _logger(logger), _size(sdlWindow->boundaries().size()), _sdlWindow(sdlWindow) {
            if (SDL_WasInit(SDL_INIT_VIDEO) == 0) {
                if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
                    logger->critical() << "Could not init SDL video subsystem: " << SDL_GetError() << std::endl;
                }
            }
        }

        Renderer::~Renderer() {
            SDL_GL_DeleteContext(_glcontext);
        }

        void Renderer::init() {
            std::string message = "Init OpenGL - ";
            // specifically request 3.2, because fucking Mesa ignores core flag with version < 3
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

            _glcontext = SDL_GL_CreateContext(_sdlWindow->sdlWindowPtr());

            if (!_glcontext) {
                // ok, try and create 2.1 context then
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 0);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
                _glcontext = SDL_GL_CreateContext(_sdlWindow->sdlWindowPtr());

                if (!_glcontext) {
                    throw Exception(message + SDL_GetError() + "[FAIL]");
                }
            }

            _logger->info() << "[RENDERER] " << message + "[OK]" << std::endl;
            SDL_GL_SetSwapInterval(0);

            char* version_string = (char*)glGetString(GL_VERSION);
            if (version_string[0] - '0' >= 3) { // we have at least gl 3.0
                glGetIntegerv(GL_MAJOR_VERSION, &_major);
                glGetIntegerv(GL_MINOR_VERSION, &_minor);
                if (_major == 3 && _minor < 2) { // anything lower 3.2
                    _renderpath = RenderPath::OGL21;
                } else {
                    _renderpath = RenderPath::OGL32;
                }
            } else {
                _major = version_string[0] - '0';
                _minor = version_string[2] - '0';
                _renderpath = RenderPath::OGL21;
            }

            _logger->info() << "[RENDERER] "
                            << "Using OpenGL " << _major << "." << _minor << std::endl;
            _logger->info() << "[RENDERER] "
                            << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
            _logger->info() << "[RENDERER] "
                            << "Version string: " << glGetString(GL_VERSION) << std::endl;
            _logger->info() << "[RENDERER] "
                            << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
            switch (_renderpath) {
                case RenderPath::OGL21:
                    _logger->info() << "[RENDERER] "
                                    << "Render path: OpenGL 2.1" << std::endl;
                    break;
                case RenderPath::OGL32:
                    _logger->info() << "[RENDERER] "
                                    << "Render path: OpenGL 3.0+" << std::endl;
                    break;
                default:
                    break;
            }

            glGetIntegerv(GL_MAX_TEXTURE_SIZE, &_maxTexSize);

            message = "Init GLEW - ";
            glewExperimental = GL_TRUE;
            GLenum glewError = glewInit();
            glGetError(); // glew sometimes throws bad enum, so clean it

            switch (glewError) {
#ifdef GLEW_ERROR_NO_GLX_DISPLAY
                // Wayland: https://github.com/nigels-com/glew/issues/172
                case GLEW_ERROR_NO_GLX_DISPLAY:
                    break;
#endif
                case GLEW_OK:
                    break;
                default:
                    throw Exception(message + "[FAIL]: " + std::string((char*)glewGetErrorString(glewError)));
            }

            _logger->info() << "[RENDERER] " << message + "[OK]" << std::endl;
            _logger->info() << "[RENDERER] "
                            << "Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

            _logger->info() << "[RENDERER] "
                            << "Extensions: " << std::endl;

            if (_renderpath == RenderPath::OGL32) {
                GLint count = 0;
                glGetIntegerv(GL_NUM_EXTENSIONS, &count);

                for (GLint i = 0; i < count; i++) {
                    _logger->info() << "[RENDERER] " << (const char*)glGetStringi(GL_EXTENSIONS, i) << std::endl;
                }
            } else {
                _logger->info() << "[RENDERER] " << (const char*)glGetString(GL_EXTENSIONS) << std::endl;
            }

            _logger->info() << "[RENDERER] "
                            << "Loading default shaders" << std::endl;
            ResourceManager::getInstance()->shader("default");
            ResourceManager::getInstance()->shader("sprite");
            ResourceManager::getInstance()->shader("font");
            ResourceManager::getInstance()->shader("animation");
            ResourceManager::getInstance()->shader("tilemap");
            ResourceManager::getInstance()->shader("lightmap");
            _logger->info() << "[RENDERER] "
                            << "[OK]" << std::endl;

            _logger->info() << "[RENDERER] "
                            << "Generating buffers" << std::endl;

            // generate projection matrix
            _MVP = glm::ortho(0.0, static_cast<double>(_rendererConfig->width()), static_cast<double>(_rendererConfig->height()), 0.0, -1.0, 1.0);

            // load egg
            _egg = ResourceManager::getInstance()->texture("data/egg.png");
        }

        void Renderer::think(const float deltaTime) {
            if (_fadeDone) {
                return;
            }

            _fadeTimer += deltaTime;

            float fadeDelay = static_cast<float>(_fadeDelay);
            if (fadeDelay < 1.0f) {
                fadeDelay = 1.0f;
            }

            while (_fadeTimer >= fadeDelay) {
                _fadeTimer -= fadeDelay;
                _fadeAlpha += _fadeStep;
                if (_fadeAlpha <= 0 || _fadeAlpha > 255) {
                    _fadeAlpha = (_fadeAlpha <= 0 ? 0 : 255);
                    _fadeDone = true;

                    auto state = Game::getInstance()->topState();
                    state->emitEvent(std::make_unique<Event::State>("fadedone"), state->fadeDoneHandler());
                    return;
                }
            }
            _fadeColor.a = _fadeAlpha;
        }

        bool Renderer::fading() {
            return !_fadeDone && !_inmovie;
        }

        void Renderer::fadeIn(uint8_t r, uint8_t g, uint8_t b, unsigned int time, bool inmovie) {
            _inmovie = inmovie;
            _fadeColor = {r, g, b, 255};
            _fadeAlpha = 255;
            _fadeStep = -1;
            _fadeDone = false;
            _fadeDelay = static_cast<unsigned>(round(time / 256));
            _fadeTimer = 0;
        }

        void Renderer::fadeOut(uint8_t r, uint8_t g, uint8_t b, unsigned int time, bool inmovie) {
            _inmovie = inmovie;
            _fadeColor = {r, g, b, 0};
            _fadeAlpha = 0;
            _fadeStep = 1;
            _fadeDone = false;
            _fadeDelay = static_cast<unsigned>(round(time / 256));
            _fadeTimer = 0;
        }

        void Renderer::beginFrame() {
            GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
            GL_CHECK(glEnable(GL_BLEND));
            GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        }

        void Renderer::endFrame() {
            GL_CHECK(glDisable(GL_BLEND));
            SDL_GL_SwapWindow(_sdlWindow->sdlWindowPtr());
        }

        const Size& Renderer::size() const {
            return _size;
        }

        void Renderer::screenshot() {
            std::string filename;
            Uint32 rmask = 0, gmask = 0, bmask = 0, amask = 0;
            SDL_Surface* output = nullptr;

            int iter = 0;
            do {
                std::string siter = std::to_string(iter);
                if (siter.size() < 3) {
                    siter.insert(0, 3 - siter.size(), '0');
                }
                filename = "screenshot" + siter + ".png";
                iter++;
            } while (CrossPlatform::fileExists(filename) && iter < 1000);

            if (CrossPlatform::fileExists(filename)) {
                _logger->warning() << "[RENDERER] Too many screenshots" << std::endl;
                return;
            }

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
            rmask = 0xff000000;
            gmask = 0x00ff0000;
            bmask = 0x0000ff00;
            amask = 0x000000ff;
#else
            rmask = 0x000000ff;
            gmask = 0x0000ff00;
            bmask = 0x00ff0000;
            amask = 0xff000000;
#endif

            output = SDL_CreateRGBSurface(0, size().width(), size().height(), 32, rmask, gmask, bmask, amask);
            uint8_t* destPixels = (uint8_t*)output->pixels;
            Base::Buffer<uint8_t> srcPixels(size().width() * size().height() * 4);

            glReadBuffer(GL_BACK);
            glReadPixels(0, 0, size().width(), size().height(), GL_RGBA, GL_UNSIGNED_BYTE, srcPixels.data());

            for (int y = 0; y < static_cast<int>(size().height()); ++y) {
                for (int x = 0; x < static_cast<int>(size().width()); ++x) {
                    uint8_t* pDestPix = &destPixels[((size().width() * y) + x) * 4];
                    uint8_t* pSrcPix = &srcPixels[((size().width() * ((size().height() - 1) - y)) + x) * 4];
                    pDestPix[0] = pSrcPix[0];
                    pDestPix[1] = pSrcPix[1];
                    pDestPix[2] = pSrcPix[2];
                    pDestPix[3] = 255;
                }
            }

            IMG_SavePNG(output, filename.c_str());
            SDL_FreeSurface(output);
            _logger->info() << "[RENDERER] Screenshot saved to " + filename << std::endl;
        }

        float Renderer::scaleX() {
            return _scaleX;
        }

        float Renderer::scaleY() {
            return _scaleY;
        }

        glm::mat4 Renderer::getMVP() {
            return _MVP;
        }

        void Renderer::drawRect(int x, int y, int w, int h, Color color) {
            std::vector<glm::vec2> vertices;

            glm::vec4 fcolor = glm::vec4(
                (float) color.red() / 255.0f,
                (float) color.green() / 255.0f,
                (float) color.blue() / 255.0f,
                (float) color.alpha() / 255.0f
            );

            vertices.push_back(glm::vec2((float)x, (float)y));
            vertices.push_back(glm::vec2((float)x, (float)y + (float)h));
            vertices.push_back(glm::vec2((float)x + (float)w, (float)y));
            vertices.push_back(glm::vec2((float)x + (float)w, (float)y + (float)h));

            auto defaultShader = ResourceManager::getInstance()->shader("default");
            defaultShader->use();
            defaultShader->setUniform("color", fcolor);
            defaultShader->setUniform("MVP", getMVP());

            VertexArray vertexArray;

            std::unique_ptr<VertexBuffer> coordinatesVertexBuffer =
                std::make_unique<VertexBuffer>(&vertices[0], vertices.size() * sizeof(glm::vec2), VertexBuffer::UsagePattern::DynamicDraw);
            VertexBufferLayout coordinatesVertexBufferLayout;
            coordinatesVertexBufferLayout.addAttribute({(unsigned int)defaultShader->getAttrib("Position"), 2, VertexBufferAttribute::Type::Float});
            vertexArray.addBuffer(coordinatesVertexBuffer, coordinatesVertexBufferLayout);

            static unsigned int indexes[6] = {0, 1, 2, 3, 2, 1};
            IndexBuffer indexBuffer(indexes, 6, IndexBuffer::UsagePattern::StaticDraw);

            GL_CHECK(glDrawElements(GL_TRIANGLES, indexBuffer.count(), GL_UNSIGNED_INT, nullptr));
        }

        void Renderer::drawRect(const Point& pos, const Size& size, Color color) {
            drawRect(pos.x(), pos.y(), size.width(), size.height(), color);
        }

        void Renderer::drawRectangle(const Rectangle& rectangle, const Texture* const texture) {
            float x1 = (float)rectangle.position().x();
            float y1 = (float)rectangle.position().y();
            float x2 = (float)(rectangle.position().x() + rectangle.size().width());
            float y2 = (float)(rectangle.position().y() + rectangle.size().height());
            std::vector<glm::vec2> vertices = {
                // aPosition       // aTexturePosition
                glm::vec2(x1, y1), glm::vec2(0.0, 0.0), glm::vec2(x1, y2), glm::vec2(0.0, 1.0),
                glm::vec2(x2, y1), glm::vec2(1.0, 0.0), glm::vec2(x2, y2), glm::vec2(1.0, 1.0),
            };

            auto spriteShader = ResourceManager::getInstance()->shader("video");
            spriteShader->use();

            texture->bind(0);
            spriteShader->setUniform("uTexture", 0);
            spriteShader->setUniform("uProjectionMatrix", getMVP());

            std::unique_ptr<VertexBuffer> vertexBuffer =
                std::make_unique<VertexBuffer>(&vertices[0], vertices.size() * sizeof(glm::vec2), VertexBuffer::UsagePattern::StaticDraw);
            VertexBufferLayout vertexBufferLayout({
                {0, 2, VertexBufferAttribute::Type::Float}, // aPosition
                {1, 2, VertexBufferAttribute::Type::Float}  // aTexturePosition
            });
            VertexArray vertexArray;
            vertexArray.addBuffer(vertexBuffer, vertexBufferLayout);

            static unsigned int indexes[6] = {0, 1, 2, 3, 2, 1};
            IndexBuffer indexBuffer(indexes, 6, IndexBuffer::UsagePattern::StaticDraw);

            GL_CHECK(glDrawElements(GL_TRIANGLES, indexBuffer.count(), GL_UNSIGNED_INT, nullptr));
        }

        void Renderer::drawPartialRectangle(const Point& point, const Rectangle& rectangle, const Texture* const texture) {
            auto x1 = (float)point.x();
            auto y1 = (float)point.y();
            auto x2 = (float)(point.x() + rectangle.size().width());
            auto y2 = (float)(point.y() + rectangle.size().height());

            auto dx1 = (float)rectangle.position().x() / (float)texture->size().width();
            auto dy1 = (float)rectangle.position().y() / (float)texture->size().height();
            auto dx2 = (float)(rectangle.position().x() + rectangle.size().width()) / (float)texture->size().width();
            auto dy2 = (float)(rectangle.position().y() + rectangle.size().height()) / (float)texture->size().height();

            std::vector<glm::vec2> vertices = {
                // aPosition       // aTexturePosition
                glm::vec2(x1, y1), glm::vec2(dx1, dy1), glm::vec2(x1, y2), glm::vec2(dx1, dy2),
                glm::vec2(x2, y1), glm::vec2(dx2, dy1), glm::vec2(x2, y2), glm::vec2(dx2, dy2),
            };

            auto spriteShader = ResourceManager::getInstance()->shader("video");
            spriteShader->use();

            texture->bind(0);
            spriteShader->setUniform("uTexture", 0);
            spriteShader->setUniform("uProjectionMatrix", getMVP());

            std::unique_ptr<VertexBuffer> vertexBuffer =
                std::make_unique<VertexBuffer>(&vertices[0], vertices.size() * sizeof(glm::vec2), VertexBuffer::UsagePattern::StaticDraw);
            VertexBufferLayout vertexBufferLayout({
                {0, 2, VertexBufferAttribute::Type::Float}, // aPosition
                {1, 2, VertexBufferAttribute::Type::Float}  // aTexturePosition
            });
            VertexArray vertexArray;
            vertexArray.addBuffer(vertexBuffer, vertexBufferLayout);

            static unsigned int indexes[6] = {0, 1, 2, 3, 2, 1};
            IndexBuffer indexBuffer(indexes, 6, IndexBuffer::UsagePattern::StaticDraw);

            GL_CHECK(glDrawElements(GL_TRIANGLES, indexBuffer.count(), GL_UNSIGNED_INT, nullptr));
        }

        void Renderer::drawRectangle(const Rectangle& rectangle, const Texture* const texture, const Texture* const egg, const Shader* const shader) {
            glm::vec2 vertices[4] = {glm::vec2((float)rectangle.position().x(), (float)rectangle.position().y()),
                                     glm::vec2((float)rectangle.position().x(), (float)(rectangle.position().y() + rectangle.size().height())),
                                     glm::vec2((float)(rectangle.position().x() + rectangle.size().width()), (float)rectangle.position().y()),
                                     glm::vec2((float)(rectangle.position().x() + rectangle.size().width()),
                                               (float)(rectangle.position().y() + rectangle.size().height()))};
            glm::vec2 UV[4] = {glm::vec2(0.0, 0.0), glm::vec2(0.0, 1.0), glm::vec2(1.0, 0.0), glm::vec2(1.0, 1.0)};

            shader->use();

            texture->bind(0);
            egg->bind(1);

            VertexArray vertexArray;

            std::unique_ptr<VertexBuffer> coordinatesVertexBuffer =
                std::make_unique<VertexBuffer>(&vertices[0], sizeof(vertices), VertexBuffer::UsagePattern::DynamicDraw);

            VertexBufferLayout coordinatesVertexBufferLayout;
            coordinatesVertexBufferLayout.addAttribute({(unsigned int)shader->getAttrib("Position"), 2, VertexBufferAttribute::Type::Float});
            vertexArray.addBuffer(coordinatesVertexBuffer, coordinatesVertexBufferLayout);

            std::unique_ptr<VertexBuffer> textureCoordinatesVertexBuffer =
                std::make_unique<VertexBuffer>(&UV[0], sizeof(UV), VertexBuffer::UsagePattern::DynamicDraw);
            VertexBufferLayout textureCoordinatesVertexBufferLayout;
            textureCoordinatesVertexBufferLayout.addAttribute({(unsigned int)shader->getAttrib("TexCoord"), 2, VertexBufferAttribute::Type::Float});
            vertexArray.addBuffer(textureCoordinatesVertexBuffer, textureCoordinatesVertexBufferLayout);

            static unsigned int indexes[6] = {0, 1, 2, 3, 2, 1};
            IndexBuffer indexBuffer(indexes, 6, IndexBuffer::UsagePattern::StaticDraw);

            GL_CHECK(glDrawElements(GL_TRIANGLES, indexBuffer.count(), GL_UNSIGNED_INT, nullptr));
        }

        void Renderer::drawPartialRectangle(const Point& point, const Rectangle& rectangle, const Texture* const texture, const Texture* const egg,
                                            const Shader* const shader) {
            glm::vec2 vertices[4] = {glm::vec2((float)point.x(), (float)point.y()),
                                     glm::vec2((float)point.x(), (float)(point.y() + rectangle.size().height())),
                                     glm::vec2((float)(point.x() + rectangle.size().width()), (float)point.y()),
                                     glm::vec2((float)(point.x() + rectangle.size().width()), (float)(point.y() + rectangle.size().height()))};
            glm::vec2 UV[4] = {glm::vec2((float)rectangle.position().x() / (float)texture->size().width(),
                                         (float)rectangle.position().y() / (float)texture->size().height()),
                               glm::vec2((float)rectangle.position().x() / (float)texture->size().width(),
                                         (float)(rectangle.position().y() + rectangle.size().height()) / (float)texture->size().height()),
                               glm::vec2((float)(rectangle.position().x() + rectangle.size().width()) / (float)texture->size().width(),
                                         (float)rectangle.position().y() / (float)texture->size().height()),
                               glm::vec2((float)(rectangle.position().x() + rectangle.size().width()) / (float)texture->size().width(),
                                         (float)(rectangle.position().y() + rectangle.size().height()) / (float)texture->size().height())};

            shader->use();
            texture->bind(0);
            egg->bind(1);

            VertexArray vertexArray;

            std::unique_ptr<VertexBuffer> coordinatesVertexBuffer =
                std::make_unique<VertexBuffer>(&vertices[0], sizeof(vertices), VertexBuffer::UsagePattern::DynamicDraw);
            VertexBufferLayout coordinatesVertexBufferLayout;
            coordinatesVertexBufferLayout.addAttribute({(unsigned int)shader->getAttrib("Position"), 2, VertexBufferAttribute::Type::Float});
            vertexArray.addBuffer(coordinatesVertexBuffer, coordinatesVertexBufferLayout);

            std::unique_ptr<VertexBuffer> textureCoordinatesVertexBuffer =
                std::make_unique<VertexBuffer>(&UV[0], sizeof(UV), VertexBuffer::UsagePattern::DynamicDraw);
            VertexBufferLayout textureCoordinatesVertexBufferLayout;
            textureCoordinatesVertexBufferLayout.addAttribute({(unsigned int)shader->getAttrib("TexCoord"), 2, VertexBufferAttribute::Type::Float});
            vertexArray.addBuffer(textureCoordinatesVertexBuffer, textureCoordinatesVertexBufferLayout);

            static unsigned int indexes[6] = {0, 1, 2, 3, 2, 1};
            IndexBuffer indexBuffer(indexes, 6, IndexBuffer::UsagePattern::StaticDraw);

            GL_CHECK(glDrawElements(GL_TRIANGLES, indexBuffer.count(), GL_UNSIGNED_INT, nullptr));
        }

        glm::vec4 Renderer::fadeColor() {
            return glm::vec4((float)_fadeColor.r / 255.0, (float)_fadeColor.g / 255.0, (float)_fadeColor.b / 255.0, (float)_fadeColor.a / 255.0);
        }

        int32_t Renderer::maxTextureSize() {
            return 1024;
            return _maxTexSize;
        }

        Texture* Renderer::egg() {
            return _egg;
        }

        Renderer::RenderPath Renderer::renderPath() {
            return _renderpath;
        }
    }
}
