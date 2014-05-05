#ifndef OCTAL_BASE_DEFAULT_TYPES_H__
#define OCTAL_BASE_DEFAULT_TYPES_H__

#include <cstddef>

namespace Precision{
    namespace Octal{
        namespace Default_Type{
            using digit                 = char;
            constexpr unsigned short k_base    = 8;
            struct image{
                static constexpr digit set[k_base]
                    {'0', '1', '2', '3', '4', '5', '6', '7'};
            };
        }
    }
}

#endif