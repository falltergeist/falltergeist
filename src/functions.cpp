/*
 * Copyright 2012-2015 Falltergeist Developers.
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

// Falltergeist includes
#include "Exception.h"
#include "functions.h"
#include "ResourceManager.h"

// Third party includes
#include <libfalltergeist.h>

namespace Falltergeist
{

std::string _t(MSG_TYPE type, size_t number)
{
    std::vector<std::string> msgFiles = {
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
        "text/english/game/pro_item.msg"
    };

    if (type < 0 || type >= msgFiles.size())
    {
        throw Exception("_t() - wrong MSG file type: " + std::to_string(type));
    }

    auto msg = ResourceManager::msgFileType(msgFiles.at(type));
    return msg->message(number)->text();
}

}
