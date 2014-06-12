#ifndef PRECISION_COMPLEX_NUMBER_DEFINITION___H___
#define PRECISION_COMPLEX_NUMBER_DEFINITION___H___

#include "Impl/Precision_Tags.h"
#include "Impl/Shared_Constants.h"

//Please refer to the documentation in Precision_Int_General_Base.h
//  for a list of conditions for each template parameter.

//This class is used a template for Precision_Complex_General_Base.h
//  since no matter the number type, e.g. integral or fraction, the
//  implementation shall be the same.

#define COMP_TEMPL_                     \
    template <                          \
        typename CharT,                 \
        CharT const *const _0,          \
        typename ByteType,              \
        ByteType Base,                  \
        CharT const *const _symbols,    \
        template <typename...>          \
            class Container,            \
        typename SignType,              \
        typename Scalar_type            \
    >

#define COMP_INST_  \
    Number <CharT, _0, ByteType, Base, _symbols, Container, SignType, Scalar_Type>

namespace Precision{
    namespace General_Base{
        namespace Complex{
            template <
                typename CharT, CharT const *const _0,
                typename ByteType, ByteType Base,
                CharT const *const _symbols,
                template <typename...> class Container,
                typename SignType, typename ScalarType
            >
            class Number : Tag::Complex, Tag::Static{
                public:
            //Type aliases
                    using scalar_type   = ScalarType;
                    using str_type      = typename scalar_type::str_type;
                    using sign_type     = typename scalar_type::sign_type;
                    using image_type    = typename scalar_type::image_type;
                    using diglist_type  = typename scalar_type::diglist_type;
                    using digit_type    = typename scalar_type::digit_type;
                    using lli           = typename scalar_type::lli;
                    using ld            = typename scalar_type::ld;
                    using size_type     = typename scalar_type::size_type;
            //Arithmetic operators
                    Number& operator+=(const Number&);
                    Number& operator-=(const Number&);
                    Number& operator*=(const Number&);
                    Number& operator/=(const Number&);

                    Number operator-()const;
            //Read-only functions
                        //True ~ Real, False ~ Imaginary
                    sign_type sign(bool)const;
                    const scalar_type& real()const;
                    const scalar_type& imaginary()const;
                    scalar_type magnitude()const;
                    scalar_type phase()const;
                    short compare(const Number&)const;

                    static constexpr digit_type base();
                    static constexpr digit_type digit0();
            //Modifers
                        //True ~ Real, False ~ Imaginary
                    void sign(sign_type, bool);
                    void real(const scalar_type&);
                    void imaginary(const scalar_type&);
                    void negate();
                    void swap(Number&);

            //Constructors and destructor
                    Number(
                        const scalar_type& new_real = scalar_type(0),
                        const scalar_type& new_imag = scalar_type(0)
                    );
                    Number(
                        scalar_type&& new_real,
                        scalar_type&& new_imag
                    );
                    Number(const str_type&);
                    Number(const Number&)               = default;
                    Number(Number&&)                    = default;
                    Number& operator=(const Number&)    = default;
                    Number& operator=(Number&&)         = default;
                    ~Number()                           = default;

                private:
                    scalar_type m_real, m_imag;
            };
        }
    }
}

#include "Impl/Precision_Complex_Number_General_Base.inl"

#undef COMP_INST_
#undef COMP_TEMPL_

#endif