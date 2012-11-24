#include "Fallout/FrmFileType.h"
#include "Fallout/DatFileItem.h"

namespace Falltergeist
{

FrmFileType::FrmFileType(DatFileItem * datFileItem)
{
    _datFileItem = datFileItem;
    _initialized = false;
    _init();
}

FrmFileType::~FrmFileType()
{
    delete [] _directions; _directions = 0;
}

void FrmFileType::_init()
{
    if (_initialized) return;
    _datFileItem->seek(0);
    (*_datFileItem) >> _version >> _framesPerSecond >> _actionFrame >> _framesPerDirection;

    _directions = new FrmDirection[6];

    unsigned short i,j;
    for (i = 0; i < 6; i++) (*_datFileItem) >> _directions[i].shiftX;
    for (i = 0; i < 6; i++) (*_datFileItem) >> _directions[i].shiftY;
    for (i = 0; i < 6; i++) (*_datFileItem) >> _directions[i].dataOffset;

    (*_datFileItem) >> _dataSize;
    // Reading directions
    for (i = 0; i < 6; i++)
    {
        // if direction is the same as first
        if (i > 0) if (_directions[i].dataOffset == _directions[0].dataOffset) {
            //std::cout << "Direction same as first... skiping" << std::endl;
            _directions[i] = _directions[0];
            continue;
        }

        _directions[i].frames = new FrmFrame[_framesPerDirection];
        for (j = 0; j < _framesPerDirection; j++)
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
    return _version;
}

void FrmFileType::setVersion(unsigned int version)
{
    _version = version;
}

unsigned short FrmFileType::getFramesPerSecond()
{
    return _framesPerSecond;
}

void FrmFileType::setFramesPerSecond(unsigned short framesNumber)
{
    _framesPerSecond = framesNumber;
}

unsigned short FrmFileType::getFramesPerDirection()
{
    return _framesPerDirection;
}

void FrmFileType::setFramesPerDirection(unsigned short framesNumber)
{
    _framesPerDirection = framesNumber;
}

unsigned short FrmFileType::getActionFrame()
{
    return _actionFrame;
}

void FrmFileType::setActionFrame(unsigned short frameNumber)
{
    _actionFrame = frameNumber;
}

FrmDirection * FrmFileType::getDirections()
{
    return _directions;
}

void FrmFileType::setDirections(FrmDirection * directions)
{
    delete [] _directions; _directions = 0;
    _directions = directions;
}

}
