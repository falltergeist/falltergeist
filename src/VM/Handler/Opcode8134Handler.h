#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            class Opcode8134 : virtual public IFalloutOpcode {
            public:
                Opcode8134(std::shared_ptr<VM::Script> script);;

            private:
                void _run() override;
            };
        }
    }
}
