#ifndef PRECISION_MATH_TRIG_FUNCTIONS_GENERAL_BASE__H__
#define PRECISION_MATH_TRIG_FUNCTIONS_GENERAL_BASE__H__

#include "General_Base/Impl/Shared_Constants.h"

//Trigonomic functions -- default is radians
namespace Precision{
    namespace Math{
        template <typename Number_Type>
        Number_Type sin(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type cos(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type tan(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type csc(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type sec(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type cot(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type asin(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type acos(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type atan(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type acsc(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type asec(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type acot(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );



        template <typename Number_Type>
        Number_Type sinh(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type cosh(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type tanh(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type csch(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type sech(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type coth(
            const Number_Type&,
            const Number_Type& = Number_Type(k_pi_str)
        );

        template <typename Number_Type>
        Number_Type asinh(const Number_Type&);

        template <typename Number_Type>
        Number_Type acosh(const Number_Type&);

        template <typename Number_Type>
        Number_Type atanh(const Number_Type&);

        template <typename Number_Type>
        Number_Type acsch(const Number_Type&);

        template <typename Number_Type>
        Number_Type asech(const Number_Type&);

        template <typename Number_Type>
        Number_Type acoth(const Number_Type&);
    }
}

#include "Precision_Math_Trigonometry.inl"

#endif
