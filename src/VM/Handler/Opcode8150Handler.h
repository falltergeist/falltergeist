#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            class Opcode8150 : virtual public IFalloutOpcode {
            public:
                Opcode8150(std::shared_ptr<VM::Script> script);;

            private:
                void _run() override;
            };
        }
    }
}
