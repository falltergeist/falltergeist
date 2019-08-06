#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            class Opcode8149 : virtual public IFalloutOpcode {
            public:
                Opcode8149(std::shared_ptr<VM::Script> script);;

            private:
                void _run() override;
            };
        }
    }
}
