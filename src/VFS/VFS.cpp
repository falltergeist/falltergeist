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
#include "../VFS/VFS.h"

// C++ standard includes
#include <string>
#include <vector>

// Falltergeist includes
#include "../CrossPlatform.h"
#include "../VFS/File.h"
#include "../VFS/Plugin/DatFile.h"
#include "../VFS/Plugin/System.h"

// Third party includes

namespace Falltergeist
{
namespace VFS
{

VFS::VFS()
{
    // OS filesystem plugin. Read directly from disk
    _plugins.push_back(new Plugin::System);

    // one plugin instance per DAT file
    for (auto filename : CrossPlatform::findFalloutDataFiles())
    {
        _plugins.push_back(new Plugin::DatFile(CrossPlatform::findFalloutDataPath() + "/" + filename));
    }

    // Here comes other plugins
    // Zip archives... network repos... etc
}

VFS::~VFS()
{
    for (auto& item : _cache)
    {
        delete item.second;
    }

    for (auto plugin : _plugins)
    {
        delete plugin;
    }
}

File* VFS::open(const std::string& filename)
{
    if (_cache.find(filename) != _cache.end())
    {
        return _cache.at(filename);
    }

    for(auto plugin : _plugins)
    {
        auto file = plugin->open(filename);
        if (file)
        {
            _cache.insert(std::make_pair(filename, file));
            return file;
        }
    }

    return nullptr;
}

}
}
