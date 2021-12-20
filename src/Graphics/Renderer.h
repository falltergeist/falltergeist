#pragma once

#include <memory>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <SDL.h>
#include "../Graphics/IRendererConfig.h"
#include "../Graphics/Point.h"
#include "../Graphics/Rectangle.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Size.h"
#include "../ILogger.h"

namespace Falltergeist
{
    namespace Graphics
    {
        class Texture;

        class Renderer
        {
            public:
                enum class RenderPath
                {
                    OGL21 = 0,
                    OGL32,
                    GLES1,
                    GLES2
                };

                Renderer(std::unique_ptr<IRendererConfig> rendererConfig, std::shared_ptr<ILogger> logger);
                ~Renderer();

                void init();

                void beginFrame();
                void endFrame();
                void think(const float &deltaTime);

                unsigned int width() const;
                unsigned int height() const;
                Size size() const;

                float scaleX();
                float scaleY();

                bool fading();

                void fadeIn(uint8_t r, uint8_t g, uint8_t b, unsigned int time, bool inmovie = false);
                void fadeOut(uint8_t r, uint8_t g, uint8_t b, unsigned int time, bool inmovie = false);

                void setCaption(const std::string& caption);
                SDL_Window* sdlWindow();

                glm::mat4 getMVP();

                void drawRect(int x, int y, int w, int h, SDL_Color color);
                void drawRect(const Point &pos, const Size &size, SDL_Color color);
                void drawRectangle(const Rectangle& rectangle, const Texture* const texture);
                // Draw scaled texture in the rectangle
                void drawRectangle(const Rectangle& rectangle, const Texture* const texture, const Texture* const egg, const Shader* const shader);
                // Draw rectangle part of the texture in the given position. unscaled
                void drawPartialRectangle(const Point& position, const Rectangle& rectangle, const Texture* const texture, const Texture* const egg, const Shader* const shader);

                glm::vec4 fadeColor();

                void screenshot();

                int32_t maxTextureSize();

                Texture* egg();

                RenderPath renderPath();

            protected:
                RenderPath _renderpath = RenderPath::OGL21;

                short _fadeStep = 0;
                float _fadeTimer = 0;
                unsigned int _fadeDelay = 0;
                unsigned int _fadeAlpha = 0;
                bool _fadeDone = true;
                SDL_Color _fadeColor = {0, 0, 0, 0};

                bool _inmovie = false;

                float _scaleX = 1.0;
                float _scaleY = 1.0;

                SDL_Window* _sdlWindow;
                SDL_GLContext _glcontext;
                glm::mat4 _MVP;
                GLint _major;
                GLint _minor;
                int32_t _maxTexSize;

                Texture* _egg;

            private:
                std::unique_ptr<IRendererConfig> _rendererConfig;
                std::shared_ptr<ILogger> logger;
        };
    }
}
