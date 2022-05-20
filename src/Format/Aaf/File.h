#pragma once

#include <cstdint>
#include <memory>
#include <vector>
#include "../../Format/Aaf/Glyph.h"
#include "../../Format/Dat/Item.h"

namespace Falltergeist
{
    namespace Format
    {
        namespace Dat
        {
            class Stream;
        }

        namespace Aaf
        {
            class File : public Dat::Item
            {
                public:
                    File(Dat::Stream&& stream);

                    uint32_t* rgba();

                    const std::vector<Glyph>& glyphs() const;

                    uint16_t maximumHeight() const;
                    uint16_t maximumWidth() const;
                    uint16_t horizontalGap() const;
                    uint16_t verticalGap() const;
                    uint16_t spaceWidth() const;

                protected:
                    std::vector<Glyph> _glyphs;
                    uint32_t _signature;
                    uint16_t _maximumHeight = 0;
                    uint16_t _maximumWidth = 0;
                    uint16_t _horizontalGap = 0;
                    uint16_t _spaceWidth = 0;
                    uint16_t _verticalGap = 0;
                    std::vector<uint32_t> _rgba;

                    void _loadRgba(Dat::Stream& stream);
            };
        }
    }
}
