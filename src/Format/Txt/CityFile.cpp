#include "../../Format/Dat/Stream.h"
#include "../../Format/Ini/File.h"
#include "../../Format/Txt/CityFile.h"

namespace Falltergeist
{
    namespace Format
    {
        namespace Txt
        {
            CityFile::CityFile(Dat::Stream&& stream)
            {
                std::istream istr(&stream);
                _parseText(istr);
            }

            const std::vector<City>& CityFile::cities() const
            {
                return _cities;
            }

            City::Size CityFile::_sizeByName(std::string name) const
            {
                Ini::Parser::toLower(name);
                if (name == "small")
                {
                    return City::Size::Small;
                }
                else if (name == "medium")
                {
                    return City::Size::Medium;
                }
                else
                {
                    return City::Size::Large;
                }
            }


            void CityFile::_parseText(std::istream& stream)
            {
                Ini::Parser parser(stream);
                auto file = parser.parse();
                for (auto section : file->sections())
                {
                    City city;
                    city.name = section["area_name"];
                    auto coords = section["world_pos"].toArray();
                    if (coords.size() >= 2)
                    {
                        city.worldX = coords[0].second.toInt();
                        city.worldY = coords[1].second.toInt();
                    }
                    city.startState = section["start_state"].toBool();
                    city.size = _sizeByName(section["size"]);
                    city.townMapArtIdx = section["townmap_art_idx"].toInt();
                    city.townMapLabelArtIdx = section["townmap_label_art_idx"].toInt();
                    // parse entrances
                    for (auto prop : section.listByMask("entrance_%d"))
                    {
                        auto entranceArray = prop.get().toArray();
                        if (entranceArray.size() >= 7)
                        {
                            CityEntrance entrance;
                            entrance.startState = entranceArray[0].second.toBool();
                            entrance.townMapX = entranceArray[1].second.toInt();
                            entrance.townMapY = entranceArray[2].second.toInt();
                            entrance.mapName = entranceArray[3].second.str();
                            entrance.elevation = entranceArray[4].second.toInt();
                            entrance.tileNum = entranceArray[5].second.toInt();
                            entrance.orientation = entranceArray[6].second.toInt();
                            city.entrances.push_back(entrance);
                        }
                    }
                    _cities.push_back(city);
                }
            }
        }
    }
}
