#ifndef PRECISION_RANDOM_GENERAL_BASE_H__H_
#define PRECISION_RANDOM_GENERAL_BASE_H__H_

#include <cstddef>

namespace Precision{
    namespace General_Base{
        template <typename Integer_Type>
        class Random{
            public:
                using type = Integer_Type;
            //Read-only
                const type& seed()const;
                const type& max()const;
                const type& min()const;
                const type& and1()const;
                const type& and2()const;
                const type& and3()const;
                const type& and4()const;
                typename type::lli order_of_entropy()const;
                std::size_t push1()const;
                std::size_t push2()const;
                std::size_t push3()const;
                static constexpr typename type::digit_10_type base();
            //Retrieve and/or change state
                type operator()();
                Random<Integer_Type>& discard();
            //Change settings
                Random<Integer_Type>& seed(const type&);
                Random<Integer_Type>& max(const type&);
                Random<Integer_Type>& min(const type&);
                Random<Integer_Type>& and1(const type&);
                Random<Integer_Type>& and2(const type&);
                Random<Integer_Type>& and3(const type&);
                Random<Integer_Type>& and4(const type&);
                Random<Integer_Type>& order_of_entropy(typename type::lli);
                Random<Integer_Type>& push1(size_t);
                Random<Integer_Type>& push2(size_t);
                Random<Integer_Type>& push3(size_t);
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
                    const type& INmax = type(1).logical_shift(100),
                    const type& INmin = 0,
                //Order of Entropy
                //  --> Inf => More random but slower
                //  --> -Inf => Less random but faster
                //Resembles a K^(-e^2), i.e. a form of the Gaussian function
                //  Currently set on a relatively fast setting with low randomness
                    typename type::lli INorder_of_entropy = -5,
                //These help randomize each digit
                    const type& INand1 = 0xBFFFFFF6,
                    const type& INand2 = 0xBFFAFFFF,
                    const type& INand3 = 0xDDFECB7F,
                    const type& INand4 = 0xDFFFFFEF,
                //These help refresh the number to avoid repetition
                    std::size_t INpush1 = 8, std::size_t INpush2 = 11, std::size_t INpush3 = 18,
                //By default, the object shall discard the first few states
                //  to reach the maximum digit count.
                    bool call_discard = true
                );
            private:
                type m_seed, m_max, m_min;
                type m_and1, m_and2, m_and3, m_and4;
                typename type::lli m_order_of_entropy;
                std::size_t m_push1, m_push2, m_push3; 
        };
    }
}

#include "Impl/Precision_Random_General_Base.inl"

#endif