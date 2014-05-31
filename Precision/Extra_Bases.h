#ifndef EXTRA_BASES_H_
#define EXTRA_BASES_H_

#include "Precision_Binary.h"
#include "Precision_Octal.h"
#include "Precision_Hexadecimal.h"
#include "Precision_ABC.h"
#include "Precision_Base36.h"

#ifdef USE_BASE_MAKER_

/* Temp solution until a more better method is found
*/
#define MAKE_TYPE(TYPE, BASE)   \
    General_Base::TYPE          \
    <Base36::image::type, Base36::image::glyphs, byte_type, BASE>

#define MAKE_TNUM_(TYPE, NAME, BASE)                                    \
    inline MAKE_TYPE(TYPE, BASE) make_##NAME##BASE(long long int val)   \
        {return MAKE_TYPE(TYPE, BASE)(val);}                            \
    inline MAKE_TYPE(TYPE, BASE) make_##NAME##BASE                      \
        (const MAKE_TYPE(TYPE, BASE)::str_type& image)                  \
    {return MAKE_TYPE(TYPE, BASE)(image);}

#define MAKE_BASE_MAKER_(TYPE, NAME)    \
    MAKE_TNUM_(TYPE, NAME, 2)           \
    MAKE_TNUM_(TYPE, NAME, 3)           \
    MAKE_TNUM_(TYPE, NAME, 4)           \
    MAKE_TNUM_(TYPE, NAME, 5)           \
    MAKE_TNUM_(TYPE, NAME, 6)           \
    MAKE_TNUM_(TYPE, NAME, 7)           \
    MAKE_TNUM_(TYPE, NAME, 8)           \
    MAKE_TNUM_(TYPE, NAME, 9)           \
    MAKE_TNUM_(TYPE, NAME, 10)          \
    MAKE_TNUM_(TYPE, NAME, 11)          \
    MAKE_TNUM_(TYPE, NAME, 12)          \
    MAKE_TNUM_(TYPE, NAME, 13)          \
    MAKE_TNUM_(TYPE, NAME, 14)          \
    MAKE_TNUM_(TYPE, NAME, 15)          \
    MAKE_TNUM_(TYPE, NAME, 16)          \
    MAKE_TNUM_(TYPE, NAME, 17)          \
    MAKE_TNUM_(TYPE, NAME, 18)          \
    MAKE_TNUM_(TYPE, NAME, 19)          \
    MAKE_TNUM_(TYPE, NAME, 20)          \
    MAKE_TNUM_(TYPE, NAME, 21)          \
    MAKE_TNUM_(TYPE, NAME, 22)          \
    MAKE_TNUM_(TYPE, NAME, 23)          \
    MAKE_TNUM_(TYPE, NAME, 24)          \
    MAKE_TNUM_(TYPE, NAME, 25)          \
    MAKE_TNUM_(TYPE, NAME, 26)          \
    MAKE_TNUM_(TYPE, NAME, 27)          \
    MAKE_TNUM_(TYPE, NAME, 28)          \
    MAKE_TNUM_(TYPE, NAME, 29)          \
    MAKE_TNUM_(TYPE, NAME, 30)          \
    MAKE_TNUM_(TYPE, NAME, 31)          \
    MAKE_TNUM_(TYPE, NAME, 32)          \
    MAKE_TNUM_(TYPE, NAME, 33)          \
    MAKE_TNUM_(TYPE, NAME, 34)          \
    MAKE_TNUM_(TYPE, NAME, 35)          \
    MAKE_TNUM_(TYPE, NAME, 36)          \

namespace Precision{
    MAKE_BASE_MAKER_(Int, int)
    MAKE_BASE_MAKER_(Float, float)
    MAKE_BASE_MAKER_(Fract, fract)
    MAKE_BASE_MAKER_(UInt, uint)
    MAKE_BASE_MAKER_(UFloat, ufloat)
    MAKE_BASE_MAKER_(UFract, ufract)
}

#undef MAKE_TNUM_
#undef MAKE_BASE_MAKER_

#endif

/* Desired Behaviour (Doesn't work)
#define MAKE_BASE_MAKER_(TYPE, NAME)                                        \
    template <byte_type MakeBase>                                           \
    using make_##NAME_type = General_Base::TYPE                             \
        <Base36::image::type, Base36::image::glyphs, byte_type, MakeBase>;  \
    template <byte_type MakeBase>                                           \
    make_##NAME_type<MakeBase> make_##NAME(long long int val)               \
        {return make_##NAME_type<MakeBase>(val);}                           \
    template <byte_type MakeBase>                                           \
    make_##NAME_type<MakeBase> make_##NAME                                  \
        (typename const make_##NAME_type<MakeBase>::str_type& image)        \
    {return make_##NAME_type<MakeBase>(image);}

namespace Precision{
    MAKE_BASE_MAKER_(Int, int)
    MAKE_BASE_MAKER_(Float, float)
    MAKE_BASE_MAKER_(Fract, fract)
    MAKE_BASE_MAKER_(UInt, uint)
    MAKE_BASE_MAKER_(UFloat, ufloat)
    MAKE_BASE_MAKER_(UFract, ufract)
}
*/

#endif