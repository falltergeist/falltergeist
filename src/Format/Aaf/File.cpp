// Project includes
#include "../../Format/Dat/Stream.h"
#include "../../Format/Aaf/File.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Format
    {
        namespace Aaf
        {
            File::File(Dat::Stream&& stream)
            {
                stream.setPosition(0);

                _signature     = stream.uint32(); // should be "AAFF"
                _maximumHeight = stream.uint16();
                _horizontalGap = stream.uint16();
                _spaceWidth    = stream.uint16();
                _verticalGap   = stream.uint16();

                // Glyphs info
                for (unsigned i = 0; i != 256; ++i)
                {
                    uint16_t width  = stream.uint16();
                    uint16_t height = stream.uint16();
                    uint32_t offset = stream.uint32();

                    if (width > _maximumWidth)
                    {
                        _maximumWidth = width;
                    }

                    _glyphs.push_back(Glyph(width, height));
                    _glyphs.back().setDataOffset(offset);
                }

                _loadRgba(stream);
            }

            void File::_loadRgba(Dat::Stream& stream)
            {
                //_rgba = new uint32_t[_maximumWidth * _maximumHeight * 256]();
                // leave 1 px around glyph
                _rgba.resize((_maximumWidth + 2) * 16 * (_maximumHeight + 2) * 16);

                for (unsigned i = 0; i != 256; ++i)
                {
                    uint32_t glyphY = (i/16) * _maximumHeight+(i/16)*2+1;
                    uint32_t glyphX = (i%16) * _maximumWidth+(i%16)*2+1;

                    // Move glyph to bottom
                    glyphY += _maximumHeight - _glyphs.at(i).height();

                    stream.setPosition(0x080C + _glyphs.at(i).dataOffset());

                    for (uint16_t y = 0; y != _glyphs.at(i).height(); ++y)
                    {
                        for (uint16_t x = 0; x != _glyphs.at(i).width(); ++x)
                        {
                            uint8_t byte = stream.uint8();
                            if (byte != 0)
                            {
                                uint8_t alpha = 0;
                                switch (byte)
                                {
                                    case 7:
                                        alpha = 255;
                                        break;
                                    case 6:
                                        alpha = 219;
                                        break;
                                    case 5:
                                        alpha = 169;
                                        break;
                                    case 4:
                                        alpha = 145;
                                        break;
                                    case 3:
                                        alpha = 116;
                                        break;
                                    case 2:
                                        alpha = 66;
                                        break;
                                    case 1:
                                    default:
                                        alpha = 30;
                                        break;
                                }

                                _rgba[(glyphY + y)*((_maximumWidth+2)*16)  + glyphX + x] = 0xFFFFFF00 | alpha;
                            }
                        }
                    }
                }
            }

            uint32_t* File::rgba()
            {
                return _rgba.data();
            }

            const std::vector<Glyph>& File::glyphs() const
            {
                return _glyphs;
            }

            uint16_t File::horizontalGap() const
            {
                return _horizontalGap;
            }

            uint16_t File::maximumHeight() const
            {
                return _maximumHeight;
            }

            uint16_t File::maximumWidth() const
            {
                return _maximumWidth;
            }

            uint16_t File::spaceWidth() const
            {
                return _spaceWidth;
            }

            uint16_t File::verticalGap() const
            {
                return _verticalGap;
            }
        }
    }
}
