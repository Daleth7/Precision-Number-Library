#ifndef GENERALIZED_MATH_FUNCTION_TEMPLATES__H__
#define GENERALIZED_MATH_FUNCTION_TEMPLATES__H__

#include <utility>
#include "Shared_Constants.h"

namespace Precision{
    namespace Math{
        template <typename Number_Type>
        Number_Type sqrt(const Number_Type&);

        template <typename Number_Type, typename Integer_Type>
        Number_Type root(const Number_Type&, const Integer_Type&);

        template <typename Integer_Type>
        Integer_Type factorial_range(const Integer_Type&, const Integer_Type&);

        template <typename Number_Type>
        Number_Type factorial_gamma(const Number_Type&);

        template <typename Integer_Type>
        Integer_Type factorial(const Integer_Type&);

        template <typename Floating_Type>
        Floating_Type ln(Floating_Type);

        template <typename Floating_Type>
        Floating_Type log(const Floating_Type&);

        template <typename Floating_Type>
        Floating_Type log(
            const Floating_Type& x,
            const Floating_Type& base
        );

        template <typename Floating_Type>
        Floating_Type exp(const Floating_Type&);

        template <typename Number_Type, typename Number_Type2>
        Number_Type exponentiate(const Number_Type&, const Number_Type2&);

        template <typename Integer_Type>
        Integer_Type gcd(const Integer_Type&, const Integer_Type&);

        template <typename Integer_Type>
        Integer_Type lcm(const Integer_Type&, const Integer_Type&);

    //Arithmetic-Geometric mean
        template <typename Number_Type>
        Number_Type agm(const Number_Type&, const Number_Type&);
    }
}

#include "Precision_Math_Shared_Functions.inl"

#endif