#pragma once

namespace Falltergeist {
    namespace Lua {
        struct EventHandlerContext final {
            int targetIndex;
            int handlerIndex;
            EventHandlerContext(int targetIndex, int handlerIndex) : targetIndex(targetIndex), handlerIndex(handlerIndex) {}
        };
    }
}