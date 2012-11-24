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
    static Surface * getSurface(std::string filename);
};

}

#endif // FALLTERGEIST_RESOURCEMANAGER_H
