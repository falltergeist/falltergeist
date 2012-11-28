#ifndef FALLTERGEIST_BIOFILETYPE_H
#define FALLTERGEIST_BIOFILETYPE_H

#include <string>

namespace Falltergeist
{
class DatFileItem;

class BioFileType
{
protected:
    DatFileItem * _datFileItem;
    void _init();
    std::string * _text;
public:
    BioFileType(DatFileItem * datFileItem);
    ~BioFileType();
    const char * getText();
};

}
#endif // FALLTERGEIST_BIOFILETYPE_H
