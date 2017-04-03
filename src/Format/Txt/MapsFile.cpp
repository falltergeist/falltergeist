/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2012-2015 Falltergeist developers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

// C++ standard includes

// Falltergeist includes
#include "../Dat/Stream.h"
#include "../Ini/File.h"
#include "../Ini/Parser.h"
#include "../Txt/MapsFile.h"

// Third party includes

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
