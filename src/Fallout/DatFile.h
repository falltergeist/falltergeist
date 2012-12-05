#ifndef FALLTERGEIST_DATFILE_H
#define FALLTERGEIST_DATFILE_H

#include "../Engine/File.h"
#include <list>
#include <map>
#include <string>
#include <iostream>
#include <fstream>

namespace Falltergeist
{
class DatFileItem;
class FrmFileType;
class PalFileType;
class LstFileType;
class FonFileType;
class AafFileType;
class GcdFileType;
class MsgFileType;
class BioFileType;

class DatFile : public File
{
protected:
    std::list<VirtualFile *> * _items;  // items list
    std::map<std::string, FrmFileType *> * _frmFiles; // opened FRM Files
    std::map<std::string, PalFileType *> * _palFiles; // opened PAL Files
    std::map<std::string, LstFileType *> * _lstFiles; // opened LST Files
    std::map<std::string, FonFileType *> * _fonFiles; // opened FON Files
    std::map<std::string, AafFileType *> * _aafFiles; // opened AAF Files
    std::map<std::string, GcdFileType *> * _gcdFiles; // opened GCD Files
    std::map<std::string, MsgFileType *> * _msgFiles; // opened MSG Files
    std::map<std::string, BioFileType *> * _bioFiles; // opened BIO Files
public:
    DatFile(const char * filename);
    virtual ~DatFile();
    std::list<VirtualFile *> * getItems();
    VirtualFile * getItem(std::string filename);
    FrmFileType * getFrmFileType(std::string filename);
    PalFileType * getPalFileType(std::string filename);
    LstFileType * getLstFileType(std::string filename);
    FonFileType * getFonFileType(std::string filename);
    AafFileType * getAafFileType(std::string filename);
    GcdFileType * getGcdFileType(std::string filename);
    MsgFileType * getMsgFileType(std::string filename);
    BioFileType * getBioFileType(std::string filename);
};

}
#endif // FALLTERGEIST_DATFILE_H
