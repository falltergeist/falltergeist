#include "PalFileType.h"

namespace Falltergeist
{

PalFileType::PalFileType(DatFileItem * datFileItem)
{
    _datFileItem = datFileItem;
    _initialized = false;
    _init();
}

void PalFileType::_init()
{
    if (_initialized) return;
    _initialized = true;
}

}
