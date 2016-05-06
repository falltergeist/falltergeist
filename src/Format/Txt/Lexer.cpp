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
#include <cctype>
#include <clocale>

// Falltergeist includes
#include "Lexer.h"

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Txt
{

int Lexer::lex()
{
    if (_recallToken)
    {
        _recallToken = false;
    }
    else
    {
        _lastToken = _nextToken();
    }
    return _lastToken.type;
}

void Lexer::unLex()
{
    _recallToken = true;
}

bool Lexer::eof()
{
    return _stream.eof();
}

bool Lexer::expect(int type)
{
    if (lex() != type)
    {
        unLex();
        return false;
    }
    return true;
}

const Lexer::Token& Lexer::last()
{
    return _lastToken;
}

Lexer::Token Lexer::_nextToken()
{
    Lexer::Token token;
    auto ch = _stream.get();
    // skip any leading whitespaces
    while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
    {
        ch = _stream.get();
    }
    if (ch >= '0' && ch <= '9')
    {
        do
        {
            token.intData *= 10;
            token.intData += (ch - '0');
            token.data.push_back((char)ch);
            ch = _stream.get();
        } while (ch >= '0' && ch <= '9');

        if (ch == '%') // skip percent sign
        {
            token.data.push_back('%');
        }
        else
        {
            _stream.unget();
        }
        token.type = T_CONSTANT;
    }
    else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_')
    {
        std::string lc;
        do
        {
            lc.push_back((char)std::tolower(ch));
            token.data.push_back((char)ch);
            ch = _stream.get();
        } while ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || (ch == '_'));
        _stream.unget();
        if (lc == "if")
        {
            token.type = T_IF;
        }
        else if (lc == "and")
        {
            token.type = T_AND;
        }
        else if (lc == "or")
        {
            token.type = T_OR;
        }
        else
        {
            token.type = T_IDENTIFIER;
        }
    }
    else if (ch == '>')
    {
        if (_stream.get() == '=')
        {
            token.type = T_GREATER_EQUAL;
        }
        else
        {
            token.type = '>';
            _stream.unget();
        }
    }
    else if (ch == '<')
    {
        if (_stream.get() == '=')
        {
            token.type = T_LESS_EQUAL;
        }
        else
        {
            token.type = '<';
            _stream.unget();
        }
    }
    else if (ch == '=')
    {
        if (_stream.get() == '=')
        {
            token.type = T_EQUAL;
        }
        else
        {
            token.type = '=';
            _stream.unget();
        }
    }
    else if (ch != std::char_traits<char>::eof())
    {
        token.type = (int)ch;
        //token.data.push_back((char)ch);
    }
    else
    {
        token.type = T_EOF;
    }
    return token;
}

char Lexer::_get(Lexer::Token& token)
{
    char ch = (char)_stream.get();
    token.data += ch;
    return ch;
}


Lexer::Lexer(const std::string& line) : _stream(line)
{
}

}
}
}
