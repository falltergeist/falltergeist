#pragma once

// Project includes
#include "../Dat/Item.h"
#include "../Fon/Glyph.h"

// Third-party includes

// stdlib
#include <vector>

namespace Falltergeist
{
    namespace Format
    {
        namespace Dat
        {
            class Stream;
        }

        namespace Fon
        {
            class File : public Dat::Item
            {
                public:
                    File(Dat::Stream&& stream);
                    uint32_t* rgba();

                    const std::vector<Glyph>& glyphs() const;

                    uint32_t maximumHeight() const;
                    uint32_t maximumWidth() const;
                    uint32_t horizontalGap() const;
                    uint32_t verticalGap() const;
                    uint32_t spaceWidth() const;

                protected:
                    std::vector<Glyph> _glyphs;
                    uint32_t _maximumHeight = 0;
                    uint32_t _maximumWidth = 0;
                    uint32_t _horizontalGap = 0;
                    uint32_t _spaceWidth = 0;
                    uint32_t _verticalGap = 0;
                    std::vector<uint32_t> _rgba;
                    uint32_t _numchars;

                    void _loadRgba(Dat::Stream& stream);
            };
        }
    }
}
