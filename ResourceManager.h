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
class Surface;

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
    static Surface * getSurface(std::string filename);
};

}

#endif // FALLTERGEIST_RESOURCEMANAGER_H
