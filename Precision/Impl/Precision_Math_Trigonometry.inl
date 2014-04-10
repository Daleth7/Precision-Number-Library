#include "General_Base/Precision_Math_Shared_Functions.h"
#include "General_Base/Precision_Tags.h"
#include "General_Base/Precision_Math_Shared_Helpers.h"

#include <type_traits>

namespace Precision{
    namespace Math{
        template <typename Number_Type>
        Number_Type sin(const Number_Type& angle, const Number_Type& pi_val){
            Number_Type toreturn(
                angle
                - (
                    angle > pi_val
                    ? Helper::cast(0, angle)
                    : Helper::cast(angle/(Helper::cast(2, angle)*pi_val), angle)
                        . integer()*pi_val
                )
            );
            if(
                toreturn == Helper::cast(0, angle) ||
                toreturn.magnitude() == pi_val
            )   return Helper::cast(0, angle);
            else if(toreturn*Helper::cast(2, angle) == pi_val)
                return Helper::cast(angle.sign(), angle);
            Number_Type _x(toreturn), fact(Helper::cast(1, angle));
            const Number_Type _x_2(toreturn*toreturn);
            typename Number_Type::size_type i(1);
            while(true){
                const Number_Type old(toreturn);    _x.negate();    i += 2;
                toreturn += (_x *= _x_2)/(fact *= Helper::cast(i*(i-1), angle));
                if(old == toreturn)
                    return toreturn;
            }
        }

        template <typename Number_Type>
        Number_Type cos(const Number_Type& angle, const Number_Type& pi_val)
            {return sin(angle + pi_val/Helper::cast(2, angle), pi_val);}

        template <typename Number_Type>
        Number_Type tan(const Number_Type& angle, const Number_Type& pi_val)
            {return sin(angle, pi_val)/cos(angle, pi_val);}

        template <typename Number_Type>
        Number_Type csc(const Number_Type& angle, const Number_Type& pi_val)
            {return Helper::cast(1, angle)/sin(angle, pi_val);}

        template <typename Number_Type>
        Number_Type sec(const Number_Type& angle, const Number_Type& pi_val)
            {return Helper::cast(1, angle)/cos(angle, pi_val);}

        template <typename Number_Type>
        Number_Type cot(const Number_Type& angle, const Number_Type& pi_val)
            {return cos(angle, pi_val)/sin(angle, pi_val);}

        template <typename Number_Type>
        Number_Type arcsin(const Number_Type& result, const Number_Type& pi_val)
            {return pi_val/Helper::cast(2, result) - arccos(result, pi_val);}

        template <typename Number_Type>
        Number_Type arccos(const Number_Type& result, const Number_Type& pi_val)
            {return arcsec(Helper::cast(1, result)/result, pi_val);}

        template <typename Number_Type>
        Number_Type arctan(const Number_Type& result, const Number_Type& pi_val){
            const short comp(result.magnitude().compare(1));
            if(comp == 0)
                return Helper::cast(0, result);
            else if(comp == 1){
                auto casted = Helper::cast(4, result);
                casted.sign(result.sign());
                return pi_val/casted;
            }

            Number_Type toreturn(result), _x(result), old(0);
            const Number_Type _x_2(result*result);
            typename Number_Type::size_type N(1);
            while(!Helper::are_equal(toreturn, old, true)){
                old = toreturn;
                _x.negate();
                toreturn += (_x *= _x_2)/Helper::cast(N += 2, result);
            }
            return toreturn;
        }

        template <typename Number_Type>
        Number_Type arccsc(const Number_Type& result, const Number_Type& pi_val)
            {return pi_val/Helper::cast(2, result) - arcsec(result, pi_val);}

