// Project includes
#include "../Dat/Stream.h"
#include "../Pal/Color.h"
#include "../Pal/File.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Format
    {
        namespace Pal
        {
            File::File(Dat::Stream&& stream)
            {
                stream.setPosition(3);

                _colors.emplace_back(0, 0, 0, 0); // zero color (transparent)

                for (unsigned i = 1; i != 256; ++i)
                {
                    uint8_t r = stream.uint8();
                    uint8_t g = stream.uint8();
                    uint8_t b = stream.uint8();
                    _colors.emplace_back(r, g, b);
                }

                // I guess this section requires a little explanation
                // Thing is, original engine uses indexed/paletted textures
                // and palette contains 'magic' animated colors
                // we can, ofcourse use paletted textures, and different shaders for rgba (png) textures,
                // but, while hackish, this is probably simpler/faster.
                // So, we have 6 groups of animations, with 1-6 colors each
                // Red and Alpha components denotes 'magical' color,
                // while Green denotes group, and Blue - index.
                // Because in OpenGL colors are floats from 0.0 to 1.0
                // we need numbers, that being divided by 255 will give 'round' values,
                // this number is 51.
                // Then, in shaders, we'll calculate resulting index by multiplying
                // original value by 255 and then dividing by 51.
                // So, color 0.2 will give: 0.2*255/51=1, all we need now is to subtract 1.
                // So resulting formulae is: index = color.b * 255 / 51 -1;

                for (unsigned i = 229; i<=254; ++i)
                {
                    // magic, sorry
                    _colors.at(i).setAlpha(51);
                    _colors.at(i).setRed(153);
                    _colors.at(i).nomod();
                }

                // SLIME
                for (unsigned int i=229; i<=232; i++)
                {
                    _colors.at(i).setGreen(0); //
                    _colors.at(i).setBlue((i-229)*51);
                }

                // MONITORS
                for (unsigned int i=233; i<=237; i++)
                {
                    _colors.at(i).setGreen(51); //
                    _colors.at(i).setBlue((i-233)*51);
                }

                // SLOW FIRE
                for (unsigned int i=238; i<=242; i++)
                {
                    _colors.at(i).setGreen(102); //
                    _colors.at(i).setBlue((i-238)*51);
                }

                // FAST FIRE
                for (unsigned int i=243; i<=247; i++)
                {
                    _colors.at(i).setGreen(153); //
                    _colors.at(i).setBlue((i-243)*51);
                }

                // SHORE
                for (unsigned int i=248; i<=253; i++)
                {
                    _colors.at(i).setGreen(204); //
                    _colors.at(i).setBlue((i-248)*51);
                }

                // ALARM
                _colors.at(254).setGreen(255); //
                _colors.at(254).setBlue(0);
            }

            const Color* File::color(unsigned index) const
            {
                return &_colors.at(index);
            }
        }
    }
}
