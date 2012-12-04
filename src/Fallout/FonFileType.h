#ifndef FALLTERGEIST_FONFILETYPE_H
#define FALLTERGEIST_FONFILETYPE_H

namespace Falltergeist
{
class DatFileItem;

struct FonSymbol
{
    unsigned int width;
    unsigned int dataOffset;
    char * data;
};

class FonFileType
{
protected:
    DatFileItem * _datFileItem;
    void _init();
    unsigned int _numberOfCharacters;
    unsigned int _height;
    unsigned int _distance;
    FonSymbol * _symbols;
public:
    FonFileType(DatFileItem * datFileItem);
    ~FonFileType();
};

}
#endif // FALLTERGEIST_FONFILETYPE_H
