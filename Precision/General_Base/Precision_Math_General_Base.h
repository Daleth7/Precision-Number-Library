#ifndef MATH_GEN_BASE_I_H_HH
#define MATH_GEN_BASE_I_H_HH

namespace Precision{
    namespace Math{
        template <typename Integer_Type>
        Integer_Type fibonacci(size_t* =nullptr, size_t=1);

        template <typename OutIter>
        void erato_sieve(OutIter dest, size_t max);

        template <typename Floating_Type>
        Floating_Type remainder(const Floating_Type&, const Floating_Type&);
    }
}

#include "Impl/Precision_Math_General_Base.inl"

#endif
