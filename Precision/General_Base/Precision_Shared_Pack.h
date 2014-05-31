#ifndef SHARED_INSTANTIATION_PACK__H__
#define SHARED_INSTANTIATION_PACK__H__

namespace Precision{
    namespace Base36{
        struct image{
            using type = char;

            static constexpr type glyphs[36] = {
                '0', '1', '2', '3', '4', '5', '6',
                '7', '8', '9', 'A', 'B', 'C', 'D',
                'E', 'F', 'G', 'H', 'I', 'J', 'K',
                'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                'S', 'T', 'U', 'V', 'W', 'X', 'Y',
                'Z'
            };
        };
    }
}

#endif