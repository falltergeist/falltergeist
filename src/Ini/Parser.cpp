/*
 * Copyright 2012-2016 Falltergeist Developers.
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

// Related headers
#include "../Ini/Parser.h"

// C++ standard includes
#include <algorithm>
#include <functional>
#include <sstream>

// Falltergeist includes
#include "../Logger.h"
#include "../Ini/File.h"

// Third party includes

namespace Falltergeist
{
namespace Ini
{

Parser::Parser(std::istream &stream) : _stream(stream), _section("")
{
}

Parser::~Parser()
{
}

void Parser::_trim(std::string &line)
{
    _ltrim(line);
    _rtrim(line);
}

void Parser::_rtrim(std::string &line)
{
    if (line.find(";") != std::string::npos)
    {
        line.erase(line.find(";"));
    }

    line.erase(find_if(line.rbegin(), line.rend(), std::not1(std::ptr_fun<int, int>(isspace))).base(), line.end());
}

void Parser::_ltrim(std::string &line)
{
    line.erase(line.begin(), find_if(line.begin(), line.end(), std::not1(std::ptr_fun<int, int>(isspace))));
}

void Parser::_toLower(std::string &line)
{
    std::transform(line.begin(), line.end(), line.begin(), ::tolower);
}

bool Parser::_tryBool(std::string &line, bool *val)
{
    auto maybeBool = line;
    _toLower(maybeBool);

    if (maybeBool == "yes" || maybeBool == "true" || maybeBool == "on")
    {
        *val = true;
        return true;
    }
    else if (maybeBool == "no" || maybeBool == "false" || maybeBool == "off")
    {
        *val = false;
        return true;
    }
    return false;
}

bool Parser::_parseBool(std::string &name, std::string &line, std::shared_ptr<File> ini)
{
    bool value;
    if (_tryBool(line, &value))
    {
        Logger::debug("INI") << "boolean value found for property `" << name << "`: " <<
                std::boolalpha << value << std::noboolalpha << std::endl;
        ini->section(_section)->setPropertyBool(name, value);
        return true;
    }

    return false;
}

int Parser::_tryDecimal(std::string &line, int* intval,double* doubleval)
{
    std::istringstream ss(line);
    enum { BEGIN, SIGN, INTEGRAL, DOT, FRACTIONAL, EXP, EXP_SIGN, EXP_DIGITS, ERROR } state = BEGIN;

    for (std::string::const_iterator it = line.begin(); state != ERROR && it != line.end(); ++it)
    {
        char sym = *it;
        switch (state)
        {
            case BEGIN:
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
                break;

            case SIGN:
                if (isdigit(sym))
                {
                    state = INTEGRAL;
                }
                else
                {
                    state = ERROR;
                }
                break;

            case INTEGRAL:
                if (sym == '.')
                {
                    state = DOT;
                }
                else if (!isdigit(sym))
                {
                    state = ERROR;
                }
                break;

            case DOT:
                if (isdigit(sym))
                {
                    state = FRACTIONAL;
                }
                else
                {
                    state = ERROR;
                }
                break;

            case FRACTIONAL:
                if (sym == 'e' || sym == 'E')
                {
                    state = EXP;
                }
                else if(!isdigit(sym))
                {
                    state = ERROR;
                }
                break;

            case EXP:
                if (sym == '+' || sym == '-')
                {
                    state = EXP_SIGN;
                }
                else
                {
                    state = ERROR;
                }
                break;

            case EXP_SIGN:
                if (isdigit(sym))
                {
                    state = EXP_DIGITS;
                }
                else
                {
                    state = ERROR;
                }
                break;

            case EXP_DIGITS:
                if (!isdigit(sym))
                {
                    state = ERROR;
                }
                break;

            case ERROR:
                // do nothing, just suppress warning
                break;
        }
    }

    if (state == INTEGRAL)
    {
        ss >> *intval;
        return 1;
    }

    if (state == FRACTIONAL || state == EXP || state == EXP_DIGITS)
    {
        ss >> *doubleval;
        return -1;
    }

    return 0;
}


bool Parser::_parseDecimal(std::string &name, std::string &line, std::shared_ptr<File> ini)
{
    int intval;
    double doubleval;
    int ret = _tryDecimal(line, &intval, &doubleval);
    if (ret!=0)
    {
        if (ret > 0)
        {
            Logger::debug("INI") << "integer value found for property `" << name << "`: " << intval << std::endl;
            ini->section(_section)->setPropertyInt(name, intval);
            return  true;
        }

        else if (ret < 0)
        {
            Logger::debug("INI") << "double value found for property `" << name << "`: " << doubleval << std::endl;
            ini->section(_section)->setPropertyDouble(name, doubleval);
            return true;
        }
    }

    return false;
}


bool Parser::_parseArrayBool(std::vector<Value> &vec, std::string val)
{
    bool value;
    if (_tryBool(val,&value))
    {
        Logger::debug("INI") << "boolean value found for property `" << "`: " <<
                std::boolalpha << value << std::noboolalpha << std::endl;
        vec.push_back(Value(value));
        return true;
    }

    return false;
}


bool Parser::_parseArrayDecimal(std::vector<Value> &vec, std::string val)
{
    int intval;
    double doubleval;
    int ret = _tryDecimal(val, &intval, &doubleval);
    if (ret!=0)
    {
        if (ret > 0)
        {
            Logger::debug("INI") << "integer value found for property `" << "`: " << intval << std::endl;
            vec.push_back(Value(intval));
            return true;
        }

        if (ret < 0)
        {
            Logger::debug("INI") << "double value found for property `" << "`: " << doubleval << std::endl;
            vec.push_back(Value(doubleval));
            return true;
        }
    }
    return false;
}

bool Parser::_parseArray(std::string &name, std::string &line, std::shared_ptr<File> ini)
{
    auto ss = line;
    std::vector<Value> _vec;
    while (ss.find(",")!=std::string::npos)
    {
        std::string val=ss.substr(0,ss.find(","));
        ss.erase(0,ss.find(",")+1);
        if (_parseArrayDecimal(_vec,val)) continue;
        if (_parseArrayBool(_vec,val)) continue;
        Logger::debug("INI") << "string value found for property `" << "`: " << val << std::endl;
        _vec.push_back(Value(val));
    }
    if (_vec.size()>0)
    {
        if (!_parseArrayDecimal(_vec,ss) && !_parseArrayBool(_vec,ss))
        {
            Logger::debug("INI") << "string value found for property `" << "`: " << ss << std::endl;
            _vec.push_back(Value(ss));
        }
        ini->section(_section)->setPropertyArray(name, _vec);
        Logger::debug("INI") << "array value found for property `" << name << "`: " << line << std::endl;
        return true;
    }
    return false;
}

std::shared_ptr<File> Parser::parse()
{
    auto ini = std::shared_ptr<File>(new File());
    std::string line;

    Logger::info("INI") << "start parsing config file." << std::endl;

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
            _toLower(_section);

            Logger::debug("INI") << "start section: `" << _section << "`" << std::endl;
            continue;
        }

        auto eqPos = line.find('=');
        if (eqPos == std::string::npos)
        {
            Logger::warning("INI") << "malformed line: " << line << std::endl;
            continue;
        }

        auto name  = line.substr(0, eqPos);
        auto value = line.substr(eqPos + 1);
        _rtrim(name);
        _ltrim(value);

        // Property names are case-insensitive
        _toLower(name);

        // Try to parse boolean
        if (_parseBool(name, value, ini)) continue;
        // Try to parse decimal (double or integer)
        if (_parseDecimal(name, value, ini)) continue;
        // Try to parse array
        if (_parseArray(name, value, ini)) continue;

        // Interpret value as string if none of other parsers succeeded
        Logger::debug("INI") << "string value found for property `" << name << "`: " << value << std::endl;
        ini->section(_section)->setPropertyString(name, value);
    }

    return ini;
}

}
}
