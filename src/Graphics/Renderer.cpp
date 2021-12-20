#include <cmath>
#include <memory>
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>
#include <SDL_image.h>
#include "../Base/Buffer.h"
#include "../CrossPlatform.h"
#include "../Event/State.h"
#include "../Exception.h"
#include "../Game/Game.h"
#include "../Graphics/GLCheck.h"
#include "../Graphics/Point.h"
#include "../Graphics/Renderer.h"
#include "../Graphics/VertexArray.h"
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/IndexBuffer.h"
#include "../Graphics/IRendererConfig.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Texture.h"
#include "../Input/Mouse.h"
#include "../ResourceManager.h"
#include "../Settings.h"
#include "../State/State.h"

namespace Falltergeist
{
    namespace Graphics
    {
        using Game::Game;

        Renderer::Renderer(std::unique_ptr<IRendererConfig> rendererConfig, std::shared_ptr<ILogger> logger)
        {
            _rendererConfig = std::move(rendererConfig);
            this->logger = std::move(logger);

            std::string message = "Renderer initialization - ";
            if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
            {
                logger->critical() << "[VIDEO] " << message + "[FAIL]" << std::endl;
                throw Exception(SDL_GetError());
            }
            this->logger->info() << "[VIDEO] " << message << "[OK]" << std::endl;
        }

        Renderer::~Renderer()
        {
        }

        void Renderer::init()
        {
            // TODO: android/ios
            // _width = deviceWidth;
            // _height = deviceHeight;
            // Game::getInstance()->engineSettings()->setFullscreen(true);
            // Game::getInstance()->engineSettings()->setScale(1); //or 2, if fullhd device

            std::string message =  "SDL_CreateWindow " + std::to_string(_rendererConfig->width()) + "x" + std::to_string(_rendererConfig->height()) + "x" + std::to_string(32) + " - ";

            uint32_t flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

            if (_rendererConfig->isFullscreen()) {
                flags |= SDL_WINDOW_FULLSCREEN;
            }

            if (_rendererConfig->isAlwaysOnTop()) {
                // SDL_WINDOW_ALWAYS_ON_TOP is available on X11 only, >= SDL 2.0.5
                flags |= 0x00008000; // Copied from SDL_WindowFlags::SDL_WINDOW_ALWAYS_ON_TOP
            }

            _sdlWindow = SDL_CreateWindow(
                "",
                _rendererConfig->x(),
                _rendererConfig->y(),
                _rendererConfig->width(),
                _rendererConfig->height(),
                flags
            );

            if (!_sdlWindow) {
                throw Exception(message + "[FAIL]");
            }

            logger->info() << "[RENDERER] " << message + "[OK]" << std::endl;

            message =  "Init OpenGL - ";
            // specifically request 3.2, because fucking Mesa ignores core flag with version < 3
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
            _glcontext = SDL_GL_CreateContext(_sdlWindow);

            if (!_glcontext) {
                // ok, try and create 2.1 context then
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 0);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
                _glcontext = SDL_GL_CreateContext(_sdlWindow);

                if (!_glcontext) {
                    throw Exception(message + "[FAIL]");
                }
            }

            logger->info() << "[RENDERER] " << message + "[OK]" << std::endl;
            SDL_GL_SetSwapInterval(0);

        /*
         * TODO: newrender
            if (Game::getInstance()->settings()->scale() != 0)
            {
                switch (Game::getInstance()->settings()->scale())
                {
                    default:
                    case 1:
                        _size.setWidth((int)(_size.width() / (_size.height() / 480.0)));
                        _size.setHeight(480);
                        break;
                    case 2:
                        _size.setWidth((int)(_size.width() / (_size.height() / 960.0)));
                        _size.setHeight(960);
                        break;
                }
                SDL_RenderSetLogicalSize(_sdlRenderer, _size.width(), _size.height());
                SDL_RenderGetScale(_sdlRenderer, &_scaleX, &_scaleY);
            }
        */

