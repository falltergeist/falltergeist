#include "../Dat/Stream.h"
#include "../Ini/File.h"
#include "../Txt/MapsFile.h"

namespace Falltergeist
{
    namespace Format
    {
        namespace Txt
        {
            MapsFile::MapsFile(Dat::Stream&& stream)
            {
                std::istream istr(&stream);
                _parseText(istr);
            }

            const std::vector<Map>& MapsFile::maps() const
            {
                return _maps;
            }

            void MapsFile::_parseText(std::istream& stream)
            {
                Ini::Parser parser(stream);
                auto file = parser.parse();
                for (auto section : file->sections())
                {
                    Map map = Map();
                    map.name = section["map_name"];
                    map.lookupName = section["lookup_name"];
                    map.music = section["music"];
                    parser.toLower(map.music);
                    for (auto pair : section["ambient_sfx"].toArray())
                    {
                        parser.toLower(pair.first);
                        map.ambientSfx[pair.first] = static_cast<unsigned char>(pair.second.toInt());
                    }
                    map.saved = section["saved"].toBool();
                    auto canRest = section["can_rest_here"].toArray();
                    if (canRest.size() >= Map::NUM_ELEVATIONS)
                    {
                        for (int i = 0; i < Map::NUM_ELEVATIONS; i++)
                        {
                            map.canRestHere[i] = canRest[i].second.toBool();
                        }
                    }

                    for (auto prop : section.listByMask("random_start_point_%d"))
                    {
                        MapStartPoint point = MapStartPoint();
                        for (auto pair : prop.get().toArray())
                        {
                            if (pair.first == "elev")
                            {
                                point.elevation = pair.second.toInt();
                            }
                            else if (pair.first == "tile_num")
                            {
                                point.tileNum = pair.second.toInt();
                            }
                        }
                        map.randomStartPoints.push_back(point);
                    }

                    _maps.push_back(map);
                }
            }
        }
    }
}
