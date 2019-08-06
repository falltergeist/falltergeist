#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            class Opcode8138 : virtual public IFalloutOpcode {
            public:
                Opcode8138(std::shared_ptr<VM::Script> script);;

            private:
                void _run() override;
            };
        }
    }
}
