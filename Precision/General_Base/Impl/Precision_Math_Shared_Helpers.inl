#include "Precision_Tags.h"

namespace Precision{
    namespace Math{
        namespace Helper{
        //are_equal is used in the case when a Fract might be passed to
        //  avoid infinite loops and recursions
            template <typename Number_Type>
            bool are_equal(
                const Number_Type& f, const Number_Type& s,
                bool by_precision, std::true_type
            ){return by_precision ? (f.decimal() == s.decimal()) : (f == s);}

            template <typename Number_Type>
            bool are_equal(
                const Number_Type& f, const Number_Type& s,
                bool, std::false_type
            ){return (f == s);}

            template <typename Number_Type>
            bool are_equal(
                const Number_Type& f, const Number_Type& s,
                bool by_precision
            ){return are_equal(f, s, by_precision,
                typename std::is_base_of<Tag::Fraction, Number_Type>::type());}

        //cast shall be used to safely convert among Precision types, mainly to
        //  ensure any cast to Fract or Float will also carry the precision
        //Needs another object from which to extract the precision.
            template <typename Number_Type>
            Number_Type cast(
                const Number_Type& n,
                const Number_Type&,
                std::true_type
            ){return n;}

            template <typename Number_Type1, typename Number_Type2>
            Number_Type1 cast2(
                const Number_Type2& n,
                const Number_Type1&,
                std::true_type
            ){return Number_Type1(n);}

            template <typename Number_Type1, typename Number_Type2>
            Number_Type1 cast2(
                const Number_Type2& n,
                const Number_Type1& sample,
                std::false_type
            ){return Number_Type1(n, sample.precision());}

            template <typename Number_Type1, typename Number_Type2>
            Number_Type1 cast(
                const Number_Type2& n,
                const Number_Type1& sample,
                std::false_type
            ){
                return cast2(
                    n, sample,
                    typename std::is_base_of<Tag::Integral, Number_Type1>::type()
                );
            }

            template <typename Number_Type1, typename Number_Type2>
            Number_Type1 cast(const Number_Type2& n, const Number_Type1& sample){
                return cast(
                    n, sample,
                    typename std::is_same<Number_Type1, Number_Type2>::type()
                );
            }
        }
    }
}
