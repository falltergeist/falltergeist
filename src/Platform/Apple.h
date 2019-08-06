#pragma once

#if defined (__APPLE__)

#include "../Platform/IPlatform.h"

namespace Falltergeist
{
    namespace Platform
    {
        class Apple : public IPlatform
        {
            public:
                std::string name() override;
                std::vector<std::string> compactDiscDrivePaths() override;
                uint32_t microtime() override;
        };
    }
}
#endif
