#include "Fallout/FrmFileType.h"
#include "Fallout/DatFile.h"

namespace Falltergeist
{

FrmFileType::FrmFileType(std::string fileName, DatFile * datFile) : DatFileItem(fileName, datFile)
{
    _readed = false;

}

FrmFileType::~FrmFileType()
{
    delete [] _directions;
}

void FrmFileType::_init()
{
    DatFileItem::_init();
    if (_readed) return;
    seek(0);
    (*this) >> _version >> _fps >> _actionFrame >> _framesPerDirection;


    //std::cout << "_version: " << _version << std::endl;
    //std::cout << "_fps: " << _fps << std::endl;
    //std::cout << "_actionFrame: " << _actionFrame << std::endl;
    //std::cout << "_framesPerDirection: " << _framesPerDirection << std::endl;

    _directions = new FrmDirection[6];

    for (unsigned char i = 0; i < 6; i++)
    {
        (*this) >> _directions[i].shiftX;
        //std::cout << "_directions[" << (int) i << "][shiftX]: " << _directions[i].shiftX << std::endl;
    }
    for (unsigned char i = 0; i < 6; i++)
    {
        (*this) >> _directions[i].shiftY;
        //std::cout << "_directions[" << (int)i << "][shiftY]: " << _directions[i].shiftY << std::endl;
    }
    for (unsigned char i = 0; i < 6; i++)
    {
        (*this) >> _directions[i].dataOffset;
        //std::cout << "_directions[" << (int)i << "][dataOffset]: " << _directions[i].dataOffset << std::endl;
    }
    (*this) >> _dataSize;
    //std::cout << "_dataSize: " << _dataSize << std::endl;


    // Reading directions
    for (unsigned char i = 0; i < 6; i++)
    {
        //std::cout << "Reading direction ["<< (int) i <<"]" << std::endl;
        // if direction is the same as first
        if (i > 0) if (_directions[i].dataOffset == _directions[0].dataOffset) {
            //std::cout << "Direction same as first... skiping" << std::endl;
            _directions[i] = _directions[0];
            continue;
        }

        _directions[i].frames = new FrmFrame[_framesPerDirection];
        for (unsigned short j = 0; j < _framesPerDirection; j++)
        {
            //std::cout << "Reading frame["<< (int) j <<"]" << std::endl;
            (*this) >> _directions[i].frames[j].width;
            //std::cout << "frame["<< (int) j <<"][width] = " << _directions[i].frames[j].width << std::endl;
            (*this) >> _directions[i].frames[j].height;
            //std::cout << "frame["<< (int) j <<"][height] = " << _directions[i].frames[j].height << std::endl;
            (*this) >> _directions[i].frames[j].dataSize;
            //std::cout << "frame["<< (int) j <<"][dataSize] = " << _directions[i].frames[j].dataSize << std::endl;
            (*this) >> _directions[i].frames[j].offsetX;
            //std::cout << "frame["<< (int) j <<"][offsetX] = " << _directions[i].frames[j].offsetX << std::endl;
            (*this) >> _directions[i].frames[j].offsetY;
            //std::cout << "frame["<< (int) j <<"][offsetY] = " << _directions[i].frames[j].offsetY << std::endl;
            // skip the data of frame
            skip(_directions[i].frames[j].dataSize);
        }
    }

    _readed = true;
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
