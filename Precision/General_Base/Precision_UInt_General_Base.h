#ifndef HHHH____PRECISION_UNSIGNED_INT_IMPL_GENERAL_BASE_H
#define HHHH____PRECISION_UNSIGNED_INT_IMPL_GENERAL_BASE_H

#include "Precision_Int_General_Base.h"

#include "Impl/Precision_Tags.h"
#include "Impl/Shared_Constants.h"

#include <sstream>
#include <utility>

//Please refer to the documentation in Precision_Int_General_Base.h
//  for a list of conditions for each template parameter.

#define UINT_TEMPL_                     \
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

#define INST_PARAMS_    \
        CharT, _0, ByteType, Base, _symbols, Container, SignType

#define UINT_INST_ UInt <INST_PARAMS_>

namespace Precision{
    namespace General_Base{
        template <
            typename CharT, CharT const *const _0,
            typename ByteType = byte_type, ByteType Base = 10,
            CharT const *const _symbols = Constant::symbols,
            template <typename...> class Container = default_container_type,
            typename SignType = SignClass
        >
        class UInt : Tag::Integral, Tag::Unsigned {
            public:
        //Type aliases
                using Signed_Int    = Int<INST_PARAMS_>;
                using str_type      = typename Signed_Int::str_type;
                using ulli          = unsigned long long int;
                using ld            = typename Signed_Int::ld;
                using lli           = typename Signed_Int::lli;
                using image_type    = typename Signed_Int::image_type;
                using diglist_type  = typename Signed_Int::diglist_type;
                using digit_type    = typename Signed_Int::digit_type;
                using sign_type     = typename Signed_Int::sign_type;
                using size_type     = typename Signed_Int::size_type;
        //Arithmetic operators
                UInt& operator+=(const UInt& rhs)
                    {return m_base += rhs.m_base, *this;}

                UInt& operator-=(const UInt& rhs){
                    m_base -= rhs.m_base;
                    if(m_base.negative())
                        m_base = 0;
                    return *this;
                }

                UInt& operator*=(const UInt& rhs)
                    {return m_base *= rhs.m_base, *this;}

                UInt& operator/=(const UInt& rhs)
                    {return m_base /= rhs.m_base, *this;}

                UInt& operator%=(const UInt& rhs)
                    {return m_base %= rhs.m_base, *this;}

                UInt& operator--()
                    {return (*this -= 1);}

                UInt operator--(int)
                    {return (*this -= 1) + 1;}

                UInt& operator++()
                    {return ++m_base, *this;}

                UInt operator++(int)
                    {return m_base++;}

        //Bitwise operators
                UInt& operator&=(const UInt& rhs)
                    {return m_base &= rhs.m_base, *this;}

                UInt& operator|=(const UInt& rhs)
                    {return m_base |= rhs.m_base, *this;}

                UInt& operator^=(const UInt& rhs)
                    {return m_base ^= rhs.m_base, *this;}

                UInt& operator<<=(const UInt& rhs)
                    {return m_base <<= rhs.m_base, *this;}

                UInt& operator>>=(const UInt& rhs)
                    {return m_base >>= rhs.m_base, *this;}

        //Logical Operators
                UInt logical_and(const UInt& s)const
                    {return UInt(m_base.logical_and(s.m_base));}

                UInt logical_or(const UInt& s)const
                    {return UInt(m_base.logical_or(s.m_base));}

                UInt logical_xor(const UInt& s)const
                    {return UInt(m_base.logical_xor(s.m_base));}

                Signed_Int logical_inversion()const
                    {return m_base.logical_inversion();}

                UInt logical_shift(lli e)const
                    {return UInt(m_base.logical_shift(e));}

                UInt logical_shift_left(size_type e)const
                    {return UInt(m_base.logical_shift_left(e));}

                UInt logical_shift_right(size_type e)const
                    {return UInt(m_base.logical_shift_right(e));}

        //Read-only functions
                sign_type sign()const
                    {return 1;}

                str_type str()const
                    {return m_base.str();}

                bool even()const
                    {return m_base.even();}

                bool odd()const
                    {return m_base.odd();}

                bool positive()const
                    {return true;}

                bool negative()const
                    {return false;}

            //Set the precision through parameter
                str_type sci_note(size_type inPrec = k_display_prec)const
                    {return m_base.sci_note(inPrec);}

                str_type
                    sci_note_w_spaces(size_type inPrec = k_display_prec)const
                {return m_base.sci_note_w_spaces(inPrec);}

                size_type count_digits()const
                    {return m_base.count_digits();}

                short compare(const UInt& s)const
                    {return m_base.compare(s.m_base);}

                const UInt& magnitude()const
                    {return *this;}

                const Signed_Int& get_signed()const
                    {return m_base;}

                Signed_Int operator-()const
                    {return -m_base;}

                    //Does not work for ~0
                Signed_Int operator~()const
                    {return Signed_Int(~m_base);}

