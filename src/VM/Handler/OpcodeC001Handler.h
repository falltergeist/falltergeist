#pragma once

#include "../../VM/IFalloutOpcode.h"

namespace Falltergeist {
    namespace VM {
        namespace Handler {
            class OpcodeC001 : virtual public IFalloutOpcode {
            public:
                OpcodeC001(std::shared_ptr<VM::Script> script);;

            private:
                void _run() override;
            };
        }
    }
}
