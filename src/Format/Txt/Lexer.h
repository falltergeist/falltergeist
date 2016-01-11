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

#ifndef FALLTERGEIST_FORMAT_TXT_LEXER_H
#define FALLTERGEIST_FORMAT_TXT_LEXER_H

// C++ standard includes
#include <sstream>

// Libfalltergeist includes

// Third party includes

namespace Falltergeist
{
namespace Format
{
namespace Txt
{

/**
 * A simple lexer for WorldmapFile parser
 */
class Lexer
{
public:
    enum Type : int
    {
        T_NONE = 0,
        T_CONSTANT = 256,
        T_IDENTIFIER,
        T_IF,
        T_AND,
        T_OR, // not used
        T_EQUAL,
        T_GREATER_EQUAL,
        T_LESS_EQUAL,
        T_EOF
    };

    struct Token
    {
        /**
         * Type of lexeme
         */
        int type = Type::T_NONE;

        /**
         * String data of lexeme
         */
        std::string data;

        /**
         * Integer data of lexeme
         */
        unsigned long intData = 0;
    };

    Lexer(const std::string& line);

    /**
     * Get next token from the stream
     */
    int lex();

    /**
     * "Unget" token. Next lex() call will return previous token instead.
     */
    void unLex();

    /**
     * Gets next token and returns true if it's of given type.
     *
     * @param type one of Token::Type constants or ASCII character.
     */
    bool expect(int type);

    const Token& last();

    bool eof();


private:
    std::istringstream _stream;
    Lexer::Token _lastToken;
    bool _recallToken = false;

    char _get(Token& token);
    Lexer::Token _nextToken();
};

}
}
}
#endif // FALLTERGEIST_FORMAT_TXT_LEXER_H
