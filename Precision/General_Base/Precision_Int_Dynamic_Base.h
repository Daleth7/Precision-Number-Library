#ifndef __PRECISION_INT_BASE_IMPL_DYNAMIC_BASE_H
#define __PRECISION_INT_BASE_IMPL_DYNAMIC_BASE_H

#include "Impl/Precision_Tags.h"
#include "Precision_Sign_Class.h"
#include "Precision_Image_Set_Wrapper.h"

#include <string>
#include <functional>
#include <cstddef>

/*  Template Parameters Clarification
    * The class will make use of a type that is a wrapper of the digit
        images and the number base.
    1) WrapperType  - The type that holds glyph type, digit type, and base
                        information. It is by swapping out objects of this type
                        that the dynamic number types can automatically
                        convert to another base and/or use a different glyph set.
                        * Must support the following:
                            * WrapperType::WrapperType
                                (iterator_type, iterator_type, base)
                            * WrapperType::WrapperType(const WrapperType&)
                            * WrapperType&
                                WrapperType::operator=(const WrapperType&)
                            * WrapperType::policy
                            * WrapperType::image_type
                            * WrapperType::iterator_type
                            * WrapperType::digit_type
                            * WrapperType::get_index(image_type, policy)
                            * WrapperType::operator[](size_type)
                            * WrapperType::plus()
                            * WrapperType::minus()
                            * WrapperType::point()
                            * WrapperType::exponent()
                            * WrapperType::space()
                            * WrapperType::slash()
                            * WrapperType::imaginary()
                            * WrapperType::base()
                            * WrapperType::digit0()
                        Defaulted to Precision::Image_Set_Wrapper::type<
                            char, char const *const,
                            Precision::byte_type,
                            Precision::Search_Policy::Normal
                            >.
    2) Container    - The container template used to store indices to the array.
                        Most STL containers will work. This shall be instantiated
                        as Container<digit_type>.
                        * Must support the following:
                            * Container::Container(size_type, digit_type)
                            * Container::Container(const Container&)
                            * Container& Container::operator=(const Container&)
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
    3) SignType     - The type used to represent the sign of the number, i.e.
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
        const std::string img_str("0123456789+-.E ");
        using dec_wrap_type = Precision::Image_Set_Wrapper::type
                                <char, std::string::const_iterator>;
        dec_wrap_type dec_wrap(img_str.cbegin(), img_str.cbegin()+10, 10);
        Precision::Dynamic::Int<dec_wrap_type> dyna_int(dec_wrap);
*/
#define INT_TEMPL_                      \
    template <                          \
        typename WrapperType,           \
        template <typename...>          \
            class Container,            \
        typename SignType               \
    >

#define INT_INST_   \
    Int <WrapperType, Container, SignType>

