#ifndef FALLTERGEIST_BIOFILETYPE_H
#define FALLTERGEIST_BIOFILETYPE_H

namespace Falltergeist
{
class DatFileItem;

class BioFileType
{
protected:
    DatFileItem * _datFileItem;
    void _init();
    char * _text;
public:
    BioFileType(DatFileItem * datFileItem);
    ~BioFileType();
    char * getText();
};

}
#endif // FALLTERGEIST_BIOFILETYPE_H
