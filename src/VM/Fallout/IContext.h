#pragma once

#include "VM/IContext.h"

namespace Falltergeist
{
    namespace VM
    {
        namespace Fallout
        {
            class IProcedure;
            class IStack;

            class IContext : public virtual VM::IContext
            {
                public:
                    virtual std::shared_ptr<IStack> dataStack() = 0;
                    virtual std::shared_ptr<IStack> returnStack() = 0;
                    virtual void setProgramCounter(unsigned counter) = 0;
                    virtual unsigned programCounter() const = 0;
                    virtual void stopExecution() = 0;
                    virtual unsigned int dynamicVarStackBase() const = 0;
                    virtual void setDynamicVarStackBase(unsigned int stackBase) = 0;
                    virtual unsigned int scriptVarStackBase() const = 0;
                    virtual void setScriptVarStackBase(unsigned int stackBase) = 0;
                    virtual std::shared_ptr<IProcedure> getProcedureByName(const std::string &name) const = 0;
                    virtual std::shared_ptr<IProcedure> getProcedureByIndex(unsigned int index) const = 0;
                    virtual std::string getIdentifierByIndex(unsigned int index) const = 0;
            };
        }
    }
}
