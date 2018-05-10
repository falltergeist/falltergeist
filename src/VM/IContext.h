#ifndef FALLTERGEIST_VM_ICONTEXT_H
#define FALLTERGEIST_VM_ICONTEXT_H

#include <memory>

namespace Falltergeist {
    namespace Game {
        class DudeObject;
    }
    namespace VM {
        class IContext {
        public:
            virtual ~IContext() = default;
            virtual std::shared_ptr<Game::DudeObject> player();
        };
    }
}

#endif //FALLTERGEIST_VM_ICONTEXT_H
