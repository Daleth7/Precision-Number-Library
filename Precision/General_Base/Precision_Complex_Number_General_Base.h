#ifndef PRECISION_COMPLEX_NUMBER_DEFINITION___H___
#define PRECISION_COMPLEX_NUMBER_DEFINITION___H___

#include "Precision_Tags.h"
#include "Shared_Constants.h"

//Please refer to the documentation in Precision_Int_General_Base.h
//  for a list of conditions for each template parameter.
//Specifically for this complex class, there is an additional parameter
//  used to represent the imaginary character as in "A+Bi".

#define COMP_TEMPL_             \
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
        CharT _imagi,           \
        template <typename...>  \
            class Container,    \
        typename SignType       \
    >

#define INST_PARAMS_                \
        CharT, _0, ByteType, Base,  \
        _plus, _neg, _point,        \
        _exp, _space, _imagi        \
        Container, SignType

#define COMP_INST_ Number <INST_PARAMS_>

namespace Precision{
    namespace General_Base{
        namespace Complex{
            template <
                typename CharT, CharT const *const _0,
                typename ByteType, ByteType Base,
                CharT _plus, CharT _neg, CharT _point,
                CharT _exp, CharT _space, CharT _imagi,
                template <typename...> class Container,
                typename SignType, typename ScalarType
            >
            class Number : Tag::Complex{
                public:
            //Type aliases
                    using scalar_type   = ScalarType;
                    using str_type      = typename scalar_type::str_type;
                    using sign_type     = typename scalar_type::sign_type;
                    using image_type    = typename scalar_type::image_type;
                    using diglist_type  = typename scalar_type::diglist_type;
                    using digit_type    = typename scalar_type::digit_type;
                    using digit_10_type = typename scalar_type::digit_10_type;
                    using lli           = typename scalar_type::lli;
                    using ld            = typename scalar_type::ld;
                    using size_type     = typename scalar_type::size_type;
            //Arithmetic operators
                    COMP_INST_& operator+=(const COMP_INST_&);
                    COMP_INST_& operator-=(const COMP_INST_&);
                    COMP_INST_& operator*=(const COMP_INST_&);
                    COMP_INST_& operator/=(const COMP_INST_&);

                    COMP_INST_ operator-()const;
            //Read-only functions
                        //True ~ Real, False ~ Imaginary
                    sign_type sign(bool)const;
                    const scalar_type& real()const;
                    const scalar_type& imaginary()const;
                    scalar_type magnitude()const;
                    scalar_type phase()const;
                    short compare(const COMP_INST_&)const;

                    static constexpr digit_10_type base();
                    static constexpr digit_type digit0();
            //Modifers
                        //True ~ Real, False ~ Imaginary
                    void sign(sign_type, bool);
                    void real(const scalar_type&);
                    void imaginary(const scalar_type&);
                    void negate();
                    void swap(COMP_INST_&);

            //Constructors and destructor
                    Complex(
                        const scalar_type& new_real = scalar_type(0),
                        const scalar_type& new_imag = scalar_type(0)
                    );
                    Complex(
                        scalar_type&& new_real,
                        scalar_type&& new_imag
                    );
                    Complex(const str_type&);
                    Complex(const COMP_INST_&)                  = default;
                    Complex(COMP_INST_&&)                       = default;
                    COMP_INST_& operator=(const COMP_INST_&)    = default;
                    COMP_INST_& operator=(COMP_INST_&&)         = default;
                    ~Complex()                                  = default;

                private:
                    scalar_type m_real, m_imag;
            };
        }
    }
}

#include "Impl/Precision_Complex_Number_General_Base.inl"

#undef INST_PARAMS_
#undef COMP_INST_
#undef COMP_TEMPL_

#endif