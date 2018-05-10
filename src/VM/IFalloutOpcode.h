#ifndef FALLTERGEIST_VM_IFALLOUTOPCODE_H
#define FALLTERGEIST_VM_IFALLOUTOPCODE_H

#include <memory>

namespace Falltergeist {
    namespace VM {
        class IFalloutContext;

        class IFalloutOpcode {
        public:
            virtual ~IFalloutOpcode() = default;
            virtual void applyTo(std::shared_ptr<IFalloutContext> context) = 0;
        };
    }
}

#endif //FALLTERGEIST_VM_IFALLOUTOPCODE_H
