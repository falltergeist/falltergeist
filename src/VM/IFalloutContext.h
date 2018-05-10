#ifndef FALLTERGEIST_VM_IFALLOUTCONTEXT_H
#define FALLTERGEIST_VM_IFALLOUTCONTEXT_H

#include "IContext.h"

namespace Falltergeist {
    namespace VM {
        class IFalloutContext : public virtual IContext {
        public:
            virtual ~IFalloutContext() = default;
        };
    }
}

#endif //FALLTERGEIST_VM_IFALLOUTCONTEXT_H
