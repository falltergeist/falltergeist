// Project includes
#include "../Fon/File.h"
#include "../Dat/Stream.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Format
    {
        namespace Fon
        {
            File::File(Dat::Stream&& stream)
            {
                stream.setEndianness(ENDIANNESS::LITTLE);
                stream.setPosition(0);

                _numchars = stream.uint32();
                _maximumHeight = stream.uint32();
                _horizontalGap = stream.uint32();
                _verticalGap = _horizontalGap; // i hope
                stream.skipBytes(8);

                for (unsigned int i = 0; i < _numchars; ++i)
                {
                    uint32_t width = stream.uint32();
                    uint32_t offset = stream.uint32();

                    if (width > _maximumWidth)
                    {
                        _maximumWidth = width;
                    }
                    _glyphs.push_back(Glyph(width, _maximumHeight));
                    _glyphs.back().setDataOffset(offset);
                }

                _spaceWidth = _glyphs.at(0x20).width();

                _loadRgba(stream);
            }

            void File::_loadRgba(Dat::Stream& stream)
            {
                _rgba.resize((_maximumWidth + 2) * 16 * (_maximumHeight + 2) * 16);

                for (unsigned int i=0; i < _numchars; i++)
                {
                    uint32_t glyphY = (i/16) * _maximumHeight+(i/16)*2+1;
                    uint32_t glyphX = (i%16) * _maximumWidth+(i%16)*2+1;

                    // Move glyph to bottom
                    glyphY += _maximumHeight - _glyphs.at(i).height();

                    if (_maximumHeight * _glyphs.at(i).width() != 0)
                    {
                        uint32_t offset = _glyphs.at(i).dataOffset();
                        uint32_t bytesPerLine = (_glyphs.at(i).width() + 7) / 8;
                        for (unsigned int y = 0; y < _maximumHeight; y++)
                        {
                            for (unsigned int x = 0; x < _glyphs.at(i).width(); x++)
                            {
                                // [offset + y * bytesPerLine + (x / 8)]
                                stream.setPosition(0x0414+offset + y * bytesPerLine + (x / 8));
                                uint8_t b = stream.uint8();

                                if (b & (1 << (7 - (x % 8))))
                                {
                                    _rgba[(glyphY + y)*(_maximumWidth+2)*16  + glyphX + x] = 0xFFFFFFFF;
                                }
                                else
                                {
                                    _rgba[(glyphY + y)*(_maximumWidth+2)*16  + glyphX + x] = 0x00000000;
                                }
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

            uint32_t File::maximumHeight() const
            {
                return _maximumHeight;
            }

            uint32_t File::maximumWidth() const
            {
                return _maximumWidth;
            }

            uint32_t File::horizontalGap() const
            {
                return _horizontalGap;
            }

            uint32_t File::verticalGap() const
            {
                return _horizontalGap;
            }

            uint32_t File::spaceWidth() const
            {
                return _spaceWidth;
            }
        }
    }
}