                image_type digit(size_type index)const
                    {return m_base.digit(index);}

                digit_type digit_10(size_type index)const
                    {return m_base.digit_10(index);}

                diglist_type digit_list()const
                    {return m_base.digit_list();}

                static constexpr digit_type base()
                    {return Signed_Int::base();}

                static constexpr image_type const* digit0()
                    {return Signed_Int::digit0();}

        //Other modifiers
                void sign(sign_type){}
                    //Multiplies integer by a power of Base
                void shift(lli tens_exp)
                    {m_base.shift(tens_exp);}

                void shift_left(size_type e)
                    {m_base.shift_left(e);}

                void shift_right(size_type e)
                    {m_base.shift_right(e);}

                void swap(UInt& s)
                    {m_base.swap(s.m_base);}

        //Conversion operators
                explicit operator Signed_Int()
                    {return m_base;}

        //Constructors and destructor
                UInt(ulli inInt = 0)
                    : m_base(inInt)
                {}

                UInt(const str_type& inImage)
                    : m_base(inImage)
                {m_base.sign(1);}

                UInt(const diglist_type& inImage, sign_type = 1)
                    : m_base(inImage, 1)
                {}

                UInt(const Signed_Int& inInt)
                    : m_base(inInt)
                {m_base.sign(1);}

                UInt(Signed_Int&& inInt)
                    : m_base(std::move(inInt))
                {m_base.sign(1);}

                UInt(const UInt&)               = default;
                UInt(UInt&&)                    = default;
                UInt& operator=(const UInt&)    = default;
                UInt& operator=(UInt&&)         = default;
                ~UInt()                         = default;
            private:
                Signed_Int   m_base;
        };

        UINT_TEMPL_
        inline UINT_INST_ operator+(UINT_INST_ lhs, const UINT_INST_& rhs)
            {return lhs += rhs;}

        UINT_TEMPL_
        inline UINT_INST_ operator-(UINT_INST_ lhs, const UINT_INST_& rhs)
            {return lhs -= rhs;}

        UINT_TEMPL_
        inline UINT_INST_ operator*(UINT_INST_ lhs, const UINT_INST_& rhs)
            {return lhs *= rhs;}

        UINT_TEMPL_
        inline UINT_INST_ operator/(UINT_INST_ lhs, const UINT_INST_& rhs)
            {return lhs /= rhs;}

        UINT_TEMPL_
        inline UINT_INST_ operator%(UINT_INST_ lhs, const UINT_INST_& rhs)
            {return lhs %= rhs;}

        UINT_TEMPL_
        inline UINT_INST_ operator&(UINT_INST_ lhs, const UINT_INST_& rhs)
            {return lhs &= rhs;}

        UINT_TEMPL_
        inline UINT_INST_ operator|(UINT_INST_ lhs, const UINT_INST_& rhs)
            {return lhs |= rhs;}

        UINT_TEMPL_
        inline UINT_INST_ operator^(UINT_INST_ lhs, const UINT_INST_& rhs)
            {return lhs ^= rhs;}

        UINT_TEMPL_
        inline UINT_INST_ operator>>(UINT_INST_ lhs, const UINT_INST_& rhs)
            {return lhs >>= rhs;}

        UINT_TEMPL_
        inline UINT_INST_ operator<<(UINT_INST_ lhs, const UINT_INST_& rhs)
            {return lhs <<= rhs;}

        UINT_TEMPL_
        inline bool operator==(const UINT_INST_& lhs, const UINT_INST_& rhs)
            {return lhs.compare(rhs) == 0;}

        UINT_TEMPL_
        inline bool operator!=(const UINT_INST_& lhs, const UINT_INST_& rhs)
            {return lhs.compare(rhs) != 0;}

        UINT_TEMPL_
        inline bool operator>=(const UINT_INST_& lhs, const UINT_INST_& rhs)
            {return lhs.compare(rhs) >= 0;}

        UINT_TEMPL_
        inline bool operator<=(const UINT_INST_& lhs, const UINT_INST_& rhs)
            {return lhs.compare(rhs) <= 0;}

        UINT_TEMPL_
        inline bool operator>(const UINT_INST_& lhs, const UINT_INST_& rhs)
            {return lhs.compare(rhs) > 0;}

        UINT_TEMPL_
        inline bool operator<(const UINT_INST_& lhs, const UINT_INST_& rhs)
            {return lhs.compare(rhs) < 0;}

        UINT_TEMPL_
        inline bool operator!(const UINT_INST_& testee)
            {return testee == 0;}
    }
}

UINT_TEMPL_
inline void swap(
    Precision::General_Base::UINT_INST_& a,
    Precision::General_Base::UINT_INST_& b
){a.swap(b);}

#undef UINT_TEMPL_
#undef UINT_INST_
#undef INST_PARAMS_

#endif  //Include guard
