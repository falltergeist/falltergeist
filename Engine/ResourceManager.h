#ifndef FALLTERGEIST_RESOURCEMANAGER_H
#define FALLTERGEIST_RESOURCEMANAGER_H

#include <list>
#include <string>

namespace Falltergeist
{
class DatFile;
class DatFileItem;
class FrmFileType;
class PalFileType;
class LstFileType;
class FonFileType;
class AafFileType;
class GcdFileType;
class MsgFileType;
class BioFileType;
class Surface;

const char * _t(unsigned int number, const char * filename);

class ResourceManager
{
protected:
    static std::list<DatFile *> * _datFiles;
public:
    ResourceManager();
    static DatFileItem * getDatFileItem(std::string filename);
    static FrmFileType * getFrmFileType(std::string filename);
    static PalFileType * getPalFileType(std::string filename);
    static LstFileType * getLstFileType(std::string filename);
    static FonFileType * getFonFileType(std::string filename);
    static AafFileType * getAafFileType(std::string filename);
    static GcdFileType * getGcdFileType(std::string filename);
    static MsgFileType * getMsgFileType(std::string filename);
    static BioFileType * getBioFileType(std::string filename);
    static Surface * getSurface(std::string filename, int x = 0, int y = 0);
};

}

#endif // FALLTERGEIST_RESOURCEMANAGER_H
