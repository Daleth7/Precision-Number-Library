#ifndef HHHH____PRECISION_UNSIGNED_FLOAT_IMPL_GENERAL_BASE_H
#define HHHH____PRECISION_UNSIGNED_FLOAT_IMPL_GENERAL_BASE_H

#include "Precision_Float_General_Base.h"
#include "Precision_UInt_General_Base.h"

#include "Impl/Precision_Tags.h"
#include "Impl/Shared_Constants.h"

//Please refer to the documentation in Precision_Int_General_Base.h
//  for a list of conditions for each template parameter.

#define UFLOAT_TEMPL_                   \
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

#define UFLOAT_INST_ UFloat <INST_PARAMS_>

#include <utility>

namespace Precision{
    namespace General_Base{
        template <
            typename CharT, CharT const *const _0,
            typename ByteType = byte_type, ByteType Base = 10,
            CharT const *const _symbols = Constant::symbols,
            template <typename...> class Container = default_container_type,
            typename SignType = SignClass
        >
        class UFloat : Tag::Floating_Point, Tag::Unsigned {
            public:
        //Type aliases
                using UInteger      = UInt<INST_PARAMS_>;
                using Integer       = Int<INST_PARAMS_>;
                using Signed_Float  = Float<INST_PARAMS_>;
                using str_type      = typename Signed_Float::str_type;
                using ld            = typename Signed_Float::ld;
                using lli           = typename Signed_Float::lli;
                using image_type    = typename Signed_Float::image_type;
                using diglist_type  = typename Signed_Float::diglist_type;
                using digit_type    = typename Signed_Float::digit_type;
                using size_type     = typename Signed_Float::size_type;
                using sign_type     = typename Signed_Float::sign_type;
        //Arithmetic operators
                UFloat& operator+=(const UFloat& rhs)
                    {return m_base += rhs.m_base, *this;}

                UFloat& operator-=(const UFloat& rhs){
                    m_base -= rhs.m_base;
                    if(m_base.negative())
                        m_base = 0;
                    return *this;
                }

                UFloat& operator*=(const UFloat& rhs)
                    {return m_base *= rhs.m_base, *this;}

                UFloat& operator/=(const UFloat& rhs)
                    {return m_base /= rhs.m_base, *this;}

                UFloat& operator%=(const UFloat& rhs)
                    {return m_base %= rhs.m_base, *this;}

                UFloat& operator--()
                    {return (*this -= 1);}

                UFloat operator--(int)
                    {return (*this -= 1) + 1;}

                UFloat& operator++()
                    {return ++m_base, *this;}

                UFloat operator++(int)
                    {return UFloat(m_base++);}

                    //Returns the power of, not XOR
                UFloat& operator^=(const Integer& rhs)
                    {return m_base ^= rhs, *this;}

                UFloat& operator^=(const UFloat& rhs)
                    {return m_base ^= rhs.m_base, *this;}

        //Read-only functions
                sign_type sign()const
                    {return 1;}

                str_type str(size_type inPrec = 0, bool inShowFull = false)const
                    {return m_base.str(inPrec, inShowFull);}

                bool even()const
                    {return m_base.even();}

                bool odd()const
                    {return m_base.odd();}

                bool positive()const
                    {return true;}

                bool negative()const
                    {return false;}

            //Set the precision through parameter
                str_type sci_note(
                    size_type inPrec = k_display_prec,
                    bool inShowFull = false
                )const{return m_base.sci_note(inPrec, inShowFull);}

                str_type sci_note_w_spaces(
                    size_type inPrec = k_display_prec,
                    bool inShowFull = false
                )const{return m_base.sci_note_w_spaces(inPrec, inShowFull);}

                size_type count_digits()const
                    {return m_base.count_digits();}

                size_type count_left_digits()const
                    {return m_base.count_left_digits();}

                size_type count_right_digits()const
                    {return m_base.count_right_digits();}

                const UFloat& magnitude()const
                    {return *this;}

                size_type precision()const
                    {return m_base.precision();}

                short compare(const UFloat& s)const
                    {return m_base.compare(s.m_base);}

                Integer integer()const
                    {return m_base.integer();}

                bool show_full()const
                    {return m_base.show_full();}

                UFloat remainder(const UFloat& s)const
                    {return UFloat(m_base.remainder(s.m_base));}

                const Signed_Float& get_signed()const
                    {return m_base;}
                
                Signed_Float operator-()const
                    {return -m_base;}

                bool is_integer()const
                    {return m_base.is_integer();}

                UFloat inverse()const
                    {return UFloat(m_base.inverse());}

                static constexpr digit_type base()
                    {return Signed_Float::base();}

                static constexpr image_type const* digit0()
                    {return Signed_Float::digit0();}

        //Other modifers
                void sign(sign_type){}

                bool show_full(bool inFlag)
                    {return m_base.show_full(inFlag);}

                    //Multiplies integer by a power of ten
                void shift(lli tens_exp)
                    {m_base.shift(tens_exp);}

                void shift_left(size_type e)
                    {m_base.shift_left(e);}

                void shift_right(size_type e)
                    {m_base.shift_right(e);}

                UFloat& invert()
                    {return m_base.invert(), *this;}

