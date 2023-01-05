#pragma once

// Project includes

// Third-party includes

// stdlib

namespace Falltergeist::Game {
    class IClosable {
    public:
        virtual bool closed() const = 0;

        virtual void close() = 0;

        virtual void open() = 0;
    };
}
