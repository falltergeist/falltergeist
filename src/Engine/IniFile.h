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
 *
 */

#ifndef FALLTERGEIST_INIFILE_H
#define	FALLTERGEIST_INIFILE_H

// C++ standard includes
#include <fstream>
#include <string>
#include <map>
// Falltergeist includes

// Third party includes

namespace Falltergeist
{

typedef std::map<std::string, std::string> IniFileSection;    

class IniFile 
{
protected:
    std::string _filename;
    std::map<std::string, IniFileSection *> _sections;
public:
    IniFile(std::string filename);
    virtual ~IniFile();
    void removeSection(std::string name);
    IniFileSection * addSection(std::string name);
    IniFileSection * getSection(std::string name);
    bool hasSection(std::string name);
    void save();
    void parse();
    
    void setFilename(std::string filename);
    std::string filename();
};

}
#endif	// FALLTERGEIST_INIFILE_H 
