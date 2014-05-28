#ifndef PRECISION_DEFAULT_INSTANTION_BASE_10_H__
#define PRECISION_DEFAULT_INSTANTION_BASE_10_H__

#include "General_Base.h"

#include "Instantiation_Packs/Precision_Default_Types.h"

#define DEFAULT_TEMPLATE_PARAMS                     \
    Default_Type::digit, Default_Type::image::set,  \
    byte_type, Default_Type::k_base

namespace Precision{
    using Int       = General_Base::Int <DEFAULT_TEMPLATE_PARAMS>;
    using Float     = General_Base::Float <DEFAULT_TEMPLATE_PARAMS>;
    using Fract     = General_Base::Fract <DEFAULT_TEMPLATE_PARAMS>;
    using UInt      = General_Base::UInt <DEFAULT_TEMPLATE_PARAMS>;
    using UFloat    = General_Base::UFloat <DEFAULT_TEMPLATE_PARAMS>;
    using UFract    = General_Base::UFract <DEFAULT_TEMPLATE_PARAMS>;
}

#include "Common_Overloads_and_Specializations.inl"

#undef DEFAULT_TEMPLATE_PARAMS

#endif
