#ifndef PRECISION_HEXADECIMAL_DEFAULT_TYPES_H__
#define PRECISION_HEXADECIMAL_DEFAULT_TYPES_H__

#include <cstddef>

namespace Precision{
    namespace Hexadecimal{
        namespace Default_Type{
            using digit                         = char;
            constexpr unsigned short k_base            = 16;
            struct image{
                static constexpr digit set[k_base]
                    {'0', '1', '2', '3', '4', '5', '6', '7',
                    '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
            };
        }
    }
}

#endif