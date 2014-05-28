#ifndef PRECISION_ABCDEF_BASE_INSTANTIATION__H__
#define PRECISION_ABCDEF_BASE_INSTANTIATION__H__

#include "General_Base.h"
#include "Instantiation_Packs/Precision_ABC_Default_Types.h"

#define DEFAULT_PARAMS                              \
    Default_Type::digit, Default_Type::image::set,  \
    byte_type, Default_Type::k_base

namespace Precision{
    namespace ABC{
        using Int       = General_Base::Int <DEFAULT_PARAMS>;
        using Float     = General_Base::Float <DEFAULT_PARAMS>;
        using Fract     = General_Base::Fract <DEFAULT_PARAMS>;
        using UInt      = General_Base::UInt <DEFAULT_PARAMS>;
        using UFloat    = General_Base::UFloat <DEFAULT_PARAMS>;
        using UFract    = General_Base::UFract <DEFAULT_PARAMS>;
    }
}

#undef DEFAULT_PARAMS

#endif