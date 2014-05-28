#include <cmath>
#include <type_traits>

namespace Precision{
    namespace Math{
        template <typename Integer_Type>
        Integer_Type fibonacci(std::size_t* term_holder, std::size_t term){
            static Integer_Type toreturn(1), hold1(1), hold2(0);
            static std::size_t curr_term(2);
            if(term > 1)
                toreturn = 1, hold1 = 1, hold2 = 0, --term;
            curr_term += term;
            for(; term > 0; --term)
                hold2 = toreturn, toreturn += hold1, hold1 = hold2;
            if(term_holder != nullptr) *term_holder = curr_term;
            return toreturn;
        }

        template <typename OutIter>
        void erato_sieve(OutIter dest, std::size_t max){
            const std::size_t init_prime(2);
            static std::vector<bool> flags((max-init_prime), true);
            static bool already_filled(false);

            if(!already_filled && max != flags.size()){
                flags.resize(max);
                std::size_t init(0);
                while(init < flags.size()){
                    std::size_t iter(init), gap(init + init_prime);

                    while((iter += gap) < flags.size())
                        flags[iter] = false;
                    
                    while(!flags[++init] && init < flags.size());
                }
                already_filled = true;
            }
            for(std::size_t i(0); i < flags.size(); ++i){
                if(flags[i])
                    *(dest++) = (i + init_prime);
            }
        }

        namespace Helper{
            template <typename Number_Type>
            Number_Type rem_helper(
                const Number_Type& f,
                const Number_Type& s,
                std::true_type
            ){return std::remainder(f ,s);}

            template <typename Number_Type>
            Number_Type rem_helper(
                const Number_Type& f,
                const Number_Type& s,
                std::false_type
            ){return f % s;}
        }

        template <typename Floating_Type>
        Floating_Type remainder(const Floating_Type& f, const Floating_Type& s)
            {return Helper::rem_helper(f, s,
                typename std::is_fundamental<Floating_Type>::type());}
    }
}