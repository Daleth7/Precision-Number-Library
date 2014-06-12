#ifndef HHHH____PRECISION_UNSIGNED_FRACT_IMPL_H
#define HHHH____PRECISION_UNSIGNED_FRACT_IMPL_H

#include "Precision_Fract_General_Base.h"

#include "Impl/Precision_Tags.h"
#include "Impl/Shared_Constants.h"

//Please refer to the documentation in Precision_Int_General_Base.h
//  for a list of conditions for each template parameter.

#define UFRACT_TEMPL_                   \
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

#define UFRACT_INST_    \
    UFract <CharT, _0, ByteType, Base, _symbols, Container, SignType>

namespace Precision{
    namespace General_Base{
        template <
            typename CharT, CharT const *const _0,
            typename ByteType = byte_type, ByteType Base = 10,
            CharT const *const _symbols = Constant::symbols,
            template <typename...> class Container = default_container_type,
            typename SignType = SignClass
        >
        class UFract : Tag::Fraction, Tag::Unsigned {
            public:
                using Signed_Fract  = Fract <CharT, _0, ByteType, Base,
                    _symbols, Container, SignType>;
                using Integer       = typename Signed_Fract::Integer;
                using Floating      = typename Signed_Fract::Floating;
                using str_type      = typename Signed_Fract::str_type;
                using sign_type     = typename Signed_Fract::sign_type;
                using image_type    = typename Signed_Fract::image_type;
                using diglist_type  = typename Signed_Fract::diglist_type;
                using digit_type    = typename Signed_Fract::digit_type;
                using ld            = typename Signed_Fract::ld;
                using lli           = typename Signed_Fract::lli;
                using size_type     = typename Signed_Fract::size_type;
        //Arithmetic operators
                UFract& operator+=(const UFract& s)
                    {return m_base += s.m_base, *this;}

                UFract& operator-=(const UFract& s){
                    m_base -= s.m_base;
                    if(m_base.negative())
                        m_base = 0;
                    return *this;
                }

                UFract& operator*=(const UFract& s)
                    {return m_base *= s.m_base, *this;}

                UFract& operator/=(const UFract& s)
                    {return m_base /= s.m_base, *this;}

                UFract& operator%=(const UFract& s)
                    {return m_base %= s.m_base, *this;}

                UFract& operator--()
                    {return --m_base, *this;}

                UFract operator--(int)
                    {return m_base--;}

                UFract& operator++()
                    {return ++m_base, *this;}

                UFract operator++(int)
                    {return m_base++;}

        //Overloaded operators with new meanings
                    //Invert the fraction
                UFract operator~()const
                    {return ~m_base;}

                    //Raise the fraction to the power of
                UFract& operator^=(const UFract& e)
                    {return m_base ^= e.m_base, *this;}

        //Read-only functions
                sign_type sign()const
                    {return 1;}

                bool even()const
                    {return m_base.even();}

                bool odd()const
                    {return m_base.odd();}

                bool positive()const
                    {return true;}

                bool negative()const
                    {return false;}

                Integer numerator()const
                    {return m_base.numerator();}

                Integer denominator()const
                    {return m_base.denominator();}

                str_type str()const
                    {return m_base.str();}

                str_type mixed()const
                    {return m_base.mixed();}

            //Set the precision through parameter
                const UFract& magnitude()const
                    {return *this;}

                size_type precision()const
                    {return m_base.precision();}

                short compare(const UFract& s)const
                    {return m_base.compare(s.m_base);}

            //Following two pairs are merely different names for the same thing
                Integer whole()const
                    {return m_base.whole();}

                Floating decimal()const
                    {return m_base.decimal();}

                Integer integer()const
                    {return m_base.integer();}

                Floating floating_point()const
                    {return this->decimal();}

                Integer gcd(const UFract& s)const
                    {return m_base.gcd(s.m_base);}

                UFract inverse()const
                    {return m_base.inverse();}

                UFract remainder(const UFract& s)const
                    {return m_base.remainder(s.m_base);}

                bool is_integer()const
                    {return m_base.is_integer();}

                const Signed_Fract& get_signed()const
                    {return m_base;}

                Signed_Fract operator-()const
                    {return -m_base;}

                static constexpr digit_type base()
                    {return Signed_Fract::base();}

                static constexpr image_type const* digit0()
                    {return Signed_Fract::digit0();}

        //Other modifiers
                void precision(size_type p)
                    {m_base.precision(p);}

                void numerator(const Integer& n)
                    {m_base.numerator(n); m_base.sign(1);}

