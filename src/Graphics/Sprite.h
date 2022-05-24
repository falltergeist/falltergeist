#pragma once

// Project includes
#include "../Format/Frm/File.h"
#include "../Graphics/Point.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Texture.h"
#include "../Graphics/Rectangle.h"
#include "../Graphics/TransFlags.h"

// Third-party includes

// stdlib
#include <string>

namespace Falltergeist
{
    namespace Graphics
    {
        class Sprite
        {
            public:
                Sprite(const std::string& filename);
                Sprite(Format::Frm::File* frm);
                void renderScaled(const Point& point, const Size& size, bool transparency = false,
                                  bool light = false, int outline = 0, unsigned int lightValue=0);
                void render(const Point& point, bool transparency = false, bool light = false, int outline = 0, unsigned int lightValue=0);
                void renderCropped(const Point& point, const Rectangle& part, bool transparency = false,
                                   bool light = false, unsigned int lightValue=0);
                const Size& size() const;
                bool opaque(const Point& point);
                void trans(Graphics::TransFlags::Trans _trans);

            private:
                GLint _uniformTex;
                GLint _uniformTexSize;
                GLint _uniformEggTex;
                GLint _uniformFade;
                GLint _uniformMVP;
                GLint _uniformCnt;
                GLint _uniformLight;
                GLint _uniformTrans;
                GLint _uniformDoEgg;
                GLint _uniformEggPos;
                GLint _uniformOutline;

                GLint _attribPos;
                GLint _attribTex;
                Texture* _texture;
                Graphics::TransFlags::Trans _trans = Graphics::TransFlags::Trans::NONE;
                Graphics::Shader*_shader;
        };
    }
}
