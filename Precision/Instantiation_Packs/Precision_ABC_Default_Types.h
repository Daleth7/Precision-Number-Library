#ifndef PRECISION_ABCDEF_DEFAULT_TYPES__H__
#define PRECISION_ABCDEF_DEFAULT_TYPES__H__

#include <cstddef>

namespace Precision{
    namespace ABC{
        namespace Default_Type{
            using digit                 = char;
            constexpr unsigned short k_base    = 26;
            struct image{
                static constexpr digit set[k_base]
                    {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
                    'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
                    'u', 'v', 'w', 'x', 'y', 'z'};
            };
        }
    }
}

#endif