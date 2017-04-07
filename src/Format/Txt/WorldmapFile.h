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

#ifndef FALLTERGEIST_FORMAT_TXT_WORLDMAPFILE_H
#define FALLTERGEIST_FORMAT_TXT_WORLDMAPFILE_H

// C++ standard includes
#include <map>
#include <sstream>
#include <vector>

// Falltergeist includes
#include "../Dat/Item.h"
#include "../Ini/Value.h"

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

class Lexer;

/**
 * An expression that can be evaluated to some numeric result.
 */
struct NumericExpression
{
    static const char* CONSTANT;       // a numeric constant
    static const char* PLAYER;         // a value of player stat, perk, trait or skill
    static const char* TIME_OF_DAY;    // returns current hour (0 - 23)
    static const char* GLOBAL;         // game global variable value
    static const char* RAND;           // a random value between 0 and 99

    NumericExpression() : func(CONSTANT), arg(Ini::Value("0")) {}

    NumericExpression(std::string func, const Ini::Value& arg) : func(func), arg(arg)
    {
    }

    std::string func;
    Ini::Value arg;
};

/**
 * A logical expression for conditions. Example: If(Player(Level) > 10)
 */
struct LogicalExpression
{
    enum class Operator
    {
        NONE = 0, EQ, NE, GT, LT, GTE, LTE
    };

    Operator _operator = Operator::NONE;
    NumericExpression _leftOperand;
    NumericExpression _rightOperand;
};

// Conditions consist of "sub-conditions" (Terms), delimited by "And".
typedef std::vector<LogicalExpression> Condition;

/**
 * Inventory item of object.
 */
struct InventoryItem
{
    unsigned int pid = 0;
    /**
     * True if this item should be wielded (weapon)
     */
    bool wielded = false;
    unsigned int minCount = 1;
    unsigned int maxCount = 1;
};

/**
 * An object that can be present within specific type of group with some probability.
 */
struct EncounterObject
{
    int pid = 1;
    int ratio = 0;
    int script = -1;
    int distance = -1;
    bool dead = false;
    std::vector<InventoryItem> items;
    Condition condition;
};


/**
 * Describes specific type of group a player can encounter, like "Raiders", "Rats", etc.
 */
struct Encounter
{
    /**
     * Type of positioning: surrounding, wedge, etc.
     */
    std::string position;
    /**
     * Spacing between each object.
     */
    int spacing;
    /**
     * (probably) distance to player. Can have dynamic expression as value.
     */
    NumericExpression distance;
    /**
     * All types of objects (critters) in this encounter. All ratios usually sum up to 100%, but it is not required.
     * With total ratio of 100% and 10 occurrences of this encounter in a group, total mean number of critters will be 10.
     * With 200% - mean is 20 critters, and so on.
     */
    std::vector<EncounterObject> objects;
};

/**
 * Reference to encounter type with number of occurrences (group size).
 */
struct EncounterGroup
{
    std::string encounterType;
    unsigned int minCount;
    unsigned int maxCount;
};

/**
 * @brief An entry in encounter table.
 * Describes a complete encounter type that can occur on specific sub-tiles.
 */
struct EncounterTableEntry
{
    enum class Action
    {
        NONE = 1,
        AMBUSH_PLAYER,
        FIGHTING
    };
    /**
     * True for "FIGHTING", false for "AMBUSH Player"
     */
    Action action = Action::NONE;
    /**
     * True for special encounters
     */
    bool isSpecial = false;
    /**
     * Force specific map for this encounter
     */
    std::string map = "";
    /**
     * Encounter chance in %
     */
    unsigned char chance = 0;
    int counter = -1;
    Condition condition;
    std::vector<EncounterGroup> team1;
    // used only when FIGHTING
    std::vector<EncounterGroup> team2;
};

/**
 * Encounter table describes types of encounters that can occur on each world map sub-tile.
 */
struct EncounterTable
{
    std::string lookupName;
    std::vector<std::string> maps;
    std::vector<EncounterTableEntry> encounters;
};

/**
 * Information about terrain type.
 */
struct TerrainType
{
    /**
     * Controls travel speed over this terrain type. Higher values should give slower speed.
     * Probably it is a number of frames to skip for each movement on the map.
     */
    int travelDelay;
    /**
     * A list of map names, used for random encounters on this terrain type.
     */
    std::vector<std::string> randomMaps;
};

/**
 * Worldmap subtile. Each subtile has it's own encounter table, terrain type and other properties.
 */
struct WorldmapSubtile
{
    enum class Fill
    {
        FILL_W, NO_FILL
    };
    std::string terrain;
    Fill fill;
    unsigned char morningChance;
    unsigned char afternoonChance;
    unsigned char nightChance;
    std::string encounterTable;
};

/**
 * A tile of worldmap. Has it's own image and a set of subtiles.
 */
struct WorldmapTile
{
    static const char SUBTILES_X = 7;
    static const char SUBTILES_Y = 6;
    int artIdx;
    int encounterDifficulty;
    std::string walkMaskName;
    WorldmapSubtile subtiles[SUBTILES_X][SUBTILES_Y];
};

/**
 * @brief WORLDMAP.TXT
 */
class WorldmapFile : public Dat::Item
{
public:
    WorldmapFile(Dat::Stream&& stream);

    int numHorizontalTiles;

    std::map<std::string, unsigned char> chanceNames;
    std::map<std::string, TerrainType> terrainTypes;
    std::map<std::string, Encounter> encounterTypes;
    std::map<std::string, EncounterTable> encounterTables;
    std::vector<WorldmapTile> tiles;

protected:

    void _parseText(std::istream& istr);

    EncounterObject _parseEncounterObject(const Ini::Value&);
    InventoryItem _parseInventoryItem(const std::string&);

    EncounterTableEntry _parseEncounterTableEntry(const Ini::Value&);
    EncounterGroup _parseEncounterGroup(Lexer& lexer);

    Condition _parseCondition(const std::string&);
    LogicalExpression _parseLogicalExpression(Lexer& lexer);
    NumericExpression _parseNumericExpression(Lexer& lexer);

    WorldmapSubtile _parseSubtile(const Ini::Value&);

    void _parseRange(Lexer& lexer, unsigned int& min, unsigned int& max);

    unsigned char _chanceByName(std::string);
    LogicalExpression::Operator _operatorByLexem(int lexem);
};

}
}
}
#endif // FALLTERGEIST_FORMAT_TXT_WORLDMAPFILE_H
