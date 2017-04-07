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

#ifndef FALLTERGEIST_FORMAT_TXT_CSVBASEDFILE_H
#define FALLTERGEIST_FORMAT_TXT_CSVBASEDFILE_H

// C++ standard includes
#include <list>
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

namespace Ini
{
class Value;
}

namespace Txt
{

struct EndDeath
{
    /**
     * GVAR_* number for the variable controlling the slide.
     */
    int globalVar = -1;

    /**
     * value that the gvar must be >= to for this slide to be shown
     */
    int minValue = 0;

    /**
     * # of a worldmap area that has to be known in order to get this one as an option
     */
    int worldAreaKnown = -1;

    /**
     *  # of a worldmap area that has to be *not* known in order to get this one as an option
     */
    int worldAreaNotKnown = -1;

    /**
     * minimum player level in order to get this one as an option
     */
    int minLevel = 0;

    /**
     * % chance of a given line to occur
     */
    unsigned char chance = 0;

    /**
     * base filename (no path path or extension) used for the narrator voice-over and subtitles.  Maximum of 8 characters.
     */
    std::string narratorFile;
};

struct EndGame
{
    /**
     * GVAR_* number for the variable controlling the slide.
     */
    int globalVar = -1;

    /**
     * Value that the gvar must be equal to for this slide to be shown.
     */
    int value = 0;

    /**
     * Line number in art\intrface\intrface.lst of the image to use for that slide.
     * If art_num is the number for the panning desert image (currently 327),
     * then that image is panned in the direction indicated by the direction field.
     */
    int artIdx = -1;

    /**
     * Base filename (no path path or extension) used for the narrator voice-over and subtitles.  Maximum of 8 characters.
     */
    std::string narratorFile;

    /**
     * direction to pan the image.  A value of -1 pans right-to-left, 1 pans left-to-right.
     * This value is only used if the art number corresponds to the panning desert image (currently 327)
     */
    int direction = 0;
};

struct GenRep
{
    /**
     * amount game_global_vars[GVAR_PLAYER_REPUTATION] must be greater than or equal to in order for that name to be used.
     */
    int threshold;

    /**
     * number of the message in editor.msg with the reputation name.
     */
    int messageId;
};

struct Holodisk
{
    /**
     * GVAR_* number for the variable corresponding to the holodisk.
     */
    int globalVar;

    /**
     * Number of the message in pipboy.msg with the title of the holodisk.
     */
    int titleMessageId;

    /**
     * number of the message in pipboy.msg where the text for the holodisk starts.
     * Numbers in the range of (text)-(text+500) are used for that holodisk.
     */
    int textMessageId;
};

struct KarmaVar
{
    /**
     * GVAR_* number for the variable corresponding to the karma.
     */
    int globalVar;

    /**
     * number of the skilldex art (line number in art\skilldex\skilldex.lst)
     */
    int artIdx;

    /**
     * name is the number of the message in editor.msg with the karma name.
     */
    int nameMessageId;

    /**
     * description is the number of the message in editor.msg with the karma description.
     */
    int descriptionMessageId;
};

struct Quest
{
    /**
     * location is the number of the message in map.msg describing the location
     */
    int locationMessageId;

    /**
     * description is the number of the message in quest.msg with the quest description.
     */
    int descriptionMessageId;

    /**
     * gvar_index is the GVAR_* number for the variable controlling the quest.
     */
    int globalVar;

    /**
     * display_threshold is the minimum value that the gvar must be for this quest to be displayed in the pipboy.
     */
    int displayTreshold;

    /**
     * completed_threshold is the minimum value that the gvar must be for this quest to be shown as completed in the pipboy.
     */
    int completedThreshold;
};

template <typename ItemType>
class CSVBasedFile : public Dat::Item
{
public:
    CSVBasedFile(Dat::Stream&& stream);

    const std::list<ItemType>& items() const;

protected:
    void _parseText(std::istream& istr);

    /**
     * Parses next item
     * @throws std::out_of_range if row is invalid and should be skipped
     */
    ItemType _parseItem(const std::vector<Ini::Value>& row);

    std::list<ItemType> _items;
};

typedef CSVBasedFile<EndDeath> EndDeathFile;
typedef CSVBasedFile<EndGame> EndGameFile;
typedef CSVBasedFile<GenRep> GenRepFile;
typedef CSVBasedFile<Holodisk> HolodiskFile;
typedef CSVBasedFile<KarmaVar> KarmaVarFile;
typedef CSVBasedFile<Quest> QuestsFile;

}
}
}
#endif // FALLTERGEIST_FORMAT_TXT_CSVBASEDFILE_H
