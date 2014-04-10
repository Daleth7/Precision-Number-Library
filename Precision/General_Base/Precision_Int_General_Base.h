#ifndef __PRECISION_INT_BASE_IMPL_GENERAL_BASE_H
#define __PRECISION_INT_BASE_IMPL_GENERAL_BASE_H

#include <string>
#include <functional>
#include <vector>
#include <cstddef>

#include "Precision_Tags.h"
#include "Shared_Constants.h"
#include "Precision_Sign_Class.h"

/*  Template Parameters Clarification
    * The class will make use of a compile-time array provided
        by the instantiator, e.g.
        constexpr char digits[10] {'0', '1', '2', '3', '4',
            '5', '6', '7', '8', '9'};
    1) CharT        - The type of character used to represent each digit in Base N
                        Must be compatible as a template parameter to
                        std::basic_string<T>. The string type (str_type) of the
                        class shall be instantiated as std::basic_string<CharT>.
    2) _0           - A pointer to the first element in the array
    3) ByteType     - The type used for the computer representation of the
                        number. This type also sets the maximum base that may
                        be used and affects the dynamic storage size. Defaulted
                        to precision_byte_type, which is guaranteed to allow a
                        base up to at least 127 and is guaranteed to be at least
                        one byte in size. It is recommended to use
                        precision_byte_type for small bases.
    4) Base         - The base N the class shall represent. Defaulted to 10.
    5) _plus        - A constant of type CharT which will represent the positive
                        sign, such as '+'. Defaulted to CharT('+').
    6) _neg         - A constant of type CharT which will represent the negative
                        sign, such as '-'. Defaulted to CharT('-').
    7) _point        - A constant of type CharT which will represent the decimal
                        point separating the integer portion of the number from
                        the decimal portion of the number, such as '.'.
                        Defaulted to CharT('.').
    8) _exp         - A constant of type CharT which will represent the
                        exponentiation sign, such as 'E' as in 1.23E-02.
                        Defaulted to CharT('E').
    9) _space       - A constant of type CharT which will represent the space
                        character, such as ' '. Defaulted to CharT(' ').
    10) Container    - The container used to store pointers to the array.
                        Most STL containers will work.
                        * Must support the following methods:
                            * Container::Container(size_type, digit_type)
                            * Bidirectional iterators
                            * Container::begin()
                            * Container::end()
                            * Container::rbegin()
                            * Container::rend()
                            * Container::push_back()
                            * Container::size()
                            * Container::insert(iterator, size_type, digit_type)
                            * Container::erase(iterator, size_type)
                            * Container::erase(iterator)
                        Defaulted to std::vector.
    11) SignType    - The type used to represent the sign of the number. Must
                        support the following methods:
                            * primitve_integral_type SignType::value()const
                            * bool SignType::positive()const
                            * bool SignType::negative()
                            * void SignType::negate()
                            * void SignType::make_positive()
                            * void SignType::make_negative()
                            * SignType::SignType(primitive_integral_type)
                        Defaulted to Precision::SignClass.

    Example Instantiation:
        constexpr char digit_image[10] {'0', '1', '2', '3', '4',
            '5', '6', '7', '8', '9'};
        using Int = Precision::General_Base::Int
                    <char, digit_image, precision_byte_type, 10>;
*/
#define INT_TEMPL_              \
    template <                  \
        typename CharT,         \
        CharT const *const _0,  \
        typename ByteType,      \
        ByteType Base,          \
        CharT _plus,            \
        CharT _neg,             \
        CharT _point,           \
        CharT _exp,             \
        CharT _space,           \
        template <typename...>  \
            class Container,    \
        typename SignType       \
    >

#define INT_INST_ Int <                     \
        CharT, _0, ByteType, Base,          \
        _plus, _neg, _point, _exp, _space,  \
        Container, SignType                 \
    >

