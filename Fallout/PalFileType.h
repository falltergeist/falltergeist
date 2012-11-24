#ifndef FALLTERGEIST_PALFILETYPE_H
#define FALLTERGEIST_PALFILETYPE_H

namespace Falltergeist
{
class DatFileItem;

struct PalColor
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    operator int();
    operator unsigned int();
};

class PalFileType
{
protected:
    PalColor * _colors;
    DatFileItem * _datFileItem;
    bool _initialized;
    void _init();
public:
    PalFileType(DatFileItem * datFileItem);
    ~PalFileType();
    PalColor * getColor(unsigned char colorIndex);
};

}
#endif // FALLTERGEIST_PALFILETYPE_H
