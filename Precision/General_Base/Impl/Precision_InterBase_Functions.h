#ifndef PRECISION_INTERBASE_FUNCTIONS_FOR_DYNAMIC_BASE_H_HHH__
#define PRECISION_INTERBASE_FUNCTIONS_FOR_DYNAMIC_BASE_H_HHH__

namespace Precision{
    template<typename IntegerType>
    IntegerType convert(
        const IntegerType&,
        const typename IntegerType::wrapper_type&
    );
}

#include "Precision_InterBase_Functions.inl"

#endif