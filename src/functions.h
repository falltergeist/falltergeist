#pragma once

#include <string>

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
        MSG_PERK,
        MSG_PROTO,
        MSG_PROTO_ITEMS,

        // Should be last entry.
        MSG_TYPE_COUNT
    };

    std::string _t(MSG_TYPE type, unsigned int number);

    std::string path_basename(const std::string& path, bool removeExtension = false);
}
