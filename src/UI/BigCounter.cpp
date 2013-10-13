/*
 * Copyright 2012-2013 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../UI/BigCounter.h"
#include "../Engine/ResourceManager.h"
#include <sstream>
#include <iostream>

namespace Falltergeist
{

BigCounter::BigCounter(int x, int y) : InteractiveSurface(0,0, x, y)
{
    _number = 0;
    _color = COLOR_WHITE;
    _length = 2;
    _numbersWhite = new std::vector<Surface *>;
    _numbersRed = new std::vector<Surface *>;
    for (int i = 0; i != 10; i++)
    {
        _numbersWhite->push_back(ResourceManager::surface("art/intrface/bignum.frm")->crop(14*i, 0, 14, 24));
    }
    for (int i = 0; i != 10; i++)
    {
        _numbersRed->push_back(ResourceManager::surface("art/intrface/bignum.frm")->crop(168 + 14*i, 0, 14, 24));
    }
    setNeedRedraw(true);
}

BigCounter::~BigCounter()
{
    while (!_numbersRed->empty())
    {
        delete _numbersRed->back();
        _numbersRed->pop_back();
    }
    delete _numbersRed;
    while (!_numbersWhite->empty())
    {
        delete _numbersWhite->back();
        _numbersWhite->pop_back();
    }
    delete _numbersWhite;
}

void BigCounter::draw()
{
    if (!needRedraw()) return;

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
        Surface * number;
        switch (_color)
        {
            case COLOR_WHITE:
                number =  _numbersWhite->at(key);
                break;
            case COLOR_RED:
                number =  _numbersRed->at(key);
                break;
        }
        number->setX(14*i);
        number->copyTo(surface);
    }
    delete [] textNumber;

    surface->setX(this->x());
    surface->setY(this->y());
    surface->setXOffset(0);
    surface->setYOffset(0);

    loadFromSurface(surface);
    delete surface;
}

void BigCounter::setNumber(unsigned int number)
{
    _number = number;
    setNeedRedraw(true);
}

unsigned int BigCounter::number()
{
    return _number;
}


void BigCounter::setColor(unsigned char color)
{
    switch(color)
    {
        case COLOR_WHITE:
        case COLOR_RED:
            if (_color != color)
            {
                _color = color;
                setNeedRedraw(true);
            }
            break;
    }
}

unsigned char BigCounter::color()
{
    return _color;
}

}
