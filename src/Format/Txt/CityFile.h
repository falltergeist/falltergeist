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

#ifndef FALLTERGEIST_FORMAT_TXT_CITYFILE_H
#define FALLTERGEIST_FORMAT_TXT_CITYFILE_H

// C++ standard includes
#include <vector>

// Falltergeist includes
#include "../Dat/Item.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Dat
{
class Stream;
}

namespace Txt
{

/**
 * @brief City entrance information.
 */
struct CityEntrance
{
    /**
     * Start state of entrance (visible or not)
     */
    bool startState;
    /**
     * X coordinate on town map
     */
    int townMapX;
    /**
     * Y coordinate on town map
     */
    int townMapY;
    /**
     * Name of associated map
     */
    std::string mapName;
    /**
     * Starting elevation
     */
    int elevation;
    /**
     * Starting tile number
     */
    int tileNum;
    /**
     * Starting orientation
     */
    int orientation;
};

/**
 * @brief City information.
 */
struct City
{
    enum class Size
    {
        Small = 1, Medium, Large
    };

    std::string name;
    int worldX = 0;
    int worldY = 0;
    bool startState;
    Size size;

    int townMapArtIdx;
    int townMapLabelArtIdx;

    std::vector<CityEntrance> entrances;
};

/**
 * @brief CITY.TXT
 */
class CityFile : public Dat::Item
{
public:
    CityFile(Dat::Stream&& stream);

    const std::vector<City>& cities() const;

protected:
    std::vector<City> _cities;


    void _parseText(std::istream& istr);

    City::Size _sizeByName(std::string name) const;
};

}
}
}
#endif //FALLTERGEIST_FORMAT_TXT_CITYFILE_H
