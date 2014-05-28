#ifndef PRECISON_MATH_SHARED_HELPERS__H__
#define PRECISON_MATH_SHARED_HELPERS__H__

namespace Precision{
    namespace Math{
        namespace Helper{
        //are_equal is used in the case when a Fract might be passed to
        //  avoid infinite loops and recursions
            template <typename Number_Type>
            bool are_equal(
                const Number_Type& f, const Number_Type& s,
                bool by_precision
            );

        //cast shall be used to safely convert among Precision types, mainly to
        //  ensure any cast to Fract or Float will also carry the precision.
        //  This helps ensure no loss in precision while not requiring the
        //      number type to define a precision() function.
        //Needs another object from which to extract the precision.
            template <typename Number_Type1, typename Number_Type2>
            Number_Type1 cast(const Number_Type2&, const Number_Type1& sample);
        }
    }
}

#include "Precision_Math_Shared_Helpers.inl"

#endif