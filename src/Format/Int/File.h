#pragma once

// Project includes
#include "../../Format/Dat/Item.h"
#include "../../Format/Dat/Stream.h"
#include "../../Format/Int/Procedure.h"

// Third-party includes

// stdlib
#include <map>
#include <string>
#include <vector>

namespace Falltergeist
{
    namespace Format
    {
        namespace Int
        {
            class File : public Dat::Item
            {
                public:
                    File(Dat::Stream&& stream);

                    const std::vector<Procedure>& procedures() const;

                    // returns procedure with a given name or nullptr if none found
                    const Procedure* procedure(const std::string& name) const;

                    const std::map<unsigned int, std::string>& identifiers() const;
                    const std::map<unsigned int, std::string>& strings() const;

                    // current position in script file
                    size_t position() const;

                    // set current position in script file
                    void setPosition(size_t);

                    // the size of script file
                    size_t size() const;

                    // read the next opcode
                    uint16_t readOpcode();

                    // read the next value
                    uint32_t readValue();

                protected:
                    Dat::Stream _stream;

                    std::vector<Procedure> _procedures;

                    std::map<unsigned int, std::string> _functions;
                    std::vector<unsigned int> _functionsOffsets;
                    std::map<unsigned int, std::string> _identifiers;
                    std::map<unsigned int, std::string> _strings;
            };
        }
    }
}
