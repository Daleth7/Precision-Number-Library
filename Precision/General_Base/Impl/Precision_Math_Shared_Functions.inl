#include <type_traits>
#include <cmath>
#include "Precision_Tags.h"
#include "Precision_Math_Shared_Helpers.h"
#include "Precision_Exception.h"

namespace Precision{
    namespace Math{
        namespace Helper{
            template <typename Number_Type>
            Number_Type sqrt_helper(const Number_Type& base, std::true_type)
                {return std::sqrt(base);}

            template <typename Number_Type>
            Number_Type sqrt_helper(const Number_Type& base, std::false_type){
                if(base.negative()){
                    throw exception(
                        exception::complex_number,
                        "Precision::Math::sqrt(Number_Type)"
                    );
                }else if(
                    base == Helper::cast(0, base) ||
                    base == Helper::cast(1, base)
                )   return base;
            //Uses Babylonian method:
            //  http://en.wikipedia.org/wiki/Methods_of_computing_square_roots
            //      #Babylonian_method
                Number_Type toreturn(base/Helper::cast(2, base)), old(0);
                while(!Helper::are_equal(old, toreturn, true)){
                    old = toreturn;
                    toreturn = (toreturn + base/toreturn)/Helper::cast(2, base);
                }
                return toreturn;
            }
        }

        template <typename Number_Type>
        Number_Type sqrt(const Number_Type& base)
            {return Helper::sqrt_helper(base,
                typename std::is_fundamental<Number_Type>::type());}

        template <typename Number_Type, typename Integer_Type>
        Number_Type root(const Number_Type& base, const Integer_Type& n){
            if(base.negative() && n.even()){
                throw exception(
                    exception::complex_number,
                    "Precision::Math::root(Number_Type, Integer_Type)"
                );
            }else if(
                base == Helper::cast(0, base) ||
                base == Helper::cast(1, base)
            )   return base;
        //Newton's method
            const Number_Type N(Helper::cast(n, base));
            Number_Type toreturn(base/Helper::cast(N, base)), old(0);
            while(!Helper::are_equal(old, toreturn, true)){
                old = toreturn;
                toreturn = ((N-Helper::cast(1, base))*toreturn
                    + base/exponentiate(toreturn, N))/N;
            }
            return toreturn;
        }

        namespace Helper{
            template <typename Integer_Type>
            Integer_Type factorial_range(
                const Integer_Type& f,
                const Integer_Type& s
            ){
                if(s == f)
                    return s;
                else if(s < f)
                    return 1;
                else if(f+Integer_Type(1) == s)
                    return f*s;
                else
                    return factorial_range(f, (f+s)/Integer_Type(2))
                    * factorial_range((f+s)/Integer_Type(2)+Integer_Type(1), s);
            }

            template <typename Number_Type>
            Number_Type gamma_helper(
                const Number_Type& z,
                size_t start, size_t lim
            ){
                //Used to help find the product of a sequence, or capital PI
                //  Use the divide and conquer technique to ease the
                //  multiplications
                if(lim < start)
                    return z;
                else if(start == lim)
                    return z+Helper::cast(start, z);
                else if(lim - 1 == start)
                    return (z+Helper::cast(start, z))*(z+Helper::cast(lim, z));
                else
                    return gamma_helper(z, start, lim/2)
                        * gamma_helper(z, lim/2+1, lim);
            }
        }

        template <typename Number_Type>
        Number_Type factorial_gamma(const Number_Type& z){
            //Based on Euler's gamma function
            if(z.negative()){
                throw exception(
                    exception::divide_by_zero,
                    "Precision::Math::factorial_gamma(Number_Type)"
                );
            }
            using int_type = typename Number_Type::Integer;
            auto lim = z.precision();
            return
                exponentiate(Number_Type(lim), z)
                * Helper::factorial_range(int_type(2), int_type(lim))
                / Helper::gamma_helper(z, 0, lim)
            ;
        }

        namespace Helper{
            template <typename Integer_Type>
            Integer_Type factorial_sift(
                const Integer_Type& start,
                std::true_type
            ){
                if(start < Integer_Type(2))   return 1;
                return factorial_range(Integer_Type(2), start);
            }

            template <typename Number_Type>
            Number_Type factorial_sift(
                const Number_Type& start,
                std::false_type
            ){
                if(start.is_integer())
                    return factorial_sift(start.integer(), std::true_type());
                else
                    return factorial_gamma(start);
            }
        }

        template <typename Integer_Type>
        Integer_Type factorial(const Integer_Type& start){
            if(start.negative()){
                throw exception(
                    exception::divide_by_zero,
                    "Precision::Math::factorial(Integer_Type)"
                );
            }
            return Helper::factorial_sift(start
                , typename std::is_base_of<Tag::Integral, Integer_Type>::type());
        }

