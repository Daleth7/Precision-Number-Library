#ifndef __PRECISION_INT_BASE_IMPL_GENERAL_BASE_H
#define __PRECISION_INT_BASE_IMPL_GENERAL_BASE_H

#include <string>
#include <functional>
#include <cstddef>

#include "Impl/Precision_Tags.h"
#include "Impl/Shared_Constants.h"
#include "Precision_Sign_Class.h"

/*  Template Parameters Clarification
    * The class will make use of an array with external linkage provided
        by the instantiator, e.g.
        constexpr char digits[10] {'0', '1', '2', '3', '4',
            '5', '6', '7', '8', '9'};
    1) CharT        - The type of character or image used to represent each digit
                        in Base N. Must be compatible as a template parameter to
                        std::basic_string<T>. The string type (str_type) of the
                        class shall be instantiated as std::basic_string<CharT>.
                        The following or the equivalent of the following
                        functions must be supported for type CharT:
                        * std::istream& operator>>(std::istream&, CharT&);
                        * bool operator==(const CharT&, const CharT&);
    2) _0           - A pointer to the first digit in an array containing the
                        images of each digit. The array must have external
                        linkage.
                        Important note: It is the responsibility of the
                        instantiator to ensure _0 is a valid parameter and that
                        the array pointed to contains the appropriate images.
    3) ByteType     - The type used for the computer representation of each
                        digit. This type also sets the maximum base that may
                        be used and affects the dynamic storage size. Defaulted
                        to Precision::byte_type, which is guaranteed to allow a
                        base up to at least 127 and is guaranteed to be at least
                        one byte in size. It is recommended to use
                        Precision::byte_type for small bases.
    4) Base         - The base N the class shall represent. Defaulted to 10.
    5) _symbols     - A pointer to the first symbol in an array with external
                        linkage and that contains the images of each symbol.
                        Each symbol is further defined below in the order it
                        should appear in the array.
        * plus symbol       - An image depicting the plus sign to indicate a
                                positive number as in "+123".
        * minus symbol      - An image depicting the minus sign to indicate a
                                negative number as in "-123".
        * point symbol      - An image depicting the decimal point to indicate a
                                separation between a number's whole part and
                                decimal part as in "123.456".
        * exponent symbol   - An image depicting the exponential sign to represent
                                a power of 10 as in "1.23 E 456" which is
                                equivalent to writing "1.23 * 10^456".
        * space symbol      - An image depicting an empty space between two other
                                images as in "+ 1234".
                        The above five symbols are required as the minimum.
                        Depending on what the number type is tagged with from
                        Precision::Tag, there may be additional symbols needed.
        * slash symbol      - An image depicting the slash sign to indicate a
                                fractional number as in "12/345". Required for
                                Fraction number types, tagged with Tag::Fraction.
        * imaginary symbol  - An image depicting the imaginary number to indicate
                                a complex number as in "a + bi". Required for
                                Complex number types, tagged with Tag::Complex.
                        _symbols is defaulted to Constant::symbols which points
                        to an array containing images of type const char:
                            * plus symbol:      '+'
                            * minus symbol:     '-'
                            * point symbol:     '.'
                            * exponent symbol:  'E'
                            * space symbol:     ' '
                            * slash symbol:     '/'
                            * imaginary symbol: 'i'
                        Important note: It is the responsibility of the
                        instantiator to ensure _symbols is a valid parameter and
                        that the array pointed to contains the appropriate
                        symbols.
    6) Container    - The container used to store indices to the array.
                        Most STL containers will work.
                        * Must support the following:
                            * Container::Container(size_type, digit_type)
                            * Bidirectional iterators
                            * Container::begin()
                            * Container::end()
                            * Container::crbegin()
                            * Container::crend()
                            * Container::push_back()
                            * Container::size()
                            * Container::insert(iterator, size_type, digit_type)
                            * Container::erase(iterator, size_type)
                            * Container::erase(iterator)
                        Defaulted to Precision::default_container_type.
    7) SignType     - The type used to represent the sign of the number, i.e.
                        whether it is positive or negative. Must support the
                        following:
                            * signed_integral_type SignType::value()const
                            * bool SignType::positive()const
                            * bool SignType::negative()const
                            * void SignType::negate()
                            * void SignType::make_positive()
                            * void SignType::make_negative()
                            * SignType::SignType(sign_integral_type)
                        By convention, all number types in the Precision namespace
                        shall abide by the following rules:
                            * signed short(1) == positive
                            * signed short(-1) == negative
                        Defaulted to Precision::SignClass.

    Example Instantiation:
        constexpr char digit_image[10] {'0', '1', '2', '3', '4',
            '5', '6', '7', '8', '9'};
        using Int = Precision::General_Base::Int<char, digit_image>;
*/
#define INT_TEMPL_                      \
    template <                          \
        typename CharT,                 \
        CharT const *const _0,          \
        typename ByteType,              \
        ByteType Base,                  \
        CharT const *const _symbols,    \
        template <typename...>          \
            class Container,            \
        typename SignType               \
    >

#define INT_INST_   \
    Int <CharT, _0, ByteType, Base, _symbols, Container, SignType>

namespace Precision{
    namespace General_Base{
        template <
            typename CharT, CharT const *const _0,
            typename ByteType = byte_type, ByteType Base = 10,
            CharT const *const _symbols = Constant::symbols,
            template <typename...> class Container = default_container_type,
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
            //When calling digit(index) or digit_10(index), index shall be
            //  relative to the rightmost digit of the number, e.g. calling
            //  digit(0) on the number "123456789" will return "9".
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