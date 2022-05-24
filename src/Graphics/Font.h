#pragma once

// Project includes
#include "../Graphics/Point.h"
#include "../Graphics/Texture.h"

// Third-party includes

// stdlib
#include <memory>
#include <string>
#include <vector>

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
                Font() = default;
                virtual ~Font() = default;

                virtual unsigned short horizontalGap() = 0;
                virtual unsigned short verticalGap() = 0;
                virtual unsigned short spaceWidth() = 0;
                virtual unsigned short width() = 0;
                virtual unsigned short height() = 0;
                virtual unsigned short glyphWidth(uint8_t ch) = 0;

                virtual std::string filename() const
                {
                    return _filename;
                }

                virtual Graphics::Texture *texture()
                {
                    return _texture.get();
                }

            protected:
                std::unique_ptr<Graphics::Texture> _texture = nullptr;
                std::string _filename;
        };
    }
}
