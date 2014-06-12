#include "Precision_Tags.h"
#include "Precision_Math_Shared_Helpers.h"
#include "Precision_Exception.h"

#include <type_traits>
#include <cmath>

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
                    base == Helper::cast(base, 0) ||
                    base == Helper::cast(base, 0)
                )   return base;
            //Uses Babylonian method:
            //  http://en.wikipedia.org/wiki/Methods_of_computing_square_roots
            //      #Babylonian_method
                Number_Type
                    toreturn(base/Helper::cast(base, 2)),
                    old(Helper::cast(base, 0))
                ;
                while(!Helper::are_equal(old, toreturn)){
                    old = toreturn;
                    toreturn = (toreturn + base/toreturn)/Helper::cast(base, 2);
                }
                return toreturn;
            }
        }

        template <typename Number_Type>
        Number_Type sqrt(const Number_Type& base)
            {return Helper::sqrt_helper(base,
                typename std::is_fundamental<Number_Type>::type());}

        namespace Helper{
            template <typename Number_Type, typename Integer_Type>
            Number_Type root(
                const Number_Type& base,
                const Integer_Type& n,
                std::true_type
            ){
                if( (base < 0.0) && (n%2 == 0) ){
                    throw exception(
                        exception::complex_number,
                        "Precision::Math::root(Number_Type, Integer_Type)"
                    );
                }
            //Newton's method
                const Number_Type N(n);
                Number_Type toreturn(base/N), old(0);
                while(!Helper::are_equal(old, toreturn)){
                    old = toreturn;
                    toreturn = ((N-1)*toreturn
                        + base/std::pow(toreturn, N))/N;
                }
                return toreturn;
            }

            template <typename Number_Type, typename Integer_Type>
            Number_Type root(
                const Number_Type& base,
                const Integer_Type& n,
                std::false_type
            ){
                if(base.negative() && n.even()){
                    throw exception(
                        exception::complex_number,
                        "Precision::Math::root(Number_Type, Integer_Type)"
                    );
                }else if(
                    base == Helper::cast(base, 0) ||
                    base == Helper::cast(base, 1)
                )   return base;
            //Newton's method
                const Number_Type N(Helper::cast(base, n));
                Number_Type 
                    toreturn(base/Helper::cast(base, N)),
                    old(Helper::cast(base, 0))
                ;
                while(!Helper::are_equal(old, toreturn)){
                    old = toreturn;
                    toreturn = ((N-Helper::cast(base, 1))*toreturn
                        + base/exponentiate(toreturn, N))/N;
                }
                return toreturn;
            }
        }

        template <typename Number_Type, typename Integer_Type>
        Number_Type root(const Number_Type& base, const Integer_Type& n)
            {return Helper::root(base, n,
                typename std::is_fundamental<Number_Type>::type());}

        namespace Helper{
            template <typename Integer_Type>
            Integer_Type factorial_range(
                const Integer_Type& f,
                const Integer_Type& s
            ){
                if(s == f)
                    return s;
                else if(s < f)
                    return Helper::cast(f, 1);
                else if(f+Helper::cast(f, 1) == s)
                    return f*s;
                else
                    return factorial_range(f, (f+s)/Helper::cast(f, 2))
                    * factorial_range((f+s)/Helper::cast(f, 2)
                        + Helper::cast(f, 1), s);
            }

            template <typename Integer_Type>
            Integer_Type gamma_sift(
                const Integer_Type& start,
                std::true_type
            ){
                if(start < Helper::cast(start, 2))
                    return Helper::cast(start, 1);
                return factorial_range(Helper::cast(start, 2), start);
            }

            template <typename Number_Type>
            Number_Type gamma_sift(
                const Number_Type& z,
                std::false_type
            ){
                if(Helper::is_integer(z))
                    return factorial_sift(z.integer(), std::true_type());
                else{
                //Based on Euler's infinite product definition
                    Number_Type k(Helper::cast(z, 2));
                    const Number_Type k1 = Helper::cast(z, 1);
                    Number_Type
                        toreturn(exponentiate(k, z)/(k1+z)),
                        old(Helper::cast(z, 0))
                    ;
                    while(!Helper::are_equal(old, toreturn)){
                        old = toreturn;
                        toreturn *= exponentiate(k1+k.inverse(), z)
                            / (k1+z/k);
                        ++k;
                    }
                }
            }
        }

        template <typename Number_Type>
        Number_Type gamma(const Number_Type& z){
            if(z.negative()){
                throw exception(
                    exception::divide_by_zero,
                    "Precision::Math::gamma(Number_Type)"
                );
            }
            return Helper::gamma_sift(z,
                typename std::is_base_of<Number_Type, Tag::Integral>::type());
        }

        namespace Helper{
            template <typename Integer_Type>
            Integer_Type factorial_sift(
                const Integer_Type& start,
                std::true_type
            ){
                if(start < Helper::cast(start, 2))
                    return Helper::cast(start, 1);
                return factorial_range(Helper::cast(start, 2), start);
            }

            template <typename Number_Type>
            Number_Type factorial_sift(
                const Number_Type& start,
                std::false_type
            ){
                if(Helper::is_integer(start))
                    return factorial_sift(start.integer(), std::true_type());
                else
                    return gamma(start);
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
            const Floating_Type k1(Helper::cast(f, 1));
            if(f == k1)
                return Helper::cast(f, 0);
            else if(f <= Helper::cast(f, 0)){
                throw exception(
                    exception::complex_number,
                    "Precision::Math::ln(Floating_Type)"
                );
            }
            typedef long long int lli;
            lli i(1);
            const bool over(f > k1);
            if(over)
                f /= (f-k1);

            typedef Floating_Type F_TT; //Floating Truncated Type
            F_TT (*callbacks[2])(const F_TT&, const F_TT&, lli) = {
            //Taylor series of ln(a-1)
                [](const F_TT& fp, const F_TT& kp, lli ip)
                    {return Helper::cast(fp, ip%2 ? 1 : -1)
                        * exponentiate(fp-kp, ip)/Helper::cast(fp, ip);},
            //Taylor series of ln(y) where y = x/(x-1)
                [](const F_TT& fp, const F_TT& kp, lli ip)
                    {return kp/(Helper::cast(fp, ip)*exponentiate(fp, ip));}
            };

            Floating_Type
                toreturn(Helper::cast(f, 0)),
                old(Helper::cast(f, -1))
            ;
            while(!Helper::are_equal(old, toreturn)){
                old = toreturn;
                toreturn += callbacks[over](f, k1, i++);
            }
            return toreturn;
        }

        template <typename Floating_Type>
        Floating_Type log(const Floating_Type& b)
            {return ln(b)/ln(Helper::cast(b, 10));}

        template <typename Floating_Type>
        Floating_Type log(
            const Floating_Type& x,
            const Floating_Type& base
        ){return ln(x)/ln(base);}

        namespace Helper{
            template <typename Integer_Type>
            bool is_negative(const Integer_Type& i)
                {return (i < Helper::cast(i, 0));}

            template <typename Number_Type, typename Integer_Type>
            Number_Type exponentiate(
                const Number_Type& base,
                Integer_Type e,
                std::true_type
            ){
                if(e == Helper::cast(e, 0))
                    return Helper::cast(base, 1);
                else if(e == Helper::cast(e, 1))
                    return base;
                else if(e == Helper::cast(e, -1))
                    return Helper::cast(base, 1) / base;

                Number_Type operand(base);
                if(is_negative(e)){
                    operand = Helper::cast(base, 1)/operand;
                    e *= Helper::cast(e, -1);
                }
                    //Exponentiation by squaring
                if(e % Helper::cast(e, 2) == Helper::cast(e, 0))
                    return exponentiate( (operand * operand),
                        (e/Helper::cast(e, 2)), std::true_type() );
                else
                    return operand * exponentiate( operand,
                        (e - Helper::cast(e, 1)), std::true_type() );

            }

            template <typename Number_Type, typename Number_Type2>
            Number_Type exponentiate(
                const Number_Type& base,
                const Number_Type2& e,
                std::false_type
            ){
                if(e == Helper::cast(e, 0))
                    return Helper::cast(base, 1);
                else if(e == Helper::cast(e, 1))
                    return base;
                else if(e == Helper::cast(e, -1))
                    return Helper::cast(base, 1)/base;
                else if(Helper::is_integer(e))
                    return exponentiate(base, e.integer(), std::true_type());
                return Helper::cast(
                    e,
                    exp(ln(e.positive() ? base : Helper::cast(base, 1)/base)*e)
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
                toreturn(Helper::cast(e, 1)),
                old(Helper::cast(e, 0)),
                _x(toreturn)
            ;
            auto i(Helper::cast(typename Floating_Type::Integer(), 0));
            while(!Helper::are_equal(old, toreturn)){
                old = toreturn;
                ++i;
                toreturn += (_x *= e)/Helper::cast(_x, factorial(i));
            }
            return toreturn;
        }

        template <typename Number_Type, typename Number_Type2>
        Number_Type exponentiate(const Number_Type& f, const Number_Type2& s){
            if(s == Helper::cast(s, 0) && f == Helper::cast(f, 0)){
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
            while(prev != Helper::cast(a, 0)){
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
            if(_1.sign() != _2.sign()) return Helper::cast(_1, 0);
            Number_Type a(_1), g(_2);
            const Number_Type twos_temp(Helper::cast(a, 2));
            while(!Helper::are_equal(a, g)){
                Number_Type hold(a);
                (a += g)/=twos_temp;
                g = sqrt(hold*g);
            }
            return a;
        }
    }
}