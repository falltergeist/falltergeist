// DISCLAIMER.
// This code was taken from the ACMReader plugin of the GemRB project (http://gemrb.org)
// and then adapted for Falltergeist. All credit goes to the original authors.
// Link to the plugin: https://github.com/gemrb/gemrb/tree/8e759bc6874a80d4a8d73bf79603624465b3aeb0/gemrb/plugins/ACMReader

#pragma once

// Project includes

// Third-party includes

// stdlib

namespace Falltergeist
{
    namespace Format
    {
        namespace Acm
        {
            struct Header
            {
                uint32_t signature;
                uint32_t samples;
                uint16_t channels;
                uint16_t rate;
                uint16_t levels : 4;
                uint16_t subblocks : 12;
            };
        }
    }
}
