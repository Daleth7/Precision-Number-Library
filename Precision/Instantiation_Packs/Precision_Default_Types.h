#ifndef PRECISION_DEFAULT_INSTANTIATION__PACK__H__
#define PRECISION_DEFAULT_INSTANTIATION__PACK__H__

#include <cstddef>

namespace Precision{
    namespace Default_Type{
        using digit                         = char;
        constexpr unsigned short k_base            = 10;
        struct image{
            static constexpr digit set[k_base]
                {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
        };
    }
}

#endif