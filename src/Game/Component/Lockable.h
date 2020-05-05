#pragma once

#include <string>
#include "../../Game/Component/Component.h"

namespace Falltergeist
{
    namespace Game
    {
        namespace Component
        {
            class Lockable : public Component
            {
                public:
                    ~Lockable() override = default;

                    bool isOpened() const;
                    bool isLocked() const;

                    void open();
                    void close();

                    void lock();
                    void unlock();


                private:
                    bool _isLocked = false;
                    bool _isOpened = false;
            };
        }
    }
}
