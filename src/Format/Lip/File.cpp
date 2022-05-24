// Project includes
#include "../../Exception.h"
#include "../../Format/Dat/Stream.h"
#include "../../Format/Lip/File.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Format
    {
        namespace Lip
        {
            File::File(Dat::Stream&& stream)
            {
                stream.setPosition(0);
                stream >> _version;
                if (_version != 2)
                {
                    throw Exception("Invalid LIP file.");
                }
                stream >> _unknown1 >> _unknown2 >> _unknown3;
                stream >> _acmSize >> _phonemesCount;
                stream >> _unknown4;
                stream >> _markersCount;
                stream.readBytes(_acmName, 8);
                stream.readBytes(_unknown5, 4);

                for (uint32_t i=0; i < _phonemesCount; i++)
                {
                    uint8_t phoneme = 0;
                    stream >> phoneme;
                    _phonemes.push_back(phoneme);
                }

                for (uint32_t i=0; i < _markersCount; i++)
                {
                    uint32_t stype = 0, smarker = 0;
                    stream >> stype >> smarker;
                    _markerSamples.push_back(smarker);
                    _markerTimestamps.push_back(smarker*1000 / 22050 /2); //ms
                }
            }

            std::string File::acmName()
            {
                return std::string((char*)_acmName)+std::string((char*)_unknown5);
            }

            uint32_t File::phonemesCount()
            {
                return _phonemesCount;
            }

            uint32_t File::markersCount()
            {
                return _markersCount;
            }

            uint32_t File::acmSize()
            {
                return _acmSize;
            }

            std::vector<uint32_t>& File::timestamps()
            {
                return _markerTimestamps;
            }

            std::vector<uint8_t> &File::phonemes()
            {
                return _phonemes;
            }
        }
    }
}
