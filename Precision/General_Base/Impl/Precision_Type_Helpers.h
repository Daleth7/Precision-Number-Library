#ifndef TYPE_DETERMINERS_FOR_PRECISION___H___
#define TYPE_DETERMINERS_FOR_PRECISION___H___

/*
    Declare some helpers to decouple the type
    determining process from the classes that
    need it.
*/

#include <type_traits>
#include <limits>

namespace Precision{
    namespace Helper{
        template <typename T, typename CondType>
        struct is_fund{};

        template <typename T>
        struct is_fund<T, std::true_type>{
            using lli           = int;
            using size_type     = std::size_t;
            using digit_10_type = short int;

            static constexpr digit_10_type base = 10;
            static constexpr bool positive(T val)
                {return val > 0;}
        };

        template <typename T>
        struct is_fund<T, std::false_type>{
            using lli               = typename T::lli;
            using size_type         = typename T::size_type;
            using digit_10_type     = typename T::digit_10_type;

            static constexpr digit_10_type base = T::base();
            static constexpr bool positive(const T& val)
                {return val.positive();}
        };

    //Helper specifically for Random.
        template <typename T, typename CondType>
        struct rand_wrapper{};

        template <typename T>
        struct rand_wrapper<T, std::true_type>{
            static constexpr T max()
                {return std::numeric_limits<T>::max();}
        };

        template <typename T>
        struct rand_wrapper<T, std::false_type>{
            static constexpr T max()
                {return T(1).logical_shift_left(100);}
        };
    }
}

#endif