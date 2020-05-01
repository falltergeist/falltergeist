#pragma once

#include <sstream>

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
