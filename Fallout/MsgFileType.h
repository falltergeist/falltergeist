#ifndef FALLTERGEIST_MSGFILETYPE_H
#define FALLTERGEIST_MSGFILETYPE_H

#include <vector>
#include <string>

namespace Falltergeist
{
class DatFileItem;


struct MsgLine
{
    unsigned int code;
    std::string * sound;
    std::string * text;
};

class MsgFileType
{
protected:
    DatFileItem * _datFileItem;
    void _init();
    std::vector<MsgLine *> * _lines;
public:
    MsgFileType(DatFileItem * datFileItem);
    const char * getText(unsigned int number);
};

}
#endif // FALLTERGEIST_MSGFILETYPE_H
