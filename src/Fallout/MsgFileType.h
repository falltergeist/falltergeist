#ifndef FALLTERGEIST_MSGFILETYPE_H
#define FALLTERGEIST_MSGFILETYPE_H

#include <vector>
#include <string>
#include "../Engine/VirtualFile.h"
namespace Falltergeist
{

struct MsgLine
{
    unsigned int code;
    std::string * sound;
    std::string * text;
};

class MsgFileType : public VirtualFile
{
protected:
    void _init();
    std::vector<MsgLine *> * _lines;
public:
    MsgFileType(VirtualFile * virtualFile);
    const char * getText(unsigned int number);
};

}
#endif // FALLTERGEIST_MSGFILETYPE_H
