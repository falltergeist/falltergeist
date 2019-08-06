#pragma once

#include "../VM/IContext.h"

namespace Falltergeist
{
    namespace VM
    {
        class IFalloutProcedure;
        class IFalloutStack;

        class IFalloutContext : public virtual IContext
        {
            public:
                virtual std::shared_ptr<IFalloutStack> dataStack() = 0;
                virtual std::shared_ptr<IFalloutStack> returnStack() = 0;
                virtual void setProgramCounter(unsigned counter) = 0;
                virtual unsigned programCounter() const = 0;
                virtual void stopExecution() = 0;
                virtual unsigned int dynamicVarStackBase() const = 0;
                virtual void setDynamicVarStackBase(unsigned int stackBase) = 0;
                virtual unsigned int scriptVarStackBase() const = 0;
                virtual void setScriptVarStackBase(unsigned int stackBase) = 0;
                virtual std::shared_ptr<IFalloutProcedure> getProcedureByName(const std::string &name) const = 0;
                virtual std::shared_ptr<IFalloutProcedure> getProcedureByIndex(unsigned int index) const = 0;
                virtual std::string getIdentifierByIndex(unsigned int index) const = 0;
        };
    }
}
