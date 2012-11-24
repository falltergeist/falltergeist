#include "PalFileType.h"
#include "DatFileItem.h"
#include <iostream>

namespace Falltergeist
{

PalFileType::PalFileType(DatFileItem * datFileItem)
{
    _colors = new PalColor[256];
    _datFileItem = datFileItem;
    _initialized = false;
    _init();
}

PalFileType::~PalFileType()
{
    delete [] _colors; _colors = 0;
}

/**
 * Reads data from pal file
 * @brief PalFileType::_init
 */
void PalFileType::_init()
{
    if (_initialized) return;
    // reading colors from file
    for (unsigned char i = 0; i < 255; i++)
    {
        (*_datFileItem) >> _colors[i].red >> _colors[i].green >> _colors[i].blue;
    }
    _initialized = true;
}

/**
 * Returns color by given index
 * @brief PalFileType::getColor
 * @param colorIndex
 * @return
 */
PalColor * PalFileType::getColor(unsigned char colorIndex)
{
    return &_colors[colorIndex];
}

}
