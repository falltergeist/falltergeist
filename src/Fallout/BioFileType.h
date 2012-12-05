#ifndef FALLTERGEIST_BIOFILETYPE_H
#define FALLTERGEIST_BIOFILETYPE_H

#include "../Engine/VirtualFile.h"

namespace Falltergeist
{

class BioFileType : public VirtualFile
{
protected:
    void _init();
public:
    BioFileType(VirtualFile * virtualFile);
    ~BioFileType();
    char * getText();
};

}
#endif // FALLTERGEIST_BIOFILETYPE_H
