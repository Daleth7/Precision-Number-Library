#ifndef __PRECISION_INT_BASE_IMPL_ABSTRACT_BASE_H
#define __PRECISION_INT_BASE_IMPL_ABSTRACT_BASE_H

#include "Impl/Precision_Tags.h"
#include "Impl/Shared_Constants.h"
#include "Precision_Sign_Class.h"

#include <string>
#include <functional>
#include <cstddef>

/*  Template Parameters Clarification
    1) ByteType     - The type used for the computer representation of each
                        digit. This type also sets the maximum base that may
                        be used and affects the dynamic storage size. Defaulted
                        to Precision::byte_type, which is guaranteed to allow a
                        base up to 64 and is guaranteed to be at least
                        one byte in size. It is recommended to use
                        Precision::byte_type for small bases.
    2) Base         - The base N the class shall represent. Defaulted to 10.
    3) Container    - The container template used to store indices to the array.
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
    4) SignType     - The type used to represent the sign of the number, i.e.
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
        using Int = Precision::General_Base::Int<int, 25>;
*/
#define INT_TEMPL_                      \
    template <                          \
        typename ByteType,              \
        ByteType Base,                  \
        template <typename...>          \
            class Container,            \
        typename SignType               \
    >

#define INT_INST_ Int <ByteType, Base, Container, SignType>

namespace Precision{
    namespace General_Base{
        namespace Abstract{
            template <
                typename ByteType = byte_type, ByteType Base = 10,
                template <typename...> class Container = default_container_type,
                typename SignType = SignClass
            >
            class Int : Tag::Integral, Tag::Signed, Tag::Static {
                public:
            //Type aliases
                    using lli           = long long int;
                    using ld            = long double;
                    using digit_type    = ByteType;
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
                    digit_type digit_10(size_type)const;
                    diglist_type digit_list()const;

                    static constexpr digit_type base();
            //Other modifiers
                    void shift(lli);
                    void shift_left(size_type);
                    void shift_right(size_type);
                    void sign(sign_type);
                    void negate();
                    void swap(Int&);
            //Constructors and destructor
                    Int(lli=0);
                    Int(const diglist_type&, sign_type);

                    Int(const Int&)             = default;
                    Int(Int&&)                  = default;
                    Int& operator=(const Int&)  = default;
                    Int& operator=(Int&&)       = default;
                    ~Int()                      = default;
                protected:
                        //Helper divide function to allow modulus and divide
                        //  operators take about the same time to calculate.
                    void divide(const Int& rhs, Int* div_req, Int* mod_req);
                        //Since AND, OR, and XOR implementations differ in
                        //  only the condition, use a helper to centralize
                        //  the implementation.
                    Int& bitwise_operation(Int,
                        const std::function<bool(bool,bool)>&);
                    Int logical_operation(const Int&, unsigned short)const;

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
}

INT_TEMPL_
void swap(
    Precision::General_Base::Abstract::INT_INST_&,
    Precision::General_Base::Abstract::INT_INST_&
);

#include "Impl/Precision_Int_Abstract_Base.inl"

#undef INT_TEMPL_
#undef INT_INST_

#endif  //Include guard