#ifndef FALLTERGEIST_FRMFILETYPE_H
#define FALLTERGEIST_FRMFILETYPE_H

#include "../Engine/VirtualFile.h"

namespace Falltergeist
{

struct FrmFrame {
    unsigned short width;
    unsigned short height;
    unsigned int dataSize;
    char * data;
    short offsetX;
    short offsetY;
};

struct FrmDirection {
    short shiftX;
    short shiftY;
    unsigned int dataOffset;
    FrmFrame * frames;
};

class FrmFileType : public VirtualFile
{
protected:
    void _init(); // loads all necessary data
    unsigned int _version; // frm file version
    unsigned short _framesPerSecond;  // frames per second
    unsigned short _framesPerDirection; // frames per each direction
    unsigned short _actionFrame; // number of frame on which action is occurs
    unsigned int _dataSize;
    FrmDirection * _directions;
public:
    FrmFileType(VirtualFile * virtualFile);
    ~FrmFileType();
    unsigned short getFramesPerSecond();
    unsigned short getFramesPerDirection();
    unsigned int getVersion();
    unsigned short getActionFrame();
    char * getData();
    FrmDirection * getDirections();
    void setFramesPerSecond(unsigned short framesNumber);
    void setFramesPerDirection(unsigned short framesNumber);
    void setVersion(unsigned int version);
    void setActionFrame(unsigned short frameNumber);
    void setDirections(FrmDirection * directions);
};

}
#endif // FALLTERGEIST_FRMFILETYPE_H
