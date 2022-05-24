// Project includes
#include "../../Format/Int/Procedure.h"

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Format
    {
        namespace Int
        {
            Procedure::Procedure()
            {
            }

            uint32_t Procedure::flags() const
            {
                return _flags;
            }

            void Procedure::setFlags(uint32_t flags)
            {
                _flags = flags;
            }

            uint32_t Procedure::delay() const
            {
                return _delay;
            }

            void Procedure::setDelay(uint32_t delay)
            {
                _delay = delay;
            }

            uint32_t Procedure::conditionOffset() const
            {
                return _conditionOffset;
            }

            void Procedure::setConditionOffset(uint32_t offset)
            {
                _conditionOffset = offset;
            }

            uint32_t Procedure::bodyOffset() const
            {
                return _bodyOffset;
            }

            void Procedure::setBodyOffset(uint32_t offset)
            {
                _bodyOffset = offset;
            }

            uint32_t Procedure::argumentsCounter()
            {
                return _argumentsCounter;
            }

            void Procedure::setArgumentsCounter(uint32_t value)
            {
                _argumentsCounter = value;
            }

            bool Procedure::isTimed()
            {
                return flags() & (unsigned)PROCEDURE_FLAG::TIMED;
            }

            bool Procedure::isConditional()
            {
                return flags() & (unsigned)PROCEDURE_FLAG::CONDITIONAL;
            }

            bool Procedure::isImported()
            {
                return flags() & (unsigned)PROCEDURE_FLAG::IMPORTED;
            }

            bool Procedure::isExported()
            {
                return flags() & (unsigned)PROCEDURE_FLAG::EXPORTED;
            }

            bool Procedure::isCritical()
            {
                return flags() & (unsigned)PROCEDURE_FLAG::CRITICAL;
            }

            bool Procedure::isPure()
            {
                return flags() & (unsigned)PROCEDURE_FLAG::PURE;
            }

            bool Procedure::isInline()
            {
                return flags() & (unsigned)PROCEDURE_FLAG::INLINE;
            }

            std::string Procedure::name() const
            {
                return _name;
            }

            void Procedure::setName(const std::string& name)
            {
                _name = name;
            }
        }
    }
}
