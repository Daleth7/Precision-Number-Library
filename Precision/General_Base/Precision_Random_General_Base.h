#ifndef PRECISION_RANDOM_GENERAL_BASE_H_HH_H_
#define PRECISION_RANDOM_GENERAL_BASE_H_HH_H_

#include <cstddef>

#include "Impl/Precision_Type_Helpers.h"

namespace Precision{
    namespace General_Base{
        template <typename Integer_Type>
        class Random{
            private:
                using wrap = Helper::is_fund<Integer_Type,
                    typename std::is_fundamental<Integer_Type>::type>;
            public:
                using type          = Integer_Type;
                using lli           = typename wrap::lli;
                using size_type     = typename wrap::size_type;
                using digit_type    = typename wrap::digit_type;
            //Read-only
                const type& seed()const;
                const type& max()const;
                const type& min()const;
                const type& and1()const;
                const type& and2()const;
                const type& and3()const;
                const type& and4()const;
                lli order_of_entropy()const;
                size_type push1()const;
                size_type push2()const;
                size_type push3()const;
                static constexpr digit_type base();
            //Retrieve and/or change state
                type operator()();
                Random& discard();
            //Change settings
                Random& seed(const type&);
                Random& max(const type&);
                Random& min(const type&);
                Random& and1(const type&);
                Random& and2(const type&);
                Random& and3(const type&);
                Random& and4(const type&);
                Random& order_of_entropy(lli);
                Random& push1(size_type);
                Random& push2(size_type);
                Random& push3(size_type);
            //Constructor
                Random(
                //Seed
                    const type& INseed = 1,
                //Note about maximum:
                //  For base 10:
                //  As the generated numbers are forced to be 20 digits or less,
                //  the entropy shall decrease, and patterns will emerge. At 10
                //  digits or less, the random number generator will fail, that
                //  is, the generated numbers are no longer random after the first
                //  call. For random numbers with 20 digits or less, please use
                //  the Standard's random number generators.
                    const type& INmax = Helper::rand_wrapper<type,
                        typename std::is_fundamental<type>::type>::max(),
                    const type& INmin = 0,
                //By default, the object shall discard the first few states
                //  to reach the maximum digit count.
                    bool call_discard = true,
                //Order of Entropy
                //  --> Inf => More random but slower
                //  --> -Inf => Less random but faster
                //Resembles a K^(-e^2), i.e. a form of the Gaussian function
                //  Currently set on a relatively fast setting with low randomness
                    lli INorder_of_entropy = -5,
                //These help randomize each digit
                    const type& INand1 = 0xBFFFFFF6,
                    const type& INand2 = 0xBFFAFFFF,
                    const type& INand3 = 0xDDFECB7F,
                    const type& INand4 = 0xDFFFFFEF,
                //These help refresh the number to avoid repetition
                    size_type INpush1 = 8, size_type INpush2 = 11,
                    size_type INpush3 = 18
                );
            protected:
                type generate(std::true_type);
                type generate(std::false_type);
            private:
                type m_seed, m_max, m_min;
                type m_and1, m_and2, m_and3, m_and4;
                lli m_order_of_entropy;
                size_type m_push1, m_push2, m_push3; 
        };
    }
}

#include "Impl/Precision_Random_General_Base.inl"

#endif