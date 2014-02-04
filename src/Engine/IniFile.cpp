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

// Falltergeist includes
#include <algorithm> 

#include "../Engine/IniFile.h"
#include "../Engine/CrossPlatform.h"
#include "../Engine/Exception.h"

// Third party includes

namespace Falltergeist
{

IniFile::IniFile(std::string filename) : _filename(filename)
{    
}

IniFile::~IniFile()
{
}

void IniFile::parse()
{
    std::fstream stream(_filename, std::fstream::in);
    if (!stream.is_open())
    {
        throw Exception("IniFile::parse() - can't open stream: " + _filename);
    }        
    
    std::string line;
    while (!stream.eof())
    {
        std::getline(stream, line);
        line.erase(std::find_if(line.rbegin(), line.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), line.end()); // rtrim
        if (line.length() == 0) continue;
        
        if (line.find('[') != std::string::npos && line.find(']') != std::string::npos)
        {
            std::string name = line.substr(line.find('[') + 1, line.find(']') - 1);
            addSection(name);
        }
        else
        {
            std::string name  = line.substr(0, line.find('='));
            std::string value = line.substr(line.find('=') + 1);
            _sections.at(_sections.rbegin()->first)->insert(std::make_pair(name, value));
        }
    }
    stream.close();
}

void IniFile::removeSection(std::string name)
{
    for (auto it = _sections.begin(); it != _sections.end(); ++it)        
    {
        _sections.erase(it);
    }    
}

IniFileSection * IniFile::getSection(std::string name)
{
    for (auto it = _sections.begin(); it != _sections.end(); ++it)        
    {
        if (it->first == name) return it->second;
    }
    return 0;    
}

IniFileSection * IniFile::addSection(std::string name)
{
    auto section = new IniFileSection;
    _sections.insert(std::make_pair(name, section));
    return section;
}

bool IniFile::hasSection(std::string name)
{
    for (auto it = _sections.begin(); it != _sections.end(); ++it)        
    {
        if (it->first == name) return true;
    }
    return false;
}

void IniFile::save()
{
    std::fstream stream;
    stream.open(_filename, std::fstream::out|std::fstream::trunc);
    if (!stream.is_open())
    {
        throw Exception("IniFile::save() - can't open stream: " + _filename);
    }
    
    for (auto it = _sections.begin(); it != _sections.end(); ++it)        
    {
        stream << "[" << it->first << "]\n";
        for (auto itt = it->second->begin(); itt != it->second->end(); ++itt)
        {
            stream << itt->first << "=" << itt->second <<"\n";            
        }
        stream << "\n";
    }
    stream.close();    
}

void IniFile::setFilename(std::string filename)
{
    _filename = filename;
}

std::string IniFile::filename()
{
    return _filename;
}

}