        template <typename Floating_Type>
        Floating_Type ln(Floating_Type f){
            const Floating_Type k1(Helper::cast(1, f));
            if(f == k1)
                return Helper::cast(0, f);
            else if(f <= Helper::cast(0, f)){
                throw exception(
                    exception::complex_number,
                    "Precision::Math::ln(Floating_Type)"
                );
            }
            long long int i(1);
            const bool over(f > k1);
            if(over)
                f /= (f-k1);
            Floating_Type toreturn(Helper::cast(0, f)), old(-1);
            while(!Helper::are_equal(old, toreturn, true)){
                old = toreturn;
                toreturn
                    += over
                        //Taylor series of ln(y) where y = x/(x-1)
                    ? ( k1/(Helper::cast(i, f)*exponentiate(f, i)) )
                        //Taylor series of ln(a-1)
                    : ( (i%2 ? 1 : -1)*exponentiate(f-k1, i)/Helper::cast(i, f) )
                ;
                ++i;
            }
            return toreturn;
        }

        template <typename Floating_Type>
        Floating_Type log(const Floating_Type& b)
            {return ln(b)/ln(Helper::cast(10, b));}

        template <typename Floating_Type>
        Floating_Type log(
            const Floating_Type& x,
            const Floating_Type& base
        ){return ln(x)/ln(base);}

        namespace Helper{
            template <typename Integer_Type>
            bool is_negative(const Integer_Type& i)
                {return (i < Integer_Type(0));}

            bool is_negative(size_t);

            template <typename Number_Type, typename Integer_Type>
            Number_Type exponentiate(
                const Number_Type& base,
                Integer_Type e,
                std::true_type
            ){
                if(e == Integer_Type(0))
                    return Helper::cast(1, base);
                else if(e == Integer_Type(1))
                    return base;
                else if(e == Integer_Type(-1))
                    return Helper::cast(1, base) / base;

                Number_Type operand(base);
                if(is_negative(e))
                    operand = Helper::cast(1, base)/operand, e *= -1;
                    //Exponentiation by squaring
                if(e % Integer_Type(2) == Integer_Type(0))
                    return exponentiate( (operand * operand),
                        (e/Integer_Type(2)), std::true_type() );
                else
                    return operand * exponentiate( operand,
                        (e - Integer_Type(1)), std::true_type() );
            }

            template <typename Number_Type, typename Number_Type2>
            Number_Type2 exponentiate(
                const Number_Type& base,
                const Number_Type2& e,
                std::false_type
            ){
                if(e == Helper::cast(0, e))
                    return Helper::cast(1, base);
                else if(e == Helper::cast(1, e))
                    return base;
                else if(e == Helper::cast(-1, e))
                    return Helper::cast(1, base)/base;
                else if(e.is_integer())
                    return exponentiate(base, e.integer(), std::true_type());
                return Helper::cast(
                    exp(ln(e.positive() ? base : Helper::cast(1, base)/base)*e),
                    e
                );
            }

            template <typename Number_Type, typename Number_Type2>
            Number_Type exponentiate_sift(
                const Number_Type& f, const Number_Type2& s,
                std::true_type ttype
            ){return exponentiate(f, s, ttype);}

            template <typename Number_Type, typename Number_Type2>
            Number_Type exponentiate_sift(
                const Number_Type& f, const Number_Type2& s,
                std::false_type
            ){return exponentiate(f, s,
                typename std::is_base_of<Tag::Integral, Number_Type2>::type());}
        }

        template <typename Floating_Type>
        Floating_Type exp(const Floating_Type& e){
            Floating_Type
                toreturn(Helper::cast(1, e)),
                old(0),
                _x(toreturn)
            ;
            long long int i(0);
            while(!Helper::are_equal(toreturn, old, true)){
                old = toreturn;
                ++i;
                toreturn += (_x *= e)
                    / factorial(typename Floating_Type::Integer(i));
            }
            return toreturn;
        }

        template <typename Number_Type, typename Number_Type2>
        Number_Type exponentiate(const Number_Type& f, const Number_Type2& s){
            if(s == Number_Type2(0) && f == Number_Type(0)){
                throw exception(
                    exception::indeterminate,
                    "Precision::Math::exponentiate(Number_Type,Number_Type2)"
                );
            }
            return Helper::exponentiate_sift(f, s,
                typename std::is_integral<Number_Type2>::type());
        }

        template <typename Integer_Type>
        Integer_Type gcd(const Integer_Type& a, const Integer_Type& b){
    //Euclid's Algorithm:
    //http://en.wikipedia.org/wiki/Greatest_common_divisor
    //  #Using_Euclid.27s_algorithm
            Integer_Type toreturn(a), prev(b);
            while(prev != Integer_Type(0)){
                toreturn %= prev;
                std::swap(toreturn, prev);
            }

            return toreturn;
        }

        template <typename Integer_Type>
        Integer_Type lcm(const Integer_Type& a, const Integer_Type& b)
            {return (a*b)/gcd(a, b);}

        template <typename Number_Type>
        Number_Type agm(const Number_Type& _1, const Number_Type& _2){
            if(_1.sign() != _2.sign()) return Helper::cast(0, _1);
            Number_Type a(_1), g(_2);
            while(!Helper::are_equal(a, g, false)){
                Number_Type hold(a);
                (a += g)/=Helper::cast(2, a);
                g = sqrt(hold*g);
            }
            return a;
        }
    }
}
