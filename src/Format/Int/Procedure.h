#pragma once

// Project includes
#include "../../Format/Enums.h"

// Third-party includes

// stdlib
#include <cstdint>
#include <string>

namespace Falltergeist
{
    namespace Format
    {
        namespace Int
        {
            class Procedure
            {
                public:
                    Procedure();

                    uint32_t flags() const;
                    void setFlags(uint32_t flags);

                    uint32_t delay() const;
                    void setDelay(uint32_t delay);

                    uint32_t conditionOffset() const;
                    void setConditionOffset(uint32_t offset);

                    uint32_t bodyOffset() const;
                    void setBodyOffset(uint32_t offset);

                    uint32_t argumentsCounter();
                    void setArgumentsCounter(uint32_t value);

                    std::string name() const;
                    void setName(const std::string& name);

                    bool isTimed();
                    bool isConditional();
                    bool isImported();
                    bool isExported();
                    bool isCritical();
                    bool isPure();
                    bool isInline();

                protected:
                    std::string _name;
                    uint32_t _flags = 0;
                    uint32_t _delay = 0; // delay for timed procedures
                    uint32_t _conditionOffset = 0; // offset of condition in code for conditional procedures
                    uint32_t _bodyOffset = 0; // procedure body offset from the beginning of the file
                    uint32_t _argumentsCounter = 0; // number of arguments
            };
        }
    }
}
