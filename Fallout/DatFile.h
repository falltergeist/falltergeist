#ifndef FALLTERGEIST_DATFILE_H
#define FALLTERGEIST_DATFILE_H

#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include "Exception.h"

namespace Falltergeist
{
class DatFileItem;
class FrmFileType;

class DatFile
{
protected:
    std::string _filename;
    std::fstream * _stream;
    std::list<DatFileItem*> * _items;
public:
    DatFile(std::string filename);
    ~DatFile();
    unsigned int size();
    std::list<DatFileItem*> * getItems();
    DatFile& seek(unsigned int uint);
    unsigned int pos(void);
    std::fstream * getStream();
    DatFileItem * getItem(std::string filename);
    DatFile& operator>> (unsigned int &value);
    DatFile& operator>> (int &value);
    DatFile& operator>> (unsigned char &value);
    DatFile& operator>> (char &value);
    DatFile& operator>> (DatFileItem &value);
    FrmFileType * getFrmFileType(std::string filename);
};

}
#endif // FALLTERGEIST_DATFILE_H
