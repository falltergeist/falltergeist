#ifndef FALLTERGEIST_LSTFILETYPE_H
#define FALLTERGEIST_LSTFILETYPE_H

#include <list>
#include <string>
namespace Falltergeist
{
class DatFileItem;

class LstFileType
{
protected:
    DatFileItem * _datFileItem;
    std::list<std::string *> * _strings;
public:
    LstFileType(DatFileItem * datFileItem);
    ~LstFileType();
    std::list<std::string *> * getStrings();
};

}
#endif // FALLTERGEIST_LSTFILETYPE_H
