#pragma once

#include <string>
#include "../Format/Frm/File.h"
#include "../Graphics/Point.h"
#include "../Graphics/Shader.h"
#include "../Graphics/Texture.h"
#include "../Graphics/TransFlags.h"

namespace Falltergeist
{
    namespace Graphics
    {
        class Sprite
        {
            public:
                Sprite(const std::string& filename);
                Sprite(Format::Frm::File* frm);
                void renderScaled(int x, int y, const Size& size, bool transparency = false,
                                  bool light = false, int outline = 0, unsigned int lightValue=0);
                void render(int x, int y, bool transparency = false, bool light = false, int outline = 0, unsigned int lightValue=0);
                void renderCropped(int x, int y, int dx, int dy, unsigned int width, unsigned int height, bool transparency = false,
                                   bool light = false, unsigned int lightValue=0);
                Size size() const;
                unsigned int width() const;
                unsigned int height() const;
                bool opaque(unsigned int x, unsigned int y);
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
