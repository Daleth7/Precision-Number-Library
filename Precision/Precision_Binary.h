#ifndef PRECISION_BINARY_SPECIALIZATION
#define PRECISION_BINARY_SPECIALIZATION

#include "General_Base/Precision_Binary_Specialization.h"
#include "General_Base.h"

#define SPEC_PARAMS_  Constant::type, Constant::glyphs, block_type, 2,\
    Constant::symbols, default_container_type, SignClass

namespace Precision{
    namespace Binary{
        using Int   = General_Base::Int<SPEC_PARAMS_>;
        using Float = General_Base::Float<SPEC_PARAMS_>;
        using Fract = General_Base::Fract<SPEC_PARAMS_>;
        using UInt   = General_Base::Int<SPEC_PARAMS_>;
        using UFloat = General_Base::Float<SPEC_PARAMS_>;
        using UFract = General_Base::Fract<SPEC_PARAMS_>;
    }
}

#endif