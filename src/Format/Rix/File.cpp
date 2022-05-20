#include "../Dat/Stream.h"
#include "../Rix/File.h"

namespace Falltergeist
{
    namespace Format
    {
        namespace Rix
        {
            File::File(Dat::Stream&& stream)
            {
                stream.setPosition(0);

                // Signature
                stream.uint32();

                stream.setEndianness(ENDIANNESS::LITTLE);
                _width = stream.uint16();
                _height = stream.uint16();
                stream.setEndianness(ENDIANNESS::BIG);

                // Unknown 1
                stream.uint16();

                uint32_t palette[256];

                // Palette
                for (unsigned i = 0; i != 256; ++i)
                {
                    uint8_t r = stream.uint8();
                    uint8_t g = stream.uint8();
                    uint8_t b = stream.uint8();
                    palette[i] = (r << 26 | g << 18 | b << 10 | 0x000000FF);  // RGBA
                }

                _rgba.resize(_width * _height);

                // Data
                for (unsigned i = 0; i != (unsigned)_width * _height; ++i)
                {
                    _rgba[i] = palette[stream.uint8()];
                }
            }

            uint16_t File::width() const
            {
                return _width;
            }

            uint16_t File::height() const
            {
                return _height;
            }

            uint32_t* File::rgba()
            {
                return _rgba.data();
            }
        }
    }
}
