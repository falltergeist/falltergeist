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
#include <type_traits>

// Falltergeist includes
#include "Exception.h"
#include "functions.h"
#include "Lua/Script.h"
#include "ResourceManager.h"

// Third party includes
#include <libfalltergeist.h>

namespace Falltergeist
{

std::string translate(std::string key, std::string file)
{
    // @todo
    // move locale to config file
    // save Lua::Script(file) to future function calls
    std::string locale = "en_US";

    Lua::Script script("data/languages/" + locale + "/" + file + ".lua");
    script.run();

    return script.get(key, file + "." + key);
}

std::string _t(MSG_TYPE type, size_t number)
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
        "text/english/game/pro_item.msg"
    };
    static const auto msgFilesSize = sizeof(msgFiles) / sizeof(*msgFiles);
    static_assert(MSG_TYPE_COUNT <= msgFilesSize,
                  "MSG_TYPE enum doesn't match with msg files!");

    if (type < 0 || type >= msgFilesSize)
    {
        throw Exception("_t() - wrong MSG file type: " + std::to_string(type));
    }

    auto msg = ResourceManager::getInstance()->msgFileType(msgFiles[type]);
    return msg->message(number)->text();
}

}
