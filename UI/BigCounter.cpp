#include "UI/BigCounter.h"
#include "Engine/ResourceManager.h"
#include <sstream>
#include <iostream>

namespace Falltergeist
{

BigCounter::BigCounter(int x, int y) : InteractiveSurface(0,0, x, y)
{
    _number = 0;
    _length = 2;
    _numbersWhite = new std::vector<Surface *>;
    _numbersRed = new std::vector<Surface *>;
    for (int i = 0; i != 10; i++)
    {
        _numbersWhite->push_back(ResourceManager::getSurface("art/intrface/bignum.frm")->crop(14*i, 0, 14, 24));
    }
    for (int i = 0; i != 10; i++)
    {
        _numbersRed->push_back(ResourceManager::getSurface("art/intrface/bignum.frm")->crop(168 + 14*i, 0, 14, 24));
    }
}

BigCounter::~BigCounter()
{
    delete _numbersRed;
    delete _numbersWhite;
}

void BigCounter::draw()
{
    InteractiveSurface::draw();
    // new surface
    Surface * surface = new Surface(14*_length, 24);
    // number as text
    std::stringstream ss;
    ss << _number;

    char * textNumber = new char[_length + 1]();

    for (unsigned int i = 0; i < _length; ++i)
    {
        textNumber[i] = '0';
    }

    unsigned int length = strlen(ss.str().c_str());
    unsigned int diff = _length - length;
    for (unsigned int i = 0; i < length; i++)
    {
        textNumber[diff + i] = ss.str().c_str()[i];
    }


    for (unsigned int i = 0; i < _length; i++)
    {
        int key = 9 -  ('9' - textNumber[i]);
        //std::cout << key << std::endl;
        Surface * number =  _numbersWhite->at(key);
        number->setX(14*i);
        number->copyTo(surface);
    }
    delete [] textNumber;

    surface->setX(getX());
    surface->setY(getY());
    loadFromSurface(surface);
}

void BigCounter::setNumber(unsigned int number)
{
    _number = number;
    needRedraw = true;
}

}
