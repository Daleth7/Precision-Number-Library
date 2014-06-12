#ifndef PRECISON_MATH_SHARED_HELPERS__H__
#define PRECISON_MATH_SHARED_HELPERS__H__

#include <type_traits>

namespace Precision{
    namespace Math{
        namespace Helper{
        //are_equal is used in the case when the comparison MUST be
        //  by precision. This is especially important in the case
        //  of Fraction types, to avoid infinite loops or recursions.
            template <typename Number_Type>
            bool are_equal(const Number_Type& f, const Number_Type& s);

        //cast shall be used to safely convert among Precision types, mainly to
        //  ensure any cast to Fract or Float will also carry the precision.
        //  This helps ensure no loss in precision while not requiring the
        //      number type to declare a precision() function.
        //Needs another object from which to extract the precision.
            template <typename Number_Type1, typename Number_Type2>
            Number_Type1 cast(const Number_Type1& sample, const Number_Type2&);
            template <typename Number_Type1, typename Number_Type2>
            Number_Type1 cast(const Number_Type1& sample, Number_Type2&&);

        //is_integer and integer are used to relax the requirement for a type
        //  to declare and define is_integer and integer members.
            template <typename T>
            bool is_integer(const T&);
        }
    }
}

#include "Precision_Math_Shared_Helpers.inl"

#endif