            char *version_string = (char*)glGetString(GL_VERSION);
            if (version_string[0]-'0' >=3) { //we have at least gl 3.0
                glGetIntegerv(GL_MAJOR_VERSION, &_major);
                glGetIntegerv(GL_MINOR_VERSION, &_minor);
                if (_major == 3 && _minor < 2) { // anything lower 3.2
                    _renderpath = RenderPath::OGL21;
                } else {
                    _renderpath = RenderPath::OGL32;
                }
            } else {
                _major = version_string[0]-'0';
                _minor = version_string[2]-'0';
                _renderpath = RenderPath::OGL21;
            }


            logger->info() << "[RENDERER] " << "Using OpenGL " << _major << "." << _minor << std::endl;
            logger->info() << "[RENDERER] " << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
            logger->info() << "[RENDERER] " << "Version string: " << glGetString(GL_VERSION) << std::endl;
            logger->info() << "[RENDERER] " << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
            switch (_renderpath) {
                case RenderPath::OGL21:
                    logger->info() << "[RENDERER] " << "Render path: OpenGL 2.1"  << std::endl;
                    break;
                case RenderPath::OGL32:
                    logger->info() << "[RENDERER] " << "Render path: OpenGL 3.0+" << std::endl;
                    break;
                default:
                    break;
            }

            glGetIntegerv(GL_MAX_TEXTURE_SIZE, &_maxTexSize);

            message =  "Init GLEW - ";
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

            logger->info() << "[RENDERER] " << message + "[OK]" << std::endl;
            logger->info() << "[RENDERER] " << "Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

            logger->info() << "[RENDERER] " << "Extensions: " << std::endl;

            if (_renderpath == RenderPath::OGL32) {
                GLint count;
                glGetIntegerv(GL_NUM_EXTENSIONS, &count);

                for (GLint i = 0; i < count; i++) {
                    logger->info() << "[RENDERER] " << (const char *) glGetStringi(GL_EXTENSIONS, i) << std::endl;
                }
            } else {
                logger->info() << "[RENDERER] " << (const char *) glGetString(GL_EXTENSIONS) << std::endl;
            }

            logger->info() << "[RENDERER] " << "Loading default shaders" << std::endl;
            ResourceManager::getInstance()->shader("default");
            ResourceManager::getInstance()->shader("sprite");
            ResourceManager::getInstance()->shader("font");
            ResourceManager::getInstance()->shader("animation");
            ResourceManager::getInstance()->shader("tilemap");
            ResourceManager::getInstance()->shader("lightmap");
            logger->info() << "[RENDERER] " << "[OK]" << std::endl;

            logger->info() << "[RENDERER] " << "Generating buffers" << std::endl;

            // generate projection matrix
            _MVP = glm::ortho(
                0.0,
                static_cast<double>(_rendererConfig->width()),
                static_cast<double>(_rendererConfig->height()),
                0.0,
                -1.0,
                1.0
            );

            // load egg
            _egg = ResourceManager::getInstance()->texture("data/egg.png");
        }