        template <typename Number_Type>
        Number_Type arcsec(const Number_Type& result, const Number_Type& pi_val){
            const short comp(result.magnitude().compare(1));
            if(comp == 0){
                auto casted = Helper::cast(2, result);
                casted.sign(result.sign());
                return pi_val/casted;
            }else if(comp == 1)
                return Helper::cast(0, result);

            Number_Type
                toreturn(result), _x(result), old(0),
                _odds(Helper::cast(1, result)), _evens(Helper::cast(1, result))
            ;
            const Number_Type _x_2(result*result);
            typename Number_Type::size_type N(0), i(1);
            while(!Helper::are_equal(toreturn, old, true)){
                old = toreturn;
                ++N;
                toreturn += (
                    (_odds *= Helper::cast(N*(N-1), result))
                    / (_evens *= Helper::cast(2*N, result))
                    / (_x *= _x_2)
                    / Helper::cast(i += 2, result)
                );
            }
            return toreturn;
        }

        template <typename Number_Type>
        Number_Type arccot(const Number_Type& result, const Number_Type& pi_val)
            {return pi_val/Helper::cast(2, result) - arctan(result, pi_val);}



        template <typename Number_Type>
        Number_Type sinh(
            const Number_Type& angle,
            const Number_Type& pi_val
        ){
            Number_Type toreturn(angle), _x(angle), old(0), D(1);
            const Number_Type _x_2(angle*angle);
            size_t N(1);
            while(!Helper::are_equal(toreturn, old, true)){
                old = toreturn;
                N += 2;
                toreturn += (_x *= _x_2)/(D *= Helper::cast(N*(N-1), angle));
            }
            return toreturn;
        }

        template <typename Number_Type>
        Number_Type cosh(
            const Number_Type& angle,
            const Number_Type& pi_val
        ){return exp(angle) - sinh(angle, pi_val);}

        template <typename Number_Type>
        Number_Type tanh(
            const Number_Type& angle,
            const Number_Type& pi_val
        ){return sinh(angle, pi_val)/cosh(angle, pi_val);}

        template <typename Number_Type>
        Number_Type csch(
            const Number_Type& angle,
            const Number_Type& pi_val
        ){return Helper::cast(1, angle)/sinh(angle, pi_val);}

        template <typename Number_Type>
        Number_Type sech(
            const Number_Type& angle,
            const Number_Type& pi_val
        ){return Helper::cast(1, angle)/cosh(angle, pi_val);}

        template <typename Number_Type>
        Number_Type coth(
            const Number_Type& angle,
            const Number_Type& pi_val
        ){return cosh(angle, pi_val)/sinh(angle, pi_val);}

        template <typename Number_Type>
        Number_Type arcsinh(const Number_Type& angle){
            Number_Type toreturn(angle), _x(angle), old(0);
            const Number_Type _x_2(angle*angle);
            size_t N(1);
            while(!Helper::are_equal(toreturn, old, true)){
                old = toreturn;
                _x.negate();
                Number_Type fact_sq(factorial(Helper::cast(++N, angle)));
                toreturn
                    = (_x *= _x_2)
                    * factorial(Helper::cast(2*N, angle))
                    / Helper::cast(2*N+1, angle)
                    / exponentiate(Helper::cast(2, angle), 2*N)
                    / (fact_sq * fact_sq)
                ;
            }
            return toreturn;
        }

        template <typename Number_Type>
        Number_Type arccosh(const Number_Type& angle){
            Number_Type e(Helper::cast(2, angle)*arctanh(angle));
            return e * (
                Helper::cast(1, angle)
                - angle
                - exp(-e) * ( ++sqrt(++(angle*angle)) )
            );
        }

        template <typename Number_Type>
        Number_Type arctanh(const Number_Type& angle){
            Number_Type toreturn(angle), _x(angle), old(0);
            const Number_Type _x_2(angle*angle);
            size_t N(1);
            while(!Helper::are_equal(toreturn, old, true)){
                old = toreturn;
                toreturn = (_x *= _x_2)/Helper::cast(N += 2, angle);
            }
            return toreturn;
        }

        template <typename Number_Type>
        Number_Type arccsch(const Number_Type& angle)
            {return arcsinh(Helper::cast(1, angle)/angle);}

        template <typename Number_Type>
        Number_Type arcsech(const Number_Type& angle)
            {return arccosh(Helper::cast(1, angle)/angle);}

        template <typename Number_Type>
        Number_Type arccoth(const Number_Type& angle)
            {return arctanh(Helper::cast(1, angle)/angle);}
    }
}