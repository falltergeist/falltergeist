/*
 * Copyright 2012-2018 Falltergeist Developers.
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

#ifndef FALLTERGEIST_INI_PARSER_H
#define FALLTERGEIST_INI_PARSER_H

// C++ standard includes
#include <memory>
#include <string>
#include <vector>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{
namespace Ini
{

class File;
class Value;

class Parser
{
public:
    Parser(std::istream &stream);
    ~Parser();

    std::shared_ptr<File> parse();

private:
    std::istream &_stream; // stream to parse
    std::string  _section; // current section

protected:
    void _trim(std::string &line);

    void _rtrim(std::string &line);

    void _ltrim(std::string &line);

    void _toLower(std::string &line);

    bool _tryBool(std::string &line, bool* val);

    int _tryDecimal(std::string &line, int* intval, double* doubleval);

    bool _parseBool(std::string &name, std::string &line, std::shared_ptr<File> ini);

    bool _parseDecimal(std::string &name, std::string &line, std::shared_ptr<File> ini);

    bool _parseArray(std::string &name, std::string &line, std::shared_ptr<File> ini);

    bool _parseArrayDecimal(std::vector<Value> &vec, std::string val);
    bool _parseArrayBool(std::vector<Value> &vec, std::string val);

};

}
}
#endif // FALLTERGEIST_INI_PARSER_H
