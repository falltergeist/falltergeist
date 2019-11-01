#pragma once

#include <memory>
#include <string>
#include <vector>
#include "../Graphics/Point.h"
#include "../Graphics/Texture.h"

namespace Falltergeist
{
    namespace Graphics
    {
        struct TextSymbol
        {
            uint8_t chr;
            Point position;
        };

        class Font
        {
            public:
                Font() {}
                virtual ~Font() {}

                virtual unsigned short horizontalGap() { return 0; }
                virtual unsigned short verticalGap() { return 0; }
                virtual unsigned short spaceWidth() { return 0; }
                virtual unsigned short width() { return 0; }
                virtual unsigned short height() { return 0; }
                virtual unsigned short glyphWidth(uint8_t ch) { return 0; }

                virtual std::string filename() const { return _filename; }
                virtual Graphics::Texture *texture() { return _texture.get(); }

            protected:
                std::unique_ptr<Graphics::Texture> _texture = nullptr;
                std::string _filename;
        };
    }
}
