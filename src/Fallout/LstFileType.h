#ifndef FALLTERGEIST_LSTFILETYPE_H
#define FALLTERGEIST_LSTFILETYPE_H

#include <list>
#include <string>
#include "../Engine/VirtualFile.h"
namespace Falltergeist
{

class LstFileType : public VirtualFile
{
protected:
    std::list<std::string *> * _strings;
public:
    LstFileType(VirtualFile * virtualFile);
    ~LstFileType();
    std::list<std::string *> * getStrings();
};

}
#endif // FALLTERGEIST_LSTFILETYPE_H
