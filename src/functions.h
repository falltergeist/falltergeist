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

#ifndef FALLTERGEIST_FUNCTIONS_H
#define FALLTERGEIST_FUNCTIONS_H

// C++ standard includes
#include <string>

// Falltergeist includes

// Third party includes

namespace Falltergeist
{

enum MSG_TYPE : unsigned int
{
    MSG_INVENTORY = 0,
    MSG_LOAD_SAVE,
    MSG_OPTIONS,
    MSG_MISC,
    MSG_EDITOR,
    MSG_TRAITS,
    MSG_SKILLS,
    MSG_STATS,
    MSG_SKILLDEX,
    MSG_DIALOG_BOX,
    MSG_PROTO,
    MSG_PROTO_ITEMS,

    // Should be last entry.
    MSG_TYPE_COUNT
};

std::string _t(MSG_TYPE type, unsigned int number);

std::string path_basename(const std::string& path, bool removeExtension = false);

}
#endif // FALLTERGEIST_FUNCTIONS_H
