#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            class OpcodeA001 : virtual public IFalloutOpcode {
            public:
                OpcodeA001(std::shared_ptr<VM::Script> script);;

            private:
                void _run() override;
            };
        }
    }
}
