#ifndef PRECISION_BASE3636_GENERAL_BASE__H__
#define PRECISION_BASE3636_GENERAL_BASE__H__

#include "General_Base.h"

#define DEFAULT_PARAMS Constant::type, Constant::glyphs, byte_type, 36

namespace Precision{
    namespace Base36{
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