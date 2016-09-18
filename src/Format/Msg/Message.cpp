/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2012-2015 Falltergeist developers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

// C++ standard includes

// Falltergeist includes
#include "../../Format/Msg/Message.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Msg
{

Message::Message()
{
}

Message::~Message()
{
}

void Message::setNumber(unsigned long number)
{
    _number = number;
}

unsigned long Message::number()
{
    return _number;
}

void Message::setSound(std::string sound)
{
    _sound = sound;
}

std::string Message::sound()
{
    return _sound;
}

void Message::setText(std::string text)
{
    _text = text;
}

std::string Message::text()
{
    return _text;
}

std::string* Message::textPointer()
{
    return &_text;
}

Message::operator std::string ()
{
    return _text;
}

}
}
}
