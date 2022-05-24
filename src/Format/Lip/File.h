#pragma once

// Project includes
#include "../Dat/Item.h"

// Third-party includes

// stdlib
#include <string>
#include <vector>

namespace Falltergeist
{
    namespace Format
    {
        namespace Dat
        {
            class Stream;
        }

        namespace Lip
        {
            class File : public Dat::Item
            {
                public:
                    File(Dat::Stream&& stream);
                    std::string acmName();
                    uint32_t phonemesCount();
                    uint32_t markersCount();
                    uint32_t acmSize();
                    std::vector<uint32_t>& timestamps();
                    std::vector<uint8_t>& phonemes();

                protected:
                    uint32_t _version;
                    uint32_t _unknown1;
                    uint32_t _unknown2;
                    uint32_t _unknown3;
                    uint32_t _acmSize;
                    uint32_t _phonemesCount;
                    uint32_t _unknown4;
                    uint32_t _markersCount;
                    uint8_t  _acmName[8];
                    uint8_t  _unknown5[4];
                    std::vector<uint8_t> _phonemes;
                    std::vector<uint32_t> _markerSamples;
                    std::vector<uint32_t> _markerTimestamps;
            };
        }
    }
}
