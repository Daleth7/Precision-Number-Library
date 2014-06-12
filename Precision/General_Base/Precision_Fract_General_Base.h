#ifndef HH___PRECISION_FRACT_IMPL_H
#define HH___PRECISION_FRACT_IMPL_H

#include "Precision_Int_General_Base.h"
#include "Precision_Float_General_Base.h"

#include "Impl/Precision_Tags.h"
#include "Impl/Shared_Constants.h"

//Please refer to the documentation in Precision_Int_General_Base.h
//  for a list of conditions for each template parameter.

#define FRACT_TEMPL_                    \
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

#define FRACT_INST_ Fract <INST_PARAMS_>

namespace Precision{
    namespace General_Base{
        template <
            typename CharT, CharT const *const _0,
            typename ByteType = byte_type, ByteType Base = 10,
            CharT const *const _symbols = Constant::symbols,
            template <typename...> class Container = default_container_type,
            typename SignType = SignClass
        >
        class Fract : Tag::Fraction, Tag::Signed, Tag::Static {
            public:
                using Integer       = Int<INST_PARAMS_>;
                using Floating      = Float<INST_PARAMS_>;
                using str_type      = typename Integer::str_type;
                using sign_type     = typename Integer::sign_type;
                using image_type    = typename Integer::image_type;
                using diglist_type  = typename Integer::diglist_type;
                using digit_type    = typename Integer::digit_type;
                using ld            = typename Floating::ld;
                using lli           = typename Integer::lli;
                using size_type     = typename Integer::size_type;
        //Arithmetic operators
                Fract& operator+=(const Fract&);
                Fract& operator-=(const Fract&);
                Fract& operator*=(const Fract&);
                Fract& operator/=(const Fract&);
                Fract& operator%=(const Fract&);
                Fract& operator--();
                Fract operator--(int);
                Fract& operator++();
                Fract operator++(int);

                Fract operator-()const;

        //Overloaded operators with new meanings
                    //Invert the fraction
                Fract operator~()const;
                    //Raise the fraction to the power of
                Fract& operator^=(const Fract&);
        //Read-only functions
                sign_type sign()const;
                bool even()const;
                bool odd()const;
                bool positive()const;
                bool negative()const;
                Integer numerator()const;
                Integer denominator()const;
                str_type str()const;
                str_type mixed()const;
            //Set the precision through parameter
                Fract magnitude()const;
                size_type precision()const;
                short compare(const Fract&)const;
            //Following two pairs are merely different names for the same thing
                Integer whole()const;
                Floating decimal()const;
                Integer integer()const;
                Floating floating_point()const;
                Integer gcd(const Fract&)const;
                Fract inverse()const;

                Fract remainder(const Fract&)const;
                bool is_integer()const;
                image_type digit(size_type)const;
                digit_type digit_10(size_type)const;

                static constexpr digit_type base();
                static constexpr image_type const * digit0();
        //Other modifiers
                void precision(size_type);
                void numerator(const Integer&);
                void denominator(const Integer&);
                Fract& invert();
                void sign(sign_type);
                void negate();
                void swap(Fract& s);
                void shift(lli);
                void shift_left(size_type);
                void shift_right(size_type);
                Fract& exponentiate(const Integer&);
                Fract& exponentiate(const Fract&);

        //Overload cast operators
                explicit operator Integer() const;
                explicit operator Floating() const;

        //Constructors and destructor
                Fract(ld = 0.0, size_type = k_default_prec);
                Fract(const str_type&, size_type = k_default_prec);
                Fract(const Integer&, size_type = k_default_prec);
                Fract(const Floating&);
                explicit Fract(
                    const Integer&,
                    const Integer&,
                    size_type = k_default_prec
                );

                Fract(const Fract&)             = default;
                Fract(Fract&&)                  = default;
                Fract& operator=(const Fract&)  = default;
                Fract& operator=(Fract&&)       = default;
                ~Fract()                        = default;
            protected:
        //Helpers
                void Simplify();
                void Check_Pattern(const str_type&, const Floating&);
                Integer GCD_Helper(const Integer&, const Integer&)const;
                Integer GCF_Helper(const Integer&, const Integer&)const;
            private:
                Integer     m_numer, m_denom;
                size_type   m_precision;
                static constexpr size_type k_default_prec = 100;
        };

        FRACT_TEMPL_
        FRACT_INST_ operator+(FRACT_INST_, const FRACT_INST_&);
        FRACT_TEMPL_
        FRACT_INST_ operator-(FRACT_INST_, const FRACT_INST_&);
        FRACT_TEMPL_
        FRACT_INST_ operator*(FRACT_INST_, const FRACT_INST_&);
        FRACT_TEMPL_
        FRACT_INST_ operator/(FRACT_INST_, const FRACT_INST_&);
        FRACT_TEMPL_
        FRACT_INST_ operator%(FRACT_INST_, const FRACT_INST_&);

        FRACT_TEMPL_
        FRACT_INST_ operator^(FRACT_INST_, const FRACT_INST_&);

        FRACT_TEMPL_
        bool operator==(const FRACT_INST_&, const FRACT_INST_&);
        FRACT_TEMPL_
        bool operator!=(const FRACT_INST_&, const FRACT_INST_&);
        FRACT_TEMPL_
        bool operator>=(const FRACT_INST_&, const FRACT_INST_&);
        FRACT_TEMPL_
        bool operator<=(const FRACT_INST_&, const FRACT_INST_&);
        FRACT_TEMPL_
        bool operator>(const FRACT_INST_&, const FRACT_INST_&);
        FRACT_TEMPL_
        bool operator<(const FRACT_INST_&, const FRACT_INST_&);
        FRACT_TEMPL_
        bool operator!(const FRACT_INST_&);
    }
}

FRACT_TEMPL_
void swap(
    Precision::General_Base::FRACT_INST_&,
    Precision::General_Base::FRACT_INST_&
);

#include "Impl/Precision_Fract_General_Base.inl"

#undef FRACT_TEMPL_
#undef FRACT_INST_
#undef INST_PARAMS_

#endif  //Include guard