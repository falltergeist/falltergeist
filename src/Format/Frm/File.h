#pragma once

// Project includes
#include "../Dat/Item.h"
#include "../Frm/Direction.h"
#include "../Enums.h"

// Third-party includes

// stdlib
#include <map>
#include <vector>

namespace Falltergeist
{
    namespace Format
    {
        namespace Dat
        {
            class Stream;
        }
        namespace Pal
        {
            class File;
        }
        namespace Frm
        {
            class Direction;

            class File : public Dat::Item
            {
                public:
                    File(Dat::Stream&& stream);

                    uint32_t version() const;
                    uint16_t framesPerSecond() const;
                    uint16_t framesPerDirection() const;
                    uint16_t actionFrame() const;

                    uint16_t width() const;

                    uint16_t height() const;

                    int16_t offsetX(unsigned int direction = 0, unsigned int frame = 0) const;
                    int16_t offsetY(unsigned int direction = 0, unsigned int frame = 0) const;

                    uint32_t* rgba(Pal::File* palFile);
                    std::vector<bool>& mask(Pal::File* palFile);

                    const std::vector<Direction>& directions() const;

                protected:
                    std::vector<uint32_t> _rgba;
                    uint32_t _version = 0;
                    uint16_t _framesPerSecond = 0;
                    uint16_t _framesPerDirection = 0;
                    uint16_t _actionFrame = 0;
                    bool _animatedPalette = false;

                    std::vector<Direction> _directions;
                    std::vector<bool> _mask;
            };
        }
    }
}
