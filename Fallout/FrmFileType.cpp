#include "Fallout/FrmFileType.h"
#include "Fallout/DatFile.h"

namespace Falltergeist
{

FrmFileType::FrmFileType(DatFileItem * datFileItem)
{
    _datFileItem = datFileItem;
    _initialized = false;
}

FrmFileType::~FrmFileType()
{
    delete [] _directions;
}

void FrmFileType::_init()
{
    if (_initialized) return;
    _datFileItem->seek(0);
    (*_datFileItem) >> _version >> _fps >> _actionFrame >> _framesPerDirection;

    _directions = new FrmDirection[6];

    for (unsigned char i = 0; i < 6; i++) (*_datFileItem) >> _directions[i].shiftX;
    for (unsigned char i = 0; i < 6; i++) (*_datFileItem) >> _directions[i].shiftY;
    for (unsigned char i = 0; i < 6; i++) (*_datFileItem) >> _directions[i].dataOffset;

    (*_datFileItem) >> _dataSize;
    // Reading directions
    for (unsigned char i = 0; i < 6; i++)
    {
        // if direction is the same as first
        if (i > 0) if (_directions[i].dataOffset == _directions[0].dataOffset) {
            //std::cout << "Direction same as first... skiping" << std::endl;
            _directions[i] = _directions[0];
            continue;
        }

        _directions[i].frames = new FrmFrame[_framesPerDirection];
        for (unsigned short j = 0; j < _framesPerDirection; j++)
        {
            (*_datFileItem) >> _directions[i].frames[j].width;
            (*_datFileItem) >> _directions[i].frames[j].height;
            (*_datFileItem) >> _directions[i].frames[j].dataSize;
            (*_datFileItem) >> _directions[i].frames[j].offsetX;
            (*_datFileItem) >> _directions[i].frames[j].offsetY;
            _datFileItem->skip(_directions[i].frames[j].dataSize);
        }
    }
    _initialized = true;
}

unsigned int FrmFileType::getVersion()
{
    _init();
    return _version;
}

void FrmFileType::setVersion(unsigned int version)
{
    _version = version;
}

unsigned short FrmFileType::getFps()
{
    return _fps;
}

void FrmFileType::setFps(unsigned short fps)
{
    _fps = fps;
}

FrmDirection * FrmFileType::getDirections()
{
    _init();
    return _directions;
}

}
