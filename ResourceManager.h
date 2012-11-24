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
    std::list<DatFile *> * _datFiles;
public:
    ResourceManager();
    DatFileItem * getDatFileItem(std::string filename);
    FrmFileType * getFrmFileType(std::string filename);
    PalFileType * getPalFileType(std::string filename);
    Surface * getSurface(std::string filename);
};

}

#endif // FALLTERGEIST_RESOURCEMANAGER_H
