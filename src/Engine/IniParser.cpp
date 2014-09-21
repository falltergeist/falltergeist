/*
 * Copyright 2012-2014 Falltergeist Developers.
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
 *
 */

// C++ standard includes
#include <algorithm>
#include <sstream>

// Falltergeist includes
#include "../Engine/IniFile.h"

// Third party includes

namespace Falltergeist
{

void IniParser::_trim(std::string &line)
{
    _ltrim(line);
    _rtrim(line);
}

void IniParser::_rtrim(std::string &line)
{
    line.erase(find_if(line.rbegin(), line.rend(), std::not1(std::ptr_fun<int, int>(isspace))).base(), line.end());
}

void IniParser::_ltrim(std::string &line)
{
    line.erase(line.begin(), find_if(line.begin(), line.end(), std::not1(std::ptr_fun<int, int>(isspace))));
}

void IniParser::_tolower(std::string &line)
{
    std::transform(line.begin(), line.end(), line.begin(), ::tolower);
}

bool IniParser::_parseBool(std::string &name, std::string &line, std::shared_ptr<IniFile> ini)
{
    auto maybeBool = line;
    _tolower(maybeBool);
    bool value;
    bool isBool = false;

    if (maybeBool == "yes" || maybeBool == "true" || maybeBool == "on")
    {
        value = true;
        isBool = true;
    }
    else if (maybeBool == "no" || maybeBool == "false" || maybeBool == "off")
    {
        value = false;
        isBool = true;
    }

    if (isBool)
    {
        std::cerr << "boolean value found for property `" << name << "`: " << value << std::endl;
        ini->section(_section)->setPropertyBool(name, value);
    }

    return isBool;
}

bool IniParser::_parseDecimal(std::string &name, std::string &line, std::shared_ptr<IniFile> ini)
{
    std::istringstream ss(line);
    enum { BEGIN, SIGN, INTEGRAL, DOT, FRACTIONAL, EXP, EXP_SIGN, EXP_DIGITS, ERROR } state = BEGIN;

    for (std::string::const_iterator it = line.begin(); state != ERROR && it != line.end(); ++it)
    {
        char sym = *it;
        switch (state)
        {
            case BEGIN:
            {
                if (sym == '+' || sym == '-')
                {
                    state = SIGN;
                }
                else if (isdigit(sym))
                    {
                        state = INTEGRAL;
                    }
                    else
                    {
                        state = ERROR;
                    }
            }
                break;

            case SIGN:
            {
                if (isdigit(sym))
                {
                    state = INTEGRAL;
                }
                else
                {
                    state = ERROR;
                }
            }
                break;

            case INTEGRAL:
            {
                if (sym == '.')
                {
                    state = DOT;
                }
                else if (!isdigit(sym))
                    {
                        state = ERROR;
                    }
            }
                break;

            case DOT:
            {
                if (isdigit(sym))
                {
                    state = FRACTIONAL;
                }
                else
                {
                    state = ERROR;
                }
            }
                break;

            case FRACTIONAL:
            {
                if (sym == 'e' || sym == 'E')
                {
                    state = EXP;
                }
                else if(!isdigit(sym))
                    {
                        state = ERROR;
                    }
            }
                break;

            case EXP:
            {
                if (sym == '+' || sym == '-')
                {
                    state = EXP_SIGN;
                }
                else
                {
                    state = ERROR;
                }
            }
                break;

            case EXP_SIGN:
            {
                if (isdigit(sym))
                {
                    state = EXP_DIGITS;
                }
                else
                {
                    state = ERROR;
                }
            }
                break;

            case EXP_DIGITS:
            {
                if (!isdigit(sym))
                {
                    state = ERROR;
                }
            }

            case ERROR:
                // do nothing, just suppress warning
                break;
        }
    }

    if (state == INTEGRAL)
    {
        int value;
        ss >> value;
        std::cerr << "integer value found for property `" << name << "`: " << value << std::endl;
        ini->section(_section)->setPropertyInt(name, value);
        return  true;
    }

    if (state == FRACTIONAL || state == EXP || state == EXP_DIGITS)
    {
        double value;
        ss >> value;
        std::cerr << "double value found for property `" << name << "`: " << value << std::endl;
        ini->section(_section)->setPropertyDouble(name, value);
        return true;
    }

    return false;
}

IniParser::IniParser(std::istream &stream) : _stream(stream), _section("")
{

}

std::shared_ptr<IniFile> IniParser::parse()
{
    auto ini = std::shared_ptr<IniFile>(new IniFile());
    std::string line;

    while (std::getline(_stream, line))
    {
        // Lines starting with "#" or ";" are treated as comments and ignored
        if (line[0] == '#' || line[0] == ';') continue;

        // Prepare line
        _trim(line);

        // Skip empty lines
        if (line.length() == 0) continue;

        // Found section
        if (*line.begin() == '[' && *line.rbegin() == ']')
        {
            _section = line.substr(1, line.length() - 2);
            _tolower(_section);
            std::cerr << "start section: `" << _section << "`" << std::endl;
            continue;
        }

        auto eqPos = line.find('=');
        if (eqPos == std::string::npos)
        {
            std::cerr << "malformed line: " << line << std::endl;
            continue;
        }

        auto name  = line.substr(0, eqPos);
        auto value = line.substr(eqPos + 1);
        _rtrim(name);
        _ltrim(value);

        // Property names are case-insensitive
        _tolower(name);

        // Try to parse boolean
        if (_parseBool(name, value, ini)) continue;
        // Try to parse decimal (double or integer)
        if (_parseDecimal(name, value, ini)) continue;

        // Interpret value as string
        std::cerr << "string value found for property `" << name << "`: " << value << std::endl;
        ini->section(_section)->setPropertyString(name, value);
    }

    return ini;
}
}