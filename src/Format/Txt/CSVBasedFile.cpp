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
#include "../Txt/CSVBasedFile.h"
#include "../Txt/CSVParser.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Txt
{

template <typename ItemType>
CSVBasedFile<ItemType>::CSVBasedFile(Dat::Stream&& stream)
{
    std::istream istr(&stream);
    _parseText(istr);
}

template <typename ItemType>
const std::list<ItemType>& CSVBasedFile<ItemType>::items() const
{
    return _items;
}

template <typename ItemType>
void CSVBasedFile<ItemType>::_parseText(std::istream& istr)
{
    CSVParser parser(istr);
    auto csv = parser.parse();
    for (auto& row : *csv)
    {
        try
        {
            _items.push_back(_parseItem(row));
        }
        catch (const std::out_of_range&)
        {
            // TODO: warnings?
        }
    }
}

template <>
EndDeath CSVBasedFile<EndDeath>::_parseItem(const std::vector<Ini::Value>& row)
{
    if (row.size() < 7)
    {
        throw std::out_of_range("Expected 7 elements.");
    }
    EndDeath item;
    item.globalVar = row[0].toInt();
    item.minValue = row[1].toInt();
    item.worldAreaKnown = row[2].toInt();
    item.worldAreaNotKnown = row[3].toInt();
    item.minLevel = row[4].toInt();
    item.chance = static_cast<unsigned char>(row[5].toInt());
    item.narratorFile = row[6].str();
    return item;
}

template <>
EndGame CSVBasedFile<EndGame>::_parseItem(const std::vector<Ini::Value>& row)
{
    if (row.size() < 4)
    {
        throw std::out_of_range("Expected at least 4 elements.");
    }
    EndGame item;
    item.globalVar = row[0].toInt();
    item.value = row[1].toInt();
    item.artIdx = row[2].toInt();
    item.narratorFile = row[3].str();
    if (row.size() > 4)
    {
        item.direction = row[4].toInt();
    }
    return item;
}

template <>
GenRep CSVBasedFile<GenRep>::_parseItem(const std::vector<Ini::Value>& row)
{
    GenRep item;
    item.threshold = row.at(0).toInt();
    item.messageId = row.at(1).toInt();
    return item;
}

template <>
Holodisk CSVBasedFile<Holodisk>::_parseItem(const std::vector<Ini::Value>& row)
{
    Holodisk item;
    item.globalVar = row.at(0).toInt();
    item.titleMessageId = row.at(1).toInt();
    item.textMessageId = row.at(2).toInt();
    return item;
}

template <>
KarmaVar CSVBasedFile<KarmaVar>::_parseItem(const std::vector<Ini::Value>& row)
{
    KarmaVar item;
    item.globalVar = row.at(0).toInt();
    item.artIdx = row.at(1).toInt();
    item.nameMessageId = row.at(2).toInt();
    item.descriptionMessageId = row.at(3).toInt();
    return item;
}

template <>
Quest CSVBasedFile<Quest>::_parseItem(const std::vector<Ini::Value>& row)
{
    if (row.size() < 5)
    {
        throw std::out_of_range("Expected 5 elements.");
    }
    Quest item;
    item.locationMessageId = row[0].toInt();
    item.descriptionMessageId = row[1].toInt();
    item.globalVar = row[2].toInt();
    item.displayTreshold = row[3].toInt();
    item.completedThreshold = row[4].toInt();
    return item;
}

template class CSVBasedFile<EndDeath>;
template class CSVBasedFile<EndGame>;
template class CSVBasedFile<GenRep>;
template class CSVBasedFile<Holodisk>;
template class CSVBasedFile<KarmaVar>;
template class CSVBasedFile<Quest>;

}
}
}
