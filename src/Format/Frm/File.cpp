#include <algorithm>
#include "../Enums.h"
#include "../Dat/Stream.h"
#include "../Frm/File.h"
#include "../Pal/File.h"

namespace Falltergeist
{
    namespace Format
    {
        namespace Frm
        {
            File::File(Dat::Stream&& stream)
            {
                stream.setPosition(0);

                _version = stream.uint32();
                _framesPerSecond = stream.uint16();
                _actionFrame = stream.uint16();
                _framesPerDirection = stream.uint16();

                uint16_t shiftX[6];
                uint16_t shiftY[6];
                uint32_t dataOffset[6];
                for (unsigned int i = 0; i != 6; ++i) shiftX[i] = stream.uint16();
                for (unsigned int i = 0; i != 6; ++i) shiftY[i] = stream.uint16();
                for (unsigned int i = 0; i != 6; ++i)
                {
                    dataOffset[i] = stream.uint32();
                    if (i > 0 && dataOffset[i-1] == dataOffset[i])
                    {
                        continue;
                    }

                    _directions.emplace_back();
                    auto& direction = _directions.back();
                    direction.setDataOffset(dataOffset[i]);
                    direction.setShiftX(shiftX[i]);
                    direction.setShiftY(shiftY[i]);
                }

                // for each direction
                for (auto& direction : _directions)
                {
                    // jump to frames data at frames area
                    stream.setPosition(direction.dataOffset() + 62);

                    // read all frames
                    for (unsigned i = 0; i != _framesPerDirection; ++i)
                    {
                        uint16_t width = stream.uint16();
                        uint16_t height = stream.uint16();

                        direction.frames().emplace_back(width, height);
                        auto& frame = direction.frames().back();

                        // Number of pixels for this frame
                        // We don't need this, because we already have width*height
                        stream.uint32();

                        frame.setOffsetX(stream.int16());
                        frame.setOffsetY(stream.int16());

                        // Pixels data
                        stream.readBytes(frame.data(), frame.width() * frame.height());
                    }
                }
            }

            uint32_t File::version() const
            {
                return _version;
            }

            uint16_t File::framesPerSecond() const
            {
                return _framesPerSecond;
            }

            uint16_t File::framesPerDirection() const
            {
                return _framesPerDirection;
            }

            uint16_t File::actionFrame() const
            {
                return _actionFrame;
            }

            const std::vector<Direction>& File::directions() const
            {
                return _directions;
            }

            uint16_t File::width() const
            {
                return std::max_element(_directions.begin(), _directions.end(), [](const Direction& a, const Direction& b)
                {
                    return a.width() < b.width();
                })->width();
            }

            uint16_t File::height() const
            {
                uint16_t height = 0;
                for (auto& direction : _directions)
                {
                    height += direction.height();
                }
                return height;
            }

            uint32_t* File::rgba(Pal::File* palFile)
            {
                // TODO: this looks like a getter, which in fact creates _rgba.
                // Moreover, the content of _rgba depends on the specific palFile that was provided the first time
                // This is clearly bad semantics
                if (!_rgba.empty()) return _rgba.data();

                _rgba.resize(width()*height());

                uint16_t w = width();

                size_t positionY = 1;
                for (auto& direction : _directions)
                {
                    size_t positionX = 1;
                    for (auto& frame : direction.frames())
                    {
                        // TODO: more efficient way to generate texture?
                        for (uint16_t y = 0; y != frame.height(); ++y)
                        {
                            for (uint16_t x = 0; x != frame.width(); ++x)
                            {
                                _rgba[((y + positionY)*w) + x + positionX] = *palFile->color(frame.index(x, y));
                            }
                        }
                        positionX += frame.width() + 2;
                    }
                    positionY += direction.height();
                }
                return _rgba.data();
            }

            std::vector<bool>& File::mask(Pal::File* palFile)
            {
                if (!_mask.empty()) return _mask;

                uint16_t w = width();
                uint16_t h = height();

                _mask.resize(w*h, true);

                unsigned positionY = 1;
                for (auto& direction : _directions)
                {
                    unsigned positionX = 1;
                    for (auto& frame : direction.frames())
                    {
                        // TODO: optimize
                        for (unsigned y = 0; y != frame.height(); ++y)
                        {
                            for (unsigned x = 0; x != frame.width(); ++x)
                            {
                                _mask[((y + positionY)*w) + x + positionX] = (palFile->color(frame.index(x, y))->alpha() > 0);
                            }
                        }
                        positionX += frame.width() + 2;
                    }
                    positionY += direction.height();
                }
                return _mask;
            }

            int16_t File::offsetX(unsigned int direction, unsigned int frame) const
            {
                if (direction >= _directions.size()) direction = 0;
                return _directions.at(direction).frames().at(frame).offsetX();
            }

            int16_t File::offsetY(unsigned int direction, unsigned int frame) const
            {
                if (direction >= _directions.size()) direction = 0;
                return _directions.at(direction).frames().at(frame).offsetY();
            }
        }
    }
}
