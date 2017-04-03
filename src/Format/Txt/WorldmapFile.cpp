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
#include <sstream>

// Falltergeist includes
#include "../Dat/Stream.h"
#include "../Ini/File.h"
#include "../Ini/Parser.h"
#include "../Txt/Lexer.h"
#include "../Txt/WorldmapFile.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Txt
{

const char* NumericExpression::CONSTANT    = "";               // a numeric constant
const char* NumericExpression::PLAYER      = "Player";         // a value of player stat, perk, trait or skill
const char* NumericExpression::TIME_OF_DAY = "time_of_day";    // returns current hour (0 - 23)
const char* NumericExpression::GLOBAL      = "Global";         // game global variable value
const char* NumericExpression::RAND        = "Rand";           // a random value between 0 and 99

void WorldmapFile::_parseText(std::istream& stream)
{
    Ini::Parser parser(stream);
    auto file = parser.parse();

    for (auto pairs : file->section("Data"))
    {
        auto& str = pairs.second.str();
        if (str[str.size() - 1] == '%')
        {
            chanceNames[pairs.first] = static_cast<unsigned char>(pairs.second.toInt());
        }
    }
    for (auto pair : file->section("Data")["terrain_types"].toArray())
    {
        TerrainType terType = TerrainType();
        terType.travelDelay = pair.second.toInt();
        std::string sect = "Random Maps: " + pair.first;
        if (file->hasSection(sect))
        {
            for (auto& ref : file->section(sect).listByMask("map_%02d"))
            {
                terType.randomMaps.push_back(ref.get().str());
            }
        }
        terrainTypes[pair.first] = std::move(terType);
    }
    numHorizontalTiles = file->section("Tile Data")["num_horizontal_tiles"].toInt();
    for (auto section : file->sections())
    {
        const std::string encStr = "Encounter:";
        auto pos = section.name().find(encStr);
        if (pos == 0)
        {
            std::string name = section.name().substr(encStr.size(), std::string::npos);
            parser.trim(name);
            Encounter enc = Encounter();
            for (auto pair : section["position"].toArray())
            {
                parser.toLower(pair.first);
                if (pair.first.size() == 0)
                {
                    enc.position = pair.second.str();
                }
                else if (pair.first == "spacing")
                {
                    enc.spacing = pair.second.toInt();
                }
                else if (pair.first == "distance")
                {
                    try
                    {
                        Lexer lexer(pair.second.str());
                        enc.distance = _parseNumericExpression(lexer);
                    }
                    catch (const std::ios::failure&)
                    {
                        // TODO: warnings
                    }
                }
            }
            for (auto& ref : section.listByMask("type_%02d"))
            {
                enc.objects.push_back(_parseEncounterObject(ref.get()));
            }
            encounterTypes[name] = std::move(enc);
        }
        else if (section.name().find("Encounter Table") == 0)
        {
            EncounterTable table = EncounterTable();
            table.lookupName = section["lookup_name"];
            for (auto pair : section["maps"].toArray())
            {
                std::string mapName = pair.second.str();
                Ini::Parser::trim(mapName);
                table.maps.push_back(std::move(mapName));
            }
            for (auto& ref : section.listByMask("enc_%02d"))
            {
                table.encounters.push_back(_parseEncounterTableEntry(ref.get()));
            }
            encounterTables[table.lookupName] = std::move(table);
        }
        else if (section.name().find("Tile") == 0 && section.name() != "Tile Data")
        {
            WorldmapTile tile = WorldmapTile();
            tile.artIdx = section["art_idx"].toInt();
            tile.encounterDifficulty = section["encounter_difficulty"].toInt();
            tile.walkMaskName = section["walk_mask_name"];
            for (int i = 0; i < WorldmapTile::SUBTILES_X; i++)
            {
                for (int j = 0; j < WorldmapTile::SUBTILES_Y; j++)
                {
                    tile.subtiles[i][j] = _parseSubtile(section[std::to_string(i) + "_" + std::to_string(j)]);
                }
            }
            tiles.push_back(std::move(tile));
        }
    }
}

EncounterObject WorldmapFile::_parseEncounterObject(const Ini::Value& val)
{
    EncounterObject obj = EncounterObject();
    for (auto pair : val.toArray())
    {
        Ini::Parser::toLower(pair.first);
        if (pair.first == "ratio")
        {
            obj.ratio = pair.second.toInt();
        }
        else if (pair.first == "pid")
        {
            obj.pid = pair.second.toInt();
        }
        else if (pair.first == "script")
        {
            obj.script = pair.second.toInt();
        }
        else if (pair.first == "distance")
        {
            obj.distance = pair.second.toInt();
        }
        else if (pair.first == "item")
        {
            obj.items.push_back(_parseInventoryItem(pair.second.str()));
        }
        else if (pair.second.str() == "Dead")
        {
            obj.dead = true;
        }
        else if (pair.second.str().find("If") != std::string::npos)
        {
            obj.condition = _parseCondition(pair.second.str());
        }
    }
    return obj;
}

InventoryItem WorldmapFile::_parseInventoryItem(const std::string& value)
{
    InventoryItem item;
    Lexer lexer(value);
    try
    {
        _parseRange(lexer, item.minCount, item.maxCount);
        if (!lexer.expect(Lexer::T_CONSTANT))
        {
            throw std::ios::failure("Item PID expected.");
        }
        item.pid = lexer.last().intData;
        if ((lexer.expect('{') || lexer.expect('(')) && lexer.expect(Lexer::T_IDENTIFIER))
        {
            std::string specifier = lexer.last().data;
            Ini::Parser::toLower(specifier);
            if (specifier == "wielded")
            {
                item.wielded = true;
            }
            if (!lexer.expect('{') && !lexer.expect('('))
            {
                throw std::ios::failure("'}' or ')' expected.");
            }
        }
    }
    catch (const std::ios::failure&)
    {
        // TODO: warnings?
    }
    return item;
}

EncounterTableEntry WorldmapFile::_parseEncounterTableEntry(const Ini::Value& value)
{
    EncounterTableEntry entry;
    for (auto pair : value.toArray())
    {
        Ini::Parser::toLower(pair.first);
        if (pair.first == "chance")
        {
            entry.chance = (unsigned char)pair.second.toInt();
        }
        else if (pair.first == "counter")
        {
            entry.counter = pair.second.toInt();
        }
        else if (pair.first == "map")
        {
            entry.map = pair.second;
        }
        else if (pair.second.str() == "Special")
        {
            entry.isSpecial = true;
        }
        else if (pair.first == "enc")
        {
            // main encounter definition...
            Lexer lexer(pair.second.str());
            try
            {
                do
                {
                    entry.team1.push_back(_parseEncounterGroup(lexer));
                }
                while (lexer.expect(Lexer::T_AND));

                if (lexer.expect(Lexer::T_IDENTIFIER))
                {
                    if (lexer.last().data == "AMBUSH")
                    {
                        entry.action = EncounterTableEntry::Action::AMBUSH_PLAYER;
                    }
                    else if (lexer.last().data == "FIGHTING")
                    {
                        entry.action = EncounterTableEntry::Action::FIGHTING;
                    }
                    else
                    {
                        throw std::ios::failure("Invalid action: " + lexer.last().data);
                    }

                    do
                    {
                        entry.team2.push_back(_parseEncounterGroup(lexer));
                    }
                    while (lexer.expect(Lexer::T_AND));
                }
            }
            catch (const std::ios::failure&)
            {
                // TODO: warnings?
            }
        }
        else if (pair.second.str().find("If") == 0)
        {
            entry.condition = _parseCondition(pair.second);
        }
    }
    return entry;
}

EncounterGroup WorldmapFile::_parseEncounterGroup(Lexer& lexer)
{
    EncounterGroup grp;
    _parseRange(lexer, grp.minCount, grp.maxCount);
    if (!lexer.expect(Lexer::T_IDENTIFIER)) {
        throw std::ios::failure("Identifier expected.");
    }
    grp.encounterType = lexer.last().data;
    return grp;
}

Condition WorldmapFile::_parseCondition(const std::string& value)
{
    Condition cond;
    Lexer lexer(value);
    try
    {
        do
        {
            cond.push_back(_parseLogicalExpression(lexer));
        }
        while (lexer.expect(Lexer::T_AND));
    }
    catch (const std::ios::failure&)
    {
        // TODO: warnings?
    }
    return cond;
}

LogicalExpression WorldmapFile::_parseLogicalExpression(Lexer& lexer)
{
    LogicalExpression exp;
    
    if (!lexer.expect(Lexer::T_IF))
    {
        throw std::ios::failure("'If' expected.");
    }
    if (!lexer.expect('('))
    {
        throw std::ios::failure("'(' expected.");
    }
    exp._leftOperand = _parseNumericExpression(lexer);
    exp._operator = _operatorByLexem(lexer.lex());
    if (exp._operator != LogicalExpression::Operator::NONE)
    {
        exp._rightOperand = _parseNumericExpression(lexer);
    }
    else
    {
        lexer.unLex();
    }
    if (!lexer.expect(')'))
    {
        throw std::ios::failure("')' expected.");
    }
    return exp;
}

NumericExpression WorldmapFile::_parseNumericExpression(Lexer& lexer)
{
    NumericExpression exp;
    if (lexer.expect(Lexer::T_IDENTIFIER))
    {
        exp.func = lexer.last().data;
        if (lexer.expect('('))
        {
            bool negate = lexer.expect('-');
            if (!lexer.expect(Lexer::T_CONSTANT) && !lexer.expect(Lexer::T_IDENTIFIER))
            {
                throw std::ios::failure("Identified or constant expected.");
            }
            exp.arg = negate ? ('-' + lexer.last().data) : lexer.last().data;
            if (!lexer.expect(')'))
            {
                throw std::ios::failure("')' expected.");
            }
        }
    }
    else
    {
        bool negate = lexer.expect('-');
        if (lexer.expect(Lexer::T_CONSTANT))
        {
            exp.func = NumericExpression::CONSTANT;
            exp.arg = negate ? ('-' + lexer.last().data) : lexer.last().data;
        }
        else
        {
            throw std::ios::failure("Constant expected");
        }
    }
    return exp;
}

WorldmapSubtile WorldmapFile::_parseSubtile(const Ini::Value& value)
{
    WorldmapSubtile subtile = WorldmapSubtile();
    auto array = value.toArray();
    if (array.size() >= 6)
    {
        subtile.terrain = array[0].second;
        subtile.fill = (array[1].second.str() == "Fill_W")
                       ? WorldmapSubtile::Fill::FILL_W
                       : WorldmapSubtile::Fill::NO_FILL;
        subtile.morningChance = _chanceByName(array[2].second);
        subtile.afternoonChance = _chanceByName(array[3].second);
        subtile.nightChance = _chanceByName(array[4].second);
        subtile.encounterTable = array[5].second;
    }
    return subtile;
}

void WorldmapFile::_parseRange(Lexer& lexer, unsigned int& min, unsigned int& max)
{
    if (lexer.expect('('))
    {
        if (!lexer.expect(Lexer::T_CONSTANT))
        {
            throw std::ios::failure("Number expected");
        }
        min = lexer.last().intData;
        if (lexer.expect('-') && lexer.expect(Lexer::T_CONSTANT))
        {
            max = lexer.last().intData;
        }
        else
        {
            max = min;
        }
        if (lexer.lex() != ')')
        {
            throw std::ios::failure("')' expected");
        }
    }
    else
    {
        min = max = 1;
    }
}

unsigned char WorldmapFile::_chanceByName(std::string name)
{
    Ini::Parser::toLower(name);
    auto it = chanceNames.find(name);
    if (it != chanceNames.end())
    {
        return it->second;
    }
    return 0;
}

LogicalExpression::Operator WorldmapFile::_operatorByLexem(int lexem)
{
    switch (lexem)
    {
        case '>':
            return LogicalExpression::Operator::GT;
        case '<':
            return LogicalExpression::Operator::LT;
        case Lexer::T_GREATER_EQUAL:
            return LogicalExpression::Operator::GTE;
        case Lexer::T_LESS_EQUAL:
            return LogicalExpression::Operator::LTE;
        case Lexer::T_EQUAL:
            return LogicalExpression::Operator::EQ;
        default:
            return LogicalExpression::Operator::NONE;
    }
}

WorldmapFile::WorldmapFile(Dat::Stream&& stream)
{
    std::istream istr(&stream);
    _parseText(istr);
}

}
}
}
