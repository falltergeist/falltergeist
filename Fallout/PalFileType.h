#ifndef FALLTERGEIST_PALFILETYPE_H
#define FALLTERGEIST_PALFILETYPE_H

namespace Falltergeist
{
class DatFileItem;

class PalFileType
{
protected:
    DatFileItem * _datFileItem;
    bool _initialized;
    void _init();
public:
    PalFileType(DatFileItem * datFileItem);
};

}
#endif // FALLTERGEIST_PALFILETYPE_H
