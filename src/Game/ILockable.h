#pragma once

// Project includes

// Third-party includes

// stdlib

namespace Falltergeist::Game {
    class ILockable {
    public:
        virtual bool locked() const = 0;

        virtual void lock() = 0;

        virtual void unlock() = 0;
    };
}
