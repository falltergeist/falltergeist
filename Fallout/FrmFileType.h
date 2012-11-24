#ifndef FRMFILETYPE_H
#define FRMFILETYPE_H

#include <string>
#include "Fallout/DatFileItem.h"

namespace Falltergeist
{

struct FrmFrame {
    unsigned short width;
    unsigned short height;
    unsigned int dataSize;
    signed short offsetX;
    signed short offsetY;
};

struct FrmDirection {
    signed short shiftX;
    signed short shiftY;
    unsigned int dataOffset;
    FrmFrame * frames;
};


class FrmFileType : public DatFileItem
{

protected:
    DatFile * _datFile;
    bool _readed;
    void _init();
    unsigned int _version; // Frm file version
    unsigned short _fps;  // Frames per second
    unsigned short _actionFrame;
    unsigned short _framesPerDirection;
    FrmDirection * _directions;
    unsigned int _dataSize;

public:
    FrmFileType(std::string fileName, DatFile * datFile);
    ~FrmFileType();
    unsigned int getVersion();
    void setVersion(unsigned int version);
    unsigned short getFps();
    void setFps(unsigned short fps);
    FrmDirection * getDirections();

};

}
#endif // FRMFILETYPE_H