namespace Precision{
    namespace Dynamic_Base{
        template <
            typename WrapperType
                = Image_Set_Wrapper::type<char, char const *const>,
            template <typename...> class Container = default_container_type,
            typename SignType = SignClass
        >
        class Int : Tag::Integral, Tag::Signed, Tag::Dynamic {
            public:
        //Type aliases
                using wrapper_type  = WrapperType;
                using policy        = typename wrapper_type::policy;
                using img_iter_type = typename wrapper_type::iterator_type;
                using image_type    = typename wrapper_type::image_type;
                using str_type      = std::basic_string<image_type>;
                using lli           = long long int;
                using ld            = long double;
                using digit_type    = typename wrapper_type::digit_type;
                using diglist_type  = Container<digit_type>;
                using sign_type     = SignType;
                using size_type     = std::size_t;
        //Arithmetic operators
                Int& operator+=(const Int&);
                Int& operator-=(const Int&);
                Int& operator*=(const Int&);
                Int& operator/=(const Int&);
                Int& operator%=(const Int&);
                Int& operator--();
                Int operator--(int);
                Int& operator++();
                Int operator++(int);
        //Bitwise operators
                Int& operator&=(const Int&);
                Int& operator|=(const Int&);
                Int& operator^=(const Int&);
                Int& operator<<=(const Int&);
                Int& operator>>=(const Int&);
        //Logical Operators
                Int logical_and(const Int&)const;
                Int logical_or(const Int&)const;
                Int logical_xor(const Int&)const;
                Int logical_inversion()const;
                Int logical_shift(lli)const;
                Int logical_shift_left(size_type)const;
                Int logical_shift_right(size_type)const;
        //Read-only functions
                sign_type sign()const;
                str_type str()const;
            //Set the precision through parameter
                str_type sci_note(size_type=k_display_prec)const;
                str_type sci_note_w_spaces(size_type=k_display_prec)const;
                Int magnitude()const;
                size_type count_digits()const;
                short compare(const Int&)const;
                Int operator-()const;
            //Note that since there is no set limit to the number of digits,
            //  ~Int(0) shall throw an exception due to insufficient memory
            //  for allocation. Also note that because of the internal
            //  representation of the number, the number of bits flipped is
            //  equivalent to static_cast<Int>(log(Int, 2)) and is not
            //  guaranteed to be a multiple of eight. The sign is guaranteed
            //  to be negated.
                Int operator~()const;
                bool even()const;
                bool odd()const;
                bool positive()const;
                bool negative()const;
            //When calling digit(index) or digit_10(index), index shall be
            //  relative to the rightmost digit of the number, e.g. calling
            //  digit(0) on the number "123456789" will return "9".
                image_type digit(size_type)const;
                digit_type digit_10(size_type)const;
                diglist_type digit_list()const;

                digit_type base()const;
                const img_iter_type& digit0()const;
                const img_iter_type& symbols()const;
                const wrapper_type& wrapper()const;
        //Other modifiers
                wrapper_type wrapper(
                    const img_iter_type&,
                    const img_iter_type&,
                    digit_type
                );
                wrapper_type wrapper(const wrapper_type&);
                digit_type base(digit_type);
                img_iter_type digit0(const img_iter_type&);
                img_iter_type symbols(const img_iter_type&);
                void shift(lli);
                void shift_left(size_type);
                void shift_right(size_type);
                void sign(sign_type);
                void negate();
                void swap(Int&);
        //Constructors and destructor
            //Iterator versions
                constexpr Int(
                    const img_iter_type&,
                    const img_iter_type&,
                    digit_type
                );
                Int(
                    lli,
                    const img_iter_type&,
                    const img_iter_type&,
                    digit_type
                );
                Int(
                    const str_type&,
                    const img_iter_type&,
                    const img_iter_type&,
                    digit_type
                );
                constexpr Int(
                    const diglist_type&, sign_type,
                    const img_iter_type&,
                    const img_iter_type&,
                    digit_type
                );
            //Wrapper type versions
                constexpr Int(const wrapper_type&
                    = wrapper_type(img_iter_type(), img_iter_type(), 0));
                Int(lli, const wrapper_type&);
                Int(const str_type&, const wrapper_type&);
                Int(const diglist_type&, sign_type, const wrapper_type&);

                Int(const Int&)             = default;
                Int(Int&&)                  = default;
                Int& operator=(const Int&)  = default;
                Int& operator=(Int&&)       = default;
                ~Int()                      = default;
            protected:
                void parse(const str_type&);
                    //Helper divide function to allow modulus and divide
                    //  operators take about the same time to calculate.
                void divide(const Int& rhs, Int* div_req, Int* mod_req);
                    //Since AND, OR, and XOR implementations differ in
                    //  only the condition, use a helper to centralize
                    //  the implementation.
                Int& bitwise_operation(const Int&, unsigned short);
                Int logical_operation(const Int&, unsigned short)const;

            private:
                wrapper_type    m_wrap;
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
    Precision::Dynamic_Base::INT_INST_&,
    Precision::Dynamic_Base::INT_INST_&
);

#include "Impl/Precision_Int_Dynamic_Base.inl"

#undef INT_TEMPL_
#undef INT_INST_

#endif  //Include guard