                void denominator(const Integer& d)
                    {m_base.denominator(d); m_base.sign(1);}

                UFract& invert()
                    {return m_base.invert(), *this;}

                void sign(sign_type){}

                void swap(UFract& s)
                    {m_base.swap(s.m_base);}

                void shift(lli e)
                    {m_base.shift(e);}

                void shift_left(size_type e)
                    {m_base.shift_left(e);}

                void shift_right(size_type e)
                    {m_base.shift_right(e);}

                UFract& exponentiate(const Integer& e)
                    {return m_base.exponentiate(e), *this;}

                UFract& exponentiate(const UFract& s)
                    {return m_base.exponentiate(s.m_base), *this;}

                UFract& exponentiate(const Signed_Fract& s)
                    {return m_base.exponentiate(s), *this;}

        //Overload cast operators
                explicit operator Signed_Fract() const
                    {return m_base;}

                explicit operator Integer() const
                    {return this->integer();}

                explicit operator Floating() const
                    {return this->decimal();}

        //Constructors and destructor
                UFract(ld d = 0.0, size_type p = k_default_prec)
                    : m_base(d, p)
                {m_base.sign(1);}

                UFract(str_type i, size_type p = k_default_prec)
                    : m_base(i, p)
                {m_base.sign(1);}

                UFract(const Integer& i, size_type p = k_default_prec)
                    : m_base(i.magnitude(), p)
                {}

                UFract(const Floating& f)
                    : m_base(f.magnitude())
                {}

                explicit UFract(
                    const Integer& n,
                    const Integer& d,
                    size_type p = k_default_prec
                )
                    : m_base(n.magnitude(), d.magnitude(), p)
                {}

                UFract(const Signed_Fract& newbase)
                    : m_base(newbase.magnitude())
                {}

                UFract(Signed_Fract&& newbase)
                    : m_base(newbase.magnitude())
                {}

                UFract(const UFract&)               = default;
                UFract(UFract&&)                    = default;
                UFract& operator=(const UFract&)    = default;
                UFract& operator=(UFract&&)         = default;
                ~UFract()                           = default;
            private:
                Signed_Fract m_base;
        };

        UFRACT_TEMPL_
        UFRACT_INST_ operator+(UFRACT_INST_ f, const UFRACT_INST_& s)
            {return f += s;}

        UFRACT_TEMPL_
        UFRACT_INST_ operator-(UFRACT_INST_ f, const UFRACT_INST_& s)
            {return f -= s;}

        UFRACT_TEMPL_
        UFRACT_INST_ operator*(UFRACT_INST_ f, const UFRACT_INST_& s)
            {return f *= s;}

        UFRACT_TEMPL_
        UFRACT_INST_ operator/(UFRACT_INST_ f, const UFRACT_INST_& s)
            {return f /= s;}

        UFRACT_TEMPL_
        UFRACT_INST_ operator%(UFRACT_INST_ f, const UFRACT_INST_& s)
            {return f %= s;}

        UFRACT_TEMPL_
        UFRACT_INST_ operator^(UFRACT_INST_ f, const UFRACT_INST_& s)
            {return f ^= s;}

        UFRACT_TEMPL_
        bool operator==(const UFRACT_INST_& f, const UFRACT_INST_& s)
            {return f.compare(s) == 0;}

        UFRACT_TEMPL_
        bool operator!=(const UFRACT_INST_& f, const UFRACT_INST_& s)
            {return f.compare(s) != 0;}

        UFRACT_TEMPL_
        bool operator>=(const UFRACT_INST_& f, const UFRACT_INST_& s)
            {return f.compare(s) >= 0;}

        UFRACT_TEMPL_
        bool operator<=(const UFRACT_INST_& f, const UFRACT_INST_& s)
            {return f.compare(s) <= 0;}

        UFRACT_TEMPL_
        bool operator>(const UFRACT_INST_& f, const UFRACT_INST_& s)
            {return f.compare(s) > 0;}

        UFRACT_TEMPL_
        bool operator<(const UFRACT_INST_& f, const UFRACT_INST_& s)
            {return f.compare(s) < 0;}

        UFRACT_TEMPL_
        bool operator!(const UFRACT_INST_& f)
            {return f.compare(UFRACT_INST_(0)) == 0;}
    }
}

UFRACT_TEMPL_
void swap(
    Precision::General_Base::UFRACT_INST_& a,
    Precision::General_Base::UFRACT_INST_& b
){a.swap(b);}

#undef UFRACT_TEMPL_
#undef UFRACT_INST_
#undef INST_PARAMS_

#endif  //Include guard