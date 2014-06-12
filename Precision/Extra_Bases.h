#ifndef EXTRA_BASES_H_HHH___
#define EXTRA_BASES_H_HHH___

#include "Precision_Binary.h"
#include "Precision_Octal.h"
#include "Precision_Hexadecimal.h"
#include "Precision_ABC.h"
#include "Precision_Base36.h"

#define MAKE_BASE_MAKER_(TYPE, NAME)                                    \
    template <byte_type MakeBase>                                       \
    using make_type_##NAME = General_Base::TYPE                         \
        <Constant::type, Constant::glyphs, byte_type, MakeBase,         \
        Constant::symbols, default_container_type, SignClass>;          \
                                                                        \
    template <byte_type MakeBase, typename... Args>                     \
    make_type_##NAME<MakeBase> make_##NAME(                             \
        long double val,                                                \
        const Args&... args                                             \
    ){return make_type_##NAME<MakeBase>(val, args...);}                 \
                                                                        \
    template <byte_type MakeBase, typename... Args>                     \
    make_type_##NAME<MakeBase> make_##NAME(                             \
        const typename make_type_##NAME<MakeBase>::str_type& image,     \
        const Args&... args                                             \
    ){return make_type_##NAME<MakeBase>(image, args...);}
/*
    ){return make_type_##NAME<MakeBase>(image, args...);}               \
                                                                        \
                                                                        \
    using make_type_dyna_wrapper = Image_Set_Wrapper::type              \
        <Constant::type, Constant::type const *const, byte_type>;       \
    using make_type_dyna_##NAME = Dynamic_Base::TYPE                    \
        <make_type_dyna_wrapper, default_container_type, SignClass>;    \
                                                                        \
    template <typename... Args>                                         \
    make_type_dyna_##NAME make_dyna_##NAME(                             \
        byte_type make_base,                                            \
        long double val,                                                \
        const Args&... args                                             \
    ){                                                                  \
        return make_type_dyna_##NAME(                                   \
            val, args...,                                               \
            Constant::glyphs, Constant::symbols, make_base              \
            );                                                          \
    }                                                                   \
                                                                        \
    template <typename... Args>                                         \
    make_type_dyna_##NAME make_dyna_##NAME(                             \
        byte_type make_base,                                            \
        const make_type_dyna_##NAME::str_type& img,                     \
        const Args&... args                                             \
    ){                                                                  \
        return make_type_dyna_##NAME(                                   \
            img, args...,                                               \
            Constant::glyphs, Constant::symbols, make_base              \
            );                                                          \
    }
*/
namespace Precision{
    MAKE_BASE_MAKER_(Int, int)
    MAKE_BASE_MAKER_(Float, float)
    MAKE_BASE_MAKER_(Fract, fract)
    MAKE_BASE_MAKER_(UInt, uint)
    MAKE_BASE_MAKER_(UFloat, ufloat)
    MAKE_BASE_MAKER_(UFract, ufract)
}
#undef MAKE_BASE_MAKER_

#endif