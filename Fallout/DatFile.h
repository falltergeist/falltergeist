#ifndef FALLTERGEIST_DATFILE_H
#define FALLTERGEIST_DATFILE_H

#include <list>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include "Engine/Exception.h"

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

class DatFile
{
protected:
    std::string _filename;
    std::fstream * _stream;
    std::list<DatFileItem*> * _items;  // items list
    std::map<std::string, FrmFileType *> * _frmFiles; // opened FRM Files
    std::map<std::string, PalFileType *> * _palFiles; // opened PAL Files
    std::map<std::string, LstFileType *> * _lstFiles; // opened LST Files
    std::map<std::string, FonFileType *> * _fonFiles; // opened FON Files
    std::map<std::string, AafFileType *> * _aafFiles; // opened AAF Files
    std::map<std::string, GcdFileType *> * _gcdFiles; // opened GCD Files
    std::map<std::string, MsgFileType *> * _msgFiles; // opened MSG Files
    std::map<std::string, BioFileType *> * _bioFiles; // opened BIO Files
public:
    DatFile(std::string filename);
    ~DatFile();
    unsigned int size();
    std::fstream * getStream();
    std::list<DatFileItem*> * getItems();
    DatFile& seek(unsigned int uint);
    unsigned int pos(void);
    void setStream(std::fstream * stream);
    DatFileItem * getItem(std::string filename);
    DatFile& operator>> (unsigned int &value);
    DatFile& operator>> (int &value);
    DatFile& operator>> (unsigned char &value);
    DatFile& operator>> (char &value);
    DatFile& operator>> (DatFileItem &value);
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
