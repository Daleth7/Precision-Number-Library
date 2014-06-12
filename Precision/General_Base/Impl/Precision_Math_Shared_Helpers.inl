#include "Type_Traits_Extended/Type_Traits_Ext.h"

#include "Precision_Tags.h"

#include "Precision_Precedence_Pack.h"

namespace Precision{
    namespace Math{
        namespace Helper{
            template <typename Number_Type>
            bool are_equal(
                const Number_Type& f, const Number_Type& s,
                Tag::Fraction
            ){return f.decimal() == s.decimal();}

            template <typename Number_Type>
            bool are_equal_float_fund(
                const Number_Type& f, const Number_Type& s,
                std::true_type
            ){return ( (f < s+1e-7) && (s-1e-7 < f) );}

            template <typename Number_Type>
            bool are_equal_float_fund(
                const Number_Type& f, const Number_Type& s,
                std::false_type
            ){return f == s;}

            template <typename Number_Type, typename U>
            bool are_equal(const Number_Type& f, const Number_Type& s, U){
                return are_equal_float_fund(
                    f, s,
                    typename std::is_floating_point<Number_Type>::type()
                );
            }

            template <typename Number_Type>
            bool are_equal(const Number_Type& f, const Number_Type& s){
                return are_equal(
                    f, s,
                    typename Type_Trait::find_base<Number_Type, PRE_CATE_>::type()
                );
            }

            #include "Precision_Cast_System.inl"

            template <typename T>
            bool is_integer_prec(const T&, std::true_type)
                {return true;}

            template <typename T>
            bool is_integer_prec(const T& val, std::false_type)
                {return val.is_integer();}

            template <typename T>
            bool is_integer(const T&, std::true_type)
                {return typename std::is_integral<T>::type();}

            template <typename T>
            bool is_integer(const T& val, std::false_type){
                return is_integer_prec(
                    val,
                    typename std::is_base_of<Tag::Integral, T>::type()
                );
            }

            template <typename T>
            bool is_integer(const T& val)
                {return is_integer(val, typename std::is_fundamental<T>::type());}
        }
    }
}

#undef PRE_CATE_
#undef PRE_BASE_