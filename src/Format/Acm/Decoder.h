// DISCLAIMER.
// This code was taken from the ACMReader plugin of the GemRB project (http://gemrb.org)
// and then adapted for Falltergeist. All credit goes to the original authors.
// Link to the plugin: https://github.com/gemrb/gemrb/tree/8e759bc6874a80d4a8d73bf79603624465b3aeb0/gemrb/plugins/ACMReader

#pragma once

namespace Falltergeist
{
    namespace Format
    {
        namespace Acm
        {
            class Decoder
            {
                public:
                    Decoder(int lev_cnt);
                    virtual ~Decoder();

                    int init();

                    void decodeData(int *buffer, int blocks);

                private:
                    int _levels, _blockSize;
                    int *_memoryBuffer;

                    void _sub4d3fcc(short *memory, int *buffer, int sbSize, int blocks);

                    void _sub4d420c(int *memory, int *buffer, int sbSize, int blocks);
            };
        }
    }
}