        void Renderer::think(const float &deltaTime)
        {
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
                if (_fadeAlpha <= 0 || _fadeAlpha > 255)
                {
                    _fadeAlpha = (_fadeAlpha <= 0 ? 0 : 255);
                    _fadeDone = true;

                    auto state = Game::getInstance()->topState();
                    state->emitEvent(std::make_unique<Event::State>("fadedone"), state->fadeDoneHandler());
                    return;
                }
            }
            _fadeColor.a = _fadeAlpha;
        }

        bool Renderer::fading()
        {
            return !_fadeDone && !_inmovie;
        }

        void Renderer::fadeIn(uint8_t r, uint8_t g, uint8_t b, unsigned int time, bool inmovie)
        {
            _inmovie = inmovie;
            _fadeColor = {r, g, b, 255};
            _fadeAlpha = 255;
            _fadeStep = -1;
            _fadeDone = false;
            _fadeDelay = static_cast<unsigned>(round(time / 256));
            _fadeTimer = 0;
        }

        void Renderer::fadeOut(uint8_t r, uint8_t g, uint8_t b, unsigned int time, bool inmovie)
        {
            _inmovie = inmovie;
            _fadeColor = {r, g, b, 0};
            _fadeAlpha = 0;
            _fadeStep = 1;
            _fadeDone = false;
            _fadeDelay = static_cast<unsigned>(round(time / 256));
            _fadeTimer = 0;
        }


        void Renderer::beginFrame()
        {
            GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
            GL_CHECK(glEnable(GL_BLEND));
            GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        }

        void Renderer::endFrame()
        {
            GL_CHECK(glDisable(GL_BLEND));
            SDL_GL_SwapWindow(_sdlWindow);
        }

        unsigned int Renderer::width() const
        {
            return _rendererConfig->width();
        }

        unsigned int Renderer::height() const
        {
            return _rendererConfig->height();
        }

        Size Renderer::size() const
        {
            return {
                static_cast<int>(_rendererConfig->width()),
                static_cast<int>(_rendererConfig->height())
            };
        }

        void Renderer::screenshot()
        {
            std::string filename;
            Uint32 rmask, gmask, bmask, amask;
            SDL_Surface* output;

            int iter = 0;
            do
            {
                std::string siter = std::to_string(iter);
                if(siter.size() < 3)
                {
                    siter.insert(0, 3 - siter.size(), '0');
                }
                filename = "screenshot" + siter + ".png";
                iter++;
            }
            while (CrossPlatform::fileExists(filename) && iter < 1000);

            if (CrossPlatform::fileExists(filename))
            {
                logger->warning() << "[RENDERER] Too many screenshots" << std::endl;
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

            output = SDL_CreateRGBSurface(0, width(), height(), 32, rmask, gmask, bmask, amask);
            uint8_t *destPixels = (uint8_t*)output->pixels;
            Base::Buffer<uint8_t> srcPixels(width() * height() * 4);

            glReadBuffer(GL_BACK);
            glReadPixels(0, 0, width(), height(), GL_RGBA, GL_UNSIGNED_BYTE, srcPixels.data());

            for (int y = 0; y < static_cast<int>(height()); ++y)
            {
                for (int x = 0; x < static_cast<int>(width()); ++x)
                {
                    uint8_t* pDestPix = &destPixels[((width() * y) + x) * 4];
                    uint8_t* pSrcPix = &srcPixels[((width() * ((height() - 1) - y)) + x) * 4];
                    pDestPix[0] = pSrcPix[0];
                    pDestPix[1] = pSrcPix[1];
                    pDestPix[2] = pSrcPix[2];
                    pDestPix[3] = 255;
                }
            }

            IMG_SavePNG(output,filename.c_str());
            SDL_FreeSurface(output);
            logger->info() << "[RENDERER] Screenshot saved to " + filename << std::endl;

            return;

        }

        void Renderer::setCaption(const std::string& caption)
        {
            SDL_SetWindowTitle(_sdlWindow, caption.c_str());
        }

        SDL_Window* Renderer::sdlWindow()
        {
            return _sdlWindow;
        }

        float Renderer::scaleX()
        {
            return _scaleX;
        }

        float Renderer::scaleY()
        {
            return _scaleY;
        }

        glm::mat4 Renderer::getMVP()
        {
            return _MVP;
        }

        void Renderer::drawRect(int x, int y, int w, int h, SDL_Color color)
        {
            std::vector<glm::vec2> vertices;

            glm::vec4 fcolor = glm::vec4((float)color.r/255.0f, (float)color.g/255.0f, (float)color.b/255.0f, (float)color.a/255.0f);

            vertices.push_back(glm::vec2((float)x, (float)y));
            vertices.push_back(glm::vec2((float)x, (float)y+(float)h));
            vertices.push_back(glm::vec2((float)x+(float)w, (float)y));
            vertices.push_back(glm::vec2((float)x+(float)w, (float)y+(float)h));


            auto defaultShader = ResourceManager::getInstance()->shader("default");
            defaultShader->use();
            defaultShader->setUniform("color", fcolor);
            defaultShader->setUniform("MVP", getMVP());

            VertexArray vertexArray;

            std::unique_ptr<VertexBuffer> coordinatesVertexBuffer = std::make_unique<VertexBuffer>(
                    &vertices[0],
                    vertices.size() * sizeof(glm::vec2),
                    VertexBuffer::UsagePattern::DynamicDraw
            );
            VertexBufferLayout coordinatesVertexBufferLayout;
            coordinatesVertexBufferLayout.addAttribute({
                    (unsigned int) defaultShader->getAttrib("Position"),
                    2,
                    VertexBufferAttribute::Type::Float,
                    false,
                    0
            });
            vertexArray.addBuffer(coordinatesVertexBuffer, coordinatesVertexBufferLayout);

            static unsigned int indexes[6] = { 0, 1, 2, 3, 2, 1 };
            IndexBuffer indexBuffer(indexes, 6, IndexBuffer::UsagePattern::StaticDraw);

            GL_CHECK(glDrawElements(GL_TRIANGLES, indexBuffer.count(), GL_UNSIGNED_INT, nullptr));
        }

        void Renderer::drawRect(const Point &pos, const Size &size, SDL_Color color)
        {
            drawRect(pos.x(), pos.y(), size.width(), size.height(), color);
        }

        void Renderer::drawRectangle(const Rectangle& rectangle, const Texture* const texture)
        {
            std::vector<glm::vec2> vertices;
            std::vector<glm::vec2> UV;

            glm::vec2 vertex_up_left    = glm::vec2( (float) rectangle.position().x(), (float) rectangle.position().y());
            glm::vec2 vertex_up_right   = glm::vec2( (float)(rectangle.position().x() + rectangle.size().width()), (float) rectangle.position().y());
            glm::vec2 vertex_down_right = glm::vec2( (float)(rectangle.position().x() + rectangle.size().width()), (float)(rectangle.position().y() + rectangle.size().height()));
            glm::vec2 vertex_down_left  = glm::vec2( (float)rectangle.position().x(), (float)(rectangle.position().y() + rectangle.size().height()));

            vertices.push_back(vertex_up_left   );
            vertices.push_back(vertex_down_left );
            vertices.push_back(vertex_up_right  );
            vertices.push_back(vertex_down_right);

            glm::vec2 uv_up_left    = glm::vec2( 0.0, 0.0 );
            glm::vec2 uv_up_right   = glm::vec2( 1.0, 0.0 );
            glm::vec2 uv_down_right = glm::vec2( 1.0, 1.0);
            glm::vec2 uv_down_left  = glm::vec2( 0.0, 1.0);

            UV.push_back(uv_up_left   );
            UV.push_back(uv_down_left );
            UV.push_back(uv_up_right  );
            UV.push_back(uv_down_right);

            // TODO: different shader

            auto spriteShader = ResourceManager::getInstance()->shader("sprite");
            spriteShader->use();

            texture->bind(0);

            spriteShader->setUniform("tex",0);
            spriteShader->setUniform("fade",Game::getInstance()->renderer()->fadeColor());
            spriteShader->setUniform("MVP", Game::getInstance()->renderer()->getMVP());

            VertexArray vertexArray;

            std::unique_ptr<VertexBuffer> coordinatesVertexBuffer = std::make_unique<VertexBuffer>(
                    &vertices[0],
                    vertices.size() * sizeof(glm::vec2),
                    VertexBuffer::UsagePattern::DynamicDraw
            );
            VertexBufferLayout coordinatesVertexBufferLayout;
            coordinatesVertexBufferLayout.addAttribute({
                                                               (unsigned int) spriteShader->getAttrib("Position"),
                                                               2,
                                                               VertexBufferAttribute::Type::Float,
                                                               false,
                                                               0
                                                       });
            vertexArray.addBuffer(coordinatesVertexBuffer, coordinatesVertexBufferLayout);

            std::unique_ptr<VertexBuffer> textureCoordinatesVertexBuffer = std::make_unique<VertexBuffer>(
                    &UV[0],
                    UV.size() * sizeof(glm::vec2),
                    VertexBuffer::UsagePattern::DynamicDraw
            );
            VertexBufferLayout textureCoordinatesVertexBufferLayout;
            textureCoordinatesVertexBufferLayout.addAttribute({
                                                                      (unsigned int) spriteShader->getAttrib("TexCoord"),
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

        void Renderer::drawRectangle(const Rectangle& rectangle, const Texture* const texture, const Texture* const egg, const Shader* const shader)
        {
            glm::vec2 vertices[4] = {
                    glm::vec2((float) rectangle.position().x(), (float) rectangle.position().y()),
                    glm::vec2((float) rectangle.position().x(), (float)(rectangle.position().y() + rectangle.size().height())),
                    glm::vec2((float)(rectangle.position().x() + rectangle.size().width()), (float) rectangle.position().y()),
                    glm::vec2((float)(rectangle.position().x() + rectangle.size().width()), (float)(rectangle.position().y() + rectangle.size().height()))
            };
            glm::vec2 UV[4] = {
                    glm::vec2(0.0, 0.0),
                    glm::vec2(0.0, 1.0),
                    glm::vec2(1.0, 0.0),
                    glm::vec2(1.0, 1.0)
            };

            shader->use();

            texture->bind(0);
            egg->bind(1);

            VertexArray vertexArray;

            std::unique_ptr<VertexBuffer> coordinatesVertexBuffer = std::make_unique<VertexBuffer>(
                    &vertices[0],
                    sizeof(vertices),
                    VertexBuffer::UsagePattern::DynamicDraw
            );

            VertexBufferLayout coordinatesVertexBufferLayout;
            coordinatesVertexBufferLayout.addAttribute({
                                                               (unsigned int) shader->getAttrib("Position"),
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
                                                                      (unsigned int) shader->getAttrib("TexCoord"),
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

        void Renderer::drawPartialRectangle(const Point& point, const Rectangle& rectangle, const Texture* const texture, const Texture* const egg, const Shader* const shader)
        {
            glm::vec2 vertices[4] = {
                    glm::vec2((float) point.x(), (float) point.y()),
                    glm::vec2((float)point.x(), (float)(point.y() + rectangle.size().height())),
                    glm::vec2((float)(point.x() + rectangle.size().width()), (float)point.y()),
                    glm::vec2((float)(point.x() + rectangle.size().width()), (float)(point.y() + rectangle.size().height()))
            };
            glm::vec2 UV[4] = {
                    glm::vec2((float)rectangle.position().x() / (float)texture->size().width(), (float)rectangle.position().y() / (float)texture->size().height()),
                    glm::vec2((float)rectangle.position().x() / (float)texture->size().width(), (float)(rectangle.position().y() + rectangle.size().height()) / (float)texture->size().height()),
                    glm::vec2((float)(rectangle.position().x() + rectangle.size().width()) / (float)texture->size().width(), (float)rectangle.position().y() / (float)texture->size().height()),
                    glm::vec2((float)(rectangle.position().x() + rectangle.size().width()) / (float)texture->size().width(), (float)(rectangle.position().y() + rectangle.size().height()) / (float)texture->size().height())
            };

            shader->use();
            texture->bind(0);
            egg->bind(1);

            VertexArray vertexArray;

            std::unique_ptr<VertexBuffer> coordinatesVertexBuffer = std::make_unique<VertexBuffer>(
                    &vertices[0],
                    sizeof(vertices),
                    VertexBuffer::UsagePattern::DynamicDraw
            );
            VertexBufferLayout coordinatesVertexBufferLayout;
            coordinatesVertexBufferLayout.addAttribute({
                                                               (unsigned int) shader->getAttrib("Position"),
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
                                                                      (unsigned int) shader->getAttrib("TexCoord"),
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


        glm::vec4 Renderer::fadeColor()
        {
            return glm::vec4((float)_fadeColor.r/255.0, (float)_fadeColor.g/255.0, (float)_fadeColor.b/255.0, (float)_fadeColor.a/255.0);
        }

        int32_t Renderer::maxTextureSize()
        {
            return 1024;
            return _maxTexSize;
        }

        Texture *Renderer::egg()
        {
            return _egg;
        }

        Renderer::RenderPath Renderer::renderPath()
        {
            return _renderpath;
        }
    }
}