namespace Precision{
    namespace General_Base{
        template <
            typename CharT, CharT const *const _0,
            typename ByteType = precision_byte_type, ByteType Base = 10,
            CharT _plus = CharT('+'), CharT _neg = CharT('-'),
            CharT _point = CharT('.'), CharT _exp = CharT('E'),
            CharT _space = CharT(' '),
            template <typename...> class Container = std::vector,
            typename SignType = SignClass
        >
        class Int : Tag::Integral, Tag::Signed {
            public:
        //Type aliases
                using str_type      = std::basic_string<CharT>;
                using lli           = long long int;
                using ld            = long double;
                using image_type    = CharT;
                using digit_type    = ByteType;
                using diglist_type  = Container<digit_type>;
                using digit_10_type = digit_type;
                using sign_type     = SignType;
                using size_type     = std::size_t;
        //Arithmetic operators
                INT_INST_& operator+=(const INT_INST_&);
                INT_INST_& operator-=(const INT_INST_&);
                INT_INST_& operator*=(const INT_INST_&);
                INT_INST_& operator/=(const INT_INST_&);
                INT_INST_& operator%=(const INT_INST_&);
                INT_INST_& operator--();
                INT_INST_ operator--(int);
                INT_INST_& operator++();
                INT_INST_ operator++(int);
        //Bitwise operators
                INT_INST_& operator&=(const INT_INST_&);
                INT_INST_& operator|=(const INT_INST_&);
                INT_INST_& operator^=(const INT_INST_&);
                INT_INST_& operator<<=(const INT_INST_&);
                INT_INST_& operator>>=(const INT_INST_&);
        //Logical Operators
                INT_INST_ logical_and(const INT_INST_&)const;
                INT_INST_ logical_or(const INT_INST_&)const;
                INT_INST_ logical_xor(const INT_INST_&)const;
                INT_INST_ logical_inversion()const;
                INT_INST_ logical_shift(lli)const;
                INT_INST_ logical_shift_left(size_type)const;
                INT_INST_ logical_shift_right(size_type)const;
        //Read-only functions
                sign_type sign()const;
                str_type str()const;
            //Set the precision through parameter
                str_type sci_note(size_type=k_display_prec)const;
                str_type sci_note_w_spaces(size_type=k_display_prec)const;
                INT_INST_ magnitude()const;
                size_type count_digits()const;
                short compare(const INT_INST_&)const;
                INT_INST_ operator-()const;
            //Note that since there is no set limit to the number of digits,
            //  ~Int(0) shall throw an exception due to insufficient memory
            //  for allocation. Also note that because of the internal
            //  representation of the number, the number of bits flipped is
            //  equivalent to static_cast<Int>(log(Int, 2)) and is not
            //  guaranteed to be a multiple of eight. The sign is guaranteed
            //  to be negated.
                INT_INST_ operator~()const;
                bool even()const;
                bool odd()const;
                bool positive()const;
                bool negative()const;
                image_type digit(size_type)const;
                digit_10_type digit_10(size_type)const;

                static constexpr digit_10_type base();
                static constexpr image_type const* digit0();
        //Other modifiers
                void shift(lli);
                void shift_left(size_type);
                void shift_right(size_type);
                void sign(sign_type);
                void negate();
                void swap(INT_INST_&);
        //Constructors and destructor
                Int(lli=0);
                Int(const str_type&);
                Int(const diglist_type&, sign_type);

                Int(const INT_INST_&)             =default;
                Int(INT_INST_&&)                  =default;
                Int& operator=(const INT_INST_&)  =default;
                Int& operator=(INT_INST_&&)       =default;
                ~Int()                            =default;
            protected:
                    //Helper divide function to allow modulus and divide
                    //  operators take about the same time to calculate.
                void divide(
                    const INT_INST_& rhs,
                    INT_INST_* div_req, INT_INST_* mod_req
                );
                    //Since AND, OR, and XOR implementations differ in
                    //  only the condition, use a helper to centralize
                    //  the implementation.
                INT_INST_& bitwise_operation(
                    INT_INST_,
                    const std::function<bool(bool,bool)>&
                );
                INT_INST_ logical_operation(
                    const INT_INST_&,
                    const std::function<digit_10_type
                        (digit_10_type,digit_10_type)>&
                )const;
            private:
            //Numbers are stored in reverse, e.g. 190 040 002 would be
            //   stored as 002 040 091. The number is reversed because
            //   the length is varied according to the leftmost side.
                diglist_type    m_number;
                sign_type       m_sign;
        };

        INT_TEMPL_
        INT_INST_ operator+(INT_INST_, const INT_INST_&);
        INT_TEMPL_
        INT_INST_ operator-(INT_INST_, const INT_INST_&);
        INT_TEMPL_
        INT_INST_ operator*(INT_INST_, const INT_INST_&);
        INT_TEMPL_
        INT_INST_ operator/(INT_INST_, const INT_INST_&);
        INT_TEMPL_
        INT_INST_ operator%(INT_INST_, const INT_INST_&);

        INT_TEMPL_
        INT_INST_ operator&(INT_INST_, const INT_INST_&);
        INT_TEMPL_
        INT_INST_ operator|(INT_INST_, const INT_INST_&);
        INT_TEMPL_
        INT_INST_ operator^(INT_INST_, const INT_INST_&);
        INT_TEMPL_
        INT_INST_ operator>>(INT_INST_, const INT_INST_&);
        INT_TEMPL_
        INT_INST_ operator<<(INT_INST_, const INT_INST_&);

        INT_TEMPL_
        bool operator==(const INT_INST_&, const INT_INST_&);
        INT_TEMPL_
        bool operator!=(const INT_INST_&, const INT_INST_&);
        INT_TEMPL_
        bool operator>=(const INT_INST_&, const INT_INST_&);
        INT_TEMPL_
        bool operator<=(const INT_INST_&, const INT_INST_&);
        INT_TEMPL_
        bool operator>(const INT_INST_&, const INT_INST_&);
        INT_TEMPL_
        bool operator<(const INT_INST_&, const INT_INST_&);
        INT_TEMPL_
        bool operator!(const INT_INST_&);
    }
}

INT_TEMPL_
void swap(
    Precision::General_Base::INT_INST_&,
    Precision::General_Base::INT_INST_&
);

#include "Impl/Precision_Int_General_Base.inl"

#undef INT_TEMPL_
#undef INT_INST_

#endif  //Include guard