                UFloat& exponentiate(const Integer& s)
                    {return m_base.exponentiate(s), *this;}

                UFloat& exponentiate(const UFloat& s)
                    {return m_base.exponentiate(s.m_base), *this;}

                UFloat& exponentiate(const Signed_Float& s)
                    {return m_base.exponentiate(s), *this;}

                void swap(UFloat& s)
                    {m_base.swap(s.m_base);}

        //Overload cast operators
                explicit operator Integer() const
                    {return m_base.integer();}

                explicit operator UInteger() const
                    {return UInteger(m_base.integer());}

                explicit operator Signed_Float() const
                    {return m_base;}

        //Constructors and destructor
                UFloat(
                    ld inFP = 0.0,
                    size_type inPrec = k_default_prec
                )
                    : m_base(inFP, inPrec)
                {m_base.sign(1);}

                UFloat(
                    const str_type& inImage,
                    size_type inPrec = k_default_prec
                )
                    : m_base(inImage, inPrec)
                {m_base.sign(1);}

                explicit UFloat(
                    const Integer& inInt,
                    size_type inPrec = k_default_prec
                )
                    : m_base(inInt.magnitude(), inPrec)
                {}

                explicit UFloat(
                    Integer&& inInt,
                    size_type inPrec = k_default_prec
                )
                    : m_base(inInt.magnitude(), inPrec)
                {}

                explicit UFloat(
                    const UInteger& inInt,
                    size_type inPrec = k_default_prec
                )
                    : m_base(inInt, inPrec)
                {}

                explicit UFloat(
                    UInteger&& inInt,
                    size_type inPrec = k_default_prec
                )
                    : m_base(std::move(inInt), inPrec)
                {}

                explicit UFloat(const Signed_Float& inFP)
                    : m_base(inFP.magnitude())
                {}

                explicit UFloat(Signed_Float&& inFP)
                    : m_base(inFP.magnitude())
                {}

                UFloat(const UFloat&)               = default;
                UFloat(UFloat&&)                    = default;
                UFloat& operator=(const UFloat&)    = default;
                UFloat& operator=(UFloat&&)         = default;
                ~UFloat()                           = default;
            private:
                Signed_Float   m_base;
        };

        UFLOAT_TEMPL_
        inline UFLOAT_INST_ operator+(UFLOAT_INST_ lhs, const UFLOAT_INST_& rhs)
            {return lhs += rhs;}

        UFLOAT_TEMPL_
        inline UFLOAT_INST_ operator-(UFLOAT_INST_ lhs, const UFLOAT_INST_& rhs)
            {return lhs -= rhs;}

        UFLOAT_TEMPL_
        inline UFLOAT_INST_ operator*(UFLOAT_INST_ lhs, const UFLOAT_INST_& rhs)
            {return lhs *= rhs;}

        UFLOAT_TEMPL_
        inline UFLOAT_INST_ operator/(UFLOAT_INST_ lhs, const UFLOAT_INST_& rhs)
            {return lhs /= rhs;}

        UFLOAT_TEMPL_
        inline UFLOAT_INST_ operator%(UFLOAT_INST_ lhs, const UFLOAT_INST_& rhs)
            {return lhs %= rhs;}

        UFLOAT_TEMPL_
        inline UFLOAT_INST_ operator^(
            UFLOAT_INST_ lhs,
            const typename UFLOAT_INST_::Integer& rhs
        )   {return lhs ^= rhs;}

        UFLOAT_TEMPL_
        inline UFLOAT_INST_ operator^(UFLOAT_INST_ lhs, const UFLOAT_INST_& rhs)
            {return lhs ^= rhs;}

        UFLOAT_TEMPL_
        inline bool operator==(const UFLOAT_INST_& lhs, const UFLOAT_INST_& rhs)
            {return lhs.compare(rhs) == 0;}

        UFLOAT_TEMPL_
        inline bool operator!=(const UFLOAT_INST_& lhs, const UFLOAT_INST_& rhs)
            {return lhs.compare(rhs) != 0;}

        UFLOAT_TEMPL_
        inline bool operator>=(const UFLOAT_INST_& lhs, const UFLOAT_INST_& rhs)
            {return lhs.compare(rhs) >= 0;}

        UFLOAT_TEMPL_
        inline bool operator<=(const UFLOAT_INST_& lhs, const UFLOAT_INST_& rhs)
            {return lhs.compare(rhs) <= 0;}

        UFLOAT_TEMPL_
        inline bool operator>(const UFLOAT_INST_& lhs, const UFLOAT_INST_& rhs)
            {return lhs.compare(rhs) >= 0;}

        UFLOAT_TEMPL_
        inline bool operator<(const UFLOAT_INST_& lhs, const UFLOAT_INST_& rhs)
            {return lhs.compare(rhs) <= 0;}

        UFLOAT_TEMPL_
        inline bool operator!(const UFLOAT_INST_& testee)
            {return testee == 0;}
    }
}

UFLOAT_TEMPL_
inline void swap(
    Precision::General_Base::UFLOAT_INST_& a,
    Precision::General_Base::UFLOAT_INST_& b
){a.swap(b);}

#undef UFLOAT_TEMPL_
#undef INST_PARAMS_
#undef UFLOAT_INST_

#endif  //Include guard