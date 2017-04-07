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

// C++ standard includes
#include <algorithm>
#include <type_traits>

// Falltergeist includes
#include "Exception.h"
#include "functions.h"
#include "ResourceManager.h"

// Third party includes
#include "Format/Msg/File.h"
#include "Format/Msg/Message.h"

namespace Falltergeist
{

std::string _t(MSG_TYPE type, unsigned int number)
{
    static const std::string msgFiles[] = {
        "text/english/game/inventry.msg",
        "text/english/game/lsgame.msg",
        "text/english/game/options.msg",
        "text/english/game/misc.msg",
        "text/english/game/editor.msg",
        "text/english/game/trait.msg",
        "text/english/game/skill.msg",
        "text/english/game/stat.msg",
        "text/english/game/skilldex.msg",
        "text/english/game/dbox.msg",
        "text/english/game/proto.msg",
        "text/english/game/pro_item.msg"
    };
    static const auto msgFilesSize = sizeof(msgFiles) / sizeof(*msgFiles);
    static_assert(MSG_TYPE_COUNT <= msgFilesSize,
                  "MSG_TYPE enum doesn't match with msg files!");

    if (type >= msgFilesSize)
    {
        throw Exception("_t() - wrong MSG file type: " + std::to_string(type));
    }

    auto msg = ResourceManager::getInstance()->msgFileType(msgFiles[type]);
    return msg->message(number)->text();
}

std::string path_basename(const std::string& path, bool removeExtension)
{
    auto filename = std::string( 
        std::find_if(path.rbegin(), path.rend(), [](char c) { return c == '/' || c == '\\'; }).base(),
        path.end());
        
    if (removeExtension)
    {
        auto pivot = std::find(filename.rbegin(), filename.rend(), '.');
        return pivot == filename.rend()
            ? filename
            : std::string(filename.begin(), pivot.base() - 1);
    }
    return filename;
}